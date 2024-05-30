#include <Arduino.h>
#include <HardwareSerial.h>
#define RX_PIN 3 // Pin RX của ESP32 gửi
#define TX_PIN 1 // Pin TX của ESP32 gửi
HardwareSerial SerialESP32(1);

const int ROWS = 12;
const int COLS = 12;

bool keyMatrix[ROWS][COLS] = {0};
bool keyPressed[ROWS][COLS] = {0};

byte rowPins[ROWS] = {13, 12, 14, 27, 26, 25, 33, 32, 35, 34, 39, 36};
byte colPins[COLS] = {15, 2, 0, 4, 16, 17, 5, 18, 19, 21, 22, 23};

int keypad_12x12() {
  int index = -1;
  for (int i = 0; i < COLS; i++) {
    digitalWrite(colPins[i], LOW);
    for (int j = 0; j < ROWS; j++) {
      if (digitalRead(rowPins[j]) == LOW && !keyPressed[j][i]) {
        keyMatrix[j][i] = true;
        keyPressed[j][i] = true;
        index = j * COLS + i +1;
      } else if (digitalRead(rowPins[j]) == HIGH) {
        keyPressed[j][i] = false;
      }
    }
    digitalWrite(colPins[i], HIGH);
  }
  return index;
}


void setup() {
  Serial.begin(115200);
  SerialESP32.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
  Serial.println("HELLO");
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
  }
  for (int j = 0; j < COLS; j++) {
    pinMode(colPins[j], OUTPUT);
    digitalWrite(colPins[j], HIGH);
  }
}

void loop() {
  int pressedKey = keypad_12x12();
  if (pressedKey != -1) {
    Serial.println(pressedKey);
    SerialESP32.println(pressedKey);
  }
}
