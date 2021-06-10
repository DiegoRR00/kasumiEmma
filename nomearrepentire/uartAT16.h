/*

	ATmega 16 UART echo program
	http://www.electronicwings.com

*/ 
#ifndef F_CPU
#define F_CPU 8000000UL			/* Define frequency here its 8MHz */
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


void UART_init(long USART_BAUDRATE);
bool UART_RxChar(uint8_t *data);
void UART_TxChar(char ch);
void UART_SendString(char *str);
bool UART_available();
bool UART_RxBuffer(uint8_t *buffer, uint16_t len);
void UART_TxBuffer(uint8_t *buffer, uint16_t len);
