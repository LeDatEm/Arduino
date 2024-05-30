
#include <Arduino.h>
#include "Adafruit_SHTC3.h"
#include <Wire.h> 
#include "SSD1306Wire.h"
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <WiFiClientSecure.h>

// #include <WiFiManager.h>
// #include <EEPROM.h>

#define BUTTON_PIN 3
#define BUZZER_PIN 12

#define FIREBASE_HOST "swiftlet-farm-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "kZirda32QaVmLYuVKlTrvTXWM5uIuNyHazgzv15K"

#define WIFI_SSID "aaa"
#define WIFI_PASSWORD "80888088"



Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();

SSD1306Wire display(0x3c, SDA, SCL);

WiFiClientSecure client;

FirebaseData firebaseData;
FirebaseJson json;

String path = "/";
String GAS_ID = "AKfycbz0qHNwJf55mAqeb_o5MAyGUwu4gGxAEnvTptaGIljiSioCT5-UFr9yEQssh7mPXN9jBw";

byte done[] = {
  B00100000, B01000000,
  B10000000, B01000000,
  B00100000, B00010000,
  B00001000, B00000100
};
byte none[] = {
  B10000001, B01000010,
  B00100100, B00011000,
  B00011000, B00100100,
  B01000010, B10000001
};


float SHTC3_tprt;
float SHTC3_hmdt;

const char* host = "script.google.com";
const int httpsPort = 443;

const unsigned long interval_read = 3000;
const unsigned long interval_send_firebase = 10000;
const unsigned long interval_send_googlesheet = 60000;

unsigned long t1 = 0;
unsigned long t2 = 0;
unsigned long t3 = 0;
unsigned long led_buzzer_start_time = millis();
unsigned long led_buzzer_duration = 100;

unsigned short tickw;
unsigned short ticks;
unsigned short tickf;

uint8_t active_state = 0;
uint8_t led_buzzer_count = 0;

bool exitLoop = false;

struct Pixel {
  uint8_t x;
  uint8_t y;
};




/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void intro_logo(){
  Serial.println("[ \n\nWELLCOM TO DIEN TU SONG PHU\n ]");
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(64,0, "DIEN TU");
  display.setFont(ArialMT_Plain_24);
  display.drawString(64, 25, "SONG PHU");
  display.display();
  display.clear();
  delay(1000);
}

void SHTC3sensor_initialization(){
  unsigned long previousMillis = 0;
  const unsigned long interval = 250;

  while (!Serial){
    delay(10);
  }
  Serial.println("\\ SWIFTLET FARM XIN CHAO //\n");
  Serial.println("CONFIGUATION...");
  Serial.print("Connecting to SHTC3 sensor: ");

  while (! shtc3.begin()) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      Serial.println("[X] Couldn't find SHTC3");
      ticks++;
      intro_connecting_sensor();
      Serial.print(".");
    }
  }
  digitalWrite(LED_BUILTIN, 1);
  digitalWrite(BUZZER_PIN, 1);
  intro_successful_connection_sensor();
  delay(10);
  digitalWrite(BUZZER_PIN, 0);
  Serial.println("\n[√] Successfully connected to SHTC3 sensor");
  delay(1000);

}

void intro_connecting_sensor(){
  const char* connectingText[5] = {"1. SENSOR:", "1. SENSOR:", "1. SENSOR:.", "1. SENSOR:..", "1. SENSOR:..."};
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(64,0, "CONECTING TO");
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(1, 20, connectingText[ticks]);
  display.display();
  display.clear();

  if (ticks == 4){
    ticks = 0;
  }
}

void intro_successful_connection_sensor(){
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(64,0, "CONECTING TO");
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(1, 20, "1. SENSOR:");
  display.drawFastImage(80, 22,8, 8, done);
  display.display();
  display.clear();
}

void wifi_initialization(){
  unsigned long previousMillis = 0;
  const unsigned long interval = 250;
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("");
  Serial.print("Connecting to WIFI: ");

  while (WiFi.status() != WL_CONNECTED && !exitLoop) { //
    unsigned long currentMillis_connecting = millis();

    if (currentMillis_connecting - previousMillis >= interval) {
      previousMillis = currentMillis_connecting;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
      tickw++;
      intro_connecting_wifi();
      Serial.print(".");
    }

    setup_button_wifi();
    digitalWrite(BUZZER_PIN,0);
  }
  // if(active_state == 2){
  //   change_wifi();
  // }

  // if (WiFi.status() == WL_CONNECTED){
  //   active_state = 2;
  // }
  
  digitalWrite(LED_BUILTIN, 1);
  Serial.println();
  Serial.println();
  intro_successful_connection_wifi();
  delay(1000);
}

