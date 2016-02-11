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
/* Private Variable Declaration      	                                      */
/******************************************************************************/
static unsigned char POT_SteeringFlag = FALSE;
static unsigned char POT_GasFlag = FALSE;

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
	POT_SetSteering(STEERING_START);
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
	POT_SetGas(GAS_START);
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

/******************************************************************************/
/* POT_GetSteeringUpdateFlag
 *
 * The function returns true if there has been an update to the steering
 *  value.																	  */
/******************************************************************************/
unsigned char POT_GetSteeringUpdateFlag(void)
{
	return POT_SteeringFlag;
}

/******************************************************************************/
/* POT_SetSteeringUpdateFlag
 *
 * The function sets the steering value update flag.						  */
/******************************************************************************/
void POT_SetSteeringUpdateFlag(void)
{
	POT_SteeringFlag = TRUE;
}

/******************************************************************************/
/* POT_ClearSteeringUpdateFlag
 *
 * The function clears the steering value update flag.						  */
/******************************************************************************/
void POT_ClearSteeringUpdateFlag(void)
{
	POT_SteeringFlag = FALSE;
}

/******************************************************************************/
/* POT_GetGasUpdateFlag
 *
 * The function returns true if there has been an update to the gas value.    */
/******************************************************************************/
unsigned char POT_GetGasUpdateFlag(void)
{
	return POT_GasFlag;
}

/******************************************************************************/
/* POT_SetGasUpdateFlag
 *
 * The function sets the gas value update flag.								  */
/******************************************************************************/
void POT_SetGasUpdateFlag(void)
{
	POT_GasFlag = TRUE;
}

/******************************************************************************/
/* POT_ClearGasUpdateFlag
 *
 * The function clears the gas value update flag.						  */
/******************************************************************************/
void POT_ClearGasUpdateFlag(void)
{
	POT_GasFlag = FALSE;
}

/******************************************************************************/
/* POT_SetSteering
 *
 * The function sets the steering value on the POT.							  */
/******************************************************************************/
void POT_SetSteering(unsigned short value)
{
	if(value > 0x0FFFU)
	{
		value = 0x0FFFU;
	}
	POT_SendDataSteering(WIPER0, value);
}

/******************************************************************************/
/* POT_SetGas
 *
 * The function sets the gas value on the POT.								  */
/******************************************************************************/
void POT_SetGas(unsigned short value)
{
	if(value > 0x0FFFU)
	{
		value = 0x0FFFU;
	}
	POT_SendDataGas(WIPER0, value);
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
