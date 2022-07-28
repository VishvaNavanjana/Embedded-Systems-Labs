#include <avr/io.h>
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
void usart_send(unsigned char c){
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

void EEPROMwrite(unsigned int address, char data){

    //wait for completion of previous write                           
    while(EECR & (1<<EEPE));    
    
    //setup address and the data registers                            
    EEAR = address; 
    EEDR = data;
    
    //write logical 1 to EEMPE                          
    EECR = (1<<EEMPE);  

    //start EEPROM write               
    EECR = (1<<EEPE);   
}

char EEPROMread(unsigned int address){

    //wait for completion of previous write
    while(EECR & (1<<EEPE));    
    
    //setup address
    EEAR = address;  
    
    //start EEPROM read
    EECR = (1<<EERE);   

    return EEDR;    
}


int main()
{ 
  
	usart_init(); // initialize serial communication
	
	char data;
	char message[200];
	unsigned int address;
    unsigned int j = 0;
		
	while(data != '\r') { // take the data untill carriage return is received
        data = usart_receive(); 
        //store sentense in message
        message[j++] = data;
	}

    for (address = 0; address < j; address++)
    {
        EEPROMwrite(address,message[address]);
    }
    

  return 0;
}