void intro_connecting_wifi() {
  const char* connectingText[5] = {"2. WIFI:", "2. WIFI:", "2. WIFI:.", "2. WIFI:..", "2. WIFI:..."};

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(64, 0, "CONECTING TO");
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(1, 20, "1. SENSOR:");
  display.drawFastImage(80, 22,8, 8, done);
  display.drawString(1, 32, connectingText[tickw]);
  display.display();
  display.clear();
  if (tickw == 4){
    tickw = 0;
  }
}

void intro_successful_connection_wifi(){
  if (active_state ==1){
    Serial.print("✖ No connection to Wi-Fi ");
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64,0, "CONECTING TO");
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(1, 20, "1. SENSOR:");
    display.drawFastImage(80, 22,8, 8, done);
    display.drawString(1, 32, "2. WIFI:");
    display.drawFastImage(80, 34,8, 8, none);
    display.display();
    display.clear();
  }
  if (active_state ==2){
    Serial.print(" [√] Successfully connected to ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64,0, "CONECTING TO");
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(1, 20, "1. SENSOR:");
    display.drawFastImage(80, 22,8, 8, done);
    display.drawString(1, 32, "2. WIFI:");
    display.drawFastImage(80, 34,8, 8, done);
    display.display();
    display.clear();
  }
}

void firebase_initialization(){
  unsigned long previousMillis = 0;
  const unsigned long interval = 250;

  Serial.print("Connecting to FIREBASE: ");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  if (!Firebase.beginStream(firebaseData, path)){
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      tickf++;
      intro_connecting_firebase();
      Serial.print(".");
    }

    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("");
  }

  digitalWrite(LED_BUILTIN, 1);
  digitalWrite(BUZZER_PIN, 1);
  Serial.println("\n [√] Successfully connected FIREBASE ");
  intro_successful_connection_firebase();
  delay(50);
  digitalWrite(BUZZER_PIN, 0);
  delay(1000);
}

void intro_connecting_firebase(){
  const char* connectingText[5] = {"3. FIREBASE:", "3. FIREBASE:", "3. FIREBASE.", "3. FIREBASE:..", "3. FIREBASE:..."};

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(64,0, "CONECTING TO");
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(1, 20, "1. SENSOR:");
  display.drawFastImage(80, 22,8, 8, done);
  display.drawString(1, 32, "2. WIFI:");
  display.drawFastImage(80, 34,8, 8, done);
  display.drawString(1, 44, connectingText[tickf]);
  display.display();
  display.clear();

  if (tickf == 4){
    tickf = 0;
  }
}

void intro_successful_connection_firebase(){
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(64,0, "CONECTING TO");
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(1, 20, "1. SENSOR:");
  display.drawFastImage(80, 22,8, 8, done);
  display.drawString(1, 32, "2. WIFI:");
  display.drawFastImage(80, 34,8, 8, done);
  display.drawString(1, 44, "3. FIREBASE: ");
  display.drawFastImage(80, 46,8, 8, done);
  display.display();
  display.clear();
}

void setup_button_wifi() {
  uint8_t currentState = digitalRead(BUTTON_PIN);
  const uint8_t required_clicks = 3;
  const unsigned long long_press_duration = 3000;
  static unsigned long previousClickTime = 0;
  static unsigned long pressStartTime = 0;  
  static int buttonState = HIGH;    
  static int consecutiveClicks = 0;

  if (currentState == LOW && buttonState == HIGH) {
    pressStartTime = millis();
  }

  if (currentState == HIGH && buttonState == LOW) {
    unsigned long timeSinceLastClick = millis() - previousClickTime;

    if (timeSinceLastClick > 5000) {
      consecutiveClicks = 0;
    }
    consecutiveClicks++;
    digitalWrite(BUZZER_PIN, 1);
    delay(10);
    previousClickTime = millis();

    if (consecutiveClicks == required_clicks) {
      active_state = 1;
      exitLoop = true;
      return;
    }
  }

  if (currentState == LOW && millis() - pressStartTime >= long_press_duration) {
    digitalWrite(BUZZER_PIN, 1);
    delay(50);
    digitalWrite(BUZZER_PIN, 0);
    delay(50);
    digitalWrite(BUZZER_PIN, 1);
    delay(50);
    active_state = 2;
    exitLoop = true;
  }
  buttonState = currentState;
}

// void change_wifi(){
//   WiFi.mode(WIFI_AP);
//   WiFi.softAP("ESP8266_AP", "password");

//   server.on("/", handleRoot);
//   server.begin();
//   while (!passwordChanged) {
//     server.handleClient();
//   }
// }

// void handleRoot() {
//   String newSsid = server.arg("ssid");
//   String newPassword = server.arg("password");

//   // Thực hiện thay đổi mật khẩu WiFi tại đây

//   passwordChanged = true; // Đặt biến cờ thành true khi đã thay đổi mật khẩu
//   server.send(200, "text/plain", "Mật khẩu WiFi đã được thay đổi!");
// }

/////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  
  display.init();
  display.flipScreenVertically();
  intro_logo();
  SHTC3sensor_initialization();
  wifi_initialization();
  
  if (active_state  == 1){

  }else {
    if (active_state  == 2){
      firebase_initialization();
      client.setInsecure();
    }

  }
  Serial.println("_____________________________________________________\n");
  Serial.println("\nDATA INFOMATION");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void SHTC3_read(){
  sensors_event_t humidity, temp;
  shtc3.getEvent(&humidity, &temp);
  SHTC3_tprt = temp.temperature;
  SHTC3_hmdt = humidity.relative_humidity;
  Serial.print("\nTemperature: "); 
  Serial.print(SHTC3_tprt); 
  Serial.print(" °C || ");
  Serial.print("Humidity: "); 
  Serial.print(SHTC3_hmdt); 
  Serial.println("% rH");
  
}

void show_value(){
  if (active_state == 1){

  }else {
    read_speed_wifi();
  }
  display.drawRect(1, 0, 127, 15);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_10);
  display.drawString(64,1, "SWIFTLET  FARM");
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(1, 20, "TEMP:");
  display.drawString(55, 20, String(SHTC3_tprt,2) + " °C");
  display.setFont(ArialMT_Plain_16);
  display.drawString(1, 40,"HUMI :");
  display.drawString(55, 40, String(SHTC3_hmdt,2) + " %");
  display.display();
  display.clear();
}

void send_data_firebase(){
  json.clear();
  json.add("Temperature", SHTC3_tprt);
  json.add("Humidity", SHTC3_hmdt);
  Serial.println(" --------------------------------------------");
  Serial.println("| Connecting to Firebase                     |");

  if (WiFi.status() == WL_CONNECTED && Firebase.ready()){
    if (Firebase.setAsync(firebaseData, path, json)) {
      Serial.println("| [√] Data successfully uploaded to Firebase |");

      toggleLedBuzzer(false); 
      led_buzzer_start_time = millis();
      led_buzzer_count = 1;
    } 
    else {
      Serial.println("| [X] Data upload to Firebase unsuccessful   |");
      Serial.println("| REASON: " + firebaseData.errorReason()+ "                 |");
    }
  } 
  else {
    Serial.println("| Connection failed                          |");
  }
    Serial.println(" --------------------------------------------");

}

void read_speed_wifi() {
  long speed_wifi = WiFi.RSSI();

  if (speed_wifi > -60 && speed_wifi < 0) {
    Serial.println("WIFI Status: Good");

    static const Pixel goodWifiPixels[] = {
      {117, 10},
        {117, 7},
          {118, 7},
            {119, 8},
              {120, 9},
                {120, 10},
                  {117, 4},
                  {118, 4},
                {119, 4},
              {121, 5},
            {122, 6},
          {123, 8},
        {123, 9},
      {123, 10}
    };
    drawPixels(goodWifiPixels, sizeof(goodWifiPixels) / sizeof(goodWifiPixels[0]));
  } else{ 
    if (speed_wifi <= -60 && speed_wifi > -70) {
      Serial.println("WIFI Status: Average");

      static const Pixel averageWifiPixels[] = {
        {117, 10},
          {117, 7},
            {118, 7},
            {119, 8},
          {120, 9},
        {120, 10}
      };
      drawPixels(averageWifiPixels, sizeof(averageWifiPixels) / sizeof(averageWifiPixels[0]));
    } else{ 
      if (speed_wifi <= -70) {
        Serial.println("WIFI Status: Poor");
        static const Pixel poorWifiPixels[] = {
          {117, 10}
        };
        drawPixels(poorWifiPixels, sizeof(poorWifiPixels) / sizeof(poorWifiPixels[0]));
      } else{ 
        if (WiFi.status() != WL_CONNECTED) {
          Serial.println("[X] WIFI connection lost. Reconnecting...");

          static const Pixel connectionLostPixels[] = {
            {117, 10},
              {117, 7},
                {118, 7},
                  {119, 8},
                    {120, 9},
                      {120, 10},
                        {117, 4},
                        {118, 4},
                      {119, 4},
                    {121, 5},
                  {122, 6},
                {123, 8},
              {123, 9},
            {123, 10}
          };
          drawPixels(connectionLostPixels, sizeof(connectionLostPixels) / sizeof(connectionLostPixels[0]));
        } 
      }
    }
  }
}

