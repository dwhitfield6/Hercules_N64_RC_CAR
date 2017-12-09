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
/* Contains Miscellaneous Functions
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "HL_sys_common.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "MISC.h"
#include "TIMERS.h"
#include "USER.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/******************************************************************************/
/* Inline Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

/******************************************************************************/
/* MSC_DelayUS
 *
 * The function delays the given numebr of microseconds						  */
/******************************************************************************/
void MSC_DelayUS(unsigned long US)
{
    long prescalerL;

    if(US == 0)
    {
    	return;
    }
    prescalerL = TMR_CalculatePeriod2(US);

    while(prescalerL > 0x1FFFFFF)
    {
    	TMR_ClearTimerFlag2();	// reset timer flag
        TMR_SetTimerPeriod2(0x1FFFFFF, MISC_TIMER);
    	TMR_N2HET2_InterruptEnable(MISC_TIMER);
        while(!TMR_GetTimerFlag2());
        prescalerL -= 0x1FFFFFF;
    }

	TMR_ClearTimerFlag2();	// reset timer flag
    TMR_SetTimerPeriod2(prescalerL, MISC_TIMER);
    TMR_N2HET2_InterruptEnable(MISC_TIMER);
    while(!TMR_GetTimerFlag2());
}

/******************************************************************************/
/* MSC_DelayNOP
 *
 * The function waists the number of cycles passed into the function.		  */
/******************************************************************************/
void MSC_DelayNOP(unsigned long NOPs)
{
    unsigned long i;
    for(i=0; i<NOPs; i++)
    {
        NOP();
    }
}

/******************************************************************************/
/* MSC_Round
 *
 * This function rounds to the nearest whole number.						  */
/******************************************************************************/
double MSC_Round(double input)
{
    long temp = (long)(input + 0.5);

    return (double) temp;
}

/******************************************************************************/
/* MSC_EndianShort
 *
 * This function converts a 2 byte number from big endian to little endian or
 * vice versa.																  */
/******************************************************************************/
unsigned short MSC_EndianShort(unsigned short number)
{
    unsigned char temp1, temp2;

    temp1 = (unsigned char) (number & 0x00FF);
    temp2 = (unsigned char) (number & 0xFF00) >> 8;

    return (temp2 | (temp1 << 8));
}

/******************************************************************************/
/* MSC_EndianShortArray
 *
 * This function converts an array from big endian to little endian or
 * vice versa.																  */
/******************************************************************************/
unsigned short MSC_EndianShortArray(unsigned char* buffer)
{
    unsigned char temp1, temp2;

    temp1 = *buffer;
    buffer++;
    temp2 = *buffer;

    return (temp1 | ((unsigned int) temp2 << 8));
}

/******************************************************************************/
/* MSC_EndianLong
 *
 * This function converts a 4 byte number from big endian to little endian or
 * vice versa.																  */
/******************************************************************************/
unsigned long MSC_EndianLong(unsigned long number)
{
    unsigned char temp1, temp2, temp3, temp4;

    temp1 = (unsigned char) (number & 0x000000FF);
    temp2 = (unsigned char) (number & 0x0000FF00) >> 8;
    temp3 = (unsigned char) (number & 0x00FF0000) >> 16;
    temp4 = (unsigned char) (number & 0xFF000000) >> 24;

    return ((temp4 << 24) | (temp3 << 16) | (temp2 << 8) | temp1);
}

/******************************************************************************/
/* MSC_EndianLongArray
 *
 * This function converts an array from big endian to little endian or
 * vice versa.																  */
/******************************************************************************/
unsigned long MSC_EndianLongArray(unsigned char* buffer)
{
    unsigned char temp1, temp2, temp3, temp4;

    temp1 = *buffer;
    buffer++;
    temp2 = *buffer;
    buffer++;
    temp3 = *buffer;
    buffer++;
    temp4 = *buffer;

    return ((unsigned long)temp1 | ((unsigned long) temp2 << 8) | ((unsigned long) temp3 << 16) | ((unsigned long) temp4 << 24));
}

/******************************************************************************/
/* MSC_ReverseByte
 *
 * The function reads the value of 'This' and returns the reverse of the data.*/
/******************************************************************************/
unsigned char MSC_ReverseByte(unsigned char This)
{
    unsigned char temp=0;

    temp += (This & 0x01) << 7;
    temp += (This & 0x02) << 5;
    temp += (This & 0x04) << 3;
    temp += (This & 0x08) << 1;
    temp += (This & 0x10) >> 1;
    temp += (This & 0x20) >> 3;
    temp += (This & 0x40) >> 5;
    temp += (This & 0x80) >> 7;

    return temp;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
