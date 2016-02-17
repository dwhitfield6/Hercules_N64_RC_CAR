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

#include "N64.h"
#include "TIMERS.h"
#include "USER.h"

/******************************************************************************/
/* Private Variable Declaration      	                                      */
/******************************************************************************/
static volatile unsigned char N64_ActivityFlag = FALSE;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
TYPE_N64_BUT N64_New;
TYPE_N64_BUT N64_Old;
unsigned char N64_Buffer_Code[N64_CODE_SECTIONS];
unsigned char N64_CodeSectionBit = 0;
unsigned long N64_ControllerCount = 0;

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
	TMR_SetTimerMicroSeconds1(1.0);
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
		if(action & (1L << (8-i)))
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
/* N64_GetButtonState
 *
 * The function gets the last button press from the controler.				  */
/******************************************************************************/
unsigned char N64_GetButtonState(TYPE_N64_BUT* buttons)
{
	N64_BuildCode(READ);
	N64_CodeSectionBit = 0;
	TMR_N2HET1_Interrupt(TRUE);
	TMR_N2HET1_ON(TRUE);
	return PASS;
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

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
