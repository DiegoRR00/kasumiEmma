#include "rtcKE.h"
//int second,info->minuto,info->hora,info->dia,date,info->mes,info->anio;
uint8_t segundo, semana;
//funciones libreria
bool IsItPM(char hour_)
{
	if(hour_ & (AMPM))
	return 1;
	else
	return 0;
}

void RTC_Read_Clock(char read_clock_address, struct kasumiEmma* info)
{
	I2C_Start(Device_Write_address);
	I2C_Write(read_clock_address);
	I2C_Repeated_Start(Device_Read_address);

	segundo = I2C_Read_Ack();						/* Read second */
	info->minuto = I2C_Read_Ack();						/* Read minute */
	info->hora = I2C_Read_Nack();							/* Read hour with Nack */
	I2C_Stop();										/* Stop i2C communication */	
}

void RTC_Read_Calendar(char read_calendar_address, struct kasumiEmma* info)
{
	I2C_Start(Device_Write_address);
	I2C_Write(read_calendar_address);
	I2C_Repeated_Start(Device_Read_address);

	semana = I2C_Read_Ack();							/* Read day */
	info->dia = I2C_Read_Ack();							/* Read date */
	info->mes = I2C_Read_Ack();							/* Read month */
	info->anio = I2C_Read_Nack();							/* Read the year with Nack */
	I2C_Stop();										/* Stop i2C communication */	
}
uint8_t bcdBin (uint8_t num){
	uint8_t nibbleSup = num & 0xF0;
	uint8_t nibbleInf = num & 0x0F;
	nibbleSup = nibbleSup >> 4;
	return nibbleSup*10 + nibbleInf;
};
void rtc_init(struct kasumiEmma* info){
	I2C_Init();
	RTC_Read_Calendar(0x03, info);
	rtc_act(info);
};

void rtc_act(struct kasumiEmma* info){
	RTC_Read_Clock(0x00,info);
	if((info->minuto == 00) & (info->hora == 0)){//nuevo dia
		RTC_Read_Calendar(0x03, info);
	}
	if (info->hora & TimeFormat12){//caso 12h
		info->formato = 1;
		if(IsItPM(info->hora)){
			info->meridiano = 0;
		}
		else{
			info->meridiano = 1;
		}
	}
	else{//caso 24 horas
		info->formato = 0;
		info->meridiano = 0;
	}
};

