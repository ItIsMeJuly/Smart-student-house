const int BUTTON = 7;
const int PIR = 12; // motion sensor
const int CLK = 9;  // Pin 9 to clk on encoder
const int DT = 8;  // Pin 8 to DT on encoder
const int ROOM = 1;

int RotPosition = 0; //variables to handle the encoder
int rotation = 0;
int encoderCLK = 0;
int encoderDT = 0;
bool resetEncoder = false;
bool startFade = false;
bool encoderSwitch = false;

const int LDR = A0; //light sensor

const int GREENLED1 = 2;
const int YELLOWLED1 = 3; //pwm
const int YELLOWLED2 = 4; // pwm
const int GREENLED2 = 5;

bool green1Toggle = false; //toggles for all the leds
bool yellow1Toggle = true;
bool yellow2Toggle = false;
bool green2Toggle = true;

bool ledRandomToggle = false;

String alarm; //we use this for reading the serial port
String alarmSystem;

unsigned long timeFirstGroup = 0; //mode two by two
unsigned long timeSecondGroup = 0;

unsigned long timeGreen1Led = 0; //mode one by one
unsigned long timeYellow1Led = 0;
unsigned long timeYellow2Led = 0;
unsigned long timeGreen2Led = 0;

unsigned long timeLed1Random = 0; //mode for randomized led

unsigned long movementDetectionTime = 0; //variables to handle time outs or detect movement
bool motionDetected = false;
int noMovementCounter = 0;
int breakInCounter = 0;
const int movementTimeOut = 1000 * 60 * 5;
bool waitingModeOn = true;
bool alarmSystemOn = true;

unsigned long adjustedLightTime = 0;
bool adjustedLightLast = true;
unsigned long ambientFadeTime = 0;
unsigned long gradualChangeTime = 0;
bool initLightChange = false;

unsigned long errorDetectionTime = 0;
unsigned long timeFireAlert = 0;

int BOUNCE_DELAY = 40; // button handling variables
unsigned long buttonTime = 0;
bool buttonState = false;
bool lastButtonState = false;

enum lightModes { //using enums for the sequence state pattern to improve readability
  WAITING, AMBIENT, MANUAL, MOOD, TWOBYTWO, FADE, RANDOM, ALERT
};

lightModes currentLightMode = WAITING; //we use this to switch between states

lightModes lastLightMode = AMBIENT; //remember last state, go into it after timeout

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(GREENLED1, OUTPUT);
  pinMode(YELLOWLED1, OUTPUT);
  pinMode(YELLOWLED2, OUTPUT);
  pinMode(GREENLED2, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(PIR, INPUT);
  rotation = digitalRead(CLK);

  Serial.begin(9600);
}


void TurnOffAllLeds() { //function to turn off all leds and reset timers. Used with every button press to keep the behaviour consistent
  digitalWrite(GREENLED1, LOW);
  digitalWrite(YELLOWLED1, LOW);
  digitalWrite(YELLOWLED2, LOW);
  digitalWrite(GREENLED2, LOW);

  timeGreen1Led = millis();
  timeYellow1Led = millis();
  timeYellow2Led = millis();
  timeGreen2Led = millis();
}

int ReadEncoder () {
  encoderCLK = digitalRead(CLK);
  encoderDT = digitalRead(DT);

  if (resetEncoder) {
    RotPosition = 0;
    resetEncoder = false;
  }
  if (encoderCLK != rotation) { // we use the DT pin to find out which way we are turning
    noMovementCounter = 0;
    if (encoderDT != encoderCLK) {  // clockwise
      if (RotPosition > -20)
        RotPosition --;
    } else { //counterclockwise
      if (RotPosition < 0) {
        RotPosition++;
      }
    }
    rotation = encoderCLK;
  }
  return RotPosition;
}

bool ButtonPressed() { // boolean function that returns true if a button has been pressed
  bool buttonPressed = false;
  int readButtonPressed = digitalRead(BUTTON);

  if (readButtonPressed != lastButtonState) {
    buttonTime = millis();
  }
  if (millis() - buttonTime > BOUNCE_DELAY) {
    if (buttonState != readButtonPressed) {
      buttonState = readButtonPressed;
      if (lastButtonState == LOW) {
        noMovementCounter = 0;
        buttonPressed = true;
        TurnOffAllLeds();
        resetEncoder = true;
        RotPosition = 0;
        ResetToggles();
      }
    }
  }
  lastButtonState = readButtonPressed;
  return buttonPressed;
}

void ResetToggles() { //resetting toggles when switching between states to avoid inconsistencies with party mode when switching back and forth.
  green1Toggle = false;
  yellow1Toggle = true;
  yellow2Toggle = false;
  green2Toggle = true;
}

int RandomizeLed() { //function that randomly chooses a LED
  int RNG = random(0, 4); //randomly get a number between 0 and 3
  int ledPin = 0;
  switch (RNG) { //assign the number to a led pin
    case 0:
      ledPin = GREENLED1;
      break;
    case 1:
      ledPin = YELLOWLED1;
      break;
    case 2:
      ledPin = YELLOWLED2;
      break;
    case 3:
      ledPin = GREENLED2;
      break;
  }
  return ledPin;
}

void loop() {
  unsigned long currentTime = millis();
  bool readMotionSensor = digitalRead(PIR);

  if (Serial.available()) { //check if the alarm has been triggered via the serial port
    alarm = Serial.readStringUntil('\n');
    if (alarmSystemOn) { //default for the alarm system is on, but can be turned off manually by the reception
      if (alarm == "AlarmOn"); { /*the alarm gets triggered either because the room has not been claimed by anybody and the reception triggers it
                             OR the fire alarm system detects a fire*/
        currentLightMode = ALERT;
      }
      if (alarm == "AlarmOff") { //can be turned off manually by the fire alarm system with a button press
        TurnOffAllLeds();
        currentLightMode = lastLightMode;
      }
    }
    if (alarm == "R- Alarm off") { //reception manually turns OFF alarm
      alarmSystemOn = false;
    }
    if (alarm == "R- Alarm on") { //reception manually turns ON alarm
      alarmSystemOn = true;
    }
  }

  if (readMotionSensor) { // movement has been detected here
    noMovementCounter = 0;
    if (!motionDetected) {
      breakInCounter++;
      motionDetected = true;
    }
    if (breakInCounter == 1 && currentLightMode == WAITING) { //the system sends a message to the reception if somebody enters the room
      Serial.println(ROOM);
      breakInCounter = 0;
    }
  }
  else { //no movement has been detected here
    if (motionDetected) {
      motionDetected = false;
    }
    if (currentTime - movementDetectionTime > 2000) { //increment inactivity counter by 1 every 2 seconds
      noMovementCounter++;
      movementDetectionTime = currentTime;
    }
    if (noMovementCounter == 5) { //once inactivity counter reaches 5 the system falls asleep and waits for movement again
      breakInCounter = 0;
      waitingModeOn = true;
    }
  }

  int partyLightSpeed = ReadEncoder() * 15; //adjustable speeds and light values for all modes
  int twoByTwoLightSpeed = partyLightSpeed + 500;
  int fadeLightSpeed = partyLightSpeed + 525;
  int randomLightSpeed = partyLightSpeed + 400;
  int manualLightValue = ReadEncoder() * -12; //write this value on the PWM pin to manually adjust the LED

  int lightLevelRoom = analogRead(LDR);
  int adjustedLightLevel = map(lightLevelRoom, 0, 1023, 255, 0);
  int adjustedLightLevelLast = map(lightLevelRoom, 0, 1023, 255, 0);
  if (currentTime - adjustedLightTime > 1500) { // this if statement keeps track of the
    adjustedLightLast = !adjustedLightLast;
    if (adjustedLightLast) {
      adjustedLightLevelLast = adjustedLightLevel;
    }
    else {
      adjustedLightLevel = map(lightLevelRoom, 0, 1023, 255, 0); // map LDR so we can write the value on the PWM pin
    }
  }

  switch (currentLightMode) { // sequence state pattern for all the modes. We switch between modes with a button click
    case WAITING:
      currentLightMode = WAITING;
      noMovementCounter = 0;
      encoderCLK = digitalRead(CLK);
      encoderDT = digitalRead(DT);
      TurnOffAllLeds();
      waitingModeOn = true;
      if ((readMotionSensor || ButtonPressed()) || encoderCLK != rotation) { //go into last mode if a user interacts with the system or if a movement has been detected
        waitingModeOn = false;
        currentLightMode = lastLightMode;
      }
      break;
    case AMBIENT: // ambient mode, adjusts led strength so that illumination in the room remains the same at all times
      lastLightMode = AMBIENT;

      if (currentTime - errorDetectionTime > 2000) {
        initLightChange = true;
        errorDetectionTime = currentTime;
      }

      if (initLightChange) {
        initLightChange = false;
        analogWrite(YELLOWLED1, adjustedLightLevel);
      }

      if (waitingModeOn) {//if no movement has been detected this mode times out and goes to the waiting state
        currentLightMode = WAITING;
      }
      if (ButtonPressed()) { //switch to next mode if the button has been pressed
        resetEncoder = true;
        //        TurnOffAllLeds();
        currentLightMode = MANUAL;
      }
      break;
    case MANUAL: //mode to adjust manually adjust light level in the room
      lastLightMode = MANUAL;
      analogWrite(YELLOWLED1, manualLightValue);

      if (waitingModeOn) {//if no movement has been detected this mode times out and goes to the waiting state
        currentLightMode = WAITING;
      }
      if (ButtonPressed()) { //switch to next mode if the button has been pressed
        currentLightMode = TWOBYTWO;
      }
      break;
    case TWOBYTWO: // a type of party mode where two lights blink at a time
      lastLightMode = TWOBYTWO;
      if (currentTime - timeFirstGroup > twoByTwoLightSpeed) { //check if enough time has passed
        green1Toggle = !green1Toggle; // flip state
        yellow1Toggle = !yellow1Toggle;
        yellow2Toggle = !yellow2Toggle;
        green2Toggle = !green2Toggle;
        timeFirstGroup = currentTime; // save current time for next check
      }
      digitalWrite(GREENLED1, green1Toggle);
      digitalWrite(YELLOWLED1, yellow1Toggle);
      digitalWrite(YELLOWLED2, yellow2Toggle);
      digitalWrite(GREENLED2, green2Toggle);

      if (waitingModeOn) { //if no movement has been detected this mode times out and goes to the waiting state
        currentLightMode = WAITING;
      }
      if (ButtonPressed()) { //switch to next mode if the button has been pressed
        ResetToggles();
        currentLightMode = FADE;
      }
      break;
    case FADE: //fade mode, leds light up in order, one by one, turning all of once the after the last led lights up
      lastLightMode = FADE;
      if (currentTime - timeGreen1Led > fadeLightSpeed ) {
        digitalWrite(GREENLED1, HIGH);
      }
      if (currentTime - timeYellow1Led > fadeLightSpeed * 2) {
        digitalWrite(YELLOWLED1, HIGH);
      }
      if (currentTime - timeYellow2Led > fadeLightSpeed * 3) {
        digitalWrite(YELLOWLED2, HIGH);
      }
      if (currentTime - timeGreen2Led > fadeLightSpeed * 4) {
        digitalWrite(GREENLED2, HIGH);
      }
      if (currentTime - timeGreen2Led > fadeLightSpeed * 5) {
        TurnOffAllLeds();
      }

      if (waitingModeOn) { //if no movement has been detected this mode times out and goes to the waiting state
        currentLightMode = WAITING;
      }
      if (ButtonPressed()) { //switch to next mode if the button has been pressed
        currentLightMode = RANDOM;
      }
      break;
    case RANDOM: //mode that turns on and off random leds
      lastLightMode = RANDOM;
      if (currentTime - timeLed1Random > randomLightSpeed) {
        ledRandomToggle = !ledRandomToggle;
        digitalWrite(RandomizeLed(), ledRandomToggle); //call RandomizeLed() function to select a random pin to write on
        timeLed1Random = currentTime;
      }

      if (waitingModeOn) {
        currentLightMode = WAITING;
      }
      if (ButtonPressed()) { //switch to next mode if the button has been pressed
        currentLightMode = AMBIENT;
      }
      break;
    case ALERT: //the system only goes in this mode when a certain string has been received by the fire alarm system
      if (currentTime - timeFireAlert > 500) {
        green1Toggle = !green1Toggle;
        yellow1Toggle = !yellow1Toggle;
        yellow2Toggle = !yellow2Toggle;
        green2Toggle = !green2Toggle;

        timeFireAlert = currentTime;
      }
      digitalWrite(GREENLED1, green1Toggle);
      digitalWrite(YELLOWLED1, !yellow1Toggle);
      digitalWrite(YELLOWLED2, yellow2Toggle);
      digitalWrite(GREENLED2, !green2Toggle);

      if (ButtonPressed() || !alarmSystemOn) { //the alarm lights go off only by button press OR when receiving a string that turns off the boolean 'alarmSystemOn'
        TurnOffAllLeds();
        ResetToggles();
        currentLightMode = lastLightMode;
      }
      break;
  }
}
