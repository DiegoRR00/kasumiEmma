#include "menu.h"
#include "kasumiEmma.h"
#ifndef MENSAJES
#define MENSAJES

const char bienvenida1 [17]	PROGMEM = {"Bienvenide      "};
const char bienvenida2 [17]	PROGMEM 	= {"Equipo WorkBot  "};
char principal1 [17]	= {"HH:MMPM DD/MM/AA"};
const char principal2 [17]	PROGMEM	= {"~ Mas           "};
const char carpeta1 [17]	PROGMEM		= {"Selec. carpeta ^"};
const char carpeta20 [17]	PROGMEM		= {"~ Diego        v"};
const char carpeta21 [17]	PROGMEM		= {"~ Jorge        v"};
const char carpeta22 [17]	PROGMEM		= {"~ Sam          v"};
char reproduc1 [17]		= {"HH:MM PM        "};
char reproduc2 [40]		= {"Pan con jamon la cancion en vivo"};
const char volumen1 [17]	PROGMEM		= {"Volumen:        "};
const char config1 [17]		PROGMEM		= {"Selec. opcion: ^"};
const char config21 [17]	PROGMEM		= {"~ Ecualizador  v"};
const char config22 [17]	PROGMEM		= {"~ Neopixel     v"};
const char ecualizador1[17]	PROGMEM	= {"Selec. Eq.     ^"};
const char ecualizador21[17]	PROGMEM	= {"~ Normal       v"};
const char ecualizador22[17]	PROGMEM	= {"~ Pop          v"};
const char ecualizador23[17]	PROGMEM	= {"~ Rock         v"};
const char ecualizador24[17]	PROGMEM	= {"~ Jazz         v"};
const char ecualizador25[17]	PROGMEM	= {"~ Clasica      v"};
const char ecualizador26[17]	PROGMEM	= {"~ Bajo         v"};
const char led1 [17]	PROGMEM			= {"Selec. Color   ^"};
const char led21 [17]	PROGMEM			= {"~ Rainbow/Rosa v"};
const char led22 [17]	PROGMEM			= {"~ Rainbow/Cian v"};
const char led23 [17]	PROGMEM			= {"~ Rainbow/Rojo v"};
const char led24 [17]	PROGMEM			= {"~ Morado/Cian  v"};
const char led25 [17]	PROGMEM			= {"~ Azul/Rojo    v"};
const char led26 [17]	PROGMEM			= {"~ Verde/Rojo   v"};
const char mas1 [17]	PROGMEM			= {"Selec. Opcion  ^"};
const char mas21 [17]	PROGMEM			= {"~ Selec. Album v"};
const char mas22 [17]	PROGMEM			= {"~ Config.      v"};
#endif
#ifndef canciones
#define canciones
#define albumD "Diego"
#define albumJ "Jorge"
#define albumS "Sam"
const char album2[20][30] PROGMEM = {"NEO SKY NEO MAP","Awakening Promise","Kiseki Hikaru","START : DASH","Okosou Kiseki wo","Mirai Harmony","Hajimari wa Kimi no Sora","Katawaredoki","Sparkle","Dommage","I'm Gonna Be","Omoi yo Hitotsu ni Nare","Water Blue New World","Sunshine pika pika ondo","Happy maker","Yume ga Koko kara Hajimaru yo","VIVID WORLD","Butterfly","CHASE","Tsunagare Connect"};
const char album3[20][30] PROGMEM = {"Shin Sekai","Saikai","Unicos","Tus Ojos","Amega Na Ite","Anio Nuevo","Humanos Como Tu","Tu Volveras","San Miguel","Tus Ojos","Lost In Paradise","Bailar Contigo","Naimononedari","Palmar","Vamos A Morir","Red Swan","Tarde","Wild Side","Respiro","Unicos"};
const char album1[20][30] PROGMEM = {"Jive Talkin'","Night Fever","Sweet Child O'Mine","You Should Be Dancing","Stayin' Alive","How Deep Is Your Love","Embrujo","Obsesion","Lemon Tree","Burning Love","Suspicious Minds ","I'm Still Standing","Don't Go Breaking My Heart","More Than A Woman","If I Can't Have You","How Deep Is Your Love","Stayin' Alive","You Should Be Dancing","Sweet Child O'Mine","Night Fever"};
char cancionDisp [30] = {"                   "};
char vol2temp [17] = {"                 "};
#endif
struct menuS menuInfo;
void menu_init(struct kasumiEmma *info){
	char text1[17], text2[17];
	menuInfo.menuIndex = 0;
	menuInfo.letterIndex = 0;
	menuInfo.lcd = lq_init(0x27, 16, 2, LCD_2LINE);
	lq_clear(&menuInfo.lcd);
	lq_turnOnBacklight(&menuInfo.lcd);
	for(uint8_t p=0;p<17;p++){
		text1[p] = pgm_read_byte(&bienvenida1[p]);
		text2[p] = pgm_read_byte(&bienvenida2[p]);
	}
	imprimir(text1, text2);
	_delay_ms(1000);
	menuInfo.menuIndex=1;
	menuInfo.subIndex = 0;
	info ->menuIndex = 1;
	info -> menuSubindex = 0;
	display_menu(info);
};

