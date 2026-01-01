#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "i2c_defines.h"
#include"i2c.h"

void init_i2c(void)
{
	 //Configure I/O pin for SCL & SDA functions using PINSEL0
	 PINSEL0=SCL_EN|SDA_EN;
	 //Configure Speed for I2C Serial Communication
	 //Using I2CSCLL
	 I2SCLL=LOADVAL;
   //& I2CSCLH
	 I2SCLH=LOADVAL;
	//I2C Peripheral Enable for Communication
	 I2CONSET=1<<I2EN_BIT; 
}	

void i2c_start(void)
{
	// start condition
  I2CONSET=1<<STA_BIT;
	//wait for start bit status
	while(((I2CONSET>>SI_BIT)&1)==0);
	// clear start condition
	I2CONCLR=1<<STA_BIT;
}	

void i2c_restart(void)
{
	// start condition
	I2CONSET=1<<STA_BIT;
	//clr SI_BIT
	I2CONCLR=1<<SI_BIT;
	//wait for SI bit status
	while(((I2CONSET>>SI_BIT)&1)==0);
	// clear start condition
	I2CONCLR=1<<STA_BIT;
}	

void i2c_write(u8 dat)
{
	//put data into I2DAT
	I2DAT=dat;	
	//clr SI_BIT
	I2CONCLR = 1<<SI_BIT;
	//wait for SI bit status
	while(((I2CONSET>>SI_BIT)&1)==0);
}	

void i2c_stop(void)
{
	// issue stop condition
	I2CONSET=1<<STO_BIT;
  // clr SI bit status	
	I2CONCLR = 1<<SI_BIT;
	//stop will cleared automatically
	//while(((I2CONSET>>STO_BIT)&1));
}

u8 i2c_nack(void)
{	
	I2CONSET = 0x00; //Assert Not of Ack
  I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	return I2DAT;
}

u8 i2c_masterack(void)
{	
	I2CONSET = 0x04; //Assert Ack
  I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR = 0x04; //Clear Assert Ack
 	return I2DAT;
}
void i2c_device_write(u8 sa, u8 reg, u8 data)
{
        i2c_start();
        i2c_write(sa << 1);     // Write mode
        i2c_write(reg);         // Register address
        i2c_write(data);        // Data
        i2c_stop();
        delay_ms(10);
}

u8 i2c_device_read(u8 sa, u8 reg) 
{
        u8 data;
        i2c_start();
        i2c_write(sa << 1);     // Write mode
        i2c_write(reg);         // Register address
        i2c_restart();
        i2c_write((sa << 1) | 1); // Read mode
        data = i2c_nack();
        i2c_stop();
        return data;

}
void init_MMA7660()
{
	i2c_start();
	i2c_write(0x98);
	i2c_write(0x07);
	i2c_write(0x01);
	i2c_stop();
}
u8 read_MMA7660(u8 reg)
{
	u8 data;
	i2c_start();
	i2c_write(0x98);
	i2c_write(reg);
	i2c_restart();
	i2c_write(0x99);
	data=i2c_nack();
	if(data>31)
	{
		data=data-64;
	}
	i2c_stop();
	delay_ms(10);
	return data;
}



