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
/* Interrupt Vector Options
 *
 * Go to page 119 in data sheet for vector information.
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

#include "DAC.h"
#include "ECAP.h"
#include "INTERRUPTS.h"
#include "MISC.h"
#include "N64.h"
#include "SPI.h"
#include "TEST.h"
#include "TIMERS.h"
#include "USER.h"
#include "WAV.h"

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/******************************************************************************/
/* ISR_SPI1_INT0
 *
 * Interrupt service routine for SPI1 INT0 interrupt.                         */
/******************************************************************************/
#pragma CODE_STATE(ISR_SPI1_INT0, 32)
#pragma INTERRUPT(ISR_SPI1_INT0, IRQ)
void ISR_SPI1_INT0(void)
{
	unsigned long vector = spiREG1->INTVECT0;

	if(((vector & INTVECT) >> 1) == 0x14L)
	{
		/* The pending interrupt is a "Transmit Buffer Empty" interrupt */
		if(SPI_TX_Buffer_Remove_place != SPI_TX_Buffer_Add_place)
		{
			SPI_SendByte(SPI_TX_Buffer[SPI_TX_Buffer_Remove_place].Data,
					SPI_TX_Buffer[SPI_TX_Buffer_Remove_place].Channel,
					SPI_TX_Buffer[SPI_TX_Buffer_Remove_place].HoldCS);
			SPI_TX_Buffer_Remove_place++;
			if(SPI_TX_Buffer_Remove_place >= SPI_TX_BUFFER_SIZE)
			{
				SPI_TX_Buffer_Remove_place = 0;
			}
		}
		else
		{
			SPI_TransmitInterrupt1(OFF);
		}
	}
}

/******************************************************************************/
/* ISR_ECAP_N64
 *
 * Interrupt service routine for SPI1 INT0 interrupt.                         */
/******************************************************************************/
#pragma CODE_STATE(ISR_ECAP_N64, 32)
#pragma INTERRUPT(ISR_ECAP_N64, IRQ)
void ISR_ECAP_N64(void)
{
	volatile unsigned long flags;
	flags = ecapREG4->ECFLG;
	ecapREG4->ECCLR = INT;

	if((flags & CEVT2) && (ecapREG4->ECEINT & CEVT2))
	{
		ecapREG4->ECCLR = CEVT4 | CEVT3 | CEVT2 | CEVT1;
		ecapREG4->ECCTL2 |= REARM; 			// rearm
		N64_TimingInputBuffer[N64_TimingInputBit++] = ecapREG4->CAP1;
		N64_TimingInputBuffer[N64_TimingInputBit++] = ecapREG4->CAP2;
		//N64_TimingInputBuffer[N64_TimingInputBit++] = ecapREG4->CAP3;
		//N64_TimingInputBuffer[N64_TimingInputBit++] = ecapREG4->CAP4;
		if(N64_TimingInputBit >= N64_INPUT_BUFFER_SIZE)
		{
			ecapREG4->ECCTL2 &= ~TSCTRSTOP;		// stop the compare module
			ecapREG4->ECCTL2 |= REARM; 			// rearm
			N64_ReceivedFinished(TRUE);
			ECAP_Interrupt(FALSE);
			ecapREG4->TSCTR = ECAP_PRELOAD; 	// reset the timer
		}
	}
	if((flags & CTROVF) && (ecapREG4->ECEINT & CTROVF))
	{
		ecapREG4->ECCTL2 &= ~TSCTRSTOP;		// stop the compare module
		ecapREG4->ECCTL2 |= REARM; 			// rearm
		N64_ReceivedFinished(TRUE);
		ECAP_Interrupt(FALSE);
		ecapREG4->TSCTR = ECAP_PRELOAD; 	// reset the timer
		ecapREG4->ECCLR = CTROVF;
	}
}

/******************************************************************************/
/* ISR_Timer1
 *
 * Interrupt service routine for the N64 timer.	      	                      */
