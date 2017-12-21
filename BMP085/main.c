/*
 * BMP085.c
 *
 * Created: 20/12/2017 14:37:27
 * Author : Renan Lucas
 */ 
#define F_CPU 16000000UL

#define SCL_CLOCK  100000L

#include <avr/io.h>
#include <util/delay.h>
#include "i2cmaster.h"
#include "twimaster.h"
#include "usart.h"
#include "BMP085.h"

FILE uart_str = FDEV_SETUP_STREAM(uart_putch, uart_getch, _FDEV_SETUP_RW);

int main()
{
	stdout = stdin = &uart_str;
    uart_init();
	begin(ULTRAHIGHRES);
    while (1) 
    {
		
    }
	return 0;
}

