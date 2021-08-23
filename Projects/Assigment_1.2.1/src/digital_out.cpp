#include "digital_out.h"

Digital_out::Digital_out(int pinNumber)
{
    pinMask = pinNumber;
}

void Digital_out::init()
{
    DDRB |= (1 << pinMask);
}

void Digital_out::set_hi()
{
    PORTB |= (1 << pinMask);
}

void Digital_out::set_lo()
{
    PORTB &= ~(1 << pinMask);
}

void Digital_out::toggle()
{
    PORTB = PORTB ^ (1 << pinMask);
}