void entrada(struct kasumiEmma *info){
	if(menuInfo.menuIndex==2){//Carpeta
		//Seleccion completa
		if(info->botones==1){
			menuInfo.menuIndex=3;//Reproduciendo
			info->carpeta = menuInfo.subIndex;
		}
		//Para arriba
		else if(info->botones==2){
			menuInfo.subIndex++;
			//Loopear
			if(menuInfo.subIndex>2){
				menuInfo.subIndex=0;
			}
		}
		//Para abajo
		else if(info->botones==3){
			menuInfo.subIndex--;
			//Loopear
			if(menuInfo.subIndex==0xFF){
				menuInfo.subIndex=2;
			}
		}
		//Regresar
		else if(info->botones==4){
			menuInfo.menuIndex=8;//mas
			menuInfo.subIndex=0;
		}
	}
	else if(menuInfo.menuIndex==3){//reproduc
		if((info->botones==2) | (info->botones==3)){
			menuInfo.menuIndex = 4;
		}
	}
	else if(menuInfo.menuIndex==4){//volumen
		if(info->botones==0xAF){
			menuInfo.menuIndex = 3;
		}
		else if((info->botones != 2) | (info->botones != 3)){
			menuInfo.menuIndex = 3; //reproduc
		}
	}
	else if(menuInfo.menuIndex==5){//config
		//Seleccion completa
		if(info->botones==1){
			if(menuInfo.subIndex==0){
				menuInfo.menuIndex=6; //eq
				menuInfo.subIndex=0;
			}
			else{
				menuInfo.menuIndex = 7;//led
				menuInfo.subIndex=0;
			}
		}
		//Para arriba
		else if(info->botones==2){
			menuInfo.subIndex++;
			//Loopear
			if(menuInfo.subIndex>1){
				menuInfo.subIndex=0;
			}
		}
		//Para abajo
		else if(info->botones==3){
			menuInfo.subIndex--;
			//Loopear
			if(menuInfo.subIndex==0xFF){
				menuInfo.subIndex=1;
			}
		}
		//Regresar
		else if(info->botones==4){
			menuInfo.menuIndex=8; //mas
			menuInfo.subIndex=0;
		}
	}
	else if(menuInfo.menuIndex==6){ //eq
		//Seleccion completa
		if(info->botones==1){
			menuInfo.menuIndex=5; //config
			menuInfo.subIndex=0;
		}
		//Para arriba
		else if(info->botones==2){
			menuInfo.subIndex++;
			//Loopear
			if(menuInfo.subIndex>5){
				menuInfo.subIndex=0;
			}
		}
		//Para abajo
		else if(info->botones==3){
			menuInfo.subIndex--;
			//Loopear
			if(menuInfo.subIndex==0xFF){
				menuInfo.subIndex=5;
			}
		}
		//Regresar
		else if(info->botones==4){
			menuInfo.menuIndex=5;//config
			menuInfo.subIndex=0;
		}
	}
	else if(menuInfo.menuIndex==7){//led
		//Seleccion completa
		if(info->botones==1){
			menuInfo.menuIndex=5; //config
			menuInfo.subIndex=0;
		}
		//Para arriba
		else if(info->botones==2){
			menuInfo.subIndex++;
			//Loopear
			if(menuInfo.subIndex>5){
				menuInfo.subIndex=0;
			}
		}
		//Para abajo
		else if(info->botones==3){
			menuInfo.subIndex--;
			//Loopear
			if(menuInfo.subIndex==0xFF){
				menuInfo.subIndex=5;
			}
		}
		//Regresar
		else if(info->botones==4){
			menuInfo.menuIndex=5;//config
			menuInfo.subIndex=0;
		}
	}
	else if(menuInfo.menuIndex==8){//mas
		//Seleccion completa
		if(info->botones==1){
			if(menuInfo.subIndex==0){
				menuInfo.menuIndex=2; //carpeta
				menuInfo.subIndex=0;
			}
			else{
				menuInfo.menuIndex=5; //config
				menuInfo.subIndex=0;
			}
		}
		
		//Para arriba
		else if(info->botones==2){
			menuInfo.subIndex++;
			//Loopear
			if(menuInfo.subIndex>1){
				menuInfo.subIndex=0;
			}
		}
		//Para abajo
		else if(info->botones==3){
			menuInfo.subIndex--;
			//Loopear
			if(menuInfo.subIndex==0xFF){
				menuInfo.subIndex=1;
			}
		}
		//Regresar
		else if(info->botones==4){
			menuInfo.menuIndex=1;//principal
		}
	}
	//pq como regreso menu
	if(menuInfo.menuIndex==1){//Menu principal
		if(info->botones==0){
			menuInfo.menuIndex=8;//mas
			menuInfo.subIndex=0;
		}
		if(info->botones==1){
			menuInfo.menuIndex=3;//mas
			menuInfo.subIndex=0;
		}
	}
	else if(info->botones==0){
		menuInfo.menuIndex=1;
	}
	
	info->menuIndex = menuInfo.menuIndex;
	info->menuSubindex = menuInfo.subIndex;
	//display_menu(info);
};
void imprimir(char texto1[17], char texto2[17]){
	
	lq_clear(&menuInfo.lcd);
	lq_setCursor(&menuInfo.lcd, 0, 0);
	lq_print(&menuInfo.lcd, texto1);
	lq_setCursor(&menuInfo.lcd, 1, 0);
	lq_print(&menuInfo.lcd, texto2);
};
void imprimirIndex(){
	char text1[17], text2[17];
	if(menuInfo.menuIndex == 2){
		if(menuInfo.subIndex == 0){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&carpeta1[p]);
				text2[p] = pgm_read_byte(&carpeta22[p]);
			}
			imprimir(text1,text2);
		}
		else if(menuInfo.subIndex == 1){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&carpeta1[p]);
				text2[p] = pgm_read_byte(&carpeta20[p]);
			}
			imprimir(text1, text2);
		}
		else{
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&carpeta1[p]);
				text2[p] = pgm_read_byte(&carpeta21[p]);
			}
			imprimir(text1, text2);
		}
	}
	else if(menuInfo.menuIndex == 5){
		if(menuInfo.subIndex==0){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&config1[p]);
				text2[p] = pgm_read_byte(&config21[p]);
			}
			imprimir(text1, text2);
		}
		else{
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&config1[p]);
				text2[p] = pgm_read_byte(&config22[p]);
			}
			imprimir(text1, text2);
		}
	}
	else if(menuInfo.menuIndex == 6){
		if(menuInfo.subIndex == 0){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&ecualizador1[p]);
				text2[p] = pgm_read_byte(&ecualizador21[p]);
			}
			imprimir(text1, text2);
		}
		else if(menuInfo.subIndex == 1){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&ecualizador1[p]);
				text2[p] = pgm_read_byte(&ecualizador22[p]);
			}
			imprimir(text1, text2);
		}
		else if(menuInfo.subIndex == 2){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&ecualizador1[p]);
				text2[p] = pgm_read_byte(&ecualizador23[p]);
			}
			imprimir(text1, text2);
		}
		else if(menuInfo.subIndex == 3){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&ecualizador1[p]);
				text2[p] = pgm_read_byte(&ecualizador24[p]);
			}
			imprimir(text1, text2);
		}
		else if(menuInfo.subIndex == 4){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&ecualizador1[p]);
				text2[p] = pgm_read_byte(&ecualizador25[p]);
			}
			imprimir(text1, text2);
		}
		else{
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&ecualizador1[p]);
				text2[p] = pgm_read_byte(&ecualizador26[p]);
			}
			imprimir(text1, text2);
		}
	}
	else if(menuInfo.menuIndex == 7){
		if(menuInfo.subIndex == 0){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&led1[p]);
				text2[p] = pgm_read_byte(&led21[p]);
			}
			imprimir(text1, text2);
		}
		else if(menuInfo.subIndex == 1){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&led1[p]);
				text2[p] = pgm_read_byte(&led22[p]);
			}
			imprimir(text1, text2);
		}
		else if(menuInfo.subIndex == 2){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&led1[p]);
				text2[p] = pgm_read_byte(&led23[p]);
			}
			imprimir(text1, text2);
		}
		else if(menuInfo.subIndex == 3){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&led1[p]);
				text2[p] = pgm_read_byte(&led24[p]);
			}
			imprimir(text1, text2);
		}
		else if(menuInfo.subIndex == 4){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&led1[p]);
				text2[p] = pgm_read_byte(&led25[p]);
			}
			imprimir(text1, text2);
		}
		else{
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&led1[p]);
				text2[p] = pgm_read_byte(&led26[p]);
			}
			imprimir(text1, text2);
		}
	}
	else if(menuInfo.menuIndex == 8){
		if(menuInfo.subIndex == 0){
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&mas1[p]);
				text2[p] = pgm_read_byte(&mas21[p]);
			}
			imprimir(text1, text2);
		}
		else{
			for(uint8_t p=0;p<17;p++){
				text1[p] = pgm_read_byte(&mas1[p]);
				text2[p] = pgm_read_byte(&mas22[p]);
			}
			imprimir(text1, text2);;
		}
	}
};
void recorrer(struct kasumiEmma *info){
	if(menuInfo.menuIndex==3){
		uint8_t sizeText = 30, numEspacios = 0; //numEspacio caracteres vacios dentro del char, size cancionDisp son caracteres ASCII no válidos
		uint8_t k=0;
		for (k=0;k<30;k++){
			if(cancionDisp[k]==0){
				numEspacios++;
				if(numEspacios==2){//Si hay más de dos espacios, ya acabo la palabra
					sizeText=k;
					break;
				}
			}
			
			else{
				numEspacios=0;
			}
		}
		if(sizeText>17){//Si es necesario ciclar
			menuInfo.letterIndex++;
			char temp[17]={"*****************"};
			uint8_t j,n=0;
			//Imprimir hasta que me acabe el texto a imprimir
			for (j = 0; j < 17 && j+menuInfo.letterIndex<sizeText; j++){
				temp[j] = cancionDisp[j+menuInfo.letterIndex];
				n=j;
			}
			//Rellenar de espacios lo que sobra de la pantalla
			if(menuInfo.letterIndex>=sizeText-17){
				for(j = n;j<17;j++){
					temp[j]=' ';
				}
			}
			//Regresar la palabra de derecha a izquierda
			if (menuInfo.letterIndex>sizeText){
				uint8_t numTemp = 16 -(menuInfo.letterIndex-sizeText);
				for (uint8_t i=0;(i<menuInfo.letterIndex-16) && (numTemp+i<17);i++){
					temp[numTemp+i]=cancionDisp[i];
				}
			}
			//Reiniciar
			if(menuInfo.letterIndex>sizeText+16){
				menuInfo.letterIndex=0;
			}
			//Enviar a lcd
			lq_setCursor(&menuInfo.lcd, 1, 0);
			lq_print(&menuInfo.lcd, temp);
			//_delay_ms(500);
		}
		else{
			lq_setCursor(&menuInfo.lcd, 1, 0);
			lq_print(&menuInfo.lcd, cancionDisp);

		}
			
		
	}
};
void display_menu(struct kasumiEmma *info){
	uint8_t index = menuInfo.menuIndex;
	char text1[17], text2[17];
	if(index == 1){
		//Imprimir hora
		sprintf(principal1, "%02x:%02x   %02x/%02x/%02x", (info->hora & 0b00011111), info->minuto, info->dia, info->mes, info->anio);
		if(info->formato == 1){
			if(info->meridiano){
				principal1[6] = 'A';
			}
			else{
				principal1[6] = 'P';
			}
			principal1[7] = 'M';
		}
		else{
			principal1[6] = ' ';
			principal1[7] = ' ';
		}
		for(uint8_t p=0;p<17;p++){
			text2[p] = pgm_read_byte(&principal2[p]);
		}
		imprimir(principal1,text2);
	}
	else if(index == 2){
		imprimirIndex();
	}
	else if(index == 3){
		sprintf(reproduc1, "%02x:%02x           ",(info->hora & 0b00011111),info->minuto);
		if(info->formato == 1){
			if(info->meridiano){
				reproduc1[6] = 'A';
			}
			else{
				reproduc1[6] = 'P';
			}
			reproduc1[7] = 'M';
		}
		else{
			reproduc1[6] = ' ';
			reproduc1[7] = ' ';
		}
		if(info->carpeta==0){
			reproduc1[11] = ' ';
			reproduc1[12] = ' ';
			reproduc1[13] = 'S';
			reproduc1[14] = 'a';
			reproduc1[15] = 'm';
		}
		else if(info->carpeta==1){
			reproduc1[11] = 'D';
			reproduc1[12] = 'i';
			reproduc1[13] = 'e';
			reproduc1[14] = 'g';
			reproduc1[15] = 'o';
		}
		else{
			reproduc1[11] = 'J';
			reproduc1[12] = 'o';
			reproduc1[13] = 'r';
			reproduc1[14] = 'g';
			reproduc1[15] = 'e';
		}
		uint8_t index1;
		if(info->carpeta==0){
			for(uint8_t letra = 0; letra<30;letra++){
				cancionDisp[letra] = pgm_read_byte(&album1[info->cancion][letra]);
			}
		}
		else if(info->carpeta==1){
			index1 = info->cancion-cancionesAlbum1;
			for(uint8_t letra = 0; letra<30;letra++){
				cancionDisp[letra] = pgm_read_byte(&album2[index1][letra]);
			}
		}
		else{
			index1 = info->cancion-cancionesAlbum1-cancionesAlbum2;
			for(uint8_t letra = 0; letra<30;letra++){
				cancionDisp[letra] = pgm_read_byte(&album3[index1][letra]);
			}
		}
		if(info->cambioCancion == 1){
			menuInfo.letterIndex = 0xFF;
		}
		if(menuInfo.subIndex==0){
			imprimir(reproduc1, cancionDisp);
		}
		else if(menuInfo.subIndex==1){
			imprimir(reproduc1, cancionDisp);
		}
		else{
			imprimir(reproduc1, cancionDisp);
		}
	}
	else if(index == 4){
		sprintf(vol2temp, "%02u", info->volumen);
		for(uint8_t p=0;p<17;p++){
			text1[p] = pgm_read_byte(&volumen1[p]);
		}
		imprimir(text1, vol2temp);
	}
	else if(index == 5){
		imprimirIndex();
	}
	else if(index == 6){
		imprimirIndex();
	}
	else if(index == 7){
		imprimirIndex();
	}
	else if(index == 8){
		imprimirIndex();
	}
};