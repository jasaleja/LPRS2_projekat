/*
 * SI_main.c
 *
 *  Created on: 16.06.2015.
 *      Authors: Nenad Pekez, Sasa Talosi
 */

/* our file */
#include "SI_logic.h"
#include "SI_interrupt.h"

void init_colors()
{
	/* Define colors */
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0x000000);	//color 0
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14, 0xffffff);	//color 1
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0xff0000);	//color 2
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x1C, 0x00ff00);	//color 3
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x20, 0x00ffff);	//color 4
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x24, 0xff00ff);	//color 5
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x28, 0xffff00);	//color 6
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x2C, 0x000000);	//color 7
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x30, 0xffffff);	//color 8
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x34, 0xff1493);	//color 9
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x38, 0x8b4513);	//color 10
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x3C, 0x556b2f);	//color 11
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x40, 0x191970);	//color 12
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x44, 0xb8860b);	//color 13
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x48, 0xffe4c4);	//color 14
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x4C, 0xd2691e);	//color 15
}

int main()
{
	/*************************/
	/* VARIABLES DECLARATION */
	/*************************/

	Xuint8 row, i, j;
	Xuint8 spaceship_dir = 0, spaceship_x = 0;
	Xint8 offsets[INIT_ROWS];
    Xuint8 rigth[INIT_ROWS], left[INIT_ROWS];	//variables for changing offsets

    /************************/
    /***** MAIN PROGRAM *****/
    /************************/

	init_platform();
	init_interrupt_controller();

	generate_init_invaders_positions();

	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0b10);	//display mode

	init_colors();
	clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);

	/* Init all arrays */
	for(i = 0; i < INIT_ROWS; i++)				//init rigth, left and offsets
	{
		rigth[i] = 0;
		offsets[i] = -1;
		left[i] = 1;
	}

	for(i = 0; i < MAX_PROJECTILES_X; i++)
	{
		projectiles_num[i] = 0;

		for(j = 0; j < MAX_PROJECTILES_Y; j++)
		{
			projectiles_map[i][j] = 0;
		}
	}
	/*****************/

	draw_ship(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x, MAX_SHIP_Y);

	for(i = 0; i < INIT_NUM; i++)
	{
		draw_invader(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, invaders[i].x_crdnt, invaders[i].y_crdnt);
	}

	draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x + 1 /*??*/, MAX_SHIP_Y - 1);
	projectiles_map[spaceship_x + 1][MAX_SHIP_Y - 1] = 1;
	projectiles_num[spaceship_x + 1]++;

	draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x + 4 /*??*/, MAX_SHIP_Y - 1);
	projectiles_map[spaceship_x + 4][MAX_SHIP_Y - 1] = 1;
	projectiles_num[spaceship_x + 4]++;

	while(1)
	{
		if(input == LEFT_JOY) //23
		{
			spaceship_dir = LEFT_DIR; //0
		}

		if(input == MIDDLE_JOY)	//27
		{
			shoot_projectile(projectiles_num, spaceship_x);
		}

		if(input == RIGHT_JOY) //29
		{
			spaceship_dir = RIGHT_DIR;
		}

		if(spaceship_flag)
		{
			spaceship_flag = 0;
			move_spaceship(&spaceship_x, &spaceship_dir);
		}

		if(projectil_flag == 1)
		{
			move_projectile(projectiles_num);
			projectil_flag = 0;
		}

		for(row = 0; row < INIT_ROWS; row++)
		{
			if(flag_row[row])
			{
				move_invaders_row(row, offsets, rigth, left);
				flag_row[row] = 0;
			}
		}
	}

    return 0;
}
