#include "timer.h"

Timer1_sec::Timer1_sec(){

}
void Timer1_sec::init(){
    // Prescaler set to 1024
    TCCR1B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
    OCR1A = 16000000 / 1024 - 1;
    // Clear OC0A on compare match
    TCCR1B |= (1 << WGM12);
    TIMSK1 |= (1 << OCIE1A);
    sei();

}