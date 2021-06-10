#include "dfplayerKE.h"
#define volInicial 15

#define play 1
#define volMas 2
#define volMenos 3
#define ant 4
#define sig 5


uint8_t eq_sel;
void player_init(struct kasumiEmma* info){
	DFP_Initialize();
	_delay_ms(3000);
	for(uint8_t k=30;k>volInicial;k--){
		DFP_DecreaseVolume();
	}
	info->volumen = volInicial;
	info->estadoReproduccion = 0;
	DFP_QueryCurrentStatus();
	DFP_SetEQ(eq_sel);
// 	DFP_PlayRandomTrack();
// 	DFP_Pause();
	info->cancion = 0xFE;
	info -> carpeta = 0;
	info -> cambioCancion = 0;
	info -> entradaControl = 0;
	
};

void reproducAlbum(uint8_t albumNum, struct kasumiEmma* info){
	if(albumNum==0){
		DFP_PlayTrackInFolder(0,0);
		info->estadoReproduccion = 1;
		info->carpeta = 0;
	}
	else if(albumNum == 1){
		DFP_PlayTrackInFolder(0,0);
		for (uint8_t k=0;k<cancionesAlbum1;k++){
			DFP_PlayNext();
			_delay_ms(5);
		}
		info->estadoReproduccion = 1;
		info->carpeta = 1;
	}
	else{
		DFP_PlayTrackInFolder(0,0);
		for (uint8_t k=0;k<cancionesAlbum3;k++){
			DFP_PlayPrevious();
			_delay_ms(5);
		}
		info->estadoReproduccion = 1;
		info->carpeta = 2;
	}
	DFP_QueryCurrentTrack();
	info->cancion = DFPlayerInfo.CurrentTrack;
	info -> cambioCancion = 1;
}

void playPause(struct kasumiEmma* info){
	if(info->estadoReproduccion == 1){
		DFP_Pause();
		info->estadoReproduccion = 0;
	}
	else{
		DFP_Play();
		info->estadoReproduccion = 1;
	}
	info->cambioCancion = 1;
}

void actVol(uint8_t accion, struct kasumiEmma* info){
	if(accion == 1){
		if(info->botones<30){
			DFP_IncreaseVolume();
			info->botones++;
		}
	}
	else{
		if(info->botones>0){
			DFP_DecreaseVolume();
			info->botones--;
		}
	}
	DFP_QueryCurrentVolume();
	info->volumen = DFPlayerInfo.CurrentVolume;
}

void cambiarCancion (uint8_t accion, struct kasumiEmma* info){
	if(accion==1){
		uint8_t cancionMayor;
		if(info->carpeta == 0){
			cancionMayor = cancionesAlbum1;
		}
		else if(info->carpeta == 1){
			cancionMayor = cancionesAlbum1 + cancionesAlbum2;
		}
		else{
			cancionMayor = cancionesAlbum1 + cancionesAlbum2 + cancionesAlbum3;
		}
		DFP_QueryCurrentTrack();
		if(DFPlayerInfo.CurrentTrack == cancionMayor){
			reproducAlbum(info->carpeta, info);
		}
		else{
			DFP_PlayNext();
		}
	}
	else{
		uint8_t cancionMenor;
		if(info->carpeta == 0){
			cancionMenor = 0;
		}
		else if(info->carpeta == 1){
			cancionMenor = cancionesAlbum1 + 1;
		}
		else{
			cancionMenor = cancionesAlbum1 + cancionesAlbum2 + 1;
		}
		DFP_QueryCurrentTrack();
		if(DFPlayerInfo.CurrentTrack == cancionMenor){
			uint8_t carpetaTemp;
			if(info->carpeta < 2){
				carpetaTemp = info->carpeta+1;
			}
			else{
				carpetaTemp = 0;
			}
			reproducAlbum(carpetaTemp, info);
			DFP_PlayPrevious();
			if(carpetaTemp!=0){
				carpetaTemp--;
			}
			else{
				carpetaTemp = 2;
			}
			info->carpeta = carpetaTemp;
		}
		else{
			DFP_PlayPrevious();
		}
	}
	DFP_QueryCurrentTrack();
	info->cancion = DFPlayerInfo.CurrentTrack;
	info->cambioCancion = 1;
	info->estadoReproduccion = 1;
}

