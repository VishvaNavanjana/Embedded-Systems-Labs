
#include <util/delay.h>
#include <avr/io.h>

/*
    Desired baud Rate = 9600 bps
    X = Fosc/(16*Desired baud Rate) - 1
*/

#define BAUD 9600
#define Fosc 16000000
#define X ((Fosc/16/BAUD) - 1)

//initialize the USART port
void usart_init(){
    //Set baud rate
    UBRR0L = X;
	UBRR0H = (X>>8);
    //Asynchronous mode, no parity, 1 stop bit, 8 data bits
    UCSR0C = 0b10000110; 
    
    //Turn on Transmitor and Receiver
    UCSR0B |= 1<<TXEN0;
    UCSR0B |= 1<<RXEN0;
}

//transmit a character
void usart_send(char c){
    //Check whether USART data register is empty
    while ((UCSR0A & (1<<UDRE0)) == 0);    
    UDR0 = c;
}

//returns a received character
char usart_receive(){
    //Check whether the entire character has been received
    while((UCSR0A & (1<<RXC0)) == 0);
    return UDR0;
}

//Caesar cipher (key is 3)
char caesar_cipher(char c){
    //Only encrypt alphabetic characters
    if( (c >= 65 && c <= 87) || (c >= 97 && c <= 119) ){
        c = c + 3;
    }

    else if( c == 88) c = 65; // X->A
    else if( c == 89) c = 66; // Y->B
    else if( c == 90) c = 67; // Z->C
    else if( c == 120) c = 97; // x->A
    else if( c == 121) c = 98; // y->B
    else if( c == 122) c = 99; // z->C

    return c;
}


int main(void){

    //initialize the USART
    usart_init();

    char group_mates[] = "Vishva Navanjana E/17/297\nThisara Manohara E/17/206";

    for(int i=0 ;group_mates[i] != '\0';i++){
        usart_send(group_mates[i]);
    }

    while (1){
        usart_send(caesar_cipher(usart_receive()));
    }
    

    return 0;
}