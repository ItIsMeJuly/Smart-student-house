#include "LED.h"

void LED::init(){
    pinMode(pin, OUTPUT);
    value = LOW;
    counter = 0;
}

LED::LED(byte pin){
    this->pin = pin;

    init();
}

void LED::on(){
    digitalWrite(pin, HIGH);
    value = HIGH; //sets the last value to HIGH
    counter++; //counts the total operations the current object has done
}

void LED::off(){
    digitalWrite(pin, LOW);
    value = LOW; //sets the last value to LOW
    counter++; //count the total operation the current object has done
}

int LED::getCounter(){
    return counter;
}

int LED::getValue(){
    return value;
}

void LED::eraseCounter(){
    counter = 0;
}

//-----------------------------------------------------------------------------------------

//INDICATIOR is supplied to simplify the microwave 
Indicator::Indicator(int red, int yellow, int green): Red(new LED(red)), Yellow(new LED(yellow)), Green(new LED(green)){}

void Indicator::clear(){
    Red->off();
    Yellow->off();
    Green->off();
}

void Indicator::microwaveBlinks(){
    for(int i = 0 ; i < 3 ; i++){
        Red->off();
        delay(500);     //I am using delay because I want to block the main loop from continuing with 
        Red->on();     //further tasks and possibly messing the functionality of the LEDs (for example
        delay(500);                //starting the microwave again, while the red light still blinks)
    }
}

//makes light indication on how hot is the microwave. We have 3 lights for 3 levels of heat
/*void Indicator::indicateTemperature(int temperature, int maxTemperature){
    if(temperature < maxTemperature / 3){
        Green->on();
        Yellow->off();
        Red->off();
    }
    else if(temperature > maxTemperature / 3 && temperature < (maxTemperature / 3) * 2){
        Yellow->on();
        Green->off();
        Red->off();
    }
    else{
        Red->on();
        Yellow->off();
        Green->off();
    }
}*/

//RAII but with no cpy construction because i am just not using it in this project and just wastes space in the RAM of the arduino
Indicator::~Indicator(){
    clear();
    delete Red;
    delete Yellow;
    delete Green;
}

//getters
LED* Indicator::getRed(){
    return Red;
}

LED* Indicator::getGreen(){
    return Green;
}