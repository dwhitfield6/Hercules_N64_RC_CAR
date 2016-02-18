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
/* Contains functions for the TDA7396 audio amp.
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

#include "AUDIO.h"
#include "USER.h"

/******************************************************************************/
/* Private Variable Declaration      	                                      */
/******************************************************************************/
static volatile unsigned char Audio_Power_State = OFF;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned long Audio_Powercount = 0;

/******************************************************************************/
/* Inline Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

/******************************************************************************/
/* InitAudio
 *
 * The function initializes the Audio amplifier.							  */
/******************************************************************************/
void InitAudio(void)
{
	Audio_Power(OFF);
}

/******************************************************************************/
/* Audio_Power
 *
 * The function controls the Audio Amplifier.								  */
/******************************************************************************/
void Audio_Power(unsigned char state)
{
	if(state)
	{
		gioPORTA->DSET = (1L << AUDIO_STANDBY_GPIO);
		Audio_Power_State = ON;
	}
	else
	{
		gioPORTA->DCLR = (1L << AUDIO_STANDBY_GPIO);
		Audio_Power_State = OFF;
	}
}

/******************************************************************************/
/* Audio_GetPowerStatus
 *
 * The function returns the state of the audio amplifer.					  */
/******************************************************************************/
unsigned char Audio_GetPowerStatus(void)
{
	return Audio_Power_State;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
