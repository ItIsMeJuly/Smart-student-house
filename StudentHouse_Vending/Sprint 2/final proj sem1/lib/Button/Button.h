#include <Arduino.h>

class Button{
    byte pin;
    int lastRead = LOW;

public:     

    Button(byte pin);
    void init();

    bool checkClick();
};