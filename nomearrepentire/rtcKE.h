#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <stdbool.h>
#include "I2C_Master_H_file.h"
#include "kasumiEmma.h"

#define Device_Write_address	0xD0				/* Define RTC DS1307 slave address for write operation */
#define Device_Read_address		0xD1				/* Make LSB bit high of slave address for read operation */
#define TimeFormat12			0x40				/* Define 12 hour format */
#define AMPM					0x20
#ifndef RTC_KE
#define RTC_KE

void rtc_init(struct kasumiEmma* info);
void rtc_act(struct kasumiEmma* info);


#endif