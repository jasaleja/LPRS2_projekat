/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

/*#include <stdio.h>
#include "platform.h"
#include "xintc.h"
#include "xparameters.h"
#include "xio.h"
#include "xil_io.h"
#include "xil_exception.h"

#define VGA_PERIPH_MEM_mWriteMemory(Address, Data) \
 	Xil_Out32(Address, (Xuint32)(Data))
#define VGA_PERIPH_MEM_mReadMemory(Address) \
 	Xil_In32(Address)

#define GRAPHICS_MEM_OFF 0x2000000
#define TEXT_MEM_OFF 0x1000000
#define MAX_X 19
#define MIN_X 0
#define MAX_Y 14
#define MIN_Y 0
#define INIT_ROWS 3
#define INIT_COLS 7
#define INIT_NUM INIT_ROWS*INIT_COLS
#define PROJECTILES_NUM 20

void initialise();
void clear_graphics_screen(Xuint32 BaseAddress);
void clear_text_screen(Xuint32 BaseAddress);
void set_cursor(Xuint32 new_value);
void print_string(Xuint32 BaseAddress, char string_s[], int lenght);
void draw_square(Xuint32 BaseAddress,unsigned char x_crdnt, unsigned char y_crdnt);
void draw_ship(Xuint32 BaseAddress,unsigned char x_crdnt, unsigned char y_crdnt);
void draw_invader(Xuint32 BaseAddress,unsigned char x_crdnt, unsigned char y_crdnt);
void draw_projectile(Xuint32 BaseAddress,unsigned char x_crdnt, unsigned char y_crdnt);
void erase_square(Xuint32 BaseAddress,unsigned char x_crdnt, unsigned char y_crdnt);
void move_spaceship(unsigned char *x, unsigned char *dir);
void move_projectiles(char *projectiles);
void shoot_projectile(char *projectiles, unsigned char x);
void move_invaders_row(unsigned char row);
void check_hit(unsigned char x, unsigned char y, unsigned char who, unsigned char i);

XIntc Intc;
Xuint32 cursor_position;

typedef struct invader
{
	unsigned char x_crdnt;
	unsigned char y_crdnt;
	unsigned char alive;
} invader;

unsigned char spaceship_speed = 0;
unsigned char projectil_speed = 0;
unsigned char spaceship_flag = 0;
unsigned char projectil_flag = 0;
unsigned char input = 0;
unsigned char flag_row[INIT_ROWS];
unsigned char temp = 0;
unsigned char rigth[INIT_ROWS], left[INIT_ROWS];	//variables for changing offsets
unsigned char row;
unsigned char spaceship_x = 0;
unsigned char spaceship_dir = 0; //0 = right, other = left
unsigned char game_over = 0;
unsigned char invaders_num = INIT_NUM;

int counter = 0;

char offsets[INIT_ROWS];
char projectiles[PROJECTILES_NUM];

invader invaders[INIT_NUM];		//array of structs invaders

void vga_interrupt_handler(void * BaseAddress)
{
	input = VGA_PERIPH_MEM_mReadMemory(XPAR_MY_PERIPHERAL_0_BASEADDR);
	if(spaceship_speed == 18)
	{
		spaceship_flag = 1;
		spaceship_speed = 0;
	}
	else
		spaceship_speed++;

	if(projectil_speed == 12)
	{
		projectil_flag = 1;
		projectil_speed = 0;
	}
	else
		projectil_speed++;

	if(counter == 120)
	{
		flag_row[2] = 1;
	}
	else if(counter == 220)
	{
		flag_row[1] = 1;
	}
	else if(counter == 320)
	{
		flag_row[0] = 1;
		counter = 0;
	}
	counter++;
}

int main()
{
	initialise();
    //unsigned char spaceship_x = 0;
    //unsigned char spaceship_dir = 0; //0 = right, other = left
	unsigned char i, j, k;

    for(i = 0; i < INIT_ROWS; i++)				//init rigth, left and offsets
	{
		rigth[i] = 0;
		offsets[i] = -1;
		left[i] = 1;
	}

	for(i = 0; i < INIT_ROWS; i++)	//init positions of invaders (COL POSITIONS: 2, 4, 6, 9, 12, 14, 16)
	{
		for(j = 0; j < INIT_COLS; j++)
		{
			k = j + i*INIT_COLS;

			temp = j*2 + 2;
			if(temp == 8)
				temp = 9;
			else if(temp >= 10)
				temp = temp + 2;

			invaders[k].x_crdnt = temp;
			invaders[k].y_crdnt = i*2 + 1;
			invaders[k].alive = 1;
		}
	}

	for(i = 0; i < INIT_NUM; i++)	//draw invaders at those init positions
	{
		draw_invader(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR,invaders[i].x_crdnt,invaders[i].y_crdnt);
	}

    for(i = 0; i<=MAX_X; i++)
    {
    	projectiles[i] = -1;
    }

    draw_ship(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x, MAX_Y);

    while(1)
    {
    	if(game_over)
    	{
    		break;
    	}
    	else
    	{
			if(input == 29)
			{
				spaceship_dir = 1;
			}
			if(input == 23)
			{
				spaceship_dir = 0;
			}
			if(input == 27)
			{
				shoot_projectile(projectiles, spaceship_x);
			}
			if(spaceship_flag == 1)
			{
				spaceship_flag = 0;
				move_spaceship(&spaceship_x, &spaceship_dir);
			}
			if(projectil_flag == 1)
			{
				projectil_flag = 0;
				move_projectiles(projectiles);
			}

			for(row = 0; row < INIT_ROWS; row++)
			{
				if(flag_row[row] == 1)
				{
					move_invaders_row(row);
				}
			}
    	}
    }
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0b01);	//display mode
	clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
	set_cursor(6540);
	print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "YOU WON", 7);
    return 0;
}

void initialise()
{
	init_platform();
	XStatus Status;

	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0b10);	//display mode
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0xffffff);//fg color

	clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);

	XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x1C, 0x20C); //init terminal counter on 524
	XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x20, 1);		//enable timer

	//initialize interrupt controller
	Status = XIntc_Initialize (&Intc, XPAR_INTC_0_DEVICE_ID);
	if (Status != XST_SUCCESS)
		xil_printf ("\r\nInterrupt controller initialization failure");
	else
		xil_printf("\r\nInterrupt controller initialized");

	// Connect interrupt_handler
	Status = XIntc_Connect (&Intc, 0, (XInterruptHandler) vga_interrupt_handler, (void *)0);

	if (Status != XST_SUCCESS)
		xil_printf ("\r\nRegistering MY_TIMER Interrupt Failed");
	else
		xil_printf("\r\nMY_TIMER Interrupt registered");

	//Start the interrupt controller in real mode
	Status = XIntc_Start(&Intc, XIN_REAL_MODE);

	//Enable interrupt controller
	XIntc_Enable (&Intc, 0);
	microblaze_enable_interrupts();
}

void clear_graphics_screen(Xuint32 BaseAddress)
{
	int i;
	for (i = 0; i < 9600; i++){
	    VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x0);
	}
}

void draw_ship(Xuint32 BaseAddress,unsigned char x_crdnt, unsigned char y_crdnt)
{
	int i, j, k;
	k = x_crdnt;
	for (j = 0 + 32*y_crdnt; j < 32 + 32*y_crdnt; j++){
		i = j*(640/32) + k;

		if (j >= (0 + 32*y_crdnt) && j < (5 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x00000000);
		}
		if (j >= (5 + 32*y_crdnt) && j < (8 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x0003C000);
		}
		if (j >= (8 + 32*y_crdnt) && j < (14 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x001FF800);
		}
		if (j >= (14 + 32*y_crdnt) && j < (17 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x1FFFFFF8);
		}
		if (j >= (17 + 32*y_crdnt) && j < (32 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0xFFFFFFFF);
		}
    }
}

void draw_invader(Xuint32 BaseAddress,unsigned char x_crdnt, unsigned char y_crdnt)
{
	int i, j, k;
	k = x_crdnt;
	for (j = 0 + 32*y_crdnt; j < 32 + 32*y_crdnt; j++){
		i = j*(640/32) + k;

		if (j >= (0 + 32*y_crdnt) && j < (4 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x00000000);
		}
		if (j >= (4 + 32*y_crdnt) && j < (7 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x038001C0);
		}
		if (j >= (7 + 32*y_crdnt) && j < (10 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x00700E00);
		}
		if (j >= (10 + 32*y_crdnt) && j < (13 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x03FFFFC0);
		}
		if (j >= (13 + 32*y_crdnt) && j < (16 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x1F8FF1F8);
		}
		if (j >= (16 + 32*y_crdnt) && j < (19 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0xFFFFFFFF);
		}
		if (j >= (19 + 32*y_crdnt) && j < (22 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0xE38FF1C7);
		}
		if (j >= (22 + 32*y_crdnt) && j < (25 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0xE38001C7);
		}
		if (j >= (25 + 32*y_crdnt) && j < (28 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x007E7E00);
		}
		if (j >= (28 + 32*y_crdnt) && j < (32 + 32*y_crdnt)) {
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x00000000);
		}
    }
}

void draw_projectile(Xuint32 BaseAddress,unsigned char x_crdnt, unsigned char y_crdnt)
{
	int j, k;
	k = x_crdnt;
	for (j = 0 + 32*y_crdnt; j < 32 + 32*y_crdnt; j++){
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/32) + k)*4, 0x00018000);
	}
}

void erase_square(Xuint32 BaseAddress,unsigned char x_crdnt, unsigned char y_crdnt)
{
	int j, k;
	k = x_crdnt;
	for (j = 0 + 32*y_crdnt; j < 32 + 32*y_crdnt; j++){
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/32) + k)*4, 0x00);
	}
}

void move_spaceship(unsigned char *x, unsigned char *dir)
{
	erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, *x, MAX_Y);
	if(*dir == 0)
	{
		if(*x == MAX_X)
		{
			(*x)--;
			*dir = 1;
		} else
			(*x)++;
	} else
		if(*x == MIN_X)
		{
			(*x)++;
			*dir = 0;
		} else
			(*x)--;
	draw_ship(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, *x, MAX_Y);
}

void move_projectiles(char *projectiles)
{
	unsigned char i;

	for(i = 0; i<=MAX_X; i++)
	{
		if(projectiles[i] != -1)
		{
			erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, projectiles[i]);
			projectiles[i]--;
			check_hit(i, projectiles[i], 1, 0);//i -> x, projectiles[i] -> y, 1 -> ship
			if(projectiles[i] != -1)
				draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, i, projectiles[i]);
		}
	}
}

void shoot_projectile(char *projectiles, unsigned char x)
{
	if(projectiles[x] != -1)
		erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, x, projectiles[x]);
	projectiles[x] = MAX_Y-1;
	draw_projectile(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, x, MAX_Y-1);
}

void check_hit(unsigned char x, unsigned char y, unsigned char who, unsigned char i)
{

	unsigned char j, hit = 0;

	if(who == 1)//ship
	{
		for(j = 0; j<INIT_NUM; j++)
		{
			if(x == invaders[j].x_crdnt && y == invaders[j].y_crdnt && invaders[j].alive)
			{
				invaders[j].alive = 0;
				projectiles[x] = -1;
				erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, x, y);
				hit++;
			}
		}
	} else
	{
		if(y == projectiles[x] && invaders[i].alive)
		{
			invaders[i].alive = 0;
			projectiles[x] = -1;
			erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, x, y);
			invaders_num--;
		}
	}

	while(hit)
	{
		hit--;
		invaders_num--;
	}

	if(!invaders_num)
	{
		game_over = 1;
	}
}

void clear_text_screen(Xuint32 BaseAddress){
	int i;
	for (i = 0; i < 4800; i++){
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + i*4, 0x20);
	}
}

void print_string(Xuint32 BaseAddress, char string_s[], int lenght){
	int i;
	for (i = 0; i < lenght; i++){
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + cursor_position + i*4, (string_s[i]-0x40));
	}
}

void set_cursor(Xuint32 new_value){
	cursor_position = new_value;
}*/

