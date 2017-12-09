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
volatile unsigned char g_TMR_Flag2 = FALSE;

/******************************************************************************/
/* Private Variable Declaration      	                                      */
/******************************************************************************/

/******************************************************************************/
/* N2HET1 instruction (used for N64 timing)                                   */
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

/******************************************************************************/
/* N2HET1 instruction (used for main loop timer, DAC timer, and MISC timer)   */
/******************************************************************************/
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
        (0x00L << 26) 	| (0x00L << 23)  	|(0L << 22)		| (0x01L << 13) 		| (b0110 << 9)	| (0L << 8)		| (0L << 6)	| (1L << 5)			| (0x00L << 1)	| (0x01L << 0),
        /* Control */
        0x01FFFFFFU,
        /* Data */
        0x00000000U,
        /* Reserved */
        0x00000000U
    },

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
        (0x00L << 26) 	| (0x00L << 23)  	|(0L << 22)		| (0x02L << 13) 		| (b0110 << 9)	| (0L << 8)		| (1L << 6)	| (1L << 5)			| (0x00L << 1)	| (0x01L << 0),
        /* Control */
        0x01FFFFFFU,
        /* Data */
        0x00000000U,
        /* Reserved */
        0x00000000U
    },

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
        (0x00L << 26) 	| (0x00L << 23)  	|(0L << 22)		| (0x00L << 13) 		| (b0110 << 9)	| (0L << 8)		| (2L << 6)	| (1L << 5)			| (0x00L << 1)	| (0x01L << 0),
        /* Control */
        0x01FFFFFFU,
        /* Data */
        0x00000000U,
        /* Reserved */
        0x00000000U
    }
};

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
volatile unsigned char g_MAIN_TimerFlag = FALSE;

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
	unsigned long period = 0;
	InitN2HET1();
	InitN2HET2();
	period = TMR_CalculatePeriod2(MAIN_LOOP_US);
	TMR_SetTimerPeriod2(period, MAIN_TIMER);
	TMR_N2HET2_InterruptEnable(MAIN_TIMER);
	TMR_N2HET1_ON(TRUE);
	TMR_N2HET2_ON(TRUE);
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
	memcpy((void *)hetRAM1, (const void *)Timer1Program, sizeof(Timer1Program));
	hetREG1->PRY = N64_TIMER; // make the interrupt high priority
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
	memcpy((void *)hetRAM2, (const void *)Timer2Program, sizeof(Timer2Program));
	hetREG2->PRY = MISC_TIMER | DAC_TIMER | MAIN_TIMER; // make the interrupt high priority
}

/******************************************************************************/
/* TMR_CalculatePeriod2
 *
 * The function takes in microseconds and returns the period count for timer
 *  2.																		  */
/******************************************************************************/
unsigned long TMR_CalculatePeriod2(double US)
{
    double prescalerD;
    long prescalerL;

    if(US == 0)
    {
    	return 0;
    }

    prescalerD = MSC_Round(((double)VCLK2 * (double) US) / (15.0 * 1000000.0));
    prescalerL = (long) prescalerD;
    return prescalerL;
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
void TMR_SetTimerPeriod2(unsigned long period, unsigned long timer)
{
	signed char index = -1;
	static unsigned long last[3] = {0,0,0};
	if(period > 0x1FFFFFF)
	{
		period = 0x1FFFFFF;
	}
	while(timer)
	{
		timer >>= 1;
		index++;
	}
	if(last[index] != period)
	{
		TMR_N2HET2_ON(FALSE);
		(void)memcpy((void *)Timer2Program, (const void *)hetRAM2, sizeof(Timer2Program));
		Timer2Program[index].Control = period - 1;
		(void)memcpy((void *)hetRAM2, (const void *)Timer2Program, sizeof(Timer2Program));
		TMR_N2HET2_ON(TRUE);
	}
	last[index] = period;
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
	if(last != prescalerL)
	{
		TMR_N2HET1_ON(FALSE);
		Timer1Program[0].Control = prescalerL - 1;
		(void)memcpy((void *)hetRAM1, (const void *)Timer1Program, sizeof(Timer1Program));
		TMR_N2HET1_ON(TRUE);
	}
	last = prescalerL;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
