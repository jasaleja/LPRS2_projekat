/*
 * SI_init.c
 *
 *  Created on: 16.06.2015.
 *      Author: student
 */

#include "SI_interrupt.h"

void vga_interrupt_handler(void *BaseAddress)
{
	input = VGA_PERIPH_MEM_mReadMemory(XPAR_MY_PERIPHERAL_0_BASEADDR);

	/* spaceship and projectiles signals */
	if(spaceship_speed == SPACESHIP_SPEED)
	{
		spaceship_flag = 1;
		spaceship_speed = 0;
	}
	else
		spaceship_speed++;

	if(projectil_speed == PROJECTILE_SPEED)
	{
		projectil_flag = 1;
		projectil_speed = 0;
	}
	else
		projectil_speed++;
	/*************************************/

	/* signals of movement of rows of invaders */
	if(counter == INVADER_SPEED)
	{
		flag_row[2] = 1;
	}
	else if(counter == INVADER_SPEED*2)
	{
		flag_row[1] = 1;
	}
	else if(counter == INVADER_SPEED*3)
	{
		flag_row[0] = 1;
		counter = 0;
	}
	counter++;
	/*************************************/

	if(shoot_flag != 0)
	{
		shoot_flag--;
	}

	if(counter1 == 5)
	{
		counter1 = 0;
		flag = 1;
	}
	counter1++;
}

void init_interrupt_controller()
{
	XStatus Status;

	XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x54, 0x1E0); //init terminal counter on 524
	XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x58, 1);		//enable timer

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
