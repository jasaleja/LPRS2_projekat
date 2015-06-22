/*
 * SI_draw.c
 *
 *  Created on: 16.06.2015.
 *      Author: Nenad Pekez, Sasa Talosi
 */

#include "SI_draw.h"

void draw_square(Xuint32 BaseAddress, Xuint8 x_crdnt, Xuint8 y_crdnt)
{
	int j, k;
	k = x_crdnt;

	for (j = 0 + 32*y_crdnt; j < 32 + 32*y_crdnt; j++)
	{
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k  )*4, 0x11111111);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+1)*4, 0x11111111);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+2)*4, 0x11111111);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+3)*4, 0x11111111);
	}
}

void draw_invader(Xuint32 BaseAddress, Xuint8 x_crdnt, Xuint8 y_crdnt)
{
	int i, j, k;
	k = x_crdnt;

	for (j = 4 + 32*y_crdnt; j < 28 + 32*y_crdnt; j++)
	{
		i = j*(640/8) + k;
		if (j >= (4 + 32*y_crdnt) && j < (7 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000011);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x10000000);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+2)*4, 0x00000001);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+3)*4, 0x11000000);
		}
		else if (j >= (7 + 32*y_crdnt) && j < (10 + 32*y_crdnt)) {
			//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000000);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x01110000);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+2)*4, 0x00001110);
			//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+3)*4, 0x00000000);
		}
		else if (j >= (10 + 32*y_crdnt) && j < (13 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000011);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11111111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+2)*4, 0x11111111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+3)*4, 0x11000000);
		}
		else if (j >= (13 + 32*y_crdnt) && j < (16 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00011111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x12221111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+2)*4, 0x11112221);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+3)*4, 0x11111000);
		}
		else if (j >= (16 + 32*y_crdnt) && j < (19 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11111111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11111111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+2)*4, 0x11111111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+3)*4, 0x11111111);
		}
		else if (j >= (19 + 32*y_crdnt) && j < (22 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11100011);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11111111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+2)*4, 0x11111111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+3)*4, 0x11000111);
		}
		else if (j >= (22 + 32*y_crdnt) && j < (25 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11100011);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x10000000);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+2)*4, 0x00000001);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+3)*4, 0x11000111);
		}
		else {
			//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000000);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x01111110);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+2)*4, 0x01111110);
			//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+3)*4, 0x00000000);
		}
	}
}

void draw_ship(Xuint32 BaseAddress, Xuint8 x_crdnt, Xuint8 y_crdnt)
{
	int i, j, k;
	k = x_crdnt;

	for (j = 0 + 32*y_crdnt; j < 28 + 32*y_crdnt; j++)
	{
		i = j*(640/8) + k;
		if (j >= (0 + 32*y_crdnt) && j < (4 + 32*y_crdnt)) {
			//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000000);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x00033000);
			//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+2)*4, 0x00000000);
		}
		else if (j >= (4 + 32*y_crdnt) && j < (10 + 32*y_crdnt)) {
			//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000000);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x00333300);
			//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+2)*4, 0x00000000);
		}
		else if (j >= (10 + 32*y_crdnt) && j < (14 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00033333);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x33333333);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+2)*4, 0x33333000);
		}
		else {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x33333333);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x33333333);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+2)*4, 0x33333333);
		}
	}
}

void draw_projectile(Xuint32 BaseAddress, Xuint8 x_crdnt, Xuint8 y_crdnt)
{
	int j, k;
	k = x_crdnt;

	for (j = 2 + 32*y_crdnt; j < 30 + 32*y_crdnt; j++)
	{
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k)*4, 0x00033000);
	}
}

void erase_projectile(Xuint32 BaseAddress, Xuint8 x_crdnt, Xuint8 y_crdnt)
{
	int j, k;
	k = x_crdnt;

	for (j = 2 + 32*y_crdnt; j < 30 + 32*y_crdnt; j++)
	{
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k)*4, 0x00000000);
	}
}

void erase_square(Xuint32 BaseAddress, Xuint8 x_crdnt, Xuint8 y_crdnt)
{
	int j, k;
	k = x_crdnt;

	for (j = 0 + 32*y_crdnt; j < 32 + 32*y_crdnt; j++)
	{
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k  )*4, 0x00000000);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+1)*4, 0x00000000);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+2)*4, 0x00000000);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+3)*4, 0x00000000);
	}
}

void clear_graphics_screen(Xuint32 BaseAddress)
{
	int i;
	for (i = 0; i < 9600*4; i++){
	    VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x00000000);
	}
}
