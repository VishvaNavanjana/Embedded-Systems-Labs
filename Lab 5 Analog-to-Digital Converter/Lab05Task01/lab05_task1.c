#include <avr/io.h>

int main(){

  	int x;
	
	  //ADC1 as input
  	DDRC = DDRC & ~(1<<1);
  	//PORTD as output
  	DDRD = 0xFF;
  	 
  	//turn on ADC module 
  	ADCSRA |=(1<<ADEN);
  	  
  	//select conversion speed , use 128 as div factor
  	ADCSRA |=( 1<<ADPS0 | 1<< ADPS1 |1<<ADPS2 );	
  
  	//set voltage reference , AVcc 
  	ADMUX |= (1<<REFS0);
  	ADMUX &= ~(1<<REFS1);  
  
  	//set adc input channel (1) from mux
  	ADMUX |= (1<<MUX0);
  	ADMUX &= ~(1<<MUX1 | 1<<MUX2 | 1<<MUX3);
    
  	//start conversion
  	ADCSRA |= 1<<ADSC;
  	//right justified
  	ADMUX &= ~(1<<ADLAR);
      
    while(1){

      if((ADCSRA & 1<< ADIF)==0x10){ //checks the flag
    	  	
    	  	x = ADCL + (ADCH<<8); //calculate digital output

    	  // 1023/8 ~= 128
    		// 5v/8 = 0.625v

    		if(x == 0) PORTD = 0x00; 		// No LED -> 0v 
    		else if(x<128) PORTD = 0x01;	// 1 LEDs -> 0 - 0.625 v
    		else if(x<256) PORTD = 0x03;	// 2 LEDs -> 0.625 - 1.25 v
    		else if(x<384) PORTD = 0x07;	// 3 LEDs -> 1.25 -1.875 v
    		else if(x<512) PORTD = 0x0F;	// 4 LEDs -> 1.875 -2.5 v
    		else if(x<640) PORTD = 0x1F; 	// 5 LEDs -> 2.5 -3.125 v
    		else if(x<768) PORTD = 0x3F;	// 6 LEDs -> 3.125 -3.75 v
    		else if(x<896) PORTD = 0x7F;	// 7 LEDs -> 3.75 -4.375 v
    		else PORTD = 0xFF; 				// 8 LEDs -> 5v

     		ADCSRA |= 1<<ADSC;   //start conversion again
  		
      }     
     
    }  
  
  	return  0 ;
  
}


