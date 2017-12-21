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
#define TEMPDATA          0xF6
#define PRESSUREDATA      0xF6
#define READTEMPCMD       0x2E
#define READPRESSURECMD   0x34

uint8_t oversampling;

int16_t ac1,ac2,ac3,b1,b2,mb,mv,md;
uint16_t ac4,ac5,ac6;

uint8_t begin(uint8_t mode) {
	oversampling = mode;
	i2c_init();
	// 
	if(i2c_start(I2CADDR+I2C_WRITE)){
		printf("\nAddress registering failed\n");
		return 1;
	}
	i2c_write(AC1);
	i2c_stop();
	i2c_start(I2CADDR+I2C_READ);
	ac1 = i2c_readNak();
	i2c_stop();
	
	i2c_start(I2CADDR+I2C_WRITE);
	i2c_write(AC2);
	i2c_stop();
	i2c_start(I2CADDR+I2C_READ);
	ac2 = i2c_readNak();
	i2c_stop();
	
	printf ("\n%d\n",ac1);
	printf ("\n%d\n",ac2);/*
	printf ("\n%d\n",ac3);
	printf ("\n%d\n",ac4);
	printf ("\n%d\n",ac5);
	printf ("\n%d\n",ac6);
	printf ("\n%d\n",b1);
	printf ("\n%d\n",b2);
	printf ("\n%d\n",mb);
	printf ("\n%d\n",mv);
	printf ("\n%d\n",md);*/
	return 0;
}

#endif /* BMP085_H_ */