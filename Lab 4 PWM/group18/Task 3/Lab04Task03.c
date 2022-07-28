#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main() {

	DDRD |= (1<<6);	//configure pin6 of PORT D as an output

  	TCCR0A = 0x83; //1000 0011 setting non inverting mode Fast pwm

    OCR0A = 127;

  	while(1) {

        // 7812.5 Hz
        TCCR0B = 0x02; // 0000 0011 use 1/8 prescaler
        //OCR0A = 63;  //set value for Output compare register A
        _delay_ms(1000);

        // 976.56 Hz
        TCCR0B = 0x03; // 0000 0011 use 1/64 prescaler
        //OCR0A = 127;  //set value for Output compare register A
        _delay_ms(1000);

        // 244.14 Hz
        TCCR0B = 0x04; // 0000 0011 use 1/256 prescaler
        //OCR0A = 191;  //set value for Output compare register A
        _delay_ms(1000);

        //61.04 Hz
        TCCR0B = 0x05; // 0000 0011 use 1/1024 prescaler
        //OCR0A = 255;  //set value for Output compare register A
        _delay_ms(1000);
  	}
}
