/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 200

//will be executed when timer1 overflows
ISR(TIMER1_OVF_vect){
    PORTB = PORTB ^ (1<<5); //toggle pin 5
    TCNT1 = 49911;	//Load timer count register
}

int main(void)
{

    //for part 1
    DDRB = DDRB | (1<<5);	//configure pin5 of port B for output
    TCNT1 = 49911;	//Load timer count register

	//Set the timer1 under normal mode with 1/1024 scaler
    TCCR1A = 0x00;
    TCCR1B = 0x05;

    sei();	//enable global interrupts
    TIMSK1 |= (1 << TOIE1);	//Enable timer1 overflow interrupt


    //for part 2
    DDRB |= 0x0F;	//Setting least significant 4 bits as outputs
    unsigned char index;
    while(1){
        //Knight Rider style circuit
        for(index=0 ; index<4 ; index++){
			PORTB |= (1<<index); //set voltage as HIGH
			_delay_ms(BLINK_DELAY_MS);
			PORTB &= ~(1<<index);    //set voltage as LOW
	  	}

	  	for(index=2 ; index>=1 ; index--){
				PORTB |= (1<<index);    //set voltage as HIGH
				_delay_ms(BLINK_DELAY_MS);
				PORTB &= ~(1<<index);   //set voltage as LOW
	  	}

    }

    return 0;
}