void playerAct(struct kasumiEmma* info){
	if(info->menuIndex==2){//Carpeta
		//Seleccion completa
		if(info->botones==play){//play
			reproducAlbum(info->menuSubindex, info);
		}
	}
	else if(info->menuIndex==3){//reproduc
		if(info->botones == play){
			playPause(info);
		}
		else if(info->botones == volMas){
			actVol(1,info);
		}
		else if(info->botones == volMenos){
			actVol(0, info);
		}
		else if(info->botones == sig){
			cambiarCancion(0,info);
		}
		else if(info->botones == ant){
			cambiarCancion(1,info);
		}
	}
	else if(info->menuIndex==4){//volumen
		if(info->botones == play){
			playPause(info);
		}
		else if(info->botones == volMas){
			actVol(1,info);
		}
		else if(info->botones == volMenos){
			actVol(0, info);
		}
		else if(info->botones == sig){
			cambiarCancion(0,info);
		}
		else if(info->botones == ant){
			cambiarCancion(1,info);
		}
	}
	else if(info->menuIndex==6){ //eq
		//Seleccion completa
		if(info->botones==play){
			eq_sel = info->menuSubindex;
			DFP_SetEQ(eq_sel);
		}
	}
	//pq como regreso menu
	if(info->menuIndex==1){//Menu principal
		if(info->botones==play){
			if(info->cancion == 0xFE){
				reproducAlbum(0,info);
			}
		}
	}
	
	
// 	if(info->botones!=0xAF){
// 		//Play en principal 1
// 		if((info->menuIndex==1) & (info->botones==1)){
// 			if(info->estadoReproduccion==1){//play
// 				DFP_Stop();
// 				info->estadoReproduccion=0;
// 			}
// 			else{//pausa
// 				if(info->cancion==0xFE){
// 					DFP_PlayTrackInFolder(0,0);
// 				}
// 				DFP_Play();
// 				info->estadoReproduccion=1;
// 			}
// 			DFP_QueryCurrentTrack();
// 			info->cancion = DFPlayerInfo.CurrentTrack;
// 		}
// 		//play en selec carpeta menuSubIndex 2
// 		else if((info->menuIndex==2) & (info->botones==1)){
// 			if(info->menumenuSubIndex==0){
// 				DFP_PlayTrackInFolder(0,0);
// 				info->carpeta=0;
// 			}
// 			else if(info->menumenuSubIndex==1){
// 				DFP_PlayTrackInFolder(0,0);
// 				for(uint8_t i=0;i<cancionesAlbum1;i++){
// 					DFP_PlayNext();
// 				}
// 				info->carpeta=1;
// 			}
// 			else if(info->menumenuSubIndex==2){
// 				DFP_PlayTrackInFolder(0,0);
// 				for(uint8_t i=0;i<cancionesAlbum3;i++){
// 					DFP_PlayPrevious();
// 				}
// 				info->carpeta=2;
// 			}
// 			
// 		}
// 		//Cualquier cosa en reproduc menos menu(pw) 3
// 		else if((info->menuIndex==3)){
// 			if(info->botones==1){//play
// 				if(info->estadoReproduccion){//play
// 					DFP_Pause();
// 					info->estadoReproduccion=0;
// 				}
// 				else{//pausa
// 					DFP_Play();
// 					info->estadoReproduccion=1;
// 				}
// 			}
// 			else if(info->botones==2){//vol+
// 				DFP_IncreaseVolume();
// 				if(info->volumen<30){
// 					info->volumen++;
// 				}
// 			}
// 			else if(info->botones==3){//vol-
// 				DFP_DecreaseVolume();
// 				if(info->volumen>0){
// 					info->volumen--;
// 				}
// 			}
// 			else if(info->botones ==4){//ant
// 				DFP_PlayPrevious();
// 				info->estadoReproduccion=1;
// 				DFP_QueryCurrentTrack();
// 				info->cancion = DFPlayerInfo.CurrentTrack;
// 				info->cambioCancion = 1;
// 			}
// 			else if(info->botones==5){//sig
// 				DFP_PlayNext();
// 				info->estadoReproduccion=1;
// 				DFP_QueryCurrentTrack();
// 				info->cancion = DFPlayerInfo.CurrentTrack;
// 				info->cambioCancion = 1;
// 			}
// 		}
// 		//Volumen vol+, vol- y play 4
// 		else if((info->menuIndex==4)){
// 			if(info->botones==2){
// 				DFP_IncreaseVolume();
// 				if(info->volumen<30){
// 					info->volumen++;
// 				}
// 			}
// 			else if(info->botones==3){
// 				DFP_DecreaseVolume();
// 				if(info->volumen>0){
// 					info->volumen--;
// 				}
// 			}
// 			else if(info->botones==1){
// 				if(info->estadoReproduccion){//play
// 					DFP_Stop();
// 					info->estadoReproduccion=0;
// 				}
// 				else{//pausa
// 					DFP_Play();
// 					info->estadoReproduccion=1;
// 				}
// 			}
// 		}
// 		//play en eq 6 Subondex
// 		else if((info->menuIndex==6)){
// 			eq_sel = info->menumenuSubIndex+1;
// 		}
// 	}

};

