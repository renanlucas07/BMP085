#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED
#include <avr/io.h>
#include <string.h>
#include <stdio.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#ifndef BAUD_RATE
#define BAUD_RATE 19200
#endif

void uartInit(void);
int uartPutch(char ch, FILE *stream);
int uartGetch(FILE *stream);

void uartInit(void) {
  UBRR0H = (((F_CPU/BAUD_RATE)/16)-1)>>8;	// set baud rate
  UBRR0L = (((F_CPU/BAUD_RATE)/16)-1);
  UCSR0B = (1<<RXEN0)|(1<<TXEN0); 		// enable Rx & Tx
  UCSR0C=  (1<<UCSZ01)|(1<<UCSZ00);  	       // config USART; 8N1
  printf("\nUSART INITIALIZED\n");
}

int uartPutch(char ch, FILE *stream) {
   if (ch == '\n')
    uartPutch('\r', stream);
   while (!(UCSR0A & (1<<UDRE0)));
   UDR0=ch;
   return 0;
}

int uartGetch(FILE *stream) {
   unsigned char ch;
   while (!(UCSR0A & (1<<RXC0)));
   ch=UDR0;

   /* Echo the Output Back to terminal */
   uartPutch(ch,stream);

   return ch;
}

#endif // USART_H_INCLUDED
