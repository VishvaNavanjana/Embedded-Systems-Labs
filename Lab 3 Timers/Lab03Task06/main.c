/*
    ----------------------------------
    For 50ms interval lets use Timer0
         2ms delay
    T = 256/16 = 16us
    increments =2000/16
               =125
    initial counter value = 256-125
                          = 131

    needed overflows =  50ms/2ms = 25

    -----------------------------------
    For 500ms interval lets use Timer1
    T = 256/16 = 16us
    increments = 500ms/16us
               = 31250
    initial counter value = 65536 - 31250
                          = 34286

    -----------------------------------


*/

#include <avr/io.h>
#include<avr/interrupt.h>

unsigned char count = 0; //to count overflows of timer0

int main(void)
{
    DDRB = DDRB | (1<<5); //Configure pin 5 of PORTB for output
    DDRB = DDRB | (1<<3); //Configure pin 3 of PORTB for output

    TCNT0 = 131;  //Load timer counter registers
    TCNT1 = 34286;



    TCCR0A = 0x00; //Set Timer0 under normal mode with 1:256 prescaler
    TCCR0B = 0x04;


    TCCR1A = 0x00; //Set the timer1 under normal mode with 1:256 scaler
    TCCR1B = 0x04;

    sei();//enable global interrupts

    TIMSK0 |= (1 << TOIE0);	//Enable timer0 overflow interrupt
    TIMSK1 |= (1 << TOIE1);	//Enable timer1 overflow interrupt

    while(1)
    ;

    return 0;
}

//will be executed when timer0 overflows
ISR(TIMER0_OVF_vect){
    //increment oveflow counter
    count++;

    //toggle if overflow count is 25
    if(count==25){
         PORTB = PORTB ^ (1<<3); //toggle pin 3
         count = 0; //reset counter
    }

    TCNT0 = 131;  //Load timer counter register

}


//will be executed when timer1 overflows
ISR(TIMER1_OVF_vect){
    PORTB = PORTB ^ (1<<5); //toggle pin 5
    TCNT1 = 34286;	//Load timer count register
}


