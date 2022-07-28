#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>


unsigned char number = 0;

int main(){
  
  
  DDRB |= 63; //set LSB pins of PORT B  as outputs
  
  //PD2 and PD3 are inputs
  DDRD &= ~(1<<2);  
  DDRD &= ~(1<<3);  
  
  //set for rising edge detection for INT0 pin
  EICRA |= (1<<ISC01);
  EICRA |= (1<<ISC00);
  
  //set for rising edge detection for INT1 pin
  EICRA |= (1<<ISC11);
  EICRA |= (1<<ISC10);
  
  
  sei();//enable global interrupts
  
  EIMSK |= (1<<INT0); //enable external interrupts for int0
  EIMSK |= (1<<INT1); //enable external interrupts for int1
    
  while(1){  
    
  }
  
  return 0;

}

ISR(INT0_vect){
  //Push button B 
  
  //number is shifted once and set least bit to 1
  number = (number<<1)|1 ;
  
  PORTB = number;//display the number 

}

ISR(INT1_vect){
  //Push button A
  
  //number is shifted once
  number = (number<<1);
  
  PORTB = number; //display the number 

}





