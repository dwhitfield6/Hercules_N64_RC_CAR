/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 02/05/16     14.0_DW0a   New project creation.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Contains functions for the eCAP module for timing captures.
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

#include "ECAP.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Inline Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

/******************************************************************************/
/* InitECAP
 *
 * The function initializes the ECAP module.								  */
/******************************************************************************/
void InitECAP(void)
{
	ecapREG4->ECCTL2 |= (3L << 1); 	// Wrap after Capture Event 4 in continuous mode.
	ecapREG4->ECCTL1 |= CAPLDEN;	// Enable CAP1-4 register loads at capture event time

	/* capture 1 */
	ecapREG4->ECCTL1 |= CTRRST1;	// Reset counter after Capture Event 1 time-stamp has been captured	(used in difference mode operation)
	ecapREG4->ECCTL1 |= CAP1POL;	// Capture Event 1 triggered on a falling edge (FE)

	/* capture 2 */
	ecapREG4->ECCTL1 |= CTRRST2;	// Reset counter after Capture Event 2 time-stamp has been captured	(used in difference mode operation)
	ecapREG4->ECCTL1 &= ~CAP2POL;	// Capture Event 2 triggered on a rising edge (FE)

	/* capture 3 */
	ecapREG4->ECCTL1 |= CTRRST3;	// Reset counter after Capture Event 3 time-stamp has been captured	(used in difference mode operation)
	ecapREG4->ECCTL1 |= CAP3POL;	// Capture Event 3 triggered on a falling edge (FE)

	/* capture 4 */
	ecapREG4->ECCTL1 |= CTRRST4;	// Reset counter after Capture Event 4 time-stamp has been captured	(used in difference mode operation)
	ecapREG4->ECCTL1 &= ~CAP4POL;	// Capture Event 4 triggered on a rising edge (FE)

	ecapREG4->ECCTL2 &= ~TSCTRSTOP;		// stop
}

/******************************************************************************/
/* ECAP_Interrupt
 *
 * The function controls the ECAP interrupts.								  */
/******************************************************************************/
void ECAP_Interrupt(unsigned char state)
{
	if(state)
	{
		ecapREG4->ECEINT = CTROVF | CEVT4;	// enable overflow and compare 4
	}
	else
	{
		ecapREG4->ECEINT = 0;
	}
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
