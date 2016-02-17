/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 02/02/16     14.0_DW0a   New project creation.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#ifndef MISC_H
#define	MISC_H

#include "HL_sys_common.h"    		// TMS570LC43xx Include file
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "SYSTEM.h"

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Bit Defines                                                                */
/******************************************************************************/
#define b0 			0x00L
#define b00 		0x00L
#define b000 		0x00L
#define b0000 		0x00L
#define b00000 		0x00L
#define b000000 	0x00L
#define b0000000 	0x00L
#define b00000000 	0x00L

#define b1 			0x01L
#define b01 		0x01L
#define b001 		0x01L
#define b0001 		0x01L
#define b00001 		0x01L
#define b000001 	0x01L
#define b0000001 	0x01L
#define b00000001 	0x01L

#define b10 		0x02L
#define b010 		0x02L
#define b0010 		0x02L
#define b00010 		0x02L
#define b000010 	0x02L
#define b0000010 	0x02L
#define b00000010 	0x02L

#define b11 		0x03L
#define b011 		0x03L
#define b0011 		0x03L
#define b00011 		0x03L
#define b000011 	0x03L
#define b0000011 	0x03L
#define b00000011 	0x03L

#define b100 		0x04L
#define b0100 		0x04L
#define b00100 		0x04L
#define b000100 	0x04L
#define b0000100 	0x04L
#define b00000100 	0x04L

#define b101 		0x05L
#define b0101 		0x05L
#define b00101 		0x05L
#define b000101 	0x05L
#define b0000101 	0x05L
#define b00000101 	0x05L

#define b110 		0x06L
#define b0110 		0x06L
#define b00110 		0x06L
#define b000110 	0x06L
#define b0000110 	0x06L
#define b00000110 	0x06L

#define b111 		0x07L
#define b0111 		0x07L
#define b00111 		0x07L
#define b000111 	0x07L
#define b0000111 	0x07L
#define b00000111 	0x07L

#define b1000 		0x08L
#define b01000 		0x08L
#define b001000 	0x08L
#define b0001000 	0x08L
#define b00001000 	0x08L

#define b1001 		0x09L
#define b01001 		0x09L
#define b001001 	0x09L
#define b0001001 	0x09L
#define b00001001 	0x09L

#define b1010 		0x0AL
#define b01010 		0x0AL
#define b001010 	0x0AL
#define b0001010 	0x0AL
#define b00001010 	0x0AL

#define b1011 		0x0BL
#define b01011 		0x0BL
#define b001011 	0x0BL
#define b0001011 	0x0BL
#define b00001011 	0x0BL

#define b1100 		0x0CL
#define b01100 		0x0CL
#define b001100 	0x0CL
#define b0001100 	0x0CL
#define b00001100 	0x0CL

#define b1101 		0x0DL
#define b01101 		0x0DL
#define b001101 	0x0DL
#define b00011101 	0x0DL
#define b00001101 	0x0DL

#define b1110 		0x0EL
#define b01110 		0x0EL
#define b001110 	0x0EL
#define b0001110 	0x0EL
#define b00001110 	0x0EL

#define b1111 		0x0FL
#define b01111 		0x0FL
#define b001111 	0x0FL
#define b0001111 	0x0FL
#define b00001111 	0x0FL

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void MSC_DelayUS(unsigned long US);
void MSC_DelayNOP(unsigned long NOPs);
double MSC_Round(double input);
unsigned short MSC_EndianShort(unsigned short number);
unsigned short MSC_EndianShortArray(unsigned char* buffer);
unsigned long MSC_EndianLong(unsigned long number);
unsigned long MSC_EndianLongArray(unsigned char* buffer);

#endif	/* MISC_H */
