/*
 * defines.h
 *
 *  Created on: 16.06.2015.
 *      Author: student
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#include <stdio.h>
#include "platform.h"
#include "xintc.h"
#include "xparameters.h"
#include "xio.h"
#include "xil_io.h"
#include "xil_exception.h"
#include "xbasic_types.h"

#define VGA_PERIPH_MEM_mWriteMemory(Address, Data) \
 	Xil_Out32(Address, (Xuint32)(Data))
#define VGA_PERIPH_MEM_mReadMemory(Address) \
 	Xil_In32(Address)

#define GRAPHICS_MEM_OFF 0x2000000

#define INIT_ROWS 3
#define INIT_COLS 7
#define INIT_NUM INIT_ROWS*INIT_COLS

#define MIN_SHIP_Y 0
#define MAX_SHIP_Y 14
#define MIN_SHIP_X 0
#define MAX_SHIP_X 77

#define MAX_PROJECTILES_Y 15

#define MAX_PROJECTILES_X 79

#define LEFT_JOY 23
#define MIDDLE_JOY 27
#define RIGHT_JOY 29
#define LEFT_DIR 0
#define RIGHT_DIR 1

typedef struct invader_t
{
	unsigned char x_crdnt;
	unsigned char y_crdnt;
	unsigned char alive;
}invader_t;

#endif /* DEFINES_H_ */
