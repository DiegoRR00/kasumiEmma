#include "neopixelKE.h"

struct neopixel np_info;
struct cRGB colores[8];
//rojo, naranja
/*
char led21 [17]			= {"~ Rainbow/Rosa v"};0 
char led22 [17]			= {"~ Rainbow/Cian v"};1
char led23 [17]			= {"~ Rainbow/Rojo v"};2
char led24 [17]			= {"~ Morado/Cian  v"};3
char led25 [17]			= {"~ Azul/Rojo    v"};4
char led26 [17]			= {"~ Verde/Rojo   v"};5
*/
void neopixel_rainbow(){
	uint8_t colorIndex = 6;
	//rojo
	np_info.printArray[0].r = colores[colorIndex].r ; np_info.printArray[0].g = colores[colorIndex].g ; np_info.printArray[0].b = colores[colorIndex].b ;
	np_info.printArray[1].r = colores[colorIndex].r ; np_info.printArray[1].g = colores[colorIndex].g ; np_info.printArray[1].b = colores[colorIndex].b ;
	//naranja
	colorIndex = 7;
	np_info.printArray[2].r = colores[colorIndex].r ; np_info.printArray[2].g = colores[colorIndex].g ; np_info.printArray[2].b = colores[colorIndex].b ;
	np_info.printArray[3].r = colores[colorIndex].r ; np_info.printArray[3].g = colores[colorIndex].g ; np_info.printArray[3].b = colores[colorIndex].b ;
	//amarillo
	colorIndex = 2;
	np_info.printArray[4].r = colores[colorIndex].r ; np_info.printArray[4].g = colores[colorIndex].g ; np_info.printArray[4].b = colores[colorIndex].b ;
	np_info.printArray[5].r = colores[colorIndex].r ; np_info.printArray[5].g = colores[colorIndex].g ; np_info.printArray[5].b = colores[colorIndex].b ;
	//verde
	colorIndex = 1;
	np_info.printArray[6].r = colores[colorIndex].r ; np_info.printArray[6].g = colores[colorIndex].g ; np_info.printArray[6].b = colores[colorIndex].b ;
	np_info.printArray[7].r = colores[colorIndex].r ; np_info.printArray[7].g = colores[colorIndex].g ; np_info.printArray[7].b = colores[colorIndex].b ;
	//cian
	colorIndex = 4;
	np_info.printArray[8].r = colores[colorIndex].r ; np_info.printArray[8].g = colores[colorIndex].g ; np_info.printArray[8].b = colores[colorIndex].b ;
	np_info.printArray[9].r = colores[colorIndex].r ; np_info.printArray[9].g = colores[colorIndex].g ; np_info.printArray[9].b = colores[colorIndex].b ;
	//azul
	colorIndex = 0;
	np_info.printArray[10].r = colores[colorIndex].r ; np_info.printArray[10].g = colores[colorIndex].g ; np_info.printArray[10].b = colores[colorIndex].b ;
	np_info.printArray[11].r = colores[colorIndex].r ; np_info.printArray[11].g = colores[colorIndex].g ; np_info.printArray[11].b = colores[colorIndex].b ;
	//morado
	colorIndex = 3;
	np_info.printArray[12].r = colores[colorIndex].r ; np_info.printArray[12].g = colores[colorIndex].g ; np_info.printArray[12].b = colores[colorIndex].b ;
	np_info.printArray[13].r = colores[colorIndex].r ; np_info.printArray[13].g = colores[colorIndex].g ; np_info.printArray[13].b = colores[colorIndex].b ;
	//rosa
	colorIndex = 5;
	np_info.printArray[14].r = colores[colorIndex].r ; np_info.printArray[14].g = colores[colorIndex].g ; np_info.printArray[14].b = colores[colorIndex].b ;
	np_info.printArray[15].r = colores[colorIndex].r ; np_info.printArray[15].g = colores[colorIndex].g ; np_info.printArray[15].b = colores[colorIndex].b ;
	ws2812_brightness(np_info.printArray,np_info.pixelCount,np_info.bright);
	ws2812_sendarray((uint8_t *)np_info.printArray,np_info.pixelCount*3);
}
void neopixel_mitades(uint8_t mitadIndex, struct cRGB *color){
	//apagar lo qeu no se usa
	for(uint8_t i=0;i<mitadIndex*4;i++){
		np_info.printArray[i].r = 0;
		np_info.printArray[i].g = 0;
		np_info.printArray[i].b = 0;
	}
	//prender lo que se usa
	for(uint8_t i=mitadIndex*4;i<mitadIndex*4+8;i++){
		if(i>15){
			uint8_t k= i-16;
			np_info.printArray[k].r = color->r;
			np_info.printArray[k].g = color->g;
			np_info.printArray[k].b = color->b;
		}
		else{
			np_info.printArray[i].r = color->r;
			np_info.printArray[i].g = color->g;
			np_info.printArray[i].b = color->b;
		}
	}
	//apagar lo que no se usa parte 2
	if(mitadIndex<2){
		for(uint8_t i=mitadIndex*4+8;i<16;i++){
			np_info.printArray[i].r = 0;
			np_info.printArray[i].g = 0;
			np_info.printArray[i].b = 0;
		}
	}
	ws2812_brightness(np_info.printArray,np_info.pixelCount,np_info.bright);
	ws2812_sendarray((uint8_t *)np_info.printArray,np_info.pixelCount*3);
}
void neopixel_init(uint8_t numPixeles){
	//colores solidos
	colores[0].r = 0 ; colores[0].g = 0 ; colores[0].b = 255 ; // azul
	colores[1].r = 0 ; colores[1].g = 255 ; colores[1].b = 0 ; // verde
	colores[2].r = 128 ; colores[2].g = 128 ; colores[2].b = 0 ; // amarillo
	colores[3].r = 64 ; colores[3].g = 0 ; colores[3].b = 128 ; // morado
	colores[4].r = 0 ; colores[4].g = 192 ; colores[4].b = 128 ; // cian
	colores[5].r = 192 ; colores[5].g = 32 ; colores[5].b = 128 ; // rosa
	colores[6].r = 255 ; colores[6].g = 0 ; colores[6].b = 0 ; // rojo
	colores[7].r = 192 ; colores[7].g = 64 ; colores[7].b = 0 ; // naranja
	//co
	np_info.pixelCount = numPixeles;
	np_info.bright=7;
	np_info.combinacion=0;
	//espera
	neopixel_print_solido(&colores[0]);

};
void neopixel_act(struct kasumiEmma* info){
	if((info->menuIndex == 7) && (info->botones == 1)){
		np_info.combinacion = info->menuSubindex;
	}
	//if(info->enReproMenu==1){
		if(info->estadoReproduccion==1){
			if(np_info.combinacion<3){
				neopixel_rainbow();
			}
			else if(np_info.combinacion==3){ // mmorado
				neopixel_print_solido(&colores[3]);
			}
			else if(np_info.combinacion==4){ //Azul
				neopixel_print_solido(&colores[0]);
			}
			else if(np_info.combinacion==5){ //verde
				neopixel_print_solido(&colores[1]);
			}
		}
		else if(info->estadoReproduccion==0){
			if((np_info.combinacion>3) | (np_info.combinacion==2)){ //rojo
				neopixel_print_solido(&colores[6]);
			}
			else if((np_info.combinacion==3) | (np_info.combinacion==1)){ // cian
				neopixel_print_solido(&colores[4]);
			}
			else {//rosa
				neopixel_print_solido(&colores[5]);
			}
		}
		if(info->botones==2){//vol+
			neopixel_mitades(3,&colores[3]);
		}
		else if(info->botones==3){//vol--
			neopixel_mitades(1,&colores[4]);
		}
		else if(info->botones==4){//sig
			neopixel_mitades(0,&colores[1]);
		}
		else if(info->botones==5){//ant
			neopixel_mitades(2,&colores[2]);
		}
	//}
	
};
void neopixel_print_solido(struct cRGB *color){
	for(uint8_t n = 0; n<np_info.pixelCount;n++){
		np_info.printArray[n].r = color->r;
		np_info.printArray[n].g = color->g;
		np_info.printArray[n].b = color->b;
	}
	ws2812_brightness(np_info.printArray,np_info.pixelCount,np_info.bright);
	ws2812_sendarray((uint8_t *)np_info.printArray,np_info.pixelCount*3);
};
void combinacion_act(uint8_t newCobinacion){
	if(newCobinacion>5){
		newCobinacion=5;
	}
	np_info.combinacion=newCobinacion;
};