#include <avr/io.h>

void delay_timer0() {

    //time for 1 increment = 256 x (1/16) us
    //time for 1 overflow = 256 x (1/16) x 256 us
    //needed overflows =  500ms / 256 x (1/16) x 256 us ~ 122
    unsigned int i =0;
    while(i<122) {
        TCNT0 = 131; //load timer count register

        //set the Timer0 under normal mode with 1:256 prescaler
        TCCR0A = 0x00;
        TCCR0B = 0x04;

        //wait till timer overflow bit (TOV0) is set
        while((TIFR0&0x01)==0);

        //clear timer settings --stops the timer
        TCCR0A = 0x00;
        TCCR0B = 0x00;

        //clear the timer overflow bit (TOV0) for next round
        TIFR0 = 0x01;
        i++;
    }
}

int main (void) {

  	//configure pin 5 of PORTB for output
  	DDRB = DDRB | (1<<5);

  	while(1){
  		PORTB = PORTB ^ (1<<5); //toggle pin 5
      	delay_timer0();
  	}


}
