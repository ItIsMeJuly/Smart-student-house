#include "RotaryEncoder.h"

int RotaryEncoder::getValue(){
    return value;
}

void RotaryEncoder::init(){
    pinMode(btnPin, INPUT_PULLUP);
    pinMode(dataPin, INPUT);
    pinMode(clkPin, INPUT);

    clkPinLastRead = digitalRead(clkPin);
    lastBtnState = digitalRead(btnPin);
}

//if a rotation is read, only then the function return true and this is an optimisation to limit data transfer through the serial port
//v2 - added flag system to detect clockwise or counterclockwise rotation to support the microwave
bool RotaryEncoder::readRotation(bool & Flag){
    bool flag = false;
    currentRead = digitalRead(clkPin);
    if(clkPinLastRead == LOW && currentRead == HIGH){
        if(digitalRead(dataPin) != currentRead){
            ++value;
            Flag = true;
        }
        else{
            if(value > 0){
                --value;
            }
            Flag = false;
        }
        flag = true;
    } 
    clkPinLastRead = currentRead;
    return flag;
}


RotaryEncoder::RotaryEncoder(byte btnPin, byte dataPin, byte clkPin){
    this->btnPin = btnPin;
    this->clkPin = clkPin;
    this->dataPin = dataPin;
    value = 0;
    
    init();
}

//we check if the button on the encoder was pressed
bool RotaryEncoder::checkClick(){
    int currentRead = digitalRead(btnPin);

    if(currentRead != lastBtnState){
        if(currentRead == LOW){
            lastBtnState = currentRead;
            return true;
        }
    }
    lastBtnState = currentRead;
    return false;
}


//the methods below are formating data to transfer it to the C# application
String RotaryEncoder::send(){
    const String literal = "no";
    String text = literal + value + literal; 
    return text;
}

int RotaryEncoder::sendReal(){
    return value;
}

void RotaryEncoder::sendTime(){
    const String literal = "time";
    String text = literal + value + literal;
    Serial.println(text);
}

int RotaryEncoder::getTime(){
    return value;
}