#include <stdio.h>
#include "platform.h"
#include "xintc.h"
#include "xparameters.h"
#include "xio.h"
#include "xil_io.h"
#include "xil_exception.h"

#define VGA_PERIPH_MEM_mWriteMemory(Address, Data) \
 	Xil_Out32(Address, (Xuint32)(Data))
#define VGA_PERIPH_MEM_mReadMemory(Address) \
 	Xil_In32(Address)

#define GRAPHICS_MEM_OFF 0x2000000

XIntc Intc;
void clear_graphics_screen(Xuint32 BaseAddress)
{
	int i;
	for (i = 0; i < 9600*4; i++){
	    VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x00000000);
	}
}

void draw_square(Xuint32 BaseAddress,unsigned char x_crdnt, unsigned char y_crdnt)
{
	int j, k;
	k = x_crdnt;
	for (j = 0 + 32*y_crdnt; j < 32 + 32*y_crdnt; j++)
	{
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k  )*4, 0x22222222);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+1)*4, 0x21111112);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+2)*4, 0x21111112);
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + (j*(640/8) + k+3)*4, 0x22222222);
	}
}

int main()
{
    int i, j, k;

	init_platform();

	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0b10);	//display mode
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0x000000);//color 0
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14, 0xff0000);//color 1
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0x00ff00);//color 2
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x1C, 0x0000ff);//color 3
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x20, 0x00ffff);//color 4
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x24, 0xff00ff);//color 5
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x28, 0xffff00);//color 6
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x2C, 0x000000);//color 7
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x30, 0xffffff );//color 8
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x34, 0xff1493);//color 9
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x38, 0x8b4513);//color 10
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x3C, 0x556b2f);//color 11
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x40, 0x191970);//color 12
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x44, 0xb8860b);//color 13
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x48, 0xffe4c4);//color 14
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x4C, 0xd2691e);//color 15

	clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);

	draw_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, 76, 0);
	/*for (j = 0; j < 480; j++){
		for (k = 0; k<(640/8); k++){
			i = j*(640/8) + k;

			if (j >= (1) && j < (480) && (k >= 40) && (k < 41)) {
				VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + GRAPHICS_MEM_OFF + i*4, 0x12345678);
			}
		}
    }*/


	/*for (j = 0; j < 480; j++){
			for (k = 0; k<(640/8); k++){
				i = j*(640/8) + k;

				if (j >= (0 + 8*0) && j < (480 + 8*0) && (k >= 40) && (k < 80)) {
					VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + GRAPHICS_MEM_OFF + i*4, 0x12345678);
				}
			}
	}*/



    return 0;
}
