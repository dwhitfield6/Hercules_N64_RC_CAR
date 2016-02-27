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

#include "AUDIO.h"
#include "DAC.h"
#include "HL_gio.h"
#include "LED.h"
#include "MISC.h"
#include "N64.h"
#include "POT.h"
#include "SPI.h"
#include "SYSTEM.h"
#include "TEST.h"
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
		TEST_Toggle1(); // toggle test point

    	/* wait for the next main loop flag */
    	while(!MAIN_TimerFlag);
    	MAIN_TimerFlag = FALSE;

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
    			POT_SetSteering(255-(N64_New.Joystick[X] + 128));
    			POT_ClearSteeringUpdateFlag();
    		}
    		if(POT_GetGasUpdateFlag())
    		{
    			/* update throttle */
    			if(N64_New.A || N64_New.B)
    			{
    				/* A is pressed and B is not */
    				if(((N64_New.Joystick[Y] > Y_MIDPOINT_HIGH) && N64_New.A) || ((N64_New.Joystick[Y] < Y_MIDPOINT_LOW) && N64_New.B))
    				{
    					/* user is pushing forward or backward and its in range */
    					POT_SetGas(255-(N64_New.Joystick[Y] + 128));
    				}
    				else
    				{
    					/* user is pushing forward or backward and its not in range */
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
    		if(N64_GetButtonState(&N64_New)) // get new buttons
    		{
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
					if(N64_New.A)
					{
						LED_Green(ON);
					}
					else
					{
						LED_Green(OFF);
					}
				}
				if(N64_New.B != N64_Old.B)
				{
					POT_SetGasUpdateFlag();
					if(N64_New.B)
					{
						LED_Red(ON);
					}
					else
					{
						LED_Red(OFF);
					}
				}
				if(N64_New.Z != N64_Old.Z)
				{
					if(N64_New.Z)
					{
						WAV_AddToQueue(TURTLE);
					}
				}
				if(N64_New.R != N64_Old.R)
				{
					if(N64_New.R)
					{
						WAV_AddToQueue(BANANA);
					}
				}
				memcpy(&N64_Old, &N64_New, sizeof(TYPE_N64_BUT));
    		}
    		N64_SetUpdateFlag(FALSE);
    	}

    	/* Check for audio amplifer diagnostic fail */
    	if(Audio_IsDiagnosticFail())
    	{
    		/* audio amplifier detected a problem */
    		Audio_Power(OFF);
    	}

    	/* Increment N64 counter */
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
