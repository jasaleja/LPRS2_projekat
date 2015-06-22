/*
 * SI_globals.h
 *
 *  Created on: 16.06.2015.
 *      Author: student
 */

#ifndef SI_GLOBALS_H_
#define SI_GLOBALS_H_

#include "SI_defines.h"

/* variables for interrupts */
extern XIntc Intc;

extern  Xuint8	spaceship_speed,
		projectil_speed,
		spaceship_flag,
		projectil_flag,
		input;

extern int counter;
Xuint8 flag_row[INIT_ROWS];
/****************************/

invader_t invaders[INIT_NUM];		//array of structs invaders

Xuint8 projectiles_map[MAX_PROJECTILES_X][MAX_PROJECTILES_Y];
Xuint8 projectiles_num[MAX_PROJECTILES_X];	//num of projectiles in column

#endif /* SI_GLOBALS_H_ */
