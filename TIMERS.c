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
/* Contains functions for the RTI timers.
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

#include "MISC.h"
#include "TIMERS.h"
#include "USER.h"

/******************************************************************************/
/* Private Variable Declaration      	                                      */
/******************************************************************************/
volatile unsigned char TMR_Flag2 = FALSE;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
hetINSTRUCTION_t Timer1Program[] =
{
    /* Page 1029 TRM
     * CNT: Timebase
     *       - Instruction                  = 0
     *       - Next instruction             = 1
     *       - Conditional next instruction = na
     *       - Interrupt                    = na
     *       - Pin                          = na
     *       - Reg                          = T
     *											*/
    {
        /* Program */
    	/* reserved     | Requese number 	| break			| Next program address  |	instruction	| Angle count	| Register	| compare select	| reserved		| interrupt enable	*/
        (0x00L << 26) 	| (0x00L << 23)  	|(0L << 22)		| (0x00L << 13) 		| (b0110 << 9)	| (0L << 8)		| (3L << 6)	| (1L << 5)			| (0x00L << 1)	| (0x01L << 0),
        /* Control */
        0x01FFFFFFU,
        /* Data */
        0x00000000U,
        /* Reserved */
        0x00000000U
    }
};

hetINSTRUCTION_t Timer2Program[] =
{
    /* Page 1029 TRM
     * CNT: Timebase
     *       - Instruction                  = 0
     *       - Next instruction             = 1
     *       - Conditional next instruction = na
     *       - Interrupt                    = na
     *       - Pin                          = na
     *       - Reg                          = T
     *											*/
    {
        /* Program */
    	/* reserved     | Requese number 	| break			| Next program address  |	instruction	| Angle count	| Register	| compare select	| reserved		| interrupt enable	*/
        (0x00L << 26) 	| (0x00L << 23)  	|(0L << 22)		| (0x00L << 13) 		| (b0110 << 9)	| (0L << 8)		| (3L << 6)	| (1L << 5)			| (0x00L << 1)	| (0x01L << 0),
        /* Control */
        0x01FFFFFFU,
        /* Data */
        0x00000000U,
        /* Reserved */
        0x00000000U
    }
};


/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

/******************************************************************************/
/* InitTimers
 *
 * The function initializes the NxHET timer.								  */
/******************************************************************************/
void InitTimers(void)
{
	InitN2HET1();
	InitN2HET2();
}

/******************************************************************************/
/* InitN2HET1
 *
 * The function initializes the N2HET1 timer.								  */
/******************************************************************************/
void InitN2HET1(void)
{
	hetREG1->GCR &= ~HET_PIN_ENA;
	hetREG1->GCR |= CMS;
	hetREG1->PFR = 0;		// LRPFC / 1
	hetREG1->PFR |= 14; 	// HRPFC / 15
	(void)memcpy((void *)hetRAM1, (const void *)Timer1Program, sizeof(Timer1Program));
	hetREG1->PRY |= 0x00000001; // make the interrupt high priority
}

/******************************************************************************/
/* InitN2HET2
 *
 * The function initializes the N2HET2 timer.								  */
/******************************************************************************/
void InitN2HET2(void)
{
	hetREG2->GCR &= ~HET_PIN_ENA;
	hetREG2->GCR |= CMS;
	hetREG2->PFR = 0;		// LRPFC / 1
	hetREG2->PFR |= 14; 	// HRPFC / 15
	(void)memcpy((void *)hetRAM2, (const void *)Timer2Program, sizeof(Timer2Program));
	hetREG2->PRY |= 0x00000001; // make the interrupt high priority
}

/******************************************************************************/
/* TMR_TestTimer2
 *
 * The function tests timer 2.												  */
/******************************************************************************/
void TMR_TestTimer2(void)
{
	while(1)
	{
		gioPORTA->DSET = (1L << TEST_POINT_1);
		MSC_DelayUS(1000);
		gioPORTA->DCLR = (1L << TEST_POINT_1);
		MSC_DelayUS(1000);
	}
}

/******************************************************************************/
/* TMR_SetTimerPeriod2
 *
 * The function sets the timer 2 period										  */
/******************************************************************************/
void TMR_SetTimerPeriod2(unsigned long period)
{
	static unsigned long last = 0;
	if(period > 0x1FFFFFF)
	{
		period = 0x1FFFFFF;
	}
	TMR_N2HET2_ON(FALSE);
	if(last != period)
	{
		Timer2Program[0].Control = period - 1;
		(void)memcpy((void *)hetRAM2, (const void *)Timer2Program, sizeof(Timer2Program));
	}
	last = period;
}

/******************************************************************************/
/* TMR_SetTimerMicroSeconds1
 *
 * The function sets the timer 1 period	for the number of micro seconds.	  */
/******************************************************************************/
void TMR_SetTimerMicroSeconds1(double US)
{
    double prescalerD;
    long prescalerL;
	static unsigned long last = 0;

    prescalerD = MSC_Round(((double)VCLK2 * US) / (15.0 * 1000000.0));
    prescalerL = (long) prescalerD;

	if(prescalerL > 0x1FFFFFF)
	{
		prescalerL = 0x1FFFFFF;
	}
	TMR_N2HET1_ON(FALSE);
	if(last != prescalerL)
	{
		Timer1Program[0].Control = prescalerL - 1;
		(void)memcpy((void *)hetRAM1, (const void *)Timer1Program, sizeof(Timer1Program));
	}
	last = prescalerL;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
