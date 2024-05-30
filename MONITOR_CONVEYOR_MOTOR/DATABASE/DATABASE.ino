#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>
#include <Adafruit_SH110X.h>
#include <FirebaseESP8266.h>
#include <WiFiClientSecure.h>


//The 80's icafe FPT
//the80sicafe
#define ON_Board_LED 2                                                     //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router
#define WIFI_SSID "Wi-Fi"
#define WIFI_PASSWORD "88888888"



#define FIREBASE_HOST "database-25856-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "t8KqnBbzAItutelDTmldwjHIdXblrpd7I17mQbjz"

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//Host & httpsPort
const char* host = "script.google.com";
const int httpsPort = 443;

WiFiClientSecure client;                                                    //--> Create a WiFiClientSecure object.
FirebaseData firebaseData;
String path = "/";
FirebaseJson json;

unsigned long t1 = 0;

String GAS_ID = "AKfycbyQLXf0qBzc6IbIgNTCUUt2U0MfGEkCxQ4NJJr19l0VpXMT4w9PK_3Jt9oaw71RUW_VWQ"; //--> spreadsheet script ID
String Status;

SoftwareSerial mySerial(10, 11); // Thiết lập kết nối UART trên chân GPIO 10 (RX) và 11 (TX)

  int Sta;
  float Temperature = random(35,40);
  int Speed = random(110,300);
  float Amperage = random(0.2,1);
  float Powerconsumption = 12*Amperage;

int bien1 = 0;
int bien2 = 0;
int bien3 = 0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // Khởi tạo kết nối Serial với máy tính để theo dõi quá trình hoạt động
  mySerial.begin(9600); // khởi tạo cổng serial bổ sung để nhận dữ liệu từ MSP430G2553
  //uart.begin(9600);   // Khởi tạo kết nối UART với MSP430G2553
  display.begin(i2c_Address, true); // Address 0x3C default

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }

  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  Serial.println("");
  Serial.print("Successfully connected to ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  if(!Firebase.beginStream(firebaseData, path)){
     Serial.println("REASON: " + firebaseData.errorReason());
     Serial.println("");
  }
  //----------------------------------------
  client.setInsecure();
}

void loop() {
 
  //UART();
  // Sta = bien1;
  // if(Sta == 1){
  //   Status = "OFF";
  // } else{
  //   Status = "ON";
  // }
  // Temperature = bien1;
  // Speed = bien1 + 10;
  // Amperage = bien2;
  // Powerconsumption = bien2+10;
  // sendDataGgSheet(Status, Temperature, Speed, Amperage, Powerconsumption);

  if(millis() - t1> 52000){
    sendDataGgSheet(Status, Temperature, Speed, Amperage, Powerconsumption); //--> Calls the sendData Subroutine
    t1 = millis();
  }
}

// Subroutine for sending data to Google Sheets
void sendDataGgSheet(String Status, float Temperature, int Speed , float Amperage, float Powerconsumption) {
  Serial.print("connecting to ");
  Serial.println(host);
  
  //Connect to Google host
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  //Processing data and sending data
  String string_Status =  String(Status);
  String string_Temperature =  String(Temperature);
  String string_Speed =  String(Speed);
  String string_Amperage =  String(Amperage);
  String string_Powerconsumption =  String(Powerconsumption);
  String url = "/macros/s/" + GAS_ID + "/exec?Status=" + string_Status + "&Temperature=" + string_Temperature + "&Speed=" + string_Speed + "&Amperage=" + string_Amperage + "&Power_consumption=" + string_Powerconsumption;
  Serial.print("requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: BuildFailureDetectorESP8266\r\n" + "Connection: close\r\n\r\n");
  Serial.println("Request sent");
  //Checking whether the data was sent successfully or not
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("............................");
  Serial.println("\n");

  // digitalWrite(ON_Board_LED, 0);
  // delay(200);
  // digitalWrite(ON_Board_LED, 1);
  // delay(200);
} 

void UART(){
  if(mySerial.available()){//Read from  MSP430G2553 module and send to serial monitor
    String input = mySerial.readString();
    Serial.println(input); 
    
    // xử lí chuỗi A123aB32b lấy ra số 123 32  luu vao bien 1 2 
    int timA, tima ;//timB, timb, timC, timc= -1;
    timA = input.indexOf("A");
    tima = input.indexOf("a");
    /*timB = input.indexOf("B");
    timb = input.indexOf("b");
    timC = input.indexOf("C");
    timc = input.indexOf("c");*/
    delay(10);
    if(timA >= 0 && tima >=0)
    {
      String DulieuAa = "";
      DulieuAa = input.substring(timA+1,tima);
      bien1 = DulieuAa.toFloat();
     
    }
    /*if(timB >= 0 && timb >=0)
    {
      String DulieuBb = "";
      DulieuBb = input.substring(timB+1,timb);
      bien2 = DulieuBb.toFloat();
      
    }
       if(timC >= 0 && timc >=0)
    {
      String DulieuCc = "";
      DulieuCc = input.substring(timC+1,timc);
      bien3 = DulieuCc.toFloat();
    }*/
  }


}
// void sendDataFirebase(){
//     String Sta = "Status: " + String(Status);
//     String Tem = "Temparature: " + String(Temperature) + " °C";
//     String Spe = "Speed: " + String(Speed) + " RPM";
//     String Amp = "Amperage: " + String(Amperage) + " mA";
//     String Pwcs = "Power consumption: " + String(Powerconsumption) + " kWh";

//     Serial.println("Data System");
//     Serial.print(Sta);
//     Serial.print(" || ");
//     Serial.print(Tem);
//     Serial.print(" || ");
//     Serial.print(Spe);
//     Serial.print(" || ");
//     Serial.print(Amp);
//     Serial.print(" || ");
//     Serial.println(Pwcs);

//     Firebase.setString(firebaseData, path + "/1 ",Sta);
//     Firebase.setString(firebaseData, path + "/2 ",Tem);
//     Firebase.setString(firebaseData, path + "/3 ",Spe);
//     Firebase.setString(firebaseData, path + "/4 ",Amp);
//     Firebase.setString(firebaseData, path + "/5 ",Pwcs);
// }