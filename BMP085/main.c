/*
 * BMP085.c
 *
 * Created: 20/12/2017 14:37:27
 * Author : Renan Lucas
 */ 
#define F_CPU 16000000UL

#define SCL_CLOCK  100000L
#define BAUD_RATE 9600

#include <avr/io.h>
#include <util/delay.h>
#include "i2cmaster.h"
#include "twimaster.h"
#include "usart.h"
#include "BMP085.h"

FILE uart_str = FDEV_SETUP_STREAM(uartPutch, uartGetch, _FDEV_SETUP_RW);

int main()
{
	float temp;
	int pi, pd;
	stdout = stdin = &uart_str;
    uartInit();
	begin(ULTRAHIGHRES);
    while (1) 
    {
		temp = readTemperature();
		pi = temp;
		pd = (temp - pi)*10;
		printf("\n%d.%d",pi,pd);
    }
	return 0;
}

