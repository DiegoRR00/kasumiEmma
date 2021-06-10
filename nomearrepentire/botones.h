#ifndef F_CPU
#define  F_CPU 8000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "kasumiEmma.h"

#define botonesPin PINB
#define botonesDDR DDRB

struct botonesStatus{
	uint8_t state;
	uint8_t rango;
	uint8_t cambio;
};

struct botonesStatus botones_init(uint8_t pinInicial, uint8_t pinFinal, struct kasumiEmma* info);
void antiRebote(struct botonesStatus* botonStruct, uint8_t pinNum);
void leer(struct botonesStatus* botonStruct);