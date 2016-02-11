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
/* Contains Functions for TMS570 initialization.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "HL_sys_common.h"    		// TMS570LC43xx Include file
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "HL_gio.h"

#include "LED.h"
#include "SPI.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Inline Functions															  */
/******************************************************************************/

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* Init_Pins
 *
 * The function initializes the gpio pins.									  */
/******************************************************************************/
void Init_Pins(void)
{
	    /** bring GIO module out of reset */
	    gioREG->GCR0   = 1U;
	    gioREG->ENACLR = 0xFFU;
	    gioREG->LVLCLR = 0xFFU;

	    /* initialize port A */
	    gioPORTA->DOUT 	= 0; 	// all outputs off
	    gioPORTA->DIR	= 0;	// all pins as input
	    gioPORTA->PDR 	= 0;	// no open drain outputs
	    gioPORTA->PSL 	= 0;	// no pull-ups or pull-downs
	    gioPORTA->PULDIS = 0;	// no pull-ups or pull-downs

	    /* initialize port B */
	    gioPORTB->DOUT 	= 0; 	// all outputs off
	    gioPORTB->DIR	= 0;	// all pins as input
	    gioPORTB->PDR 	= 0;	// no open drain outputs
	    gioPORTB->PSL 	= 0;	// no pull-ups or pull-downs
	    gioPORTB->PULDIS = 0;	// no pull-ups or pull-downs

	    /* interupt polarity */
		gioREG->POL = 0;

	    /* interrupt level */
	    gioREG->LVLSET = 0;

	    /* clear all pending interrupts */
	    gioREG->FLG = 0xFFU;


	    /************* LEDs *************/
	    /* Connected to the green LED on the Launchpad */
	    gioPORTB->DIR |= (1L << GREEN_LED_GPIO); // output

	    /* Connected to the green portion of the Bi-color LED */
	    gioPORTA->DIR |= (1L << BI_GREEN_LED_GPIO); // output

	    /* Connected to the red portion of the Bi-color LED */
	    gioPORTA->DIR |= (1L << BI_RED_LED_GPIO); // output
}

/******************************************************************************/
/* Init_Modules
 *
 * The function initializes the modules.									  */
/******************************************************************************/
void Init_Modules(void)
{
	InitLEDs();
	InitSPI();
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
