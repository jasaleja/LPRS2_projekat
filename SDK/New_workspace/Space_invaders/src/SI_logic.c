/*
 * SI_logic.c
 *
 *  Created on: 16.06.2015.
 *      Author: student
 */

#include "SI_logic.h"

void move_spaceship(Xuint8 *x, Xuint8 *dir)
{
	erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, *x, SHIP_Y);
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

	draw_ship(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, *x, SHIP_Y);
}

Xint8 projectile_hit_invader(int i, int j)
{
	int n;

	/* Check if projectile hit left, center or right part of invader */
	for(n = -1; n < 2; n++)
	{
		if(invaders_map[i+n][j])
		{
			invaders_map[i+n][j] = 0;
			erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i+n, j);
			invaders_num--;
			projectiles_of_ship_num[i]--;
			xil_printf("\nPROJECTILE HIT INVADER\n\r");
			return 1;
		}
	}
	return 0;
}

Xint8 projectile_hit_projectile(int i, int j)
{
	if(projectiles_map[i][j])
	{
		projectiles_map[i][j] = 0;
		erase_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, j);
		projectiles_of_invaders_num[i]--;
		projectiles_of_ship_num[i]--;
		return 1;
	}
	else
		return 0;
}

void move_projectile_from_ship()
{
	int i, j, n;

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

				if(j == 0)		//New position will be out of screen
					projectiles_of_ship_num[i]--;
				else			//New position is not out of screen
				{
					if(!projectile_hit_invader(i, j-1) && !projectile_hit_projectile(i, j-1))
					{
						projectiles_map[i][j-1] = 1;
						draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, (j-1));
						n++;
					}
				}
			}

			j++;
		}
	}
}

void move_projectile_from_invader()
{
	int i, j, n;

	for(i = 1; i < MAX_PROJECTILES_X; i++)
	{
		n = 0;
		j = MAX_PROJECTILES_Y - 1;

		while(n < projectiles_of_invaders_num[i])
		{
			if(projectiles_map[i][j] == 2)
			{
				erase_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, j);
				projectiles_map[i][j] = 0;
				if(j == MAX_PROJECTILES_Y - 1)		    //new position will be out of screen
					projectiles_of_invaders_num[i]--;
				else									//new position is not out of screen
				{
					if(!projectile_hit_projectile(i, j+1) && projectiles_map[i][j+1] == 0 )
					{
						projectiles_map[i][j+1] = 2;
						draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, (j+1));
						n++;
					}
				}
			}
			j--;
		}
	}
}

Xint8 invader_hit_projectile(int i, int j)
{
	if(projectiles_map[i][j] == 1)
	{
		projectiles_map[i][j] = 0;
		projectiles_of_ship_num[i]--;
		invaders_num--;
		erase_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, j);
		xil_printf("\nINVADER HIT PROJECTILE\n\r");
		return 1;
	}
	else
		return 0;
}

void move_invaders_row(Xuint8* row, Xuint8* dir, Xuint8* dir_chng, int j)
{
	Xuint8 temp;
	int i;

	if(dir[j] == RIGHT)
	{
		for(i = MAX_PROJECTILES_X-1; i >= 1; i--)
		{
			if(invaders_map[i][row[j]])
			{
				erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, row[j]);

				temp = invaders_map[i][row[j]];
				invaders_map[i][row[j]] = 0;

				/* Will the new most right coordinate of invader hit a projetile? */
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
		for(i = 1; i < MAX_PROJECTILES_X; i++)
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

Xint8 invader_hit_projectile_down(int i, int j)
{
	int n;
	/* Check if projectile hit left, center or right part of invader */
	for(n = -1; n < 2; n++)
	{
		if(projectiles_map[i+n][j] == 1)
		{
			projectiles_map[i+n][j] = 0;
			projectiles_of_ship_num[i+n]--;
			invaders_num--;
			erase_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i+n, j);
			xil_printf("\nINVADER HIT PROJECTILE DOWN! projectiles_num: %d\n\r", projectiles_of_ship_num[i+n]);
			return 1;
		}
	}
	return 0;
}

void move_invaders_down(Xuint8* row, Xuint8 j)
{
	Xuint8 i, temp;

	for(i = 1; i < MAX_PROJECTILES_X-1; i++)
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

	if(row[j] + 1 == MAX_PROJECTILES_Y-1)
		row[j] = 0;
	else
		row[j]++;
}

/* Draw projectile at current position of spaceship  */
void shoot_projectile_from_ship(Xuint8 spaceship_x)
{
    if(projectiles_map[spaceship_x][SHIP_Y-1] != 1)
    {
    	projectiles_of_ship_num[spaceship_x]++;

    	if(!projectile_hit_invader(spaceship_x, SHIP_Y-1) && !projectile_hit_projectile(spaceship_x, SHIP_Y-1))
    	{
			draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x, SHIP_Y - 1);
			projectiles_map[spaceship_x][SHIP_Y - 1] = 1;
    	}
    }
}

void shoot_projectile_from_invader(Xuint8 invader_x, Xuint8* row)
{
	int j = INIT_ROWS - 1;

	while(j >= 0)
	{
		if((invaders_map[invader_x][row[j]] == 0) && (invaders_map[invader_x-1][row[j]] == 0) && (invaders_map[invader_x+1][row[j]] == 0))
		{
			j--;
		}
		else if((invaders_map[invader_x][row[j]]) && projectiles_map[invader_x][row[j]+1] == 0)
		{
			projectiles_map[invader_x][row[j]+1] = 2;
			projectiles_of_invaders_num[invader_x]++;
			draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, invader_x, row[j]+1);
			break;
		}
		else
			break;
	}
}

void generate_init_invaders_positions()
{
	Xuint8 j;

	for(j = 0; j < INIT_ROWS; j++)	//Generate positions for invaders
	{
			invaders_map[7][j+INVADER_INIT_ROW] = 1;
			invaders_map[14][j+INVADER_INIT_ROW] = 1;
			invaders_map[21][j+INVADER_INIT_ROW] = 1;

			invaders_map[33][j+INVADER_INIT_ROW] = 1;
			invaders_map[40][j+INVADER_INIT_ROW] = 1;
			invaders_map[47][j+INVADER_INIT_ROW] = 1;

			invaders_map[58][j+INVADER_INIT_ROW] = 1;
			invaders_map[65][j+INVADER_INIT_ROW] = 1;
			invaders_map[72][j+INVADER_INIT_ROW] = 1;
	}
}
