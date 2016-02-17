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
#ifndef TIMERS_H
#define	TIMERS_H

#include "HL_sys_common.h"    		// TMS570LC43xx Include file
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "SYSTEM.h"

/******************************************************************************/
/* Registers                                                                  */
/******************************************************************************/
/*~~~~~~~~~~~~ HETHCR register ~~~~~~~~~~~~*/
#define HET_PIN_ENA	(1L<<24)
#define MP			(3L<<21)
#define PPF			(1L<<18)
#define IS			(1L<<17)
#define CMS			(1L<<16)
#define TO			(1L<<0)

/*~~~~~~~~~~~~ HETPFR register ~~~~~~~~~~~~*/
#define LRPFC	(0x7L<<8)
#define HRPFC	(0x3FL<<0)

/*~~~~~~~~~~~~ HETADDR register ~~~~~~~~~~~~*/
#define HETADDR	(0x1FFL<<0)

/*~~~~~~~~~~~~ HETOFF1 register ~~~~~~~~~~~~*/
#define OFFSET1	(0x3FL<<0)

/*~~~~~~~~~~~~ HETOFF2 register ~~~~~~~~~~~~*/
#define OFFSET2	(0x3FL<<0)

/*~~~~~~~~~~~~ HETINTENAS register ~~~~~~~~~~~~*/
#define HETINTENAS	(0xFFFFFFFFL<<0)

/*~~~~~~~~~~~~ HETINTENAC register ~~~~~~~~~~~~*/
#define HETINTENAC	(0xFFFFFFFFL<<0)

/*~~~~~~~~~~~~ HETEXC1 register ~~~~~~~~~~~~*/
#define APCNT_OVRFL_ENA	(1L<<24)
#define APCNT_UNRFL_ENA	(1L<<16)
#define PRGM_OVRFL_ENA	(1L<<8)
#define APCNT_OVRFL_PRY	(1L<<2)
#define APCNT UNRFL_PRY	(1L<<1)
#define PRGM_OVRFL_PRY	(1L<<0)

/*~~~~~~~~~~~~ HETEXC2 register ~~~~~~~~~~~~*/
#define DEBUG_STATUS_FLAG 	(1L<<8)
#define APCNT_OVRFL_FLAG 	(1L<<2)
#define APCNT_UNDFL_FLAG 	(1L<<1)
#define PRGM_OVERFL_FLAG 	(1L<<0)

/*~~~~~~~~~~~~ HETPRY register ~~~~~~~~~~~~*/
#define HETPRY	(0xFFFFFFFFL<<0)

/*~~~~~~~~~~~~ HETFLG register ~~~~~~~~~~~~*/
#define HETFLG	(0xFFFFFFFFL<<0)

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern volatile unsigned char TMR_Flag2;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
inline void TMR_N2HET1_ON(unsigned char state);
inline void TMR_N2HET2_ON(unsigned char state);
inline void TMR_N2HET1_Interrupt(unsigned char state);
inline void TMR_N2HET2_Interrupt(unsigned char state);
inline void TMR_ClearTimerFlag2(void);
inline void TMR_SetTimerFlag2(void);
inline unsigned char TMR_GetTimerFlag2(void);
void InitTimers(void);
void InitN2HET1(void);
void InitN2HET2(void);
void TMR_TestTimer2(void);
void TMR_SetTimerPeriod2(unsigned long period);
void TMR_SetTimerMicroSeconds1(double US);

/******************************************************************************/
/* Inline Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* TMR_N2HET1_ON
 *
 * The function controls the timer.											  */
/******************************************************************************/
inline void TMR_N2HET1_ON(unsigned char state)
{
	if(state)
	{
		hetREG1->GCR |= TO;
	}
	else
	{
		hetREG1->GCR &= ~TO;
	}
}

/******************************************************************************/
/* TMR_N2HET2_ON
 *
 * The function controls the timer.											  */
/******************************************************************************/
inline void TMR_N2HET2_ON(unsigned char state)
{
	if(state)
	{
		hetREG2->GCR |= TO;
	}
	else
	{
		hetREG2->GCR &= ~TO;
	}
}

/******************************************************************************/
/* TMR_N2HET1_Interrupt
 *
 * The function controls the timer interrupt.								  */
/******************************************************************************/
inline void TMR_N2HET1_Interrupt(unsigned char state)
{
	if(state)
	{
		hetREG1->INTENAS |= 0x00000001;	// set the interrupt
	}
	else
	{
		hetREG1->INTENAC |= 0x00000001;	// clear the interrupt
	}
}

/******************************************************************************/
/* TMR_N2HET2_Interrupt
 *
 * The function controls the timer interrupt.								  */
/******************************************************************************/
inline void TMR_N2HET2_Interrupt(unsigned char state)
{
	if(state)
	{
		hetREG2->INTENAS |= 0x00000001;	// set the interrupt
	}
	else
	{
		hetREG2->INTENAC |= 0x00000001;	// clear the interrupt
	}
}

/******************************************************************************/
/* TMR_ClearTimerFlag2
 *
 * The function clears the tiemr flag.										  */
/******************************************************************************/
inline void TMR_ClearTimerFlag2(void)
{
	TMR_Flag2 = 0;
}

/******************************************************************************/
/* TMR_SetTimerFlag2
 *
 * The function set the tiemr flag.											  */
/******************************************************************************/
inline void TMR_SetTimerFlag2(void)
{
	TMR_Flag2 = 1;
}

/******************************************************************************/
/* TMR_GetTimerFlag2
 *
 * The function clears the tiemr flag.										  */
/******************************************************************************/
inline unsigned char TMR_GetTimerFlag2(void)
{
	return TMR_Flag2;
}

#endif	/* TIMERS_H */
