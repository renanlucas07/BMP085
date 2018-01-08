
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
#include "BMP085.h"
#include "lcd.h"

//LCD Constants
#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7


//**** Decimal Values to Display Special Characters ****
unsigned int s1[]={10,21,17,17,17,10,4,0};
unsigned int s2[]={0,10,0,4,4,17,10,4};
unsigned int s3[]={0,10,0,4,4,0,14,17};
unsigned int s4[]={1,3,5,9,9,11,27,24};
unsigned int s5[]={0,17,10,17,4,0,14,17};
unsigned int s6[]={0,10,0,4,4,0,31,0};
unsigned int s7[]={10,0,4,0,14,17,17,14};
unsigned int s8[]={0,10,0,31,17,14,0,0};
//******************************************************

FILE uart_str = FDEV_SETUP_STREAM(uartPutch, uartGetch, _FDEV_SETUP_RW);

int main(void) {
	DDRB = 0x03;
	DDRD = 0xF0;
	float temp, alt;
	int pi, pd;
	int32_t p;
	uint32_t UP;
	stdout = stdin = &uart_str;
    uartInit();
	begin(ULTRAHIGHRES);
	_delay_ms(200);
	start();
	
    while (1) {
		
		
		UP = readRawPressure();
		printf("\nRaw Pressure = %lu",UP);
		p =readPressure();
		printf("\nPressao = %ld", p);
		
		alt = readAbsAltitude();
		//Gambs
		pi = alt;
		pd = (alt - pi)*10;
		printf("\nAltidude = %d.%dm\n",pi,pd);
		
		temp = readTemperature();
		//Gambs
		pi = temp;
		pd = (temp - pi)*10;
		printf("\nTempratura real = %d.%doC\n",pi,pd);
		
		clearScreen();
		blink();
		sendString("Temperatura:");
		setCursor(1,0);
		sendInteger(pi);
		setCursor(1,2);
		sendString(".");
		setCursor(1,3);
		sendInteger(pd);
		setCursor(1,4);
		sendString("oC");
		_delay_ms(3000);
		noBlink();
		//while(!(PINB & (1<<PB2))){}
	}
	return 0;
}