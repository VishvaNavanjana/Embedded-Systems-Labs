#include <avr/io.h>

int main(){

    int light_level;

    //configure PD0 as an output
    DDRD |= (1<<0);	
    //configure ADC1 as an input (PC1)
    DDRC &= ~(1<<1);

    //Turn on the ADC module
    ADCSRA |= (1<<ADEN);

    //Select conversion speed = 128kHz
    ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));

    //Select voltage reference , AREF = 5v
    ADMUX &= ~(1<<REFS0);
    ADMUX &= ~(1<<REFS1);

    //select the ADC input channel
    ADMUX |= (1<<MUX0);
    ADMUX &= ~((1<<MUX1)|(1<<MUX2)|(1<<MUX3));
    
    //Activate the start conversion bit
    ADCSRA |= (1<<ADSC);

    //set result to be right-justified
    ADMUX &= ~(1<<ADLAR);

    //check ADIF bit to see whether conversion is completed
    while(1){
        //check ADIF flag
        if((ADCSRA & (1<<ADIF)) == 0x10){
            //calculate the digital output
            light_level = ADCL + (ADCH<<8); 
			
			//1024/2 = 512 (half value)
            if(light_level < 512){
                //Turn on led
                PORTD |= (1<<0);
            }
            else{
                //Turn off led
                PORTD &= ~(1<<0);
            }
			//start conversion again
            ADCSRA |= (1<<ADSC);
         
        }
    }

    return 0;

}