#ifndef TIMER1_SEC_H
#define TIMER1_SEC_H
#include <avr/io.h>
#include <avr/interrupt.h>

class Timer1_sec
{
    public:
        Timer1_sec(int msec);
        void init();
        void dutyCycle(int pct);
    private:
        int compareReg;
};


#endif // TIMER1_1SEC_H



