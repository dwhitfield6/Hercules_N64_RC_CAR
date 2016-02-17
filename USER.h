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
#ifndef USER_H
#define	USER_H

#include "HL_sys_common.h"    		// TMS570LC43xx Include file
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/******************************************************************************/
/* Project Name                                                               */
/******************************************************************************/
#define PROJECT_NAME "N64 RC Car"

/******************************************************************************/
/* Firmware Version                                                           */
/******************************************************************************/
#define FIRMWARE_VERSION "14.0_DW0a"

/******************************************************************************/
/* Copywrite message                                                          */
/******************************************************************************/
#define COPYWRITE_MESSAGE "Copywrite Marley Circuits 2016. All rights reserved."

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define OFF 0
#define ON 1
#define FAIL 0
#define PASS 1
#define NO 0
#define YES 1

#define MAX_UCHAR 	255
#define MAX_CHAR 	128
#define MAX_USHORT 	65535L
#define MAX_SHORT 	32767L
#define MAX_ULONG 	4294967295L
#define MAX_LONG 	2147483647L

#define ECAP4 		0
#define N2HET1_11 	1

/******************************************************************************/
/* Macro functions                                                            */
/******************************************************************************/
#define NOP() __asm(" nop");
#define Nop()	NOP()

/******************************************************************************/
/* Pin Defines                                                                */
/******************************************************************************/

/************* LEDs *************/
/* Connected to the green LED on the Launchpad */
#define GREEN_LED_GPIO 6L // GPIO B6

/* Connected to the green portion of the Bi-color LED */
#define BI_GREEN_LED_GPIO 0L // GPIO A0

/* Connected to the red portion of the Bi-color LED */
#define BI_RED_LED_GPIO 1L // GPIO A1

/************* Digital POT *************/
/* pin definitions not required */

/************* DAC *************/
/* pin definitions not required */

/************* Audio Amplifier *************/
/* Connected to the diagnostic pin on the audio amp */
#define AUDIO_DIAGNOSTIC_GPIO 5L // GPIO A5

/* Connected to the standby pin on the audio amp */
#define AUDIO_STANDBY_GPIO 2L // GPIO A2

/************* N64 controller *************/
/* Connected to the data line on the N64 controller */
#define N64_0 0L 	// GPIO B1
#define N64_1 1L 	// GPIO B0
#define N64_2 ECAP4
#define N64_3 N2HET1_11

/************* Test points *************/
/* Connected to test point 1 (j1 pin 8) */
#define TEST_POINT_1 6L // GPIO A6

/* Connected to test point 1 (j1 pin 5) */
#define TEST_POINT_2 7L // GPIO A6

/******************************************************************************/
/* Version variables                                                          */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void Init_Pins(void);
void Init_Modules(void);

#endif	/* USER_H */
