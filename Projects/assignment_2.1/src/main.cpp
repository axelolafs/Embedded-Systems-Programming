#include "timer.h"
#include "digital_out.h"

Digital_out LED(5);

int main(){
  Timer1_sec timer;
  timer.init(4);
  LED.init();

  while(true){
  }

  return 0;
}

ISR(TIMER1_COMPA_vect){
    LED.toggle();
}