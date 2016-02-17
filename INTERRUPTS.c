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

#include "INTERRUPTS.h"
#include "N64.h"
#include "SPI.h"
#include "TIMERS.h"
#include "USER.h"

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
			while(!SPI_IsTransmitBufferFull())
			{
				/* Fill the FIFO if we can */
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
					break;
				}
			}
		}
		else
		{
			SPI_TransmitInterrupt1(OFF);
		}

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
	unsigned long flags;
	flags = hetREG1->FLG;

	if(flags & 0x01L)
	{
		if(N64_Buffer_Code[N64_CodeSectionBit])
		{
			/* code section is 1 */
			gioPORTA->DSET = (1L << TEST_POINT_2);
		}
		else
		{
			/* code section is 0 */
			gioPORTA->DCLR = (1L << TEST_POINT_2);
		}
		N64_CodeSectionBit++;
		if(N64_CodeSectionBit >= N64_CODE_SECTIONS)
		{
			TMR_N2HET1_ON(FALSE);
			TMR_N2HET1_Interrupt(FALSE);
		}
	}
	hetREG1->FLG |= flags;
}

/******************************************************************************/
/* ISR_Timer2
 *
 * Interrupt service routine for the MISC timer.	        	              */
/******************************************************************************/
#pragma CODE_STATE(ISR_Timer2, 32)
#pragma INTERRUPT(ISR_Timer2, IRQ)
void ISR_Timer2(void)
{
	unsigned long flags = 0;
	flags = hetREG2->FLG;

	if(flags & 0x01L)
	{
		TMR_N2HET2_ON(FALSE);
		TMR_SetTimerFlag2();
	}

	hetREG2->FLG |= flags;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
