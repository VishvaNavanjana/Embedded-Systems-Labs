#include <avr/io.h>

int main() {
	int x;

	//set ADC1 as input
	DDRC = DDRC & ~(1<<1);

	//PORTD as output
	DDRD = 0xFF;

	//enable the ADC module
	ADCSRA |= (1<<ADEN);

	//select conversion speed
	//use 128 as div factor
	ADCSRA |=( 1<<ADPS0 | 1<< ADPS1 |1<<ADPS2 );

	//set the voltage reference
	//set AVcc as the reference voltage
	ADMUX |= (1<<REFS0);
  	ADMUX &= ~(1<<REFS1);  

  	//set adc input channel 1 from mux
  	ADMUX |= (1<<MUX0);
  	ADMUX &= ~(1<<MUX1 | 1<<MUX2 | 1<<MUX3);

  	//start conversion
  	ADCSRA |= 1<<ADSC;

  	//use right justified
  	ADMUX &= ~(1<<ADLAR);

  	while(1) {
  		//check whether the conversion is completed
  		if((ADCSRA & (1<<ADIF))) {
  			//getting the converted value
  			x = (ADCH << 8) + ADCL;

  			if(x == 0) PORTD = 0x00;
  			else if(x < 128) PORTD = 0x01;
  			else if(x < 256) PORTD = 0x03;
  			else if(x < 384) PORTD = 0x07;
    		else if(x < 512) PORTD = 0x0F;
    		else if(x < 640) PORTD = 0x1F;
    		else if(x < 768) PORTD = 0x3F;
    		else if(x < 896) PORTD = 0x7F;
    		else PORTD = 0xFF;

    		//start conversion again	
    		ADCSRA |= 1<<ADSC;	
  		}
  	}

}