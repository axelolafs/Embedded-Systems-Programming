#include "digital_in.h"
#include <avr/io.h>

Digital_in::Digital_in(int pinNumber)
{
    pinMask = 1 << pinNumber;
}

// Enables selected pin on PORTB as input and pulls it up.
void Digital_in::init()
{
    DDRB |= pinMask;
    PORTB |= pinMask;
}

bool Digital_in::is_hi()
{
    if(PINB && pinMask)
    {
        return true;
    }
    return false;
}

bool Digital_in::is_lo()
{
    if(PINB && pinMask)
    {
        return false;
    }
    return true;
}