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
/* Contains functions for the N64 controller.
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

#include "ECAP.h"
#include "MISC.h"
#include "N64.h"
#include "TIMERS.h"
#include "USER.h"

/******************************************************************************/
/* Private Variable Declaration      	                                      */
/******************************************************************************/
static volatile unsigned char N64_ActivityFlag = FALSE;
static volatile unsigned char N64_ReceiveFlag = FALSE;
static unsigned long N64_TimingRaw[N64_INPUT_BUFFER_SIZE];
static unsigned char N64_Code[8+1+32+1];

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
TYPE_N64_BUT N64_New;
TYPE_N64_BUT N64_Old;
unsigned char N64_Buffer_Code[N64_CODE_SECTIONS];
volatile unsigned char N64_CodeSectionBit = 0;
volatile unsigned long N64_ControllerCount = 0;
volatile unsigned long N64_TimingInputBuffer[N64_INPUT_BUFFER_SIZE + 10];
volatile unsigned long N64_TimingInputBit = 0;

/******************************************************************************/
/* Inline Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

/******************************************************************************/
/* InitN64
 *
 * The function initializes the N64 controler.								  */
/******************************************************************************/
void InitN64(void)
{
	gioPORTB->DSET = (1L << N64_0); // start high
	TMR_SetTimerMicroSeconds1(1.0);
	N64_SendReset();
	N64_GetButtonState(&N64_New);
	memset(&N64_Old, 0, sizeof(TYPE_N64_BUT));
}

/******************************************************************************/
/* N64_GetButtonState
 *
 * The function gets the last button press from the controler. A logic 1 is
 *  1uS of low followed by 3 uS of high, a 0 is 3uS of low followed by 1 uS
 *   of high.			  */
/******************************************************************************/
void N64_BuildCode(ENUM_N64_REG action)
{
	unsigned char i;
	unsigned char place = 0;

	/* build code */
	for(i=0;i<8;i++)
	{
		if(action & (1L << (7-i)))
		{
			/* logical 1 */
			N64_Buffer_Code[place++] = 0;
			N64_Buffer_Code[place++] = 1;
			N64_Buffer_Code[place++] = 1;
			N64_Buffer_Code[place++] = 1;
		}
		else
		{
			/* logical 0 */
			N64_Buffer_Code[place++] = 0;
			N64_Buffer_Code[place++] = 0;
			N64_Buffer_Code[place++] = 0;
			N64_Buffer_Code[place++] = 1;
		}
	}

	/* build stop bit */
	N64_Buffer_Code[place++] = 0;
	N64_Buffer_Code[place++] = 1;
	N64_Buffer_Code[place++] = 1;
	N64_Buffer_Code[place++] = 1;
}

/******************************************************************************/
/* N64_DecodeTiming
 *
 * The function decodes the raw N64 timing data.							  */
