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

#include "AUDIO.h"
#include "DAC.h"
#include "ECAP.h"
#include "LED.h"
#include "N64.h"
#include "POT.h"
#include "SPI.h"
#include "TEST.h"
#include "TIMERS.h"
#include "WAV.h"

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

	    /************* Audio Amplifier *************/
	    /* Connected to the diagnostic pin on the audio amp */
	    gioPORTA->DIR &= ~(1L << AUDIO_DIAGNOSTIC_GPIO); 	// input
	    gioPORTA->PSL |= (1L << AUDIO_DIAGNOSTIC_GPIO); 	// pull-up

	    /* Connected to the standby pin on the audio amp */
	    gioPORTA->DIR |= (1L << AUDIO_STANDBY_GPIO); 	// output

	    /************* N64 controller *************/
	    /* Connected to the data line on the N64 controller */
	    gioPORTB->DIR |= (1L << N64_0); 	// output
	    gioPORTB->PDR |= (1L << N64_0); 	// open drain
	    gioPORTB->PSL |= (1L << N64_0); 	// pull-up
	    gioPORTB->DIR &= ~(1L << N64_1); 	// input
	    gioPORTB->PSL |= (1L << N64_1); 	// pull-up

	    /************* Test points *************/
	    /* Connected to test point 1 (j1 pin 8) */
	    gioPORTA->DIR |= (1L << TEST_POINT_1); // output

	    /* Connected to test point 1 (j1 pin 5) */
	    gioPORTA->DIR |= (1L << TEST_POINT_2); // output
}

/******************************************************************************/
/* Init_Modules
 *
 * The function initializes the modules.									  */
/******************************************************************************/
void Init_Modules(void)
{
	/* enable global interrupts */
	_enable_interrupt_();

	InitTimers();
	InitSPI();
	InitAudio();
	InitLEDs();
	InitDAC();
	InitPOT();
	InitECAP();
	InitN64();
	InitWAV();
	InitTest();
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
