#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#include "commands.h"

#define signalPin 2
#define SS_PIN 10
#define RST_PIN 9
#define onPin 8

#define BOX 1

MFRC522 mfrc522(SS_PIN, RST_PIN);

LiquidCrystal lcd(6, 4, 14, 15, 16, 17);

bool active = false;
volatile int signalPinVal;

bool cardScanned = false;
bool boxOpen = false;

bool signalFlag = false;

byte openBoxId = 0x0;
String openUID;

byte nextId = 0x01;

String openBoxText = "Hi! Scan card to open box";

void handleAck() {}

// handles sending message to box
void sendMessage(byte id, byte m) {
  Serial.println("Sending message");
  byte message[2] = {id, m};
  Wire.beginTransmission(1);
  Wire.write(message, 2);
  Wire.endTransmission(1);
}

// handles addition of new box
void handleNewBox() {
  Serial.println("Creating new box");
  sendMessage(nextId, ACK);
  nextId++;
}

// handling the opening and closing of box
void handleOpenClose(byte id, bool open) {
  Serial.print("Trying to do something to box: ");
  Serial.print(id);
  Serial.print(" ");
  Serial.println(open);

  if (open) {
    if (!cardScanned) {
      sendMessage(id, NOT_OK);
      return;
    }

    if(boxOpen) {
      sendMessage(id, NOT_OK);
      return;
    }

    boxOpen = true;
    openBoxId = id;
    sendMessage(id, OK);
    Serial.print("Box open: ");
    Serial.println(openBoxId);
  } else {
    if (!cardScanned) {
      sendMessage(id, NOT_OK);
      return;
    }

    if(!boxOpen) {
      sendMessage(id, NOT_OK);
      return;
    }

    if(id != openBoxId) {
      sendMessage(id, NOT_OK);
      return;
    }

    boxOpen = false;
    cardScanned = false;
    Serial.print("Closing box: ");
    Serial.println(openBoxId);
    openBoxId = 0x0;
    openUID = "";
    sendMessage(id, OK);
  }
}

void handleWeight() {

}


void handleCalibrate() {
  // Calibrate -> select calibrate, then select box/open box

}

void getMessage() {
  Wire.clearWireTimeoutFlag();
  Serial.write("Getting message\n");
  // delay(1000);
  // send data to box first, then get what it is trying to do
  // only request the first 2 bytes, one for Id, other for command, and the last 2 for general data
  byte bytes[4];

  byte len = Wire.requestFrom(BOX, 4);
  Serial.println("we have sent request");
  Serial.print("is wire available? ");
  Serial.println(Wire.available());
  Serial.print("data we got: ");
  if (len == 0) {
    Serial.println("Error occured while requesting");
    if (Wire.getWireTimeoutFlag())
      Serial.println("Timeout error");
  } else {
    int i = 0;
    while(Wire.available()) {
      bytes[i] = Wire.read();
      i++;
    }
    Serial.println("");
    Serial.print("Command: ");
    Serial.println(bytes[1]);

    // handle command here
    switch(bytes[1]) {
      case NEW:
        handleNewBox();
        break;
        
      case CLOSE:
        handleOpenClose(bytes[0], false);
        break;

      case OPEN:
        handleOpenClose(bytes[0], true);
        break;

      case ACK:
        handleAck();
        break;

      case WEIGHT:
        handleWeight();
        break;
      
      case CALIBRATE:
        handleCalibrate();
        break;
        
      default:
        // Something happened that shouldn't and we could not understand what we should do.
        Serial.println("Default occured");
        break;
    }
  }
  signalFlag = false;
}

// void printHiOpenBox() {
//   lcd.clear();
//   lcd.print("Yeet");
//   // lcd.setCursor(0,1);
//   // lcd.print("open box.");
// }

// void printPushBoxToOpen() {
//   lcd.clear();
//   lcd.print("Press a box to");
//   lcd.setCursor(0,1);
//   lcd.print("open.");
// }

// void printOpenBox() {
//   lcd.clear();
//   lcd.print("Box open: ");
//   lcd.print(openBoxId);
// }

void interruptFunc() {
  signalFlag = true;
}

void setup() {
  Serial.begin(500000);
  delay(1500);
  Serial.println("Setup");
  delay(1500);
  pinMode(onPin, OUTPUT);
  pinMode(signalPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(signalPin), interruptFunc, FALLING);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(16, 2);
  delay(40);
  lcd.clear();
  lcd.print("hello");
  Wire.begin();
  Wire.setWireTimeout(2500000, false);
  digitalWrite(onPin, HIGH);
}

void loop() {
  // if (!boxOpen && !cardScanned) printHiOpenBox();
  // else if (!boxOpen && cardScanned) printPushBoxToOpen();
  // else printOpenBox();

  if (signalFlag) getMessage();

  if (!cardScanned) {
    if (! mfrc522.PICC_IsNewCardPresent())
      return;
    if (! mfrc522.PICC_ReadCardSerial())
      return;

    Serial.print("UID tag:");
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      openUID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      openUID.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println(openUID);
    cardScanned = true;
  }
}

