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
#ifndef POT_H
#define	POT_H

#include "HL_sys_common.h"    		// TMS570LC43xx Include file
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "SYSTEM.h"

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/
typedef enum e_mcp_pot_registers
{
    WIPER0 	= 0,
	WIPER1 	= 1,
	TCON 	= 4,
	STATUS 	= 5,
}ENUM_POT_REG;

/******************************************************************************/
/* STEERING_START
 *
 * This is the starting position of the steering.							  */
/******************************************************************************/
#define STEERING_START 127

/******************************************************************************/
/* GAS_START
 *
 * This is the starting position of the gas.								  */
/******************************************************************************/
#define GAS_START 127

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitPOT(void);
void InitPOTSteering(void);
void InitPOTGas(void);
void POT_SendDataSteering(ENUM_POT_REG reg, unsigned short data);
void POT_SendDataGas(ENUM_POT_REG reg, unsigned short data);
unsigned char POT_GetSteeringUpdateFlag(void);
void POT_SetSteeringUpdateFlag(void);
void POT_ClearSteeringUpdateFlag(void);
unsigned char POT_GetGasUpdateFlag(void);
void POT_SetGasUpdateFlag(void);
void POT_ClearGasUpdateFlag(void);
void POT_SetSteering(unsigned short value);
void POT_SetGas(unsigned short value);

#endif	/* POT_H */
