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
/* Files to Include                                                           */
/******************************************************************************/
#ifndef N64_H
#define	N64_H

#include "HL_sys_common.h"    		// TMS570LC43xx Include file
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/
typedef struct t_n64_buttons
{
    unsigned char A;			// blue
	unsigned char B;			// green
	unsigned char L;			// left top
	unsigned char R;			// right top
	unsigned char C_Pad[4];			// 4 yellow buttons
	unsigned char Start;		// red center
	unsigned char L_Pad[4];		// plus sign on right of controler
	unsigned char Z;			// back of controler
	unsigned short Joystick[2];	// controler joystick x,y
}TYPE_N64_BUT;

typedef enum e_n64
{
    RESET 			= 0xFF,
	GET_STATUS 		= 0x00,
	GET_BUTTONS		= 0x01,
	READ_MEMPACK	= 0x02,
	WRITE_MEMPACK	= 0x03,
	READ_EEPROM		= 0x04,
	WRITE_EEPROM	= 0x05,
}ENUM_N64_REG;


/******************************************************************************/
/* Y_MIDPOINT_HIGH
 *
 * This is the threshold to move the throttle forward until we register it
 *  as go forward.															  */
/******************************************************************************/
#define Y_MIDPOINT_HIGH 1000

/******************************************************************************/
/* Y_MIDPOINT_LOW
 *
 * This is the threshold to move the throttle backward until we register it
 *  as go backward.															  */
/******************************************************************************/
#define Y_MIDPOINT_LOW 900

/******************************************************************************/
/* N64_CODE_SECTIONS
 *
 * This is the nuber of 1uS code sections. There are 4 for each bit and 9
 *  bits (code + stop bit).													  */
/******************************************************************************/
#define N64_CODE_SECTIONS 36

/******************************************************************************/
/* N64_INPUT_BUFFER_SIZE
 *
 * This is the nuber of timing edgeds that we can save for a detect.		  */
/******************************************************************************/
#define N64_INPUT_BUFFER_SIZE 80

/******************************************************************************/
/* N64_SAMPLERATE
 *
 * This is the nuber of loops around the main line that we wait to sample the
 *  N64 controller.															  */
/******************************************************************************/
#define N64_SAMPLERATE 3

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define X 0
#define Y 1

#define UP 		0
#define DOWN 	1
#define LEFT 	2
#define RIGHT 	3

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern TYPE_N64_BUT N64_New;
extern TYPE_N64_BUT N64_Old;
extern unsigned char N64_Buffer_Code[N64_CODE_SECTIONS];
extern volatile unsigned char N64_CodeSectionBit;
extern volatile unsigned long N64_ControllerCount;
extern volatile unsigned long N64_TimingInputBuffer[N64_INPUT_BUFFER_SIZE + 10];
extern volatile unsigned long N64_TimingInputBit;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitN64(void);
void N64_BuildCode(ENUM_N64_REG action);
unsigned char N64_DecodeTiming(TYPE_N64_BUT* buttons);
void N64_SendReset(void);
unsigned char N64_GetButtonState(TYPE_N64_BUT* buttons);
unsigned char N64_GetUpdateFlag(void);
void N64_SetUpdateFlag(unsigned char state);
unsigned char N64_IsReceivedFinished(void);
void N64_ReceivedFinished(unsigned char state);

#endif	/* N64_H */