/******************************************************************************/
unsigned char N64_DecodeTiming(TYPE_N64_BUT* buttons)
{
	unsigned long i;
	long j;
	unsigned char index = 0;
	unsigned long reg = 0;
	unsigned long temp_buttons = 0;

	/* subtract out the starting place */
	for(i=0;i<N64_INPUT_BUFFER_SIZE;i++)
	{
		N64_TimingRaw[i] = N64_TimingInputBuffer[i] - ECAP_PRELOAD;
	}

	/* take the difference in time for the odd places */
	for(i=0;i<N64_INPUT_BUFFER_SIZE;i+=4)
	{
		/* take the difference in time for the odd places */
		for(j=3;j>=0;j--)
		{
			if(j)
			{
				/* odd buffer places */
				N64_TimingRaw[i+j] -= N64_TimingRaw[(i+j)-1];
			}
		}
	}

	/* calculate from counts to micro seconds */
	for(i=0;i<N64_INPUT_BUFFER_SIZE;i++)
	{
		N64_TimingRaw[i] = (unsigned long) MSC_Round((double) N64_TimingRaw[i] * 1000000.0 / ((double)VCLK2));
	}

	/* calculate the codes */
	for(i=0;i<N64_INPUT_BUFFER_SIZE;i+=2)
	{
		if(N64_TimingRaw[i] > 10 || N64_TimingRaw[i+1] > 10)
		{
			/* timing is out of scope */
			return FAIL;
		}
		if(N64_TimingRaw[i] > N64_TimingRaw[i+1])
		{
			N64_Code[index] = 0;
			index++;
		}
		else if(N64_TimingRaw[i] < N64_TimingRaw[i+1])
		{
			N64_Code[index] = 1;
			index++;
		}
		else
		{
			return FAIL;
		}
	}

	/* calculate the register call  */
	for(i=0;i<8L;i++)
	{
		if(N64_Code[i])
		{
			reg |= (1L << (7L-i));
		}
	}
	if(reg != GET_BUTTONS)
	{
		/* we didnt ask to read the controler */
		return FAIL;
	}
	if(N64_Code[8] != 1)
	{
		/* there wasnt a valid stop bit */
		return FAIL;
	}

	/* calculate the buttons */
	for(i=9;i<41L;i++)
	{
		if(N64_Code[i])
		{
			temp_buttons |= (1L << (i - 9L));
		}
	}

	/* button A */
	if(temp_buttons & 0x00000001)
	{
		buttons->A = 1;
	}
	else
	{
		buttons->A = 0;
	}

	/* button B */
	if(temp_buttons & 0x00000002)
	{
		buttons->B = 1;
	}
	else
	{
		buttons->B = 0;
	}

	/* button Z */
	if(temp_buttons & 0x00000004)
	{
		buttons->Z = 1;
	}
	else
	{
		buttons->Z = 0;
	}

	/* button start */
	if(temp_buttons & 0x00000008)
	{
		buttons->Start = 1;
	}
	else
	{
		buttons->Start = 0;
	}

	/* button up */
	if(temp_buttons & 0x00000010)
	{
		buttons->L_Pad[UP] = 1;
	}
	else
	{
		buttons->L_Pad[UP] = 0;
	}

	/* button down */
	if(temp_buttons & 0x00000020)
	{
		buttons->L_Pad[DOWN] = 1;
	}
	else
	{
		buttons->L_Pad[DOWN] = 0;
	}

	/* button left */
	if(temp_buttons & 0x00000040)
	{
		buttons->L_Pad[LEFT] = 1;
	}
	else
	{
		buttons->L_Pad[LEFT] = 0;
	}

	/* button right */
	if(temp_buttons & 0x00000080)
	{
		buttons->L_Pad[RIGHT] = 1;
	}
	else
	{
		buttons->L_Pad[RIGHT] = 0;
	}

	/* 2 not used bits */

	/* button left */
	if(temp_buttons & 0x00000400)
	{
		buttons->L = 1;
	}
	else
	{
		buttons->L = 0;
	}

	/* button right */
	if(temp_buttons & 0x00000800)
	{
		buttons->R = 1;
	}
	else
	{
		buttons->R = 0;
	}

	/* button C-Up */
	if(temp_buttons & 0x00001000)
	{
		buttons->C_Pad[UP] = 1;
	}
	else
	{
		buttons->C_Pad[UP] = 0;
	}

	/* button C-Down */
	if(temp_buttons & 0x00002000)
	{
		buttons->C_Pad[DOWN] = 1;
	}
	else
	{
		buttons->C_Pad[DOWN] = 0;
	}

	/* button C-Left */
	if(temp_buttons & 0x00004000)
	{
		buttons->C_Pad[LEFT] = 1;
	}
	else
	{
		buttons->C_Pad[LEFT] = 0;
	}

	/* button C-Right */
	if(temp_buttons & 0x00008000)
	{
		buttons->C_Pad[RIGHT] = 1;
	}
	else
	{
		buttons->C_Pad[RIGHT] = 0;
	}

	/* X-axis on joystick */
	buttons->Joystick[X] = (temp_buttons & 0x00FF0000) >> 16;

	/* Y-axis on joystick */
	buttons->Joystick[Y] = (temp_buttons & 0xFF000000) >> 24;

	return PASS;
}

/******************************************************************************/
/* N64_SendReset
 *
 * The function resets the N64 controler.									  */
/******************************************************************************/
void N64_SendReset(void)
{
	N64_BuildCode(RESET);
	TMR_N2HET1_InterruptEnable(N64_TIMER);
}

/******************************************************************************/
/* N64_GetButtonState
 *
 * The function gets the last button press from the controler.				  */
/******************************************************************************/
unsigned char N64_GetButtonState(TYPE_N64_BUT* buttons)
{
	unsigned char status = FAIL;
	N64_BuildCode(GET_BUTTONS);
	N64_CodeSectionBit = 0;
	N64_TimingInputBit = 0;
	ecapREG4->ECCTL2 |= REARM; 			// rearm
	ecapREG4->TSCTR = ECAP_PRELOAD; 	// reset the timer
	ecapREG4->ECCLR = 0xFFFF;			// clear all of the flags
	N64_ReceivedFinished(FALSE);
	ECAP_Interrupt(TRUE);
	ecapREG4->ECCTL2 |= TSCTRSTOP;		// start the compare module
	TMR_N2HET1_InterruptEnable(N64_TIMER);
	while(!N64_IsReceivedFinished());
	if(N64_TimingInputBit >= N64_INPUT_BUFFER_SIZE)
	{
		/* reception was successful */
		if(N64_DecodeTiming(buttons))
		{
			status = PASS;
		}
		else
		{
			/* reset the controller */
			N64_SendReset();
		}
	}
	else
	{
		/* reset the controller */
		N64_SendReset();
	}

	return status;
}

/******************************************************************************/
/* N64_GetUpdateFlag
 *
 * The function returns status of a new update from the controler.			  */
/******************************************************************************/
unsigned char N64_GetUpdateFlag(void)
{
	return N64_ActivityFlag;
}

/******************************************************************************/
/* N64_SetUpdateFlag
 *
 * The function sets the status of a new update from the controler.			  */
/******************************************************************************/
void N64_SetUpdateFlag(unsigned char state)
{
	 N64_ActivityFlag = state;
}

/******************************************************************************/
/* N64_IsReceivedFinished
 *
 * The function returns True if we are done sampling the N64 controller.	  */
/******************************************************************************/
unsigned char N64_IsReceivedFinished(void)
{
	return N64_ReceiveFlag;
}

/******************************************************************************/
/* N64_ReceivedFinished
 *
 * The function sets the done sampling flag.								  */
/******************************************************************************/
void N64_ReceivedFinished(unsigned char state)
{
	N64_ReceiveFlag = state;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
