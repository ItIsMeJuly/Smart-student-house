// Constants
const int ledRed = 5;
const int ledBlue = 6;
const int switchPin = 9;
const int ledGreen = 10;
const int ledYellow = 11;
const int INTERVAL5000 = 5000;
const int INTERVAL2000 = 2000;
int maxLight = 255;
int halfLight = 127;

// Initialization
boolean lastButton = LOW;
boolean currentButton = LOW;

int ledYellowLevel = 0;
int mot_sensor1 = 2;              // the pin that the sensor is attached to
int mot_sensor2 = 3;
int stream = LOW;             // by default, no motion detected
int flushing = LOW;
int streaming = LOW;
int val = 0;                 // variable to store the sensor status (value)
int val2 = 0;
int resetTime = 0;
int passedTime = 0;
int passedWaterTime = 0;
int resetWaterTime = 0;

int hotWaterPerc = 0;       // hot water percentage
int coldWaterPerc = 0;      // cold water percentage

void setup() {
  pinMode(switchPin, INPUT); // initilize pin as input
  pinMode(ledYellow, OUTPUT); //initilize les as an output
  pinMode(ledBlue, OUTPUT);      // initalize LED as an output
  pinMode(ledRed, OUTPUT);  // initalize LED as an output
  pinMode(ledGreen, OUTPUT);  // initalize LED as an output
  pinMode(mot_sensor1, INPUT);    // initialize sensor as an input
  Serial.begin(9600);        // initialize serial

}

boolean debounce(boolean last)
{
  boolean current = digitalRead(switchPin);
  if (last != current)
  {
    current = digitalRead(switchPin);
  }
  return current;
}

/*  Button control */
void buttonControl() {
  currentButton = debounce(lastButton);

  if (lastButton == LOW && currentButton == HIGH)
  {
    ledYellowLevel = ledYellowLevel + halfLight;
  }
  lastButton = currentButton;

  if (ledYellowLevel > maxLight) ledYellowLevel = 0;
  analogWrite(ledYellow, ledYellowLevel);
}


void tapControl() {
  int potMeasure = analogRead(A5);
  unsigned long currentWaterTime = millis();
  val = digitalRead(mot_sensor1);
  
  switch(streaming) {
    case true:
      hotWaterPerc = map(potMeasure, 1, 1023, 0, 255);
      coldWaterPerc = 255 - hotWaterPerc;
      analogWrite(ledRed, hotWaterPerc);
      analogWrite(ledBlue, coldWaterPerc);  
      
      passedWaterTime = currentWaterTime - resetWaterTime;
      if ((passedWaterTime > INTERVAL2000) && (val == LOW)) { 
          streaming = false;
          Serial.println("Faucet streaming is off");
      }
      if (val == HIGH) {
        resetWaterTime = currentWaterTime;
      }
    break;
    
    case false:
      digitalWrite(ledBlue, LOW);
      digitalWrite(ledRed, LOW);
      if (val == HIGH) {
        streaming = true;
        Serial.println("Faucet streaming is on");
        resetWaterTime = currentWaterTime;
      }
    break;
    default: 
      streaming = false;
    break;
  }
}
//  Another solution for faucet
//  val = digitalRead(mot_sensor1);   // read sensor value
//  if (val == HIGH) {           // check if the sensor is HIGH
//    digitalWrite(ledBlue, HIGH);   // turn LED ON
//    digitalWrite(ledRed, HIGH);
//
//    hotWaterPerc = map(potMeasure, 1, 1023, 0, 255);
//    coldWaterPerc = 1023 - hotWaterPerc;
//
//    analogWrite(ledRed, hotWaterPerc);
//    analogWrite(ledBlue, coldWaterPerc);
//
//    if (stream == LOW) {
//      Serial.println("Faucet stream is on");
//      stream = HIGH;       // update variable stream to HIGH
//    }
//  }
//  else {
//    digitalWrite(ledBlue, LOW); // turn LED OFF
//    digitalWrite(ledRed, LOW);
//
//    if (stream == HIGH) {
//      Serial.println("Faucet stream is off");
//      stream = LOW;       // update variable stream to LOW
//    }
//  }
//}

void toiletControl () {
  unsigned long currentTime = millis();
  val2 = digitalRead(mot_sensor2);   // read sensor value
  
  switch (flushing) {
    case true:
      digitalWrite(ledGreen, HIGH);
      passedTime = currentTime - resetTime;
      if ((passedTime > INTERVAL5000) && (val2 == LOW)) {
        flushing = false;
        Serial.println("Toilet flushing is off");
      }
    break;
    case false:
      digitalWrite(ledGreen, LOW);
      if (val2 == HIGH) {
        flushing = true;
        Serial.println("Toilet flushing is on");
        resetTime = currentTime;
      }
    break;
    default: 
      flushing = false;
    break;
  }
}


// main loop
void loop() {

  // control the lights with the button
  buttonControl();

  // Tap control
  tapControl ();


  // Toilet control
  toiletControl ();
  delay(50);
}
