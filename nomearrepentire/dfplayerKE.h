#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "kasumiEmma.h"
#include "DFPLAYER.h"
#include "uartAT16.h"
#ifndef DFP_KE_H
#define DFP_KE_H

void player_init(struct kasumiEmma* info);
void playerAct(struct kasumiEmma* info);
void playerIR (struct kasumiEmma* info);
void loop(struct kasumiEmma* info);


#endif