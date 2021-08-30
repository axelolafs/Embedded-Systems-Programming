#include "timer.h"

Timer1_sec::Timer1_sec(int msec){
    compareReg = (16000 / 64) * msec - 1;
}
void Timer1_sec::init(){
    // Set prescalar
    //TCCR1B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
    TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);

    //OCR1A = (16000000 / 1024) * sec - 1;
    OCR1A = compareReg;
    OCR1B = compareReg / 2;

    // CTC mode
    TCCR1B |= (0 << WGM13) | (1 << WGM12);
    
    //Enable Output compare interrupt for A and B
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);
    sei();

}
void Timer1_sec::dutyCycle(int pct){
    OCR1B = int(compareReg * (pct/100.0));
}
