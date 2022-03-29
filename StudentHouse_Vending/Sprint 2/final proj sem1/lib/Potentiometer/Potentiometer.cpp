#include "Potentiometer.h"

void Potentiometer::init()
{
    pinMode(pin, INPUT);
}

Potentiometer::Potentiometer(byte pin, int minValue, int maxValue)
{
    this->pin = pin;
    this->maxValue = maxValue;
    this->minValue = minValue;
    lastValue = 0;

    init();
}

int Potentiometer::getValue()
{
    value = analogRead(pin);
    value = map(value, 0, 990, minValue, maxValue);
    return value;
}

//we read the value form the pin and if the value is the same we dont send the data. Else we send the data with a header
void Potentiometer::sendSelectValue()
{
    value = analogRead(pin);
    value = map(value, 0, 1000, minValue, maxValue);
    if (value != lastValue)
    {
        String lit = "no";
        String text = lit + value + lit;
        Serial.println(text);
        lastValue = value;
    }
}

//methods below format the data in order to send it to the C# application
void Potentiometer::sendState()
{
    const String literal = "state";
    String text = literal + value + literal;
    Serial.println(text);
}

//we read a value from the pin and if it is the same the last value or just bouncing, we dont send it to the serial port
void Potentiometer::sendTemperature()
{
    int value = analogRead(pin);
    value = map(value, 0, 1000, minValue, maxValue);
    if (!((value < lastValue + 3 && value > lastValue - 3) || value == lastValue))
    {
        const String literal = "temp";
        String text = literal + value + literal;
        Serial.println(text);
        lastValue = value;
        delay(50); //delay to debounce a little
    }
}

int Potentiometer::getMaxValue()
{
    return maxValue;
}

int Potentiometer::getLastValue()
{
    return lastValue;
}