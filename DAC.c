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
/* Contains functions for the SPI digital to analog converter (MCP4822).
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

#include "DAC.h"
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
/* InitDAC
 *
 * The function initializes the MCP4822 DAC.								  */
/******************************************************************************/
void InitDAC(void)
{
	DAC_SendData(DAC_A, DAC_MIDPOINT);
	DAC_SendData(DAC_B, DAC_MIDPOINT);
}

/******************************************************************************/
/* DAC_SendData
 *
 * The function sends commands to the DAC.									  */
/******************************************************************************/
void DAC_SendData(ENUM_DAC_CHANNEL channel, unsigned short data)
{
	unsigned char temp = 0;
	if(channel == DAC_B)
	{
		temp |= 0x80;
	}
	if(DAC_GAIN)
	{
		temp |= 0x20;
	}
	temp |= 0x10; // Active mode
	temp |= ((data & 0x0F00) >> 8);
	SPI_AddToTXBuffer(temp, CS_DAC, 1);
	temp = (data & 0x00FF);
	SPI_AddToTXBuffer(temp, CS_DAC, 0);
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
