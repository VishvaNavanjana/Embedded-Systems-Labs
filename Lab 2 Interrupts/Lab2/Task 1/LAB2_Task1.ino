#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 150

int main(){
  
  
  DDRB |= 63; //set LSB pins of PORT B  as outputs
  DDRD &= ~(1<<7);  //set PD7 pin as input
  
  unsigned char count=0;
  
  while(1){
    if(PIND & (1<<7)){//if push button is pressed
      
      _delay_ms(BLINK_DELAY_MS);
      //Reset value in PORT B
      PORTB &= 0; 
      count++;
      //display number of times the push button is pressed using LEDs
      PORTB |= count;
      
    }
  }
  
  return 0;

}