#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 5

int main() {

	DDRD |= (1<<6);	//configure pin6 of PORT D as an output

	TCCR0A = 0x83; //1000 0011 setting non inverting mode Fast pwm
  	TCCR0B = 0x03; // 0000 0011 use 1/64 prescaler

    OCR0A = 0;  //set zero for Output compare register A

  	while(1) {
        while(OCR0A < 255) {
  			_delay_ms(BLINK_DELAY_MS);
  			OCR0A++;
  		}
  		while(OCR0A > 0) {
  			_delay_ms(BLINK_DELAY_MS);
  			OCR0A--;
  		}

  	}
}
