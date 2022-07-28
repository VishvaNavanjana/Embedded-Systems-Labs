/*
Duty Cycle = (OCR0A+1)/256 x 100
50 = (OCR0A+1)/256 x 100
OCR0A = 127

F_generated_wave = F_oscillator/(256 x N)
976.56Hz = 16MHz/(256 x N)
N = 64 
*/


#include <avr/io.h>

int main() {
  
  //Configure pin 6 and 7 of PORTD for output
  DDRD |= (1<<6); 
  DDRD |= (1<<7); 
  
  PORTD |= (1 << 7);//Turn on PD7
  
  TCCR0A = 0x83; //1000 0011 setting non inverting mode Fast pwm   
  TCCR0B = 0x03; //use 1/64 prescaler
  
  OCR0A = 127;
  
  while(1){
  };
  
}