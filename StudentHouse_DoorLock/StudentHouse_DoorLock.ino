#include "MFRC522.h"
#include "SPI.h"
#include <Servo.h>

const int INTERVAL1000 = 1000;
const int INTERVAL2000 = 2000;
const int SS_PIN = 10;
const int RST_PIN = 9;
const int GREENLED = 7;
const int REDLED = 6;
const int ROOM = 1;
MFRC522 rfid(SS_PIN, RST_PIN);
Servo myservo;

void setup() {
  Serial.begin(9600);
  SPI.begin();      // Initialize SPI bus
  rfid.PCD_Init();  // Initialize MFRC522
  pinMode(GREENLED, OUTPUT);
  pinMode(REDLED, OUTPUT);
  myservo.attach(8); //Attach servo on pin 8
}

void loop() {

  String line;
  if (Serial.available())
  {
    line = Serial.readStringUntil('\n'); //Read message sent from the serialport
    if (line == "AccesGranted") //Doorlock opens
    {
      AccesGranted();
    }
    else if (line == "AccesDenied") //Doorlock stays closed
    {
      AccesDenied();
    }
  }


  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }
  rfid.PICC_HaltA();      // Stop reading RFID
  rfid.PCD_StopCrypto1(); // Exit comm.
  unsigned long tag = getRFIDTag(rfid.uid.uidByte);

  Serial.println(ROOM);
  Serial.println(tag);

}

unsigned long getRFIDTag(byte scanData[]) { //Gets the RFID tag from the specified rfid scan array
  unsigned long tag = 0;
  for (int i = 0; i < 4; i++) {
    tag *= 256; // same as tag <<= 8;
    tag += scanData[i];
  }
  return tag;
}

void AccesGranted() { //Unlock the doorlock for 5 seconds
  digitalWrite(GREENLED, HIGH);
  myservo.write(0);
  delay(5000);
  myservo.write(90);
  digitalWrite(GREENLED, LOW);
}

void AccesDenied() { //Servo position stays at 90 and a red LED blinks
  myservo.write(90);
  digitalWrite(REDLED, HIGH);
  delay(1000);
  digitalWrite(REDLED, LOW);
}
