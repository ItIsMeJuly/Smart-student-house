#include "Adafruit_CCS811.h"
Adafruit_CCS811 ccs;

const int REDLED = 4;
const int BUZZER = 2;
const int BUTTON = 3;
const int INTERVAL4 = 4;
const int INTERVAL10 = 10;
const int INTERVAL500 = 500;
const int INTERVAL3000 = 3000;
const int INTERVAL60000 = 6000;

unsigned long previousTTime = 0;
unsigned long previousATime = 0;
unsigned long previousMTime = 0;
unsigned long previousPTime = 0;
unsigned long previousBTime = 0;

bool isAlarmOn = false;
bool isManualAlarmOn;
bool printOnce = true;
bool printAlarmOnce = false;
bool putAlarmOn = true;
bool isBurglarAlarmOn = false;
bool isUnder1300 = true;
int lastButtonAlarmState = LOW;
int redledState = LOW;
int redledAState = LOW;
int frequency = 700;


void setup() {
  Serial.begin(9600);
  pinMode (REDLED, OUTPUT);
  pinMode (BUTTON, INPUT);
  pinMode (BUZZER, OUTPUT);
  if (!ccs.begin()) {
    Serial.println("Failed to start sensor! Check the wiring.");
  }
}

void loop() {
  unsigned long currentTime = millis();

  int CO2 = ccs.geteCO2();
  int TVOC = ccs.getTVOC();
  if (ccs.available()) {
    if (!ccs.readData()) {
    }
  }

  String line;
  if (Serial.available())
  {
    line = Serial.readStringUntil('\n'); //Read message sent from the serialport
    if (line == "R- Alarm on") {
      putAlarmOn = true;
    }
    else if (line == "R- Alarm off") {
      putAlarmOn = false;
      isBurglarAlarmOn = false;
      digitalWrite(REDLED, LOW);
      noTone(BUZZER);
      frequency = 700;
    }
    else if (line == "killBurglar") {
      isBurglarAlarmOn = true;
    }
  }

  if (putAlarmOn) { //Switch alarmstate if boolean is switched
    Alarm();
    ManualAlarm();
  } else {
    isManualAlarmOn = false;
    isAlarmOn = false;
  }

  if (isBurglarAlarmOn)  {
    if (currentTime - previousBTime > INTERVAL4) //Make Red LED blink
    {
      BurglarAlarm();
      previousBTime = currentTime;
    }
  }

  if (isManualAlarmOn == true) {
    if (currentTime - previousTTime > INTERVAL500) //Make Red LED blink
    {
      AlarmSound();
      previousTTime = currentTime;
    }
  }

  if (isAlarmOn || isManualAlarmOn) //Print message if alarm is on
  {
    if (printOnce) {
      Serial.println("AlarmOn");
      printOnce = false;
    }
  }

  if (!isManualAlarmOn && !isAlarmOn) //Print message if alarm is off
  {
    if (!printOnce) {
      if (currentTime - previousPTime > INTERVAL3000)
      {
        Serial.println("AlarmOff");
        printOnce = true;
        previousPTime = currentTime;
      }
    }
    digitalWrite(REDLED, LOW);
  }

}


void Alarm() //If sensor senses to much CO2 particles
{
  unsigned long currentTime = millis();
  int CO2 = ccs.geteCO2();
  if (CO2 >= 10000) //Execute only if CO2 levels are high
  {
    isAlarmOn = true;
    if (currentTime - previousATime > INTERVAL500) //Make Red LED blink
    {
      AlarmSound();
      previousATime = currentTime;
    }
  } else
  {
    isAlarmOn = false;
  }
}


void ManualAlarm()
{
  unsigned long currentTime = millis();
  int button2State = digitalRead(BUTTON); //Turn on alarm manually
  if (button2State != lastButtonAlarmState)
  {
    if (button2State == HIGH && !isAlarmOn)
    {
      if (currentTime - previousMTime > INTERVAL10) {
        previousMTime = currentTime;
      }
      button2State = digitalRead(BUTTON);
      if (button2State == HIGH)
      {
        isManualAlarmOn = !isManualAlarmOn;
      }
    }
    lastButtonAlarmState = button2State;
  }
}

void AlarmSound() {
  redledState = !redledState;
  digitalWrite(REDLED, redledState);
  tone(BUZZER, 1200, 250);
  tone(BUZZER,  800, 250);
}

void BurglarAlarm() {
  if (isUnder1300)
  {
    if (frequency < 1300)
    {
      frequency++;
      Serial.println(frequency);
      tone(BUZZER, frequency);
    } else {
      isUnder1300 = false;
    }
  } else {
    if (frequency > 700)
    {
      frequency--;
      Serial.println(frequency);
      tone(BUZZER, frequency);
    } else {
      isUnder1300 = true;
    }
  }
}