void playerIR (struct kasumiEmma* info){
	if(info->entradaControl!=0){
		if(info->entradaControl==1){ // power
			DFP_Stop();
			info->estadoReproduccion = 0;
			info->carpeta = 0;
			info ->cancion = 0xFE;
		}
		else if(info->entradaControl==2){ // play
			playPause(info);
		}
		else if(info->entradaControl==3){ //vol+
			actVol(0,info);
		}
		else if(info->entradaControl==4){ //vol-
			actVol(1,info);
		}
		else if(info->entradaControl==5){ //ant
			cambiarCancion(1,info);
		}
		else if(info->entradaControl==6){ // sig
			cambiarCancion(0, info);
		}
		else if(info->entradaControl==7){//eq
			eq_sel++;
			if(eq_sel>5){
				eq_sel=0;
			}
			DFP_SetEQ(eq_sel);
		}
	}	
};
void loop(struct kasumiEmma* info){
	//Checa si no debe reproducir la nueva
	DFP_QueryCurrentStatus();
	if(DFPlayerInfo.CurrentStatus==0){
		cambiarCancion(1, info);
	}
// 	//Actualiza la cancion que estas oyendo
// 	DFP_QueryCurrentTrack();
// 	info->cancion = DFPlayerInfo.CurrentTrack;
// 	uint8_t ultimoIndex, numCanciones;
// 	if(info->carpeta==0){
// 		ultimoIndex = cancionesAlbum1;
// 		numCanciones = cancionesAlbum1;
// 	}
// 	else if(info->carpeta==1){
// 		ultimoIndex = cancionesAlbum1+cancionesAlbum2;
// 		numCanciones = cancionesAlbum2;
// 	}
// 	else{
// 		ultimoIndex = cancionesAlbum1+cancionesAlbum2+cancionesAlbum3;
// 		numCanciones = cancionesAlbum3;
// 	}
// 	if(DFPlayerInfo.CurrentTrack>=ultimoIndex){
// 		DFP_Pause();
// 		for(uint8_t j=0;j<numCanciones;j++){
// 			DFP_PlayPrevious();
// 		}
// 	}
			
	
};
