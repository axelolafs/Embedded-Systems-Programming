#ifndef TIMER1_SEC_H
#define TIMER1_SEC_H
#include <avr/io.h>
#include <avr/interrupt.h>

class Timer1_sec
{
    public:
        Timer1_sec();
        void init(int sec);
};


#endif // TIMER1_1SEC_H



