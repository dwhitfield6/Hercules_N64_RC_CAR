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
/* Contains functions for the SPI digital potentiometer.
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

#include "POT.h"
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
/* InitPOT
 *
 * The function initializes both MCP4151 digital potentiometers.			  */
/******************************************************************************/
void InitPOT(void)
{
	InitPOTSteering();
	InitPOTGas();
}

/******************************************************************************/
/* InitPOTSteering
 *
 * The function initializes both MCP4151 digital potentiometer used for
 *  steering.																  */
/******************************************************************************/
void InitPOTSteering(void)
{
	POT_SendDataSteering(TCON, 0x04);		// connect the wipers
	POT_SendDataSteering(WIPER0, STEERING_START);
}

/******************************************************************************/
/* InitPOTGas
 *
 * The function initializes both MCP4151 digital potentiometer used for the
 *  gas.																	  */
/******************************************************************************/
void InitPOTGas(void)
{
	POT_SendDataGas(TCON, 0x04);	// connect the wipers
	POT_SendDataGas(WIPER0, GAS_START);
}

/******************************************************************************/
/* POT_SendDataSteering
 *
 * The function sends commands to the digital pot connected to the steering.  */
/******************************************************************************/
void POT_SendDataSteering(ENUM_POT_REG reg, unsigned short data)
{
	unsigned char temp = reg << 4;
	temp |= ((data & 0x0100) >> 8);

	SPI_AddToTXBuffer(temp, CS_POT_STEERING, 1);
	temp = (data & 0x00FF);
	SPI_AddToTXBuffer(temp, CS_POT_STEERING, 0);
}

/******************************************************************************/
/* POT_SendDataGas
 *
 * The function sends commands to the digital pot connected to the gas.		  */
/******************************************************************************/
void POT_SendDataGas(ENUM_POT_REG reg, unsigned short data)
{
	unsigned char temp = reg << 4;
	temp |= ((data & 0x0100) >> 8);

	SPI_AddToTXBuffer(temp, CS_POT_GAS, 1);
	temp = (data & 0x00FF);
	SPI_AddToTXBuffer(temp, CS_POT_GAS, 0);
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
