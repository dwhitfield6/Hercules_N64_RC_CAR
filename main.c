/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 02/02/16     14.0_DW0a   New project creation.
 * 12/08/17     14.0_DW0b   Added RAMFUNC functionality.
 * 							Fixed minor bugs with formatting.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Contains main function.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "HL_sys_common.h"
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
/* Static functions                                                           */
/******************************************************************************/
void fastmain(void);

/******************************************************************************/
/* Global Variable                                                            */
/******************************************************************************/
extern unsigned long __RamfuncsLoadStart;
extern unsigned long __RamfuncsLoadEnd;
extern unsigned long __RamfuncsRunStart;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
int main (void)
{
#ifdef USE_RAMFUNC
	char *src;
	char *end;
	char *dest;
#endif

	_disable_IRQ_interrupt_();

#ifdef USE_RAMFUNC
	/* Copy the Ram functions */
	src  = (char *)&__RamfuncsLoadStart;
	end  = (char *)&__RamfuncsLoadEnd;
	dest = (char *)&__RamfuncsRunStart;
	while(src < end)
	{
		*dest++ = *src++;
	}
	NOP();
	NOP();
#endif

	_cacheEnable_();
	_dCacheInvalidate_();
	_iCacheInvalidate_();

	fastmain();
}

#ifdef USE_RAMFUNC
#pragma CODE_SECTION(fastmain, "TI.ramfuncs")
#endif
/******************************************************************************/
/* fastmain
 *
 * The fastmain loop. Runs from RAM.
 *																			  */
/******************************************************************************/
void fastmain(void)
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
    	while(!g_MAIN_TimerFlag);
    	g_MAIN_TimerFlag = FALSE;

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
    			POT_SetSteering(255-(g_N64_New.Joystick[X] + 128));
    			POT_ClearSteeringUpdateFlag();
    		}
    		if(POT_GetGasUpdateFlag())
    		{
    			/* update throttle */
    			if(g_N64_New.A || g_N64_New.B)
    			{
    				/* A or B is pressed */
#ifdef N64_NO_PARTIAL_THROTTLE
    				if((g_N64_New.A) && (!g_N64_New.B))
					{
						POT_SetGas(0); // full speed forward
					}
    				else if((!g_N64_New.A) && (g_N64_New.B))
					{
    					POT_SetGas(255); // full speed backward
					}
    				else
    				{
    					/* user is pushing both A and B*/
    					POT_SetGas(GAS_START);
    				}
#else
    				if(((g_N64_New.Joystick[Y] > Y_MIDPOINT_HIGH) && g_N64_New.A) || ((g_N64_New.Joystick[Y] < Y_MIDPOINT_LOW) && g_N64_New.B))
    				{
    					/* user is pushing forward or backward and its in range */
    					POT_SetGas(255-(g_N64_New.Joystick[Y] + 128));
    				}
    				else
    				{
    					/* user is pushing forward or backward and its not in range */
    					POT_SetGas(GAS_START);
    				}
#endif
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
    		if(N64_GetButtonState(&g_N64_New))
    		{
    			/* get new buttons */
				if(g_N64_New.Joystick[Y] != g_N64_Old.Joystick[Y])
				{
					POT_SetGasUpdateFlag();
				}
				if(g_N64_New.Joystick[X] != g_N64_Old.Joystick[X])
				{
					POT_SetSteeringUpdateFlag();
				}
				if(g_N64_New.A != g_N64_Old.A)
				{
					POT_SetGasUpdateFlag();
					if(g_N64_New.A)
					{
						LED_Green(ON);
					}
					else
					{
						LED_Green(OFF);
					}
				}
				if(g_N64_New.B != g_N64_Old.B)
				{
					POT_SetGasUpdateFlag();
					if(g_N64_New.B)
					{
						LED_Red(ON);
					}
					else
					{
						LED_Red(OFF);
					}
				}
				if(g_N64_New.Z != g_N64_Old.Z)
				{
					if(g_N64_New.Z)
					{
						WAV_AddToQueue(TURTLE);
					}
				}
				if(g_N64_New.R != g_N64_Old.R)
				{
					if(g_N64_New.R)
					{
						WAV_AddToQueue(BANANA);
					}
				}
				memcpy(&g_N64_Old, &g_N64_New, sizeof(TYPE_N64_BUT));
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
    	g_N64_ControllerCount++;
    	if(g_N64_ControllerCount >= N64_SAMPLERATE)
    	{
    		g_N64_ControllerCount = 0;
    		N64_SetUpdateFlag(TRUE);
    	}
    }
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
