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

Xint8 projectile_hit_invader(Xint8 i, Xint8 j)
{
	if(invaders_map[i][j])
	{
		invaders_map[i][j] = 0;
		erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, j);
		invaders_num--;
		return 1;
	}
	else if(invaders_map[i-1][j])
	{
		invaders_map[i-1][j] = 0;
		erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i-1, j);
		invaders_num--;
		return 1;
	}
	else if(invaders_map[i+1][j])
	{
		invaders_map[i+1][j] = 0;
		erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i+1, j);
		invaders_num--;
		return 1;
	}
	else
		return 0;
}

Xint8 invader_hit_projectile(Xint8 i, Xint8 j)
{
	if(projectiles_map[i][j] == 1)
	{
		projectiles_map[i][j] = 0;
		projectiles_of_ship_num[i]--;
		invaders_num--;
		erase_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, j);
		return 1;
	}
	else
		return 0;
}

Xint8 invader_hit_projectile_down(Xint8 i, Xint8 j)
{
	if(projectiles_map[i][j] == 1)
	{
		projectiles_map[i][j] = 0;
		projectiles_of_ship_num[i]--;
		invaders_num--;
		erase_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, j);
		return 1;
	}
	else if(projectiles_map[i-1][j] == 1)
	{
		projectiles_map[i-1][j] = 0;
		projectiles_of_ship_num[i]--;
		invaders_num--;
		erase_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i-1, j);
		return 1;
	}
	else if(projectiles_map[i+1][j] == 1)
	{
		projectiles_map[i+1][j] = 0;
		projectiles_of_ship_num[i]--;
		invaders_num--;
		erase_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i+1, j);
		return 1;
	}
	else
		return 0;
}

void move_projectile_from_ship()
{
	Xint8 i, j, n;

	for(i = 1; i < MAX_PROJECTILES_X; i++)
	{
		n = 0;
		j = 0;

		while(n < projectiles_of_ship_num[i])
		{
			if(projectiles_map[i][j] == 1)
			{
				erase_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, j);
				projectiles_map[i][j] = 0;
				if(j == 0)		//new position will be out of screen
					projectiles_of_ship_num[i]--;
				else									//new position is not out of screen
				{
					if(!projectile_hit_invader(i, j-1))
					{
						projectiles_map[i][j-1] = 1;
						draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, (j-1));
						n++;
					}
					else
						projectiles_of_ship_num[i]--;
				}
			}
			j++;
		}
	}
}

void move_projectile_from_invader()
{

}

/* Draw projectile at current position of spaceship  */
void shoot_projectile_from_ship(Xuint8 spaceship_x)
{
    if((projectiles_map[spaceship_x][MAX_SHIP_Y-1] == 0) && !(projectile_hit_invader(spaceship_x,MAX_SHIP_Y-1)))
    {
		projectiles_map[spaceship_x][MAX_SHIP_Y - 1] = 1;
		projectiles_of_ship_num[spaceship_x]++;
		draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x, MAX_SHIP_Y - 1);
    }
}

void shoot_projectile_from_invader(Xuint8 invader_x, Xuint8 invader_y)
{
	if((projectiles_map[invader_x][invader_y+1] == 0)
			&& (invaders_map[invader_x][invader_y+1] == 0)
			&& (invaders_map[invader_x-1][invader_y+1] == 0)
			&& (invaders_map[invader_x+1][invader_y+1] == 0)
			&& (invaders_map[invader_x][invader_y]))
	{
		projectiles_map[invader_x][invader_y+1] = 2;
		//projectiles_of_ship_num[spaceship_x]++;
		draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, invader_x, invader_y+1);
	}
}

void move_invaders_row(Xuint8* row, Xuint8* dir, Xuint8* dir_chng, Xuint8 j)
{
	Xint8 i, temp;

	if(dir[j] == RIGHT)
	{
		for(i = MAX_PROJECTILES_X-1; i >= 0; i--)
		{
			if(invaders_map[i][row[j]])
			{
				erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, row[j]);

				temp = invaders_map[i][row[j]];
				invaders_map[i][row[j]] = 0;

				/* Wil the new most right coordinate of invader hit a projetile? */
				if(!invader_hit_projectile(i+2, row[j]))
				{
					if(temp == 1)
						invaders_map[i+1][row[j]] = 2;
					else
						invaders_map[i+1][row[j]] = 1;

					draw_invader(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i+1, row[j], invaders_map[i+1][row[j]]);
				}
			}
		}
	}
	else
	{
		for(i = 0; i < MAX_PROJECTILES_X; i++)
		{
			if(invaders_map[i][row[j]])
			{
				erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, row[j]);

				temp = invaders_map[i][row[j]];
				invaders_map[i][row[j]] = 0;

				/* Wil the new most left coordinate of invader hit a projetile? */
				if(!invader_hit_projectile(i-2, row[j]))
				{
					if(temp == 1)
						invaders_map[i-1][row[j]] = 2;
					else
						invaders_map[i-1][row[j]] = 1;

					draw_invader(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i-1, row[j], invaders_map[i-1][row[j]]);
				}
			}
		}
	}

	dir_chng[j]++;
	if(dir_chng[j] == 4)
	{
		dir_chng[j] = DOWN;
		if(dir[j] == RIGHT)
			dir[j] = LEFT;
		else
			dir[j] = RIGHT;
	}

}

void move_invaders_down(Xuint8* row, Xuint8 j)
{
	Xuint8 i, temp;

	for(i = 0; i < MAX_PROJECTILES_X; i++)
	{
		if(invaders_map[i][row[j]])
		{
			erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, row[j]);

			temp = invaders_map[i][row[j]];
			invaders_map[i][row[j]] = 0;

			if(!invader_hit_projectile_down(i, row[j]+1))
			{
				if(row[j]+1 == MAX_PROJECTILES_Y-1)
					game_over = 1;

				if(temp == 1)
					invaders_map[i][row[j]+1] = 2;
				else
					invaders_map[i][row[j]+1] = 1;

				draw_invader(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, row[j]+1, invaders_map[i][row[j]+1]);
			}
		}
	}

	row[j]++;
}

void generate_init_invaders_positions()
{
	Xuint8 j;

	for(j = 0; j < INIT_ROWS; j++)	//generate positions for invaders (COL POSITIONS: 9, 18, 27, 38, 49, 58, 67)
	{
			invaders_map[7][j+1] = 1;
			invaders_map[14][j+1] = 1;
			invaders_map[21][j+1] = 1;

			invaders_map[33][j+1] = 1;
			invaders_map[40][j+1] = 1;
			invaders_map[47][j+1] = 1;

			invaders_map[58][j+1] = 1;
			invaders_map[65][j+1] = 1;
			invaders_map[72][j+1] = 1;
	}
}

