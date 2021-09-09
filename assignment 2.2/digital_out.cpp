#include "digital_out.h"
#include <avr/io.h>

Digital_out::Digital_out(int pinNumber)
{
    pinMask = 1 << pinNumber;
}

void Digital_out::init()
{
    DDRB = pinMask;
}

void Digital_out::set_hi()
{
    PORTB = pinMask;
}

void Digital_out::set_lo()
{
    PORTB &= ~pinMask;
}

void Digital_out::toggle()
{
    PORTB = PORTB ^ pinMask;
}