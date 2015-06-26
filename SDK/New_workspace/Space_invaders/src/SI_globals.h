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
		shoot_flag,
		game_over,
		input;

extern Xuint32 cursor_position;
extern int counter;

Xuint8 flag_row[INIT_ROWS];
/****************************/

int flag, counter1, s, seed;

Xuint8 invaders_map[MAX_PROJECTILES_X][MAX_PROJECTILES_Y];
Xuint8 invaders_num;

Xuint8 projectiles_of_ship_num[MAX_PROJECTILES_X];	//Number of projectiles in column
Xuint8 projectiles_map[MAX_PROJECTILES_X][MAX_PROJECTILES_Y];

#endif /* SI_GLOBALS_H_ */
