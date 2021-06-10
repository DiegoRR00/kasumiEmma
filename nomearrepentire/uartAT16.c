#include "uartAT16.h"


void UART_init(long USART_BAUDRATE)
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);/* Turn on transmission and reception */
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);/* Use 8-bit character sizes */
	UBRR0L = BAUD_PRESCALE;		/* Load lower 8-bits of the baud rate value */
	UBRR0H = (BAUD_PRESCALE >> 8);	/* Load upper 8-bits*/
}

bool UART_RxChar(uint8_t *data)
{
		while ((UCSR0A & (1 << RXC0)) == 0);/* Wait till data is received */
		*data = UDR0;			/* Return the byte*/
		return true;

}

void UART_TxChar(char ch)
{
	while (! (UCSR0A & (1<<UDRE0)));	/* Wait for empty transmit buffer*/
	UDR0 = ch ;
}

void UART_SendString(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		UART_TxChar(str[j]);	
		j++;
	}
}
bool UART_available(){
	if(UCSR0A & 1<<RXC0){
		return false;
	}
	return true;
}
bool UART_RxBuffer(uint8_t *buffer, uint16_t len)
{
	for(int i=0; i < len; i++)
	{
		if(!UART_RxChar(&buffer[i]))
		{
			//return false;
		}
		
	}
	
	return true;
}
void UART_TxBuffer(uint8_t *buffer, uint16_t len)
{
	for(int i=0; i < len; i++)
	{
		UART_TxChar(buffer[i]);
	}
}