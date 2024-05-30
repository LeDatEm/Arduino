#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" 

#define TdsSensorPin A0
#define OUTPUT1 16
#define LED_BUILTIN 2
#define SET_BUTTON 13
#define INCREASE_BUTTON 12
#define DECREASE_BUTTON 14
#define VREF 5.0
#define SCOUNT  30
#define WIFI_SSID "Wifi"
#define WIFI_PASSWORD "88888888"

WiFiClient  client;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

unsigned long myChannelNumber = 2260835;
const char * myWriteAPIKey = "VF4UK403XN0LSN65";

int analogBuffer[SCOUNT];
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;
int copyIndex = 0;

float averageVoltage = 0;
float tdsValue = 0;
float temperature = 25;
float currentValue = 0.5;
float mappedValue;

static float tempValue = currentValue;

bool isSettingMode = false;
bool lastSetButtonState = 1;
bool lastIncreaseButtonState = 1;
bool lastDecreaseButtonState = 1;
bool exitLoop = false;

unsigned long lastTime = 0;
unsigned long timerDelay = 30000;
unsigned long lastSendTime = 0;

uint8_t active_state = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

byte DONVI[8] = {
  B11001,
  B11010,
  B00100,
  B01000,
  B10000,
  B00000,
  B11011,
  B11011
};

void intro() {
  lcd.init();
  lcd.backlight();
}

void wifiConnect() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("");
  Serial.print("Connecting to WIFI: ");
  unsigned long previousMillis = 0;
  const unsigned long interval = 250; 
  while (WiFi.status() != WL_CONNECTED && !exitLoop) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      lcd.setCursor(0,0);
      lcd.print("CONNECTING TO");
      lcd.setCursor(0,1);
      lcd.print(WIFI_SSID);
      Serial.print(".");
    }
    status_Online_Offline();
  }
  lcd.clear();
  if(active_state == 2){
    lcd.setCursor(0,0);
    lcd.print("CHE DO:");
    lcd.setCursor(0,1);
    lcd.print("NO INTERNET");
  }
  if(active_state == 1){
  digitalWrite(LED_BUILTIN, 1);
  Serial.println("");
  Serial.print("☑ Successfully connected to ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  lcd.setCursor(0,0);
  lcd.print("CONNECTED");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
  }
  delay(1000);
  lcd.clear();
}

