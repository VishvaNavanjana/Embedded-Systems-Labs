

#include <util/delay.h>
#include <avr/io.h>


#define F_cpu 16000000
#define BAUD 9600
#define BRC ((F_cpu/16/BAUD)-1)
#define TX_BUFFER_SIZE 20


/*serial_init  - Initialize  the  USART  port*/
void  usart_init(unsigned  short  ubrr) 
{ 
  UBRR0 = ubrr;             // Set  baud  rate
  UCSR0B  |= (1 << TXEN0 ); // Turn on  transmitter
  UCSR0B  |= (1 << RXEN0 ); // Turn on  receiver
  UCSR0C = (3 << UCSZ00 ); // Set  for  async. operation , no parity ,// one  stop bit , 8 data  bits}
}



/*serial_out  - Output a byte to the  USART0  port*/
void  usart_send(char ch)
{ 
  while  (( UCSR0A & (1<<UDRE0 )) == 0);
  UDR0 = ch;
}

void serialWrite(char c[])
{
  for(uint8_t i = 0;i<strlen(c);i++)
  {
    usart_send(c[i]);
  }


}
/*serial_in  - Read a byte  from  the  USART0  and  return  it*/
char  usart_receive()
{
  while ( !( UCSR0A & (1 << RXC0)) );     // whether all received
  return  UDR0;
}

/*cipher the character with key = 3*/
char cipher(char ch)
{
  /*cipher only alphabetic character*/
  if(ch>=65 && ch<=87){ch = ch + 3;}
  if(ch>=97 && ch<=119){ch = ch + 3;}
  
  if(ch==88){ ch = 65;}
  if(ch==89){ ch = 66;}
  if(ch==90){ ch = 67;}
    
  if(ch==120){ ch = 97;}
  if(ch==121){ ch = 98;}
  if(ch==122){ ch = 99;}
  
  return ch;
}

int main(void){
   usart_init(BRC);

   serialWrite("Sathira Basnayake  E/16/054\n");
   serialWrite("Nadun Walikanda    E/16/389\n");
   serialWrite("Madusha Shanaka    E/16/351\n");
   serialWrite(" \n");
   _delay_ms(1000); 
  
  while(1)
  {
    usart_send(cipher(usart_receive()));
  }
  
}
