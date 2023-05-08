#include <Wire.h>
#include <Servo.h>
#include <EEPROM.h>
#include <HX711.h>

#include "commands.h"

// pins 6-9 are buttons
// pins 1,2,3,10 are data
// A3 is Servo

// each weight requires 2 pins (+ ground and power)
// (16, 14), (15, 18), (19, 20), (4, 5)

#define signalPin 1
#define setActivePin 10
#define button1Pin 8
#define button2Pin 9
#define servoPin A3

#define eLocation 0

#define nrShelf 2

float calibration_factor = 400350;

Servo servo;

bool isActive = false;

byte openAddress = 0x0;
bool isOpen = false;

int signalVal;

int buttonVal1 = LOW;
int oldButtonVal1 = LOW;

int buttonVal2 = LOW;
int oldButtonVal2 = LOW;

byte address1 = 0xFF;
byte address2 = 0xFF;

byte action = 0x0;
byte activeAddress = 0x0;

char input;

bool actionCompleted = true;
unsigned long actionTime;
unsigned long now;

// start up protocol to get new address
void boot() {
  Serial.println("Booting");
  action = NEW;
  while (!checkAvailable()) {
    delay(10);
  }
  setActive();
}

// ends start up protocol
void finishBoot() {
  action = 0x0;
  unsetActive();
}

void handleOpen(int shelf) {
  if (nrShelf == 2) {
    switch (shelf) {
      case 1:
        servo.write(90 + 85);
        break;
      case 2:
        servo.write(90 - 85);
        break;
    }
  }
  isOpen = true;
  action = 0x0;
  activeAddress = 0x0;
  unsetActive();
}

void handleClose() {
  isOpen = false;
  action = 0x0;
  activeAddress = 0x0;
  servo.write(90);
  Serial.println("Closing");
  unsetActive();
}

// check if master is available to be communicated with
bool checkAvailable() {
  signalVal = digitalRead(signalPin);
  if (signalVal == HIGH) return true;
  return false;
}

// sets signalPin to LOW to tell master that data wants to be sent
void setActive() {
  if (!isActive) {
    digitalWrite(setActivePin, HIGH);
    isActive = true;
    actionCompleted = false;
    actionTime = millis();
  }
}

// sets signalPin to HIGH to tell other slaves that its open to communication
void unsetActive() {
  if (isActive) {
    digitalWrite(setActivePin, LOW);
    actionCompleted = true;
    actionTime = 0;
    isActive = false;
  }
}

void handleNotOK() {
  action = 0x0;
  activeAddress = 0x0;
  unsetActive();
}

// handle data requests from master
void handleRequest() {
  // need to send address to log box
  // need to check if we can open or not
  // open if we can, otherwise we cant
  Serial.println("Requested"); 
  byte message[2] = {0x00, 0x00};
  switch (action) {
    case NEW:
      message[0] = activeAddress;
      message[1] = NEW;
      Wire.write(message, sizeof(message));
      break;
    case OPEN:
      message[0] = activeAddress;
      message[1] = OPEN;
      Wire.write(message, sizeof(message));
      break;
    case CLOSE:
      message[0] = activeAddress;
      message[1] = CLOSE;
      Wire.write(message, sizeof(message));
      break;
  }
}

void handleReceive(int byteCount) {

  if (byteCount > 4) {
    Serial.print("We recieved many bytes: ");
    Serial.println(byteCount);
  }

  byte bytes[byteCount];

  int i = 0;
  while (Wire.available()) {
    bytes[i] = Wire.read();
    i++;
  }

  Serial.print("Got message: ");
  Serial.println(bytes[1]);

  switch (action) {
    case NEW:
      if (bytes[1] == ACK) {
        if (address1 == 0xFF && address2 == 0xFF) {
          address1 = bytes[0];
          // EEPROM.write(eLocation, address1);
          finishBoot();
        } else {
          address2 = bytes[0];
          finishBoot();
        }
      }
      break;

    case OPEN:
      if (bytes[1] == OK) {
        if (activeAddress == address1) handleOpen(1);
        else handleOpen(2);
      } else handleNotOK();
      break;

    case CLOSE:
      if (bytes[1] == OK) handleClose();
      else handleNotOK();
      break;
  }
}

void setup() {
  pinMode(signalPin, INPUT);
  pinMode(setActivePin, OUTPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  digitalWrite(setActivePin, LOW);
  Wire.begin(1);
  Wire.onRequest(handleRequest);
  Wire.onReceive(handleReceive);
  Serial.begin(9600);
  servo.attach(servoPin);
  delay(6000);
  digitalWrite(setActivePin, LOW);
  Serial.println("Booting");
  servo.write(90);
  delay(1000);
}

void loop() {
  if (address1 == 0xFF && action != NEW) {
    Serial.println("booting 1");
    boot();
    return;
  }

  if (address2 == 0xFF && action != NEW) {
    Serial.println("booting 2");
    boot();
    return;
  }

  if (actionCompleted == false && (millis() - actionTime) > 3000) {
    Serial.println("We are unsetting active");
    unsetActive();
    delay(2500);
    action = 0x0;
  }

  // if (Serial.available()) {
  //   input = Serial.read();
  //   if (input == 'o') {
  //     if (!isOpen) {
  //       Serial.println("Trying to open box 1");
  //       if (checkAvailable()) {
  //         action = OPEN;
  //         activeAddress = address1;
  //         setActive();
  //       }
  //     } else {
  //       Serial.println("Trying to close box 1");
  //       if (checkAvailable()) {
  //         action = CLOSE;
  //         activeAddress = address1;
  //         setActive();
  //       }
  //     }
  //   } else if (input == 'p') {
  //     if (!isOpen) {
  //       Serial.println("Trying to open box 2");
  //       if (checkAvailable()) {
  //         action = OPEN;
  //         activeAddress = address2;
  //         setActive();
  //       }
  //     } else {
  //       Serial.println("Trying to close box 2");
  //       if (checkAvailable()) {
  //         action = CLOSE;
  //         activeAddress = address2;
  //         setActive();
  //       }
  //     }
  //   }
  // }


  buttonVal1 = digitalRead(button1Pin);
  buttonVal2 = digitalRead(button2Pin);

  if (buttonVal1 != oldButtonVal1) {
    oldButtonVal1 = buttonVal1;

    delay(50);
    buttonVal1 = digitalRead(button1Pin);
    if(buttonVal1 == HIGH) {
      Serial.println("Button 1 is pressed");
      if (!isOpen) {
        if (checkAvailable()) {
          action = OPEN;
          activeAddress = address1;
          setActive();
        }
      } else {
        if (checkAvailable()) {
          action = CLOSE;
          activeAddress = address1;
          setActive();
        }
      }
    }
  } 
  if (buttonVal2 != oldButtonVal2) {
    oldButtonVal2 = buttonVal2;

    delay(50);
    if (buttonVal2 == HIGH) {
      Serial.println("Button 2 is pressed");
      if (!isOpen) {
        if (checkAvailable()) {
          action = OPEN;
          activeAddress = address2;
          setActive();
        }
      } else {
        if (checkAvailable()) {
          action = CLOSE;
          activeAddress = address2;
          setActive();
        }
      }
    }
  }
}