void drawPixels(const Pixel* pixels, int numPixels) {
  for (int i = 0; i < numPixels; i++) {
    display.setPixel(pixels[i].x, pixels[i].y);
  }
}

void send_data_google_sheet() {

  Serial.println(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  Serial.print("| Connecting to ");
  Serial.print(host);
  Serial.println("                                                                                                                                     |");
  
  if (!client.connect(host, httpsPort)) {
    Serial.println("| Connection failed                                                                                                                                                   |");
    Serial.println("| [X] Data upload to Google Sheet unsuccessful                                                                                                                        |");
    Serial.println(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    return;
  }

  String string_temperature =  String(SHTC3_tprt);
  String string_humidity =  String(SHTC3_hmdt);
  String url = "/macros/s/" + GAS_ID + "/exec?Temperature=" + string_temperature + "&Humidity=" + string_humidity;

  Serial.print("| Requesting URL: https://script.google.com");
  Serial.print(url);
  Serial.println(" |");
  client.print(String("GET ") 
  + url 
  + " HTTP/1.1\r\n" 
  + "Host: " 
  + host 
  + "\r\n" 
  + "User-Agent: BuildFailureDetectorESP8266\r\n" 
  + "Connection: close\r\n\r\n");
  Serial.println("| [√] Data successfully uploaded to Google Sheet                                                                                                                      |");
  Serial.println(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------------");

  toggleLedBuzzer(false);
  led_buzzer_start_time = millis(); 
  led_buzzer_count = 2;
}

void getMemoryInfo() {
  uint32_t freeHeap = ESP.getFreeHeap();
  uint32_t sketchSpace = ESP.getSketchSize();
  uint32_t freeSketchSpace = ESP.getFreeSketchSpace();
  uint32_t flashChipSize = ESP.getFlashChipSize();

  Serial.print("Memory usage [");
  Serial.print(freeHeap);
  Serial.print("] bytes || ");
  
  Serial.print("Program size [");
  Serial.print(sketchSpace);
  Serial.print("] bytes || ");
  
  Serial.print("Free sketch space [");
  Serial.print(freeSketchSpace);
  Serial.print("] bytes || ");
  
  Serial.print("Flash chip size [");
  Serial.print(flashChipSize);
  Serial.println("] bytes\n");
}

void toggleLedBuzzer(bool on) {
  if (on) {
    digitalWrite(LED_BUILTIN, 0);
    digitalWrite(BUZZER_PIN, 1);
  } else {
    digitalWrite(LED_BUILTIN, 1);
    digitalWrite(BUZZER_PIN, 0);
  }
}


void loop() {
  if (active_state == 1) {
    unsigned long currentMillis_read = millis();
    if ((currentMillis_read - t1) > interval_read) {
      SHTC3_read();
      show_value();
      t1 = currentMillis_read;
      Serial.println(F("Memory Info: "));
      getMemoryInfo();
    }
  }

  if (active_state == 2) {
    unsigned long currentMillis_read = millis();
    unsigned long currentMillis_send_firebase = millis();
    unsigned long currentMillis_send_googlesheet = millis();

    if ((currentMillis_read - t1) > interval_read) {
      SHTC3_read();
      show_value();
      t1 = currentMillis_read;
      Serial.print(F("Memory info: "));
      getMemoryInfo();
    }

    if ((currentMillis_send_firebase - t2) > interval_send_firebase) {
      send_data_firebase();
      t2 = currentMillis_send_firebase;
    }

    if ((currentMillis_send_googlesheet - t3) > interval_send_googlesheet) {
      send_data_google_sheet();
      t3 = currentMillis_send_googlesheet;
    }

    if (millis() - led_buzzer_start_time <= led_buzzer_duration * led_buzzer_count) {
      int interval = led_buzzer_duration / 2;
      int currentLedBuzzerIndex = (millis() - led_buzzer_start_time) / interval;

      if (currentLedBuzzerIndex % 2 == 0) {
        toggleLedBuzzer(true);
      } else {
        toggleLedBuzzer(false);
      }
    } 
    else {
      toggleLedBuzzer(false);
    }
  }
}

