/*
------------------------------------------------
F = 7812Hz

F_generated_wave = F_oscillator/(256 x N)
100Hz = 16MHz/(256 x N)
N = 8
------------------------------------------------
F = 976Hz

F_generated_wave = F_oscillator/(256 x N)
1000Hz = 16MHz/(256 x N)
N = 64
------------------------------------------------
F = 244Hz

F_generated_wave = F_oscillator/(256 x N)
10000Hz = 16MHz/(256 x N)
N = 256
------------------------------------------------
F = 61Hz

F_generated_wave = F_oscillator/(256 x N)
18000Hz = 16MHz/(256 x N)
N = 1024
------------------------------------------------
*/


#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 500

int main() {

	DDRD |= (1<<6);	//configure pin6 of PORT D as an output

  	TCCR0A = 0x83; //1000 0011 setting non inverting mode Fast pwm
	
	//OCR0A = 255;
	
  	while(1) {

        // 7812.5 Hz
        TCCR0B = 0x02; // 0000 0011 use 1/64 prescaler
        OCR0A = 255;  //set zero for Output compare register A
        _delay_ms(1000);

        // 976.56 Hz
        TCCR0B = 0x02; // 0000 0011 use 1/64 prescaler
        OCR0A = 255;   //set zero for Output compare register A
        _delay_ms(1000);

        // 244.14 Hz
        TCCR0B = 0x04; // 0000 0011 use 1/64 prescaler
        OCR0A = 255;   //set zero for Output compare register A
        _delay_ms(1000);

        //61.04 Hz
        TCCR0B = 0x05; // 0000 0011 use 1/64 prescaler
        OCR0A = 255;   //set zero for Output compare register A
        _delay_ms(1000);
  	}
}