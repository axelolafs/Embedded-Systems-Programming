
// Implementation for part 1
/*
#include <util/delay.h>
#include <avr/io.h>

int main()
{
  DDRB = (1<<0);
  while(true)
  {
    PORTB = PORTB ^ (1<<0);
    _delay_ms(500);
  }
}
*/

// Implementation for part 2
#include <util/delay.h>
#include "digital_out.h"

int main()
{
    //Initialize output on PB0
    Digital_out output(0);

    while(true)
    {
        output.toggle();
        _delay_ms(500);
    }
}