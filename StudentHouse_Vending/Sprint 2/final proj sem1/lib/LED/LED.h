#include <Arduino.h>

class LED{
    byte pin;
    int value;
    int counter;

public:

    LED(byte pin);
    void init();
    void on();
    void off();
    int getCounter();
    int getValue();
    void eraseCounter();
};

class Indicator{
    LED* Red;
    LED* Yellow;
    LED* Green;

public:

    Indicator(int red, int yellow, int green);

    void microwaveBlinks();
    void indicateTemperature(int temp, int maxTemp);
    void clear();
    LED* getRed();
    LED* getGreen();

    ~Indicator();
};