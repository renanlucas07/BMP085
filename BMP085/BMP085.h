#include <stdio.h>
/*
 * BMP085.h
 *
 * Created: 21/12/2017 11:00:27
 *  Author: Renan Lucas
 */ 


#ifndef BMP085_H_
#define BMP085_H_

// CALIBRATION COEFFICIENTS		// MUST BE READ FROM THE SENSOR
#define AC1 0xAA
#define AC2 0xAC
#define AC3 0xAE
#define AC4 0xB0
#define AC5 0xB2
#define AC6 0xB4
#define B1  0xB6
#define B2  0xB8
#define MB  0xBA
#define MC  0xBC
#define MD  0xBE

#define I2CADDR			  0xEE

#define ULTRALOWPOWER	  0
#define STANDARD		  1
#define HIGHRES			  2
#define ULTRAHIGHRES	  3
#define CONTROL           0xF4 
#define DATA			  0xF6
#define READTEMPCMD       0x2E
#define READPRESSURECMD   0x34

uint8_t oversampling;

int16_t ac1,ac2,ac3,b1,b2,mb,mc,md;
uint16_t ac4,ac5,ac6;

// Returns 0 if succeeds, 1 if fails
uint8_t begin(uint8_t mode) {
	oversampling = mode;
	i2cInit();
	// 
	if(i2cStart(I2CADDR+I2C_WRITE)){
		printf("\nAddress registering failed\n");
		return 1;
	}
	i2cWrite(AC1);
	i2cStop();
	i2cStart(I2CADDR+I2C_READ);
	ac1 = i2cReadAck();
	ac1 <<= 8;
	ac1 |= i2cReadNack();
	i2cStop();
	
	i2cStart(I2CADDR+I2C_WRITE);
	i2cWrite(AC2);
	i2cStop();
	i2cStart(I2CADDR+I2C_READ);
	ac2 = i2cReadAck();
	ac2 <<= 8;
	ac2 |= i2cReadNack();
	i2cStop();
	
	i2cStart(I2CADDR+I2C_WRITE);
	i2cWrite(AC3);
	i2cStop();
	i2cStart(I2CADDR+I2C_READ);
	ac3 = i2cReadAck();
	ac3 <<= 8;
	ac3 |= i2cReadNack();
	i2cStop();
	
	//bugado
	i2cStart(I2CADDR+I2C_WRITE);
	i2cWrite(AC4);
	i2cStop();
	i2cStart(I2CADDR+I2C_READ);
	ac4 = i2cReadAck();
	ac4 <<= 8;
	ac4 |= i2cReadNack();
	
	i2cStop();
	
	i2cStart(I2CADDR+I2C_WRITE);
	i2cWrite(AC5);
	i2cStop();
	i2cStart(I2CADDR+I2C_READ);
	ac5 = i2cReadAck();
	ac5 <<= 8;
	ac5 |= i2cReadNack();
	i2cStop();
	
	i2cStart(I2CADDR+I2C_WRITE);
	i2cWrite(AC6);
	i2cStop();
	i2cStart(I2CADDR+I2C_READ);
	ac6 = i2cReadAck();
	ac6 <<= 8;
	ac6 |= i2cReadNack();
	i2cStop();
	
	i2cStart(I2CADDR+I2C_WRITE);
	i2cWrite(B1);
	i2cStop();
	i2cStart(I2CADDR+I2C_READ);
	b1 = i2cReadAck();
	b1 <<= 8;
	b1 |= i2cReadNack();
	i2cStop();
	
	i2cStart(I2CADDR+I2C_WRITE);
	i2cWrite(B2);
	i2cStop();
	i2cStart(I2CADDR+I2C_READ);
	b2 = i2cReadAck();
	b2 <<= 8;
	b2 |= i2cReadNack();
	i2cStop();
	
	i2cStart(I2CADDR+I2C_WRITE);
	i2cWrite(MB);
	i2cStop();
	i2cStart(I2CADDR+I2C_READ);
	mb = i2cReadAck();
	mb <<= 8;
	mb |= i2cReadNack();
	i2cStop();
	
	i2cStart(I2CADDR+I2C_WRITE);
	i2cWrite(MC);
	i2cStop();
	i2cStart(I2CADDR+I2C_READ);
	mc = i2cReadAck();
	mc <<= 8;
	mc |= i2cReadNack();
	i2cStop();
	
	i2cStart(I2CADDR+I2C_WRITE);
	i2cWrite(MD);
	i2cStop();
	i2cStart(I2CADDR+I2C_READ);
	md = i2cReadAck();
	md <<= 8;
	md |= i2cReadNack();
	i2cStop();
	
	printf ("\nAC1 = %d\n",ac1);
	printf ("\nAC2 = %d\n",ac2);
	printf ("\nAC3 = %d\n",ac3);
	printf ("\nAC4 = %u\n",ac4);
	printf ("\nAC5 = %u\n",ac5);
	printf ("\nAC6 = %u\n",ac6);
	printf ("\nB1 = %d\n",b1);
	printf ("\nB2 = %d\n",b2);
	printf ("\nMB = %d\n",mb);
	printf ("\nMC = %d\n",mc);
	printf ("\nMD = %d\n",md);
	
	return 0;
}

float readTemperature() {
	int32_t UT,X1,X2;
	float temp;
	i2cStart(I2CADDR+I2C_WRITE);
	i2cWrite(CONTROL);
	i2cWrite(READTEMPCMD);
	i2cStop();
	_delay_us(4500);
	i2cStart(I2CADDR+I2C_WRITE);
	i2cWrite(DATA);
	i2cStop();
	i2cStart(I2CADDR+I2C_READ);
	UT = i2cReadAck();
	UT <<= 8;
	UT |= i2cReadNack();
	printf("\nUT = %ld",UT);
	X1 = ((UT - (int32_t)ac6) * ((int32_t)ac5) >> 15);
	X2 = (((int32_t)mc << 11) / (X1 + (int32_t)md));
	printf("\nx1 = %ld, x2= %ld, B5 = %ld",X1, X2,X1+X2);
	printf("\nTemp = %ld",((X1 + X2 + 8) >> 4));
	temp = ((X1 + X2 + 8) >> 4);
	temp /= 10.0;
	return temp;
} 

#endif /* BMP085_H_ */