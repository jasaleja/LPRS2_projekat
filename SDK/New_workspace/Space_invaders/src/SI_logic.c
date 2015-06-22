/*
 * SI_logic.c
 *
 *  Created on: 16.06.2015.
 *      Author: student
 */

#include "SI_logic.h"

void move_spaceship(Xuint8 *x, Xuint8 *dir)
{
	erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, *x, MAX_SHIP_Y);
	if(*dir == 0)
	{
		if(*x == MAX_SHIP_X)
		{
			(*x)--;
			*dir = 1;
		}
		else
			(*x)++;
	}
	else if(*x == MIN_SHIP_X)
	{
		(*x)++;
		*dir = 0;
	}
	else
		(*x)--;

	draw_ship(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, *x, MAX_SHIP_Y);
}

void move_projectile(Xuint8 *projectiles_num)
{
	int i, j, k = 0, n = 0;
	int new_j[] = {0, 0, 0, 0, 0, 0, 0};

	for(i = 1; i < MAX_PROJECTILES_X - 1; i++)
	{
		n = 0;
		//j = MAX_PROJECTILES_Y - 1;

		//while(n < projectiles_num[i])
		for(j = MAX_PROJECTILES_Y - 1; j >= 0; j--)
		{
			if(projectiles_map[i][j])
			{
				erase_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, j);

				if((j-1) >= 0)	//new position is not out of screen
					draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, (j-1));
				else			//new position is out of screen
					projectiles_num[i]--;

				new_j[n] = j-1;	//save new position
				n++;			//how many times to modify map
			}
		//	j--;
		}

		//modify this colon with new positions
		for(k = 0; k < n; k++)
		{
			projectiles_map[i][new_j[k] + 1] = 0;		//old position
			if(new_j[k] >= 0)							//only if position is in the screen
				projectiles_map[i][new_j[k]] = 1;		//new position
		}
	}
}

/* draw projectile at current position of spaceship  */
void shoot_projectile(Xuint8* projectiles_num, Xuint8 spaceship_x)
{
    //if(projectiles_map[spaceship_x + 1][MAX_SHIP_Y-1] == 1) //??
    	//erase_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x + 1, MAX_SHIP_Y - 1);

    projectiles_map[spaceship_x + 1][MAX_SHIP_Y - 1] = 1;
    projectiles_num[spaceship_x + 1]++;
    draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x + 1 /*??*/, MAX_SHIP_Y - 1);

}

void move_invaders_row(Xuint8 row, Xint8* offsets, Xuint8* rigth, Xuint8* left)
{
	Xuint8 i;

	for(i = row*INIT_COLS; i < (row+1)*INIT_COLS; i++)
	{
		if(invaders[i].alive)
		{
			erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR,invaders[i].x_crdnt,invaders[i].y_crdnt);
			invaders[i].x_crdnt = invaders[i].x_crdnt + offsets[row];
			draw_invader(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR,invaders[i].x_crdnt,invaders[i].y_crdnt);
		}
	}

	if(offsets[row] == -1)
	{
		if(left[row] < 3)
		{
			left[row]++;
		}
		else if(left[row] == 3)
		{
			left[row] = 0;
			offsets[row] = 1;
		}
	}
	else if(offsets[row] == 1)
	{
		if(rigth[row] < 3)
		{
			rigth[row]++;
		}
		else if(rigth[row] == 3)
		{
			rigth[row] = 0;
			offsets[row] = -1;
		}
	}
	else if(offsets[row] == 0)
	{
		offsets[row] = -1;
	}
}

void generate_init_invaders_positions()
{
	Xuint8 i, j, k, temp;

	for(i = 0; i < INIT_ROWS; i++)	//generate positions for invaders (COL POSITIONS: 9, 18, 27, 38, 49, 58, 67)
	{
		for(j = 0; j < INIT_COLS; j++)
		{
			k = j + i*INIT_COLS;	//index of invaders array

			temp = 9*(j+1); 		//9 18 27 36 45 54 63
			if(temp == 36)
				temp = 38;
			else if(temp >= 38)
				temp = temp + 4;

			invaders[k].x_crdnt = temp;
			invaders[k].y_crdnt = i*2 + 1;
			invaders[k].alive = 1;
		}
	}
}
