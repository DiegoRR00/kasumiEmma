#ifndef F_CPU
#define F_CPU 8000000
#endif

#ifndef KASUMIN_EMMA
#define KASUMIN_EMMA
#include <avr/io.h>
#include <util/delay.h>
#define cancionesAlbum1 20
#define cancionesAlbum2 20
#define cancionesAlbum3 20
#define botonesInicial	0xAF
#define cancionInit		0xFE


struct kasumiEmma{
	uint8_t estadoReproduccion; //player
	uint8_t botones; // 0xAF no hay entrada en cierto tiempo botones
	uint8_t volumen; //player
	uint8_t menuIndex; //menu
	uint8_t menuSubindex; //menu
	uint8_t entradaControl; //player
	uint8_t cancion; //player
	uint8_t carpeta; //player
	uint8_t hora; //rtc
	uint8_t minuto; //rtc
	uint8_t meridiano;//si es 1, am rtc
	uint8_t formato; //si es uno formato 12 rtc
	uint8_t dia; //rtc
	uint8_t mes; //rtc
	uint8_t anio; //rtc
	uint8_t cambioCancion; //player
};
#endif