#include <Arduino.h>
#include "fifo.h"
#include "digital_out.h"

void timerIntSecond();
Fifo fifo;
Digital_out LED(5);


int main(){
  init();
  Serial.begin(9600);
  int serialData;
  timerIntSecond();

  while(1){
    if(fifo.is_full()){
      LED.set_hi();
    }
    else{
      LED.set_lo();
      if (Serial.available() > 0) {
        serialData = Serial.read();
        fifo.put(serialData);
      }
    }
  }
  return 0;
}

void timerIntSecond(){
  TCCR1B = 0;
  TCCR1A = 0;
  TIMSK1 = 0;
  // prescaler to 1024 and CTC mode
  TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
  
  // Compare on a second interval
  OCR1A = (16000000/1024) - 1;
  // enable interrupt for compare register 1 A
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

ISR(TIMER1_COMPA_vect){
  if (!fifo.is_empty()){
    fifo.get();
  }
}