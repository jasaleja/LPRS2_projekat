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
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k-1)*4, 0x10101010);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+0)*4, 0x10101010);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+1)*4, 0x10101010);
	}
}

void draw_invader(Xuint32 BaseAddress, Xuint8 x_crdnt, Xuint8 y_crdnt, Xuint8 type)
{
	int i, j, k;
	k = x_crdnt;

	if(type == 1)
	{
		for (j = 16 + 32*y_crdnt; j < 32 + 32*y_crdnt; j++)
		{
			i = j*(640/8) + k;
			if (j >= (16 + 32*y_crdnt) && j < (18 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000110);
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000000);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x01100000);
			}
			else if (j >= (18 + 32*y_crdnt) && j < (20 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000001);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x10000001);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x10000000);
			}
			else if (j >= (20 + 32*y_crdnt) && j < (22 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000111);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11111111);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11100000);
			}
			else if (j >= (22 + 32*y_crdnt) && j < (24 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00011112);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x21111112);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x21111000);
			}
			else if (j >= (24 + 32*y_crdnt) && j < (26 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x11111111);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11111111);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11111111);
			}
			else if (j >= (26 + 32*y_crdnt) && j < (28 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x11001111);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11111111);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11110011);
			}
			else if (j >= (28 + 32*y_crdnt) && j < (30 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x11001100);
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000000);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x00110011);
			}
			else {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000011);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11000011);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11000000);
			}
		}
	}
	else
	{
		for (j = 16 + 32*y_crdnt; j < 32 + 32*y_crdnt; j++)
		{
			i = j*(640/8) + k;
			if (j >= (16 + 32*y_crdnt) && j < (18 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000110);
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000000);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x01100000);
			}
			else if (j >= (18 + 32*y_crdnt) && j < (20 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x11000001);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x10000001);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x10000011);
			}
			else if (j >= (20 + 32*y_crdnt) && j < (22 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x11001111);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11111111);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11110011);
			}
			else if (j >= (22 + 32*y_crdnt) && j < (24 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x11111112);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x21111112);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x21111111);
			}
			else if (j >= (24 + 32*y_crdnt) && j < (26 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x11111111);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11111111);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11111111);
			}
			else if (j >= (26 + 32*y_crdnt) && j < (28 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00111111);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11111111);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11111100);
			}
			else if (j >= (28 + 32*y_crdnt) && j < (30 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000110);
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000000);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x01100000);
			}
			else {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00011000);
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000000);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x00011000);
			}
		}
	}
}

void draw_invader_2(Xuint32 BaseAddress, Xuint8 x_crdnt, Xuint8 y_crdnt)
{
	int i, j, k;
	k = x_crdnt;

	for (j = 16 + 32*y_crdnt; j < 32 + 32*y_crdnt; j++)
	{
		i = j*(640/8) + k;
		if (j >= (16 + 32*y_crdnt) && j < (18 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000110);
			//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000000);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x01100000);
		}
		else if (j >= (18 + 32*y_crdnt) && j < (20 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x11000001);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x10000001);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x10000011);
		}
		else if (j >= (20 + 32*y_crdnt) && j < (22 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x11001111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11111111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11110011);
		}
		else if (j >= (22 + 32*y_crdnt) && j < (24 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x11111112);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x21111112);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x21111111);
		}
		else if (j >= (24 + 32*y_crdnt) && j < (26 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x11111111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11111111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11111111);
		}
		else if (j >= (26 + 32*y_crdnt) && j < (28 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00111111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x11111111);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x11111100);
		}
		else if (j >= (28 + 32*y_crdnt) && j < (30 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000110);
			//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000000);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x01100000);
		}
		else {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00011000);
			//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00000000);
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x00011000);
		}
	}
}

void draw_ship(Xuint32 BaseAddress, Xuint8 x_crdnt, Xuint8 y_crdnt)
{
	int i, j, k;
	k = x_crdnt;

	if(lives > INIT_LIVES-1)
	{
		for (j = 2 + 32*y_crdnt; j < 28 + 32*y_crdnt; j++)
		{
			i = j*(640/8) + k;
			if (j >= (2 + 32*y_crdnt) && j < (6 + 32*y_crdnt)) {
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000000);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00033000);
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x00000000);
			}
			else if (j >= (6 + 32*y_crdnt) && j < (12 + 32*y_crdnt)) {
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000000);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00333300);
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x00000000);
			}
			else if (j >= (12 + 32*y_crdnt) && j < (16 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00033333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x33333333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x33333000);
			}
			else {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x33333333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x33333333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x33333333);
			}
		}
	}
	else if(lives == INIT_LIVES-1)
	{
		for (j = 2 + 32*y_crdnt; j < 28 + 32*y_crdnt; j++)
		{
			i = j*(640/8) + k;
			if (j >= (2 + 32*y_crdnt) && j < (6 + 32*y_crdnt)) {
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000000);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00033000);
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x00000000);
			}
			else if (j >= (6 + 32*y_crdnt) && j < (12 + 32*y_crdnt)) {
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000000);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00333300);
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x00000000);
			}
			else if (j >= (12 + 32*y_crdnt) && j < (16 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x0003333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x33333300);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x0333300);
			}
			else if (j >= (16 + 32*y_crdnt) && j < (22 + 32*y_crdnt)){
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00033333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x33333333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x33330000);
			}
			else {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x33333333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x33333333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x33333333);
			}
		}
	}
	else
	{
		for (j = 2 + 32*y_crdnt; j < 28 + 32*y_crdnt; j++)
		{
			i = j*(640/8) + k;
			if (j >= (2 + 32*y_crdnt) && j < (6 + 32*y_crdnt)) {
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000000);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00033000);
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x00000000);
			}
			else if (j >= (6 + 32*y_crdnt) && j < (12 + 32*y_crdnt)) {
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00000000);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x00333000);
				//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x00000000);
			}
			else if (j >= (12 + 32*y_crdnt) && j < (16 + 32*y_crdnt)) {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00033300);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x03333300);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x33333000);
			}
			else if (j >= (16 + 32*y_crdnt) && j < (22 + 32*y_crdnt)){
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00333333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x33333333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x33330000);
			}
			else {
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i-1)*4, 0x00033333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+0)*4, 0x33333333);
				VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (i+1)*4, 0x33333333);
			}
		}
	}
}

void draw_projectile(Xuint32 BaseAddress, Xuint8 x_crdnt, Xuint8 y_crdnt)
{
	int j, k;
	k = x_crdnt;

	for (j = 4 + 32*y_crdnt; j < 28 + 32*y_crdnt; j++)
	{
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k)*4, 0x00033000);
	}
}

void draw_invader_projectile(Xuint32 BaseAddress, Xuint8 x_crdnt, Xuint8 y_crdnt)
{
	int j, k;
	k = x_crdnt;

	for (j = 6 + 32*y_crdnt; j < 26 + 32*y_crdnt; j++)
	{
		if (j >= (7 + 32*y_crdnt) && j < (9 + 32*y_crdnt))
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k)*4, 0x02222220);
		else
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k)*4, 0x00022000);
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
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k-1)*4, 0x00000000);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+0)*4, 0x00000000);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+1)*4, 0x00000000);
	}
}

void clear_graphics_screen(Xuint32 BaseAddress)
{
	int i;
	for (i = 0; i < 9600*4; i++){
	    VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x00000000);
	}
}
