#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd.h"
#include "lcd.c"

#define FOSC 16000000
#define BAUD 9600
#define UBRR (FOSC / BAUD / 16) - 1

char alphanumeric[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', '#', '*'};

char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

//initialize keypad
void init_keypad()
{
    DDRC |= 0x0f;    //set pc0-pc3 as output
    DDRB &= ~(0x0f); //set pb0-pb3 as input
}

unsigned int col, row;

//read from keypad
char read_keypad()
{
    while (1)
    {
        for (col = 0; col < 4; col++)
        {
            PORTC |= (1 << col);
            for (row = 0; row < 4; row++)
            {
                if (PINB & (1 << row))
                {
                    _delay_ms(500);
                    return keys[row][col];
                }
            }
            PORTC &= ~(1 << col);
        }
    }
}

void print_message(int r, char str[])
{
    lcd_gotoxy(0, r);
    lcd_puts(str);
}

void print_char(int x, int y, char c)
{
    lcd_gotoxy(x, y);
    lcd_putc(c);
}

void print_encrypted(char *str)
{
    unsigned int count = 0, pos, i;

    print_message(0, "Encrypted Text:");

    lcd_gotoxy(0, 1);
    while (count < 10)
    {
        for (pos = 0; pos < 16; pos++)
        {
            if (alphanumeric[pos] == *(str + count))
                break;
        }
        print_char(count, 1, alphanumeric[pos]);
        count++;
    }
}

void cipher(char *str, int key)
{
    unsigned int pos = 0, count = 0;

    while (count < 10)
    {
        for (pos = 0; pos < 16; pos++)
        {
            if (alphanumeric[pos] == *(str + count))
                break;
        }
        *(str + count) = alphanumeric[(pos + key) % 16];
        count++;
    }
}

//*******************************************
//initialize the USART port
void usart_init()
{
    //Set baud rate
    UBRR0L = UBRR;
    UBRR0H = (UBRR >> 8);
    //Asynchronous mode, no parity, 1 stop bit, 8 data bits
    UCSR0C = 0b10000110;

    //Turn on Transmitor and Receiver
    UCSR0B |= 1 << TXEN0;
    UCSR0B |= 1 << RXEN0;
}

//transmit a character
void usart_send(unsigned char c)
{
    //Check whether USART data register is empty
    while ((UCSR0A & (1 << UDRE0)) == 0)
        ;
    UDR0 = c;
}

//returns a received character
char usart_receive()
{
    //Check whether the entire character has been received
    while ((UCSR0A & (1 << RXC0)) == 0)
        ;
    return UDR0;
}

void EEPROMwrite(unsigned int address, char data)
{

    //wait for completion of previous write
    while (EECR & (1 << EEPE))
        ;

    //setup address and the data registers
    EEAR = address;
    EEDR = data;

    //write logical 1 to EEMPE
    EECR = (1 << EEMPE);

    //start EEPROM write
    EECR = (1 << EEPE);
}

char EEPROMread(unsigned int address)
{

    //wait for completion of previous write
    while (EECR & (1 << EEPE))
        ;

    //setup address
    EEAR = address;

    //start EEPROM read
    return EEDR;
}

//*******************************************

int main()
{

    usart_init();
    //Initialize display and select type of cursor
    //display on, cursor off
    lcd_init(LCD_DISP_ON);

    char key = '3', entered;
    EEPROMwrite(0, key);

    char *str = "";
    unsigned int count = 0;

    while (1)
    {
        init_keypad();

        print_message(0, "Encrypt    - #");
        print_message(1, "Change Key - *");
        entered = read_keypad();

        if (entered == '*')
        {
            lcd_clrscr();
            print_message(0, "Enter Key :");

            key = read_keypad();
            EEPROMwrite(0, key);

            lcd_clrscr();
            print_message(0, "KEY CHANGED !!");
            _delay_ms(1000);
            lcd_clrscr();
            continue;
        }
        else if (entered == '#')
        {
            lcd_clrscr();
            print_message(0, "Enter Text :");

            lcd_gotoxy(0, 1); //go to the next line
            while (count < 10)
            {
                entered = read_keypad();
                *(str + count) = entered;
                print_char(count, 1, entered);
                count++;
            }

            lcd_clrscr();
            cipher(str, (key - 48));
            print_encrypted(str);

            entered = read_keypad();
            if (entered == '#')
            {
                lcd_clrscr();
                print_message(0, "Finished");
                break;
            }

            lcd_clrscr();
            //shift from the old string
            str = str + count;
            count = 0;
        }
    }
    return 0;
}
