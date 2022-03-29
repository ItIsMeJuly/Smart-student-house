#include <Arduino.h>
#include "LED.h"
#include "Potentiometer.h"
#include "RotaryEncoder.h"
#include "Button.h"
#include "MFRC522.h"
#include "SPI.h"
#include "LDR.h"

//constants for the RFID
#define SS_PIN 10
#define RST_PIN 9

//The sensors and actuators as objects
RotaryEncoder *rot = new RotaryEncoder(8, 7, 4);
Button *vend = new Button(5);
Potentiometer *temperature = new Potentiometer(15, 0, 1000);
Potentiometer *selector = new Potentiometer(14, 0, 10);
LDR *light = new LDR(16);
LED *green = new LED(3);
Indicator *indic = new Indicator(2, 5, 3);
MFRC522 mfrc522(SS_PIN, RST_PIN);

//time variables
long long startTime;
long long potentTime;
long long LedTime;
long long cur;

//flags for the functions and loop
bool ledFlag = false;
bool Flag = NULL;
bool innerLoop = false;
bool microFlag = false;

//the content that is read from the chip/card
String content = ""; //reading from the chip

//function to return a package ready to be sent to the C# app
String timeRemaining(long time)
{
  const String literal = "dur";
  String timeRemaining = literal + time + literal;
  return timeRemaining;
}

void setup()
{
  Serial.begin(9600);
  startTime = millis();
  potentTime = millis();
  cur = millis();
  SPI.begin();
  mfrc522.PCD_Init();
}

//blinks the green led without delays
void greenBlinks()
{
  if (green->getCounter() < 2)
  {
    if (green->getValue() == LOW)
    {
      green->on();
    }
    else if (green->getValue() == HIGH)
    {
      green->off();
    }
  }
  else{
    ledFlag = false;
    green->eraseCounter();
  }
}

//blinks the red led 3 times without delays
void microwaveBlinks(Indicator* c){
  if(c->getRed()->getCounter() < 6){
    if(c->getRed()->getValue() == LOW){
      c->getRed()->on();
    }
    else{
      c->getRed()->off();
    }
  }
  else{
    microFlag = false;
    c->getRed()->eraseCounter();
  }
}

void loop()
{
  //if the arduino sends a close statement, the arduino program goes to its initial state
  if (Serial.available())
  {
    if (Serial.readString() == "close")
    {
      innerLoop = false;
    }
  }
  if (innerLoop == false) //the card reading is done only if there is no authorized access
  {
    if (!mfrc522.PICC_IsNewCardPresent())
    {
      return;
    }

    if (!mfrc522.PICC_ReadCardSerial())
    {
      return;
    }

    content = "";
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
  }

  if (content.substring(1) == "19 F6 77 C2" || innerLoop == true)
  {
    //if the correct chip is read, we get into the main loop
    if (rot->readRotation(Flag)) // if a value is read from the rotary encoder, we send the data through the serial comunication port
    {
      rot->sendTime();
    }
    if (innerLoop == false)
    {
      Serial.println("open"); //if we get into the main loop, the arduino sends a signal to the C# to show the panels
    }
    innerLoop = true;
    if (millis() - potentTime > 200)
    { 
      //every 200ms we call the red blinks without delays and also send the product number and temperature
      if(microFlag){
        microwaveBlinks(indic);
      }
      selector->sendSelectValue();
      temperature->sendTemperature();
      potentTime = millis();
    }
    
    //if the button is pressed, we send the number we want to pick and if the product is available the green led blinks.
    //i have dalay here because it is not stopping any part of the program
    if (vend->checkClick())
    {
      Serial.println(selector->getValue());
      String ret = Serial.readString();
      Indicator *indic = new Indicator(2, 5, 3);
      //we are reading information from the pc and the arduino processes it
      if (ret == "true")
      {
        LED *copy = indic->getGreen();
        copy->on();
        delay(250);
        copy->off();
      }
    }



    //this is the microwave

    //every 300ms we send the temperature to the serial port
    if (millis() - startTime > 300)
    {
      temperature->sendTemperature();
      startTime = millis();
    }
    //if we press the button on the rotary encoder and the LDR does not pick much light(the door is closed),
    //the timer for the microwave starts
    if (rot->checkClick() && light->readValue() < 300)
    {
      unsigned long long duration = rot->getTime() * 1000 + startTime; //calculate the total duration that has been set
      startTime = millis();
      unsigned long current = 0;
      while (millis() <= duration) //while the timer is not equal to 0, we stay in this for loop
      {
        if (rot->readRotation(Flag)) //now if a movement on the rotary encoder is detected, only the duration changes
        {
          if (Flag == true) //rotation to the right
          {
            duration += 1000; 
          }
          else //rotation to the left
          {
            duration -= 1000; 
          }
          Serial.println(timeRemaining((duration - startTime) / 1000)); //then we send the time ramaining to the visual studio app
        }
        //we have the code for the vending here, because now the vending is out of scope and we need to 
        //place the same function in the while block
        selector->sendSelectValue();
        if (vend->checkClick())
        {
          Serial.println(selector->getValue());
          String ret = Serial.readString();
          //we are reading information from the pc and the arduino processes it
          if (ret == "true")
          {
            ledFlag = true; //we set the ledFlag to true to start the blinks without delays
          }
        }

        if (millis() - startTime > 300) //send information every 300ms to not overwhelm the serial port
        { 
          if(ledFlag){  //if the ledFlag is true the green led blinks without interupting the flow of the program
            greenBlinks(); 
          }
          temperature->sendTemperature(); //we send the temperature to the serial port
          Serial.println(timeRemaining((duration - startTime) / 1000)); //we send the time remaining to serial port
          startTime = millis();
          if (light->readValue() > 350) //if the LDR detect light (the door is open), the RED led turn on and
          //we can change the temperature and pick items from the vending while the door is open (does not block the program)
          {
            indic->getRed()->on();
            while (light->readValue() > 350)
            {
              temperature->sendTemperature();
              if(ledFlag){
                greenBlinks();
              }
              if (rot->readRotation(Flag))
              {
                if (Flag == true)
                  duration += 1000;
                else
                  duration -= 1000;
                Serial.println(timeRemaining((duration - startTime) / 1000));
              }
              selector->sendSelectValue();
              if (vend->checkClick())
              {
                Serial.println(selector->getValue()); //we are reading information from the pc and the arduino processes it
                String ret = Serial.readString();
                if (ret == "true")
                {
                  ledFlag = true;
                }
              }
            }
            indic->getRed()->off();
            current = millis();   //nullify the difference in time when the stop occurs
            current -= startTime; //we count the time for which the timer was stopped and then we subtract it
            duration += current;  //new duration;
          }
          startTime = millis();
        }
        ///current = lastPoint;
      }
      microFlag = true; //when the timer finishes, the flag sets to true and the microwave red led blinks 
    }
  }
  else
  {
    Serial.println("Access denied"); //if the card is not authorized we send access denied
    delay(1000);
  }
}
