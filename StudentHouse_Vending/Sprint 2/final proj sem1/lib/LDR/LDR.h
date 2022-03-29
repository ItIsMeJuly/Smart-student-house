#include "Arduino.h"

class LDR{
    byte pin;
    int value;

public:

    LDR(byte pin);
    void init();
    int readValue();
};