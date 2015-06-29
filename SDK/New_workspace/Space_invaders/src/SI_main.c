/*
 * SI_main.c
 *
 *  Created on: 16.06.2015.
 *      Authors: Nenad Pekez, Sasa Talosi
 */

#include "SI_logic.h"
#include "SI_interrupt.h"
#include <stdlib.h>

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

void clear_text_screen(Xuint32 BaseAddress){
    int i;
    for (i = 0; i < 4800; i++)
    {
        VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + i*4, 0x20);
    }
}

void print_string(Xuint32 BaseAddress, char string_s[], int lenght){
    int i;
    for (i = 0; i < lenght; i++)
    {
        VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + cursor_position + i*4, (string_s[i]-0x40));
    }
}

void set_cursor(Xuint32 new_value)
{
    cursor_position = new_value;
}

int main()
{
	/*************************/
	/* VARIABLES DECLARATION */
	/*************************/

	Xuint8 i, j, row[INIT_ROWS];
	Xuint8 spaceship_dir, spaceship_x;
	Xuint8 invader_dir[INIT_ROWS], invader_dir_chng[INIT_ROWS];	//Variables for changing invader position
	//Xuint8 invader_x = 0, invader_y = 0;

    /************************/
    /***** MAIN PROGRAM *****/
    /************************/

	init_platform();
	init_interrupt_controller();

	clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);

	while(1)
	{
		init_colors();
		clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);

		/* Menu */
		VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0b01);    //text mode

		set_cursor(6530);
		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "SHOOT TO START", 14);

		while(input != MIDDLE_JOY)
		{
			//seed++;
		}
		//srand(seed);
		/********/

		/* Init all arrays and variables */
		for(i = 0; i < INIT_ROWS; i++)
		{
			invader_dir[i] = RIGHT;
			invader_dir_chng[i] = 1;
			row[i] = i+INVADER_INIT_ROW;

			counter = 0;
			flag_row[i] = 0;
		}

		for(i = 0; i < MAX_PROJECTILES_X; i++)
		{
			projectiles_of_ship_num[i] = 0;

			for(j = 0; j < MAX_PROJECTILES_Y; j++)
			{
				projectiles_map[i][j] = 0;
				invaders_map[i][j] = 0;
			}
		}

		generate_init_invaders_positions();

		spaceship_dir = 0;
		spaceship_x = 1;

		invaders_num = INIT_NUM;
		game_over = 0;
		//seed = 0;
		/*****************/

		/* Initial draw */
		VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0b10);	//display mode

		draw_ship(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x, SHIP_Y);

		for(i = 0; i < INIT_ROWS; i++)
		{
			for(j = 0; j < MAX_PROJECTILES_X; j++)
			{
				if(invaders_map[j][row[i]])
				{
					draw_invader(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, j, row[i], invaders_map[j][row[i]]);
				}
			}
		}
		/***************/


		/*projectiles_map[16][4] = 1;
		projectiles_of_ship_num[16] = 1;
		draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, 16, 4);
		projectil_flag = 0;*/

		while(1)
		{
			if(input == LEFT_JOY)
			{
				spaceship_dir = LEFT;
			}

			if(input == MIDDLE_JOY)
			{
				if(shoot_flag == 0)
				{
					shoot_projectile_from_ship(spaceship_x);
					shoot_flag = SHOOT_SPEED;
				}
			}

			if(input == RIGHT_JOY)
			{
				spaceship_dir = RIGHT;
			}

			if(spaceship_flag)
			{
				move_spaceship(&spaceship_x, &spaceship_dir);
				spaceship_flag = 0;
			}

			if(projectil_flag)
			{
				move_projectile_from_ship(projectiles_map, projectiles_of_ship_num);
				projectil_flag = 0;
			}

			//if(flag)
			{
				//invader_x = rand()%80;
				//invader_y = row[rand()%3];
				//shoot_projectile_from_invader(invader_x, invader_y);
				//flag = 0;
			}

			for(i = 0; i < INIT_ROWS; i++)
			{
				if(flag_row[i])
				{
					if(invader_dir_chng[i] == DOWN)
					{
						invader_dir_chng[i]++;
						move_invaders_down(row, i);
					}
					else
						move_invaders_row(row, invader_dir, invader_dir_chng, i);

					flag_row[i] = 0;
				}
			}

			if(invaders_num == 0 || game_over)
				break;
		}

		VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0b01);    //text mode
		clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
		set_cursor(3658);

		if(game_over)
			print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "GAME OVER", 9);
		else
			print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "YOU WON", 7);
	}
    return 0;
}
