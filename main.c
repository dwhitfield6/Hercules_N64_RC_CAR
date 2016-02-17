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
/* Contains main function.
 *                                                                            */
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
#include "HL_gio.h"
#include "LED.h"
#include "MISC.h"
#include "N64.h"
#include "POT.h"
#include "SPI.h"
#include "SYSTEM.h"
#include "TIMERS.h"
#include "WAV.h"

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Global Variable                                                            */
/******************************************************************************/

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
int main (void)
{
	/* initialize the gpio pins */
	Init_Pins();

	/* initialize the hardware modules */
	Init_Modules();

	/* play the N64 starting sound */
	WAV_AddToQueue(START);

    while(1)
    {
    	/* Check for wav file activity */
    	if(WAV_IsPlaying())
    	{
    		/* wav playback occuring */
    		if(!WAV_IsStarted())
    		{
    			/* wav file has not started playing so setup */
    			WAV_Finished(FALSE);
    			if(WAV_SetupPlayback(WAV_PlayingQueue[0]))
    			{
    				/* set up the system for WAV file playback */
    				WAV_Started(TRUE);
    			}
    			else
    			{
    				/* wav file could not be set up to play */
    				WAV_Finished(TRUE);
    			}
    		}
    		if(WAV_IsFinished())
    		{
    			/* wav file finished playing */
    			WAV_Started(FALSE);
    			WAV_EraseFromQueue(); 		// erase the file from the playback queue
    			if(!WAV_PlayingQueue[0])
    			{
    				/* there are no more files to play */
    				WAV_Playing(FALSE);
    			}
    		}
    	}

    	/* Check for digital pot activity */
    	if(POT_GetSteeringUpdateFlag() || POT_GetGasUpdateFlag())
    	{
    		if(POT_GetSteeringUpdateFlag())
    		{
    			/* update steering */
    			POT_SetSteering(N64_New.Joystick[X]);
    			POT_ClearSteeringUpdateFlag();
    		}
    		if(POT_GetGasUpdateFlag())
    		{
    			/* update throttle */
    			if(N64_New.A && !N64_New.B)
    			{
    				/* A is pressed and B is not */
    				if(N64_New.Joystick[Y] > Y_MIDPOINT_HIGH)
    				{
    					/* user is pushing forward */
    					POT_SetGas(N64_New.Joystick[Y]);
    				}
    				else
    				{
    					/* user is not pushing forward */
    					POT_SetGas(GAS_START);
    				}
    			}
    			else if(N64_New.B && !N64_New.A)
    			{
    				/* B is pressed and A is not */
    				if(N64_New.Joystick[Y] < Y_MIDPOINT_LOW)
    				{
    					/* user is pushing backward */
    					POT_SetGas(N64_New.Joystick[Y]);
    				}
    				else
    				{
    					/* user is not pushing backward */
    					POT_SetGas(GAS_START);
    				}
    			}
    			else
    			{
    				/* neither A nor B is pressed */
    				POT_SetGas(GAS_START);
    			}
    			POT_ClearGasUpdateFlag();
    		}
    	}

    	/* Check for N64 controller activity */
    	if(N64_GetUpdateFlag())
    	{
    		N64_GetButtonState(&N64_New); // get new buttons

    		if(N64_New.Joystick[Y] != N64_Old.Joystick[Y])
    		{
    			POT_SetGasUpdateFlag();
    		}
    		if(N64_New.Joystick[X] != N64_Old.Joystick[X])
    		{
    			POT_SetSteeringUpdateFlag();
    		}
    		if(N64_New.A != N64_Old.A)
    		{
    			POT_SetGasUpdateFlag();
    		}
    		if(N64_New.B != N64_Old.B)
    		{
    			POT_SetGasUpdateFlag();
    		}
    		if(N64_New.Z != N64_Old.Z)
    		{
    			WAV_AddToQueue(TURTLE);
    		}
    		if(N64_New.R != N64_Old.R)
    		{
    			WAV_AddToQueue(BANANA);
    		}
    		memcpy(&N64_Old, &N64_New, sizeof(TYPE_N64_BUT));
    		N64_SetUpdateFlag(FALSE);
    	}

    	N64_ControllerCount++;
    	if(N64_ControllerCount >= N64_SAMPLERATE)
    	{
    		N64_ControllerCount = 0;
    		N64_SetUpdateFlag(TRUE);
    	}
    }
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
