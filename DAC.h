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
#ifndef DAC_H
#define	DAC_H

#include "HL_sys_common.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "SYSTEM.h"

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/
typedef enum e_dac_channel
{
    DAC_A = 0,
	DAC_B = 1,
}ENUM_DAC_CHANNEL;

/******************************************************************************/
/* DAC_GAIN
 *
 * Set this to 1 for low gain or 0 for high gain.							  */
/******************************************************************************/
#define DAC_GAIN 1

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define DAC_FULL_SCALE_POSITIVE	4095L
#define DAC_FULL_SCALE_NEGATIVE 0L
#define DAC_MIDPOINT			2047L

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitDAC(void);
void DAC_SendData(ENUM_DAC_CHANNEL channel, unsigned short data);

#endif	/* DAC_H */
