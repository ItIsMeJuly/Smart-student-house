#include "Arduino.h"

class RotaryEncoder{
    byte btnPin;
    byte dataPin;
    byte clkPin;
    int value;
    int clkPinLastRead;
    int currentRead;
    int lastBtnState;

public:

    RotaryEncoder(byte btnPin, byte dataPin, byte clkPin);

    void init();
    bool readRotation(bool & flag);
    bool checkClick();
    int sendReal();
    String send();
    void sendTime();
    int getTime();
    int getValue();
};