#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//#define BLINK_DELAY_MS 200

int main(){
  
  
  DDRB |= (1<<0); //PB0 is output
  DDRD &= ~(1<<2);  //PD2 is input
  
  //set for falling edge detection
  EICRA |= (1<<ISC01);
  EICRA |= (0<<ISC00);
  
  sei();//enable global interrupts
  
  EIMSK |= (1<<INT0); //enable external interrupts for int0
  
    
  while(1){  
    
  }
  
  return 0;

}

ISR(INT0_vect){
  PORTB ^= (1<<0);//toggle bit 0 of PORT B
 // _delay_ms(BLINK_DELAY_MS);

}







