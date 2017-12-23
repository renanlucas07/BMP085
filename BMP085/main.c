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

int main(void)
{
	float temp, alt;
	int pi, pd;
	int32_t p;
	uint32_t UP;
	stdout = stdin = &uart_str;
    uartInit();
	begin(ULTRAHIGHRES);
    while (1) 
    {
		temp = readTemperature();
		//Gambs
		pi = temp;
		pd = (temp - pi)*10;
		printf("\nTempratura real = %d.%doC\n",pi,pd);
		
		UP = readRawPressure();
		printf("\nRaw Pressure = %lu",UP);
		p =readPressure();
		printf("\nPressao = %ld", p);
		
		alt = readAbsAltitude();
		//Gambs
		pi = alt;
		pd = (alt - pi)*10;
		printf("\nAltidude = %d.%dm\n",pi,pd);
    }
	return 0;
}

