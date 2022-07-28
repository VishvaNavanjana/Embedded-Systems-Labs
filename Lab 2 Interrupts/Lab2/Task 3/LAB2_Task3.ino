#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 200

unsigned char count = 0;

int main(){
  
  
  DDRB |= 63; //set LSB pins of PORT B  as outputs
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
  
  PORTB &= 0;//Reset value in PORT B
  count++;
  //_delay_ms(BLINK_DELAY_MS);
  //display number of times the push button is pressed
  PORTB |= count;

}







