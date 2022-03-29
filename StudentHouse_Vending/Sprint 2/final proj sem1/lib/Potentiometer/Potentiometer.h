#include <Arduino.h>

class Potentiometer{
    byte pin;
    int value;
    int minValue;
    int maxValue;
    int lastValue;

public:

    Potentiometer(byte pin, int minValue, int maxValue);
    void init();
    int getValue();
    void sendState();
    void sendTemperature();
    int getMaxValue();
    void sendSelectValue();
    int getLastValue();
};