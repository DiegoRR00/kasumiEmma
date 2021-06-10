
#ifndef MENU_H
#define  MENU_H
#ifndef F_CPU
#define  F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <avr/pgmspace.h> //https://www.nongnu.org/avr-libc/user-manual/pgmspace.html
#include "liquid_crystal_i2c.h"
#include "kasumiEmma.h"

/*
menuIndex
	0	bienvenida
	1	menuPrincipal	Hora fecha mas
	2	carpeta			Tres carpetas
		Sub indice
			0	Diego	001
			1	Jorge	002
			2	Sam		003
	3	reproduciendo	Hora carpeta # nombre cancion
	4	volumen			Volumen # num volumen
	5	config			Ecualizador / color led
		Sub
			0	Eq
			1	led
	6	ecualizador		6 ecualizadores
		Sub
			0	Normal
			1	Pop
			2	Rock
			3	Jazz
			4	Clasica
			5	Bajo		
	7	led				6 opciones de led
		Sub
			0	Rainbow / Rosa
			1	Rainbow / Cian
			2	Rainbow / Rojo
			3	Morado / Cian
			4	Azul / Rojo
			5	Verde / Rojo
	8	mas				Carpeta / config
		Sub
			0	Selec Carpeta
			1	Config
*/

struct menuS{
	uint8_t menuIndex;
	uint8_t subIndex;
	uint8_t letterIndex;
	struct LiquidCrystalDevice_t lcd;
};

void menu_init(struct kasumiEmma *info);
void display_menu(struct kasumiEmma *info);
void entrada(struct kasumiEmma *info);
void imprimir(char texto1[17], char texto2[17]);
void imprimirIndex();
void recorrer(struct kasumiEmma *info);
#endif