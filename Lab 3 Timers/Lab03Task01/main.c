#include <avr/io.h>

void delay_timer0(){
  /* 2ms delay

     T = 256/16 = 16
     increments =2000/16
                =125
     initial counter value = 256-125
                           = 131

  */

  TCNT0 = 131;  //Load timer counter register

  TCCR0A = 0x00; //Set Timer0 under normal mode with 1:256 prescaler    
  TCCR0B = 0x04;

  while((TIFR0&0X01)==0); //Wait till timer overflow bit is set

  TCCR0A = 0x00; //Clear timer settings to stop the timer
  TCCR0B = 0x00;

  TIFR0 = 0x01; //Clear the timer overflow bit for next round

}

int main (void){

  DDRB = DDRB | (1<<5); //Configure pin 5 of PORTB for output

  while(1){
    PORTB = PORTB ^ (1<<5); //Toggle pin 5
    delay_timer0();
  }

}
