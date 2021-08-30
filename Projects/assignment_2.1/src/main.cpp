#include "timer.h"
#include "digital_out.h"

Digital_out LED(0);

int main(){
  Timer1_sec timer(20);
  timer.init();
  LED.init();
  timer.dutyCycle(10);

  while(true){
  }

  return 0;
}

ISR(TIMER1_COMPA_vect){
    LED.set_hi();
}

ISR(TIMER1_COMPB_vect){
    LED.set_lo();
}
