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
/* Contains functions for the SPI bus.
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

#include "SPI.h"

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
/* InitSPI
 *
 * The function initializes the SPI bus.									  */
/******************************************************************************/
void InitSPI(void)
{
	InitSPI1();
}

/******************************************************************************/
/* InitSPI1
 *
 * The function initializes the SPI module 1 bus.							  */
/******************************************************************************/
void InitSPI1(void)
{
	spiREG1->GCR0 &= ~nRESET; 			// SPI is in the reset state.
	spiREG1->GCR0 |= nRESET; 			// SPI is out of the reset state

	SPI_Parameters1(master, 0, 500L);	// set up SPI parameters
	spiREG1->GCR1 |= SPIEN;				// Activates SPI
}

/******************************************************************************/
/* SPI_Parameters1
 *
 * The function configures the SPI module.									  */
/******************************************************************************/
void SPI_Parameters1(ENUM_MASTER_SLAVE master_slave, unsigned char mode, unsigned long speedKhz)
{
    double speed = (double) speedKhz;
    speed *= 1000.0;

    if(master_slave == master)
    {
    	spiREG1->GCR1 |= MASTER;	// SPISOMI[7:0] pins are inputs, SPISIMO[7:0] pins are outputs
    }
    else
    {
    	spiREG1->GCR1 &= ~MASTER;	// SPISIMO[7:0] pins are inputs, SPISOMI[7:0] pins are outputs
    }

    spiREG1->GCR1 |= CLKMOD;		// Clock is internally-generated.

    // = (unsigned long) MSC_Round(((double)PBCLK/(2.0 * (double) speedKhzDB)) - 1.0);
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
