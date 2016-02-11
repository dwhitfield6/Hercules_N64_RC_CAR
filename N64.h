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
	unsigned char C[4];			// 4 yellow buttons
	unsigned char Start;		// red center
	unsigned char L_Pad[4];		// plus sign on right of controler
	unsigned char Z;			// back of controler
	unsigned short Joystick[2];	// controler joystick x,y
}TYPE_N64_BUT;

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
/* Defines                                                                    */
/******************************************************************************/
#define X 0
#define Y 1

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern TYPE_N64_BUT N64_New;
extern TYPE_N64_BUT N64_Old;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitN64(void);
unsigned char N64_GetButtonState(TYPE_N64_BUT* buttons);
unsigned char N64_GetUpdateFlag(void);
void N64_SetUpdateFlag(unsigned char state);

#endif	/* N64_H */
