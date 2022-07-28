#include <avr/io.h>
#include <avr/interrupt.h>

int main() {
	DDRD |= (1<<6);
	DDRD |= (1<<7);

	//PORTD |= (1 << 6); // turn on the led initially
  	PORTD |= (1 << 7); // turn on the led initially

  	TCNT0 = 0;

  	TCCR0B = 0x03; // 1/64 pre scalar
                   // 0000 0011
  	TCCR0A = 0x83; // setting non inverting mode Fast pwm
                   //1000 0011

  	OCR0A = 5;

  	while(1) {
  	}
}
