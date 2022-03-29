#include "LDR.h"

LDR::LDR(byte pin): pin{pin}{
    init();
}

void LDR::init(){
    pinMode(pin, INPUT);
}

//read the value from the LDR
int LDR::readValue(){
    return analogRead(pin);
}