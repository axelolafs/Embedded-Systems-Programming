
// Implementation for part 1
/*
#include <util/delay.h>
#include <avr/io.h>

int main()
{
  DDRB |= (1<<0);
  while(true)
  {
    PORTB = PORTB ^ (1<<0);
    _delay_ms(500);
  }
}
*/

// Implementation for part 2
/*
#include <util/delay.h>
#include "digital_out.h"

int main()
{
    //Initialize output on PB0
    Digital_out output(0);
    output.init();
    while(true)
    {
        output.toggle();
        _delay_ms(200);
    }
}
*/


// Implementation of part 3

#include <util/delay.h>
#include "digital_out.h"
#include "Digital_in.h"

int main(){
  // LED on PB0 and BUTTON on PB1
  Digital_out LED(0);
  Digital_in BUTTON(1);

  LED.init();
  BUTTON.init();
  
  while(true){
    _delay_ms(150);
    if(BUTTON.is_lo())
    {
      LED.set_lo();
    }
    else LED.toggle();
  }
}
