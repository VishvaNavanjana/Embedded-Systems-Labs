#include avrio.h
#include utildelay.h

#define BLINK_DELAY_MS 500 

int main (void){

  DDRB = 0x0F;  configure pins of PORTB for output
  
while(1){
  
  turn on leds
  PORTB = 0x0F;
  _delay_ms(BLINK_DELAY_MS);
  
  
  turn off leds
  PORTB = 0x00;
   _delay_ms(BLINK_DELAY_MS);
  
  
}
}