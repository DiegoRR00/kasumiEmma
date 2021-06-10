#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "IR_NEC.h"
#include "kasumiEmma.h"

void IR_read(struct kasumiEmma *info)
{
	DDRC |= 1;
	cli();
	uint8_t recibimos = IR_data_ready();
	sei();
	if (recibimos){
		uint8_t paquete = IR.command;
		if (paquete == 0x45) {//power
			info->entradaControl = 1;
			
		}
		else if (paquete == 0x44) {// play
			info->entradaControl = 2;
		}
		else if (paquete == 0x09) {// vol+
			info->entradaControl = 3;
			 
		}
		else if (paquete == 0x15) {// vol-
			info->entradaControl = 4;
			 
		}
		else if (paquete == 0x40) {// prev
			info->entradaControl = 5;
			//PORTC |= 1<<5;
		}
		else if (paquete == 0x43) {// next
			info->entradaControl = 6;
			 
		}
		else if (paquete == 0x07) { // equalizador
			info->entradaControl = 7;
			 
		}
		else{
			info->entradaControl = 0xAF;
			 
		}
		_delay_ms(15);
		//PORTC = 0;
	}
	else{
		info->entradaControl = 0;
	}
}