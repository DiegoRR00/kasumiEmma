#include "botones.h"

struct botonesStatus botones_init(uint8_t pinInicial, uint8_t pinFinal, struct kasumiEmma* info){
	struct botonesStatus botonStruct;
	botonStruct.state=0;
	botonStruct.rango = pinInicial*10 + pinFinal+1;
	botonStruct.cambio = 0;
	info->botones = 0xAF;
	EIMSK |= 1<<INT1;
	EICRA |= 1<<ISC11;
	sei();
	return botonStruct;
};
void antiRebote(struct botonesStatus* botonStruct, uint8_t pinNum){
	_delay_ms(10);
	if((botonesPin & 1<<pinNum)){//000x 0000
		return;
	}
	sei();
	while(!(botonesPin & 1<<pinNum));
	
	botonStruct->cambio = 1;
	botonStruct->state = pinNum;
};
void leer(struct botonesStatus* botonStruct){
	botonStruct->cambio = 0;
	uint8_t pinInicial, pinFinal;
	//5-8 58 5 58-5*10->8
	pinInicial = botonStruct->rango/10;
	pinFinal = botonStruct->rango-pinInicial*10;
	for(uint8_t i = pinInicial; i<pinFinal; i++){
		if(!(botonesPin & 1<<i)){
			antiRebote(botonStruct,i);
			if(botonStruct->cambio == 1){
				break;
			}
		}
	}
};