void status_Online_Offline() {
  uint8_t currentState = digitalRead(SET_BUTTON);
  const unsigned long long_press_duration = 3000;
  static unsigned long pressStartTime = 0;
  static int buttonState = HIGH;
  static bool active_state_set = false;

  if (currentState == LOW && buttonState == HIGH) {
    pressStartTime = millis();
  }

  if (currentState == LOW && millis() - pressStartTime >= long_press_duration && !active_state_set) {
    active_state = 2;
    active_state_set = true;
    exitLoop = true;
  } else {
    active_state = 1;
  }
  buttonState = currentState;
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  ThingSpeak.begin(client);
  pinMode(TdsSensorPin, INPUT);
  pinMode(OUTPUT1, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SET_BUTTON, INPUT_PULLUP);
  pinMode(INCREASE_BUTTON, INPUT_PULLUP);
  pinMode(DECREASE_BUTTON, INPUT_PULLUP);
  digitalWrite(LED_BUILTIN, 1);
  intro();
  wifiConnect();
  EEPROM.get(0, currentValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setButton() {
  bool setButtonState = digitalRead(SET_BUTTON);
  bool increaseButtonState = digitalRead(INCREASE_BUTTON);
  bool decreaseButtonState = digitalRead(DECREASE_BUTTON);
  
  if (setButtonState == 0 && lastSetButtonState == 1) {
    isSettingMode = !isSettingMode;
    
    if (!isSettingMode) {
      currentValue = tempValue;
      if (currentValue < 0.0) {
        currentValue = 0.0;
      }
      if (currentValue > 1.0) {
        currentValue = 1.0; 
      }
      EEPROM.put(0, currentValue);
      EEPROM.commit(); 
    }
  }

  if (isSettingMode) {
    digitalWrite(LED_BUILTIN, 0);
    if (increaseButtonState == 0 && lastIncreaseButtonState == 1) {
      tempValue += 0.05;
      if (tempValue > 1.0) {
        tempValue = 1.0; 
      }
    }
    if (decreaseButtonState == 0 && lastDecreaseButtonState == 1) {
      tempValue -= 0.05;
      if (tempValue < 0.0) {
        tempValue = 0.0;
      }
    }
  } else {
    digitalWrite(LED_BUILTIN, 1);
  }
  
  lastSetButtonState = setButtonState;
  lastIncreaseButtonState = increaseButtonState;
  lastDecreaseButtonState = decreaseButtonState;
}

void readTDS(){
     static unsigned long analogSampleTimepoint = millis();
   if(millis()-analogSampleTimepoint > 40U) 
   {
     analogSampleTimepoint = millis();
     analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
     analogBufferIndex++;
     if(analogBufferIndex == SCOUNT) 
         analogBufferIndex = 0;
   }   
   static unsigned long printTimepoint = millis();
   if(millis()-printTimepoint > 800U)
   {
      printTimepoint = millis();
      for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
        analogBufferTemp[copyIndex]= analogBuffer[copyIndex];
      averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0;
      float compensationCoefficient=1.0+0.02*(temperature-25.0);
      float compensationVolatge=averageVoltage/compensationCoefficient;
      tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5;
      Serial.print("TDS Value:");
      Serial.print(tdsValue,0);
      Serial.println("ppm");
   }
}

int getMedianNum(int bArray[], int iFilterLen) 
{
      int bTab[iFilterLen];
      for (byte i = 0; i<iFilterLen; i++)
      bTab[i] = bArray[i];
      int i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++) 
      {
      for (i = 0; i < iFilterLen - j - 1; i++) 
          {
        if (bTab[i] > bTab[i + 1]) 
            {
        bTemp = bTab[i];
            bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
         }
      }
      }
      if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
      else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}

float mapToFloat(int x, int in_min, int in_max, float out_min, float out_max) {
  return (float)(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void showValue() {
  lcd.setCursor(2, 0);
  lcd.print("MUC");
  lcd.setCursor(7, 0);
  lcd.print("|");
  lcd.setCursor(9, 0);
  lcd.print("DO MAN");
  lcd.setCursor(7, 1);
  lcd.print("|");
  lcd.setCursor(1, 1);

  if (isSettingMode) {
    lcd.print(tempValue);

    static unsigned long lastBlinkTime = 0;
    const unsigned long blinkInterval = 500;
    static bool cursorVisible = false;

    unsigned long currentTime = millis();
    if (currentTime - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = currentTime;
      cursorVisible = !cursorVisible;
    }

    if (cursorVisible) {
      lcd.createChar(0, DONVI);
      lcd.setCursor(5,1);
      lcd.write((byte)0);
    } else {
      lcd.setCursor(5, 1);
      lcd.print(" ");
    }

  } else {
    lcd.print(currentValue);
    lcd.createChar(0, DONVI);
    lcd.setCursor(5,1);
    lcd.write((byte)0);
  }

  lcd.setCursor(9, 1);
  lcd.print(mappedValue);
  lcd.createChar(0, DONVI);
  lcd.setCursor(14,1);
  lcd.write((byte)0);
}

void checkTdsSensorPin() {
  static unsigned long lastBlinkTime = 0;
  const unsigned long blinkInterval = 500;
  static bool cursorVisible = false;
  if (mappedValue >= currentValue) {
    unsigned long currentTime = millis();
    if (currentTime - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = currentTime;
      cursorVisible = !cursorVisible;
    }

    if (cursorVisible) {
      lcd.setCursor(8,1);
      lcd.print("!");
    } else {
      lcd.setCursor(8, 1);
      lcd.print(" ");
    }

    digitalWrite(OUTPUT1, 1);
  } else {
    lcd.setCursor(8, 1);
    lcd.print(" ");

    digitalWrite(OUTPUT1, 0);
  }
}
void sentData(){
  int x = ThingSpeak.writeField(myChannelNumber, 1, mappedValue, myWriteAPIKey);
  if (x == 200) {
    Serial.print("Channel update successful | Value:");
    Serial.println(mappedValue);
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  setButton();
  readTDS();
  mappedValue = mapToFloat(tdsValue, 0, 1000, 0.0, 1.0);
  if(mappedValue >= 1.0){
    mappedValue = 1.0;
  }
  showValue();
  checkTdsSensorPin();
  if(active_state == 1){
    unsigned long currentTime = millis();
    if (currentTime - lastSendTime >= timerDelay) {
      sentData();
      lastSendTime = currentTime; 
    }
  }
}


// void getMemoryInfo() {
//   uint32_t freeHeap = ESP.getFreeHeap();
//   uint32_t sketchSpace = ESP.getSketchSize();
//   uint32_t freeSketchSpace = ESP.getFreeSketchSpace();
//   uint32_t flashChipSize = ESP.getFlashChipSize();

//   Serial.print("Memory usage [");
//   Serial.print(freeHeap);
//   Serial.print("] bytes || ");
  
//   Serial.print("Program size [");
//   Serial.print(sketchSpace);
//   Serial.print("] bytes || ");
  
//   Serial.print("Free sketch space [");
//   Serial.print(freeSketchSpace);
//   Serial.print("] bytes || ");
  
//   Serial.print("Flash chip size [");
//   Serial.print(flashChipSize);
//   Serial.println("] bytes\n");
// }


