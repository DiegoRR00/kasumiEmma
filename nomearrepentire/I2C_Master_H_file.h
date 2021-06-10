/*
 * I2C_Master_H_file.h
 * www.electronicwings.com
 */ 


#ifndef I2C_MASTER_H_FILE_H_					/* Define library H file if not defined */
#define I2C_MASTER_H_FILE_H_
#ifndef F_CPU
#define F_CPU 8000000UL							/* Define CPU clock Frequency e.g. here its 8MHz */
#endif
#include <avr/io.h>								/* Include AVR std. library file */
#include <util/delay.h>							/* Include inbuilt defined Delay header file */
#include <math.h>								/* Include math function */
#include <util/twi.h>
#include <stdint.h>
#define SCL_CLK 100000L							/* Define SCL clock frequency */
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1))))) /* Define bit rate */
#define I2C_PRESCALER_MASK 0xF8

void I2C_Init();								/* I2C initialize function */
uint8_t  I2C_Start(char write_address);			/* I2C start function */
uint8_t  I2C_Repeated_Start(char read_address);	/* I2C repeated start function */
void I2C_Stop();								/* I2C stop function */
void I2C_Start_Wait(char write_address);		/* I2C start wait function */
uint8_t  I2C_Write(char data);					/* I2C write function */
int I2C_Read_Ack();							/* I2C read ack function */
int I2C_Read_Nack();							/* I2C read nack function */
uint8_t i2c_master_sendByte(uint8_t address, uint8_t data);
uint8_t i2c_master_start(uint8_t address, uint8_t mode);

#endif											/* I2C_MASTER_H_FILE_H_ */