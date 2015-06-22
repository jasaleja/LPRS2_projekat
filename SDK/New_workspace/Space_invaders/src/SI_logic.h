/*
 * SI_logic.h
 *
 *  Created on: 16.06.2015.
 *      Author: student
 */

#ifndef SI_LOGIC_H_
#define SI_LOGIC_H_

#include "SI_defines.h"
#include "SI_globals.h"
#include "SI_draw.h"

void move_spaceship(Xuint8*, Xuint8*);
void shoot_projectile(Xuint8*, Xuint8);
void move_projectile(Xuint8*);
void move_invaders_row(Xuint8, Xint8*, Xuint8*, Xuint8*);
void generate_init_invaders_positions();

#endif /* SI_LOGIC_H_ */