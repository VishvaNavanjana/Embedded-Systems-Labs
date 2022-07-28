/*
     T = 1024/16 = 64us
     Maximum time for 1 overflow = 256x64us
                                 = 16.384ms

     Lets take 2ms delay
     T = 256/16 = 16us
     increments =2000/16
                =125
     initial counter value = 256-125
                           = 131


*/

#include <avr/io.h>
#include<avr/interrupt.h>


unsigned char count = 0; //to count overflows

int main(void)
{
    DDRB = DDRB | (1<<5); //Configure pin 5 of PORTB for output

    TCNT0 = 131;  //Load timer counter register

    TCCR0A = 0x00; //Set Timer0 under normal mode with 1:256 prescaler
    TCCR0B = 0x04;

    sei();//enable global interrupts
    TIMSK0 |= (1 << TOIE0);	//Enable timer0 overflow interrupt

    while(1)
    ;

    return 0;
}

//will be executed when timer0 overflows
ISR(TIMER0_OVF_vect){
    //increment oveflow counter
    count++;

    //toggle if overflow count is 50
    if(count==50){
         PORTB = PORTB ^ (1<<5); //toggle pin 5
         count = 0; //reset counter
    }

    TCNT0 = 131;  //Load timer counter register

}

