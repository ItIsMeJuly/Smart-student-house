#include "Button.h"

//if the button is pressed, the method sends true or else false
bool Button::checkClick(){
    int read = digitalRead(pin);
    if(read != lastRead){
        if(read == HIGH){
            return true;
        }
    }
    return false;
}

void Button::init(){
    pinMode(pin, INPUT);
}

Button::Button(byte pin) : pin(pin){
    init();
}