/******************************************************************************/
#pragma CODE_STATE(ISR_Timer1, 32)
#pragma INTERRUPT(ISR_Timer1, IRQ)
void ISR_Timer1(void)
{
	volatile unsigned long flags;
	flags = hetREG1->FLG;

	if((flags & N64_TIMER) && (hetREG1->INTENAS & N64_TIMER))
	{
		if(N64_CodeSectionBit < N64_CODE_SECTIONS)
		{
			if(N64_Buffer_Code[N64_CodeSectionBit])
			{
				/* code section is 1 */
				gioPORTB->DSET = (1L << N64_0);
			}
			else
			{
				/* code section is 0 */
				gioPORTB->DCLR = (1L << N64_0);
			}
			N64_CodeSectionBit++;
		}
	}

	if(N64_CodeSectionBit >= N64_CODE_SECTIONS)
	{
		TMR_N2HET1_InterruptDisable(N64_TIMER);
	}
	hetREG1->FLG = 0xFFFFFFFF;
}

/******************************************************************************/
/* ISR_Timer2
 *
 * Interrupt service routine for the MISC and DAC timer.       	              */
/******************************************************************************/
#pragma CODE_STATE(ISR_Timer2, 32)
#pragma INTERRUPT(ISR_Timer2, IRQ)
void ISR_Timer2(void)
{
	volatile unsigned long flags = 0;
	unsigned short temp_ushort = 0;
	short temp_short;
	long temp_long;
	static unsigned short last_temp_ushort = 0;
	flags = hetREG2->FLG;

	if((flags & MISC_TIMER) && (hetREG2->INTENAS & MISC_TIMER))
	{
		/* interrupt for MSC timer */
		TMR_N2HET2_InterruptDisable(MISC_TIMER);
		TMR_SetTimerFlag2();
		hetREG2->FLG = MISC_TIMER;
	}
	if((flags & DAC_TIMER) && (hetREG2->INTENAS & DAC_TIMER))
	{
        if(CurrentWAVFile.BitsPerSample == 8)
        {
    		/* 8 bit samples */
        	temp_ushort = *CurrentWAVFile.BufferPointer; // unsigned char
        	temp_ushort <<= 4;
            if(temp_ushort != last_temp_ushort)
            {
				DAC_SendData(DAC_A, temp_ushort);
				temp_ushort = DAC_FULL_SCALE_POSITIVE - temp_ushort;
				DAC_SendData(DAC_B, temp_ushort);
            }
            last_temp_ushort = temp_ushort;
            CurrentWAVFile.BufferPointer += CurrentWAVFile.SampleRepeat;
            CurrentWAVFile.CurrentSample++;
        }
        else
        {
        	/* 16 bit samples */
            temp_short = (short)MSC_EndianShortArray(CurrentWAVFile.BufferPointer) / 2; // signed short
            temp_long = temp_short + 32768;
            temp_ushort = temp_long;
            temp_ushort >>= 4;
            if(temp_ushort != last_temp_ushort)
            {
				DAC_SendData(DAC_A, temp_ushort);
				temp_ushort = (DAC_FULL_SCALE_POSITIVE + 1) - temp_ushort;
				DAC_SendData(DAC_B, temp_ushort);
            }
            last_temp_ushort = temp_ushort;
            CurrentWAVFile.BufferPointer += CurrentWAVFile.SampleRepeat;
            CurrentWAVFile.CurrentSample++;
        }

        if(CurrentWAVFile.CurrentSample > CurrentWAVFile.NumSamples)
        {
        	/* file is done playing */
        	TMR_N2HET2_InterruptDisable(DAC_TIMER);
        	DAC_SendData(DAC_A, DAC_MIDPOINT);
        	DAC_SendData(DAC_B, DAC_MIDPOINT);
        	WAV_Finished(TRUE);
        	last_temp_ushort = 0;
        }
        hetREG2->FLG = DAC_TIMER;
	}
	if((flags & MAIN_TIMER) && (hetREG2->INTENAS & MAIN_TIMER))
	{
		MAIN_TimerFlag = TRUE;
		hetREG2->FLG = MAIN_TIMER;
	}
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
