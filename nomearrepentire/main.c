/*
 * nomearrepentire.c
 *
 * Created: 09/06/2021 12:44:40 a. m.
 * Author : sabam
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"

#include "kasumiEmma.h"
#include "rtcKE.h"
#include "menu.h"
#include "botones.h"
#include "neopixelKE.h"
#include "IR_KE.h"
#include "dfplayerKE.h"
#include "uartcfg.h"
#include "uart.h"

struct kasumiEmma info;
struct botonesStatus botonRead;
TaskHandle_t retorno;
uint8_t contador = 0;

ISR (INT1_vect){
	leer(&botonRead);
	cli();
		botonRead.cambio = 0;
		info.botones = botonRead.state;
 		playerAct(&info);
 		neopixel_act(&info);
 		entrada(&info);//lcd
// 		
		
		botonRead.state = 0xAF;
		info.botones = botonRead.state;
		
		contador = 0;
		//vTaskResume(retorno);
}

static void playerT(void *pvParameters);
static void botonT(void *pvParameters);
static void lcdT(void *pvParameters);
//static void neopixelT(void *pvParameters);
static void rtcT(void *pvParameters);
static void irT(void *pvParameters);



int main(void)
{
	IR_init(0);
	sei();
	botonRead = botones_init(0,5, &info); //inicializar boton
	neopixel_init(16);
	rtc_init(&info);
	player_init(&info);
	menu_init(&info);
	uart_init();
	uart_tx(0x4F);
	//entrada(&info);
	DDRC |= 1<<1 | 1<<2 | 1<<3;
	xTaskCreate(playerT, "player", 100, NULL, 2, &retorno);
	xTaskCreate(botonT, "boton", 85, NULL, 2, NULL);
	xTaskCreate(lcdT, "lcd", 150, NULL, 1, NULL);
	//xTaskCreate(neopixelT, "neopixel", 100, NULL, 2, NULL);
	xTaskCreate(rtcT, "rtc", 85, NULL, 0, NULL);
	xTaskCreate(irT, "ir", 85, NULL, 0, NULL);
	
	
	vTaskStartScheduler();
    /* Replace with your application code */
    while (1) 
    {
    }
}

static void playerT(void *pvParameters){
	(void) pvParameters;
	while(1){
		contador++;
		PORTC ^= 1<<1;
		uart_tx(0x01);
		loop(&info);
		if(info.cambioCancion==1){
			display_menu(&info);
			uart_tx(0xFF);
			uart_tx(info.cancion);
			uart_tx(info.menuIndex);
			uart_tx(info.menuSubindex);
			info.cambioCancion = 0;
		}
		vTaskDelay(67);
	}
}
static void botonT(void *pvParameters){
	(void) pvParameters;
	while(1){
		uart_tx(0x02);
		//Para quitar pantalla de volumen
		contador++;
		if(contador > 5){
			botonRead.cambio = 1;
			//PORTC ^= 1<<1;
			
			contador = 0;
			entrada(&info);
			neopixel_act(&info);
		}
		vTaskDelay(67);
	}
}
static void lcdT(void *pvParameters){
	(void) pvParameters;
	while(1){
		uart_tx(0x03);
		display_menu(&info);
		recorrer(&info);
		vTaskDelay(33);
	}
}

static void rtcT(void *pvParameters){
	(void) pvParameters;
	while(1){
		uart_tx(0x04);
		rtc_act(&info);
		vTaskDelay(67);
	}
}
static void irT(void *pvParameters){
	(void) pvParameters;
	while(1){
		uart_tx(0x05);
		IR_read(&info);
		if(info.entradaControl != 0){
			playerIR(&info);
		}
		vTaskDelay(15);
	}
}
