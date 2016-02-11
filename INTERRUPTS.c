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
#include "SPI.h"
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

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
