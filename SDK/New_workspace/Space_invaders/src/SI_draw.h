/*
 * SI_draw.h
 *
 *  Created on: 16.06.2015.
 *      Author: student
 */

#ifndef SI_DRAW_H_
#define SI_DRAW_H_

#include "SI_defines.h"
#include "SI_globals.h"

void draw_square(Xuint32, Xuint8, Xuint8);
void draw_invader(Xuint32, Xuint8, Xuint8, Xuint8);
void draw_ship(Xuint32, Xuint8, Xuint8);
void draw_projectile(Xuint32, Xuint8, Xuint8);
void draw_invader_projectile(Xuint32, Xuint8, Xuint8);
void erase_projectile(Xuint32, Xuint8, Xuint8);
void erase_square(Xuint32, Xuint8, Xuint8);
void clear_graphics_screen(Xuint32);

#endif /* SI_DRAW_H_ */

