#ifndef NEOPIXELRETO_H
#define NEOPIXELRETO_H

#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include "kasumiEmma.h"
#include "light_ws2812.h"

struct neopixel{
	uint8_t pixelCount;
	struct cRGB printArray[16];
	uint8_t bright;
	uint8_t combinacion;
};

void neopixel_init(uint8_t numPixeles);
void neopixel_act(struct kasumiEmma* info);
void neopixel_print_solido(struct cRGB *color);
void combinacion_act(uint8_t newCobinacion);

#endif