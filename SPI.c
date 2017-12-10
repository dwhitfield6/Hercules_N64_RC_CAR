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
/* Contains functions for the SPI bus.
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
#include "SPI.h"
#include "SYSTEM.h"
#include "USER.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
volatile TYPE_SPI_BUFFER g_SPI_TX_Buffer[SPI_TX_BUFFER_SIZE];
volatile long g_SPI_TX_Buffer_Add_place = 0;
volatile long g_SPI_TX_Buffer_Remove_place = 0;

/******************************************************************************/
/* Inline Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

/******************************************************************************/
/* InitSPI
 *
 * The function initializes the SPI bus.									  */
/******************************************************************************/
void InitSPI(void)
{
	InitSPI1();
}

/******************************************************************************/
/* InitSPI1
 *
 * The function initializes the SPI module 1 bus.							  */
/******************************************************************************/
void InitSPI1(void)
{
	spiREG1->GCR0 &= ~nRESET; 			// SPI is in the reset state.
	spiREG1->GCR0 |= nRESET; 			// SPI is out of the reset state

	SPI_Parameters1(master, 0, 3000L);	// set up SPI parameters
	SPI_SetPins(TRUE);
	spiREG1->DELAY = 0;
	spiREG1->DELAY |= (0x0FUL << 24) + (0x0FUL << 16); 	// set chip select delays
	spiREG1->GCR1 |= SPIEN;				// Activates SPI
}

/******************************************************************************/
/* SPI_Parameters1
 *
 * The function configures the SPI module.									  */
/******************************************************************************/
void SPI_Parameters1(ENUM_MASTER_SLAVE master_slave, unsigned char mode, unsigned long speedKhz)
{
    double speed = (double) speedKhz;
    speed *= 1000.0;
    unsigned long prescale;

    if(master_slave == master)
    {
    	spiREG1->GCR1 |= MASTER;	// SPISOMI[7:0] pins are inputs, SPISIMO[7:0] pins are outputs
    }
    else
    {
    	spiREG1->GCR1 &= ~MASTER;	// SPISIMO[7:0] pins are inputs, SPISOMI[7:0] pins are outputs
    }

    spiREG1->DEF = 0xFFL; 	// SPISCSx is set to 1 when no transfer is active

    /* set word length to 8 bits */
    spiREG1->FMT0 &= ~CHARLEN;
    spiREG1->FMT0 |= 8;

    switch (mode)
    {
		case 0:
			spiREG1->FMT0 &= ~POLARITY;
			spiREG1->FMT0 |= PHASE;
			break;
		case 1:
			spiREG1->FMT0 &= ~POLARITY;
			spiREG1->FMT0 &= ~PHASE;
			break;
		case 2:
			spiREG1->FMT0 |= POLARITY;
			spiREG1->FMT0 |= PHASE;
			break;
		default:
			spiREG1->FMT0 |= POLARITY;
			spiREG1->FMT0 &= ~PHASE;
			break;
    }
    spiREG1->GCR1 |= CLKMOD;		// Clock is internally-generated.

    /* set the prescale for the SPI clock frequency */
    prescale = (unsigned long) MSC_Round(((double)VCLK1/speed) - 1.0);
    if(prescale > 255)
    {
    	prescale = 255;
    }
    spiREG1->FMT0 &= ~PRESCALE;
    spiREG1->FMT0 |= (prescale << 8);
}

/******************************************************************************/
/* SPI_TransmitInterrupt1
 *
 * The function controls the SPI transmit interrupt.						  */
/******************************************************************************/
void SPI_TransmitInterrupt1(unsigned char state)
{
	if(state)
	{
		spiREG1->INT0 |= TXINTENA;
	}
	else
	{
		spiREG1->INT0 &= ~TXINTENA;
	}
}

/******************************************************************************/
/* SPI_ReceiveInterrupt1
 *
 * The function controls the SPI receive interrupt.							  */
/******************************************************************************/
void SPI_ReceiveInterrupt1(unsigned char state)
{
	if(state)
	{
		spiREG1->INT0 |= RXINTENA;
	}
	else
	{
		spiREG1->INT0 &= ~RXINTENA;
	}
}

/******************************************************************************/
/* SPI_IsTransmitBufferFull
 *
 * The function returns the status of the trnasmit buffer.					  */
/******************************************************************************/
unsigned char SPI_IsTransmitBufferFull(void)
{
	if(spiREG1->BUF & TXFULL)
	{
		return TRUE; 	// The transmit buffer is full; SPIDAT0/SPIDAT1 is not ready to accept new data.
	}
	return FALSE;	// The transmit buffer is empty; SPIDAT0/SPIDAT1 is ready to accept a new data
}

/******************************************************************************/
/* SPI_SetPins
 *
 * The function sets the pins to SPI mode or as GPIO.						  */
/******************************************************************************/
void SPI_SetPins(unsigned char state)
{
	spiREG1->PC0 = 0; 			// set pins a GPIO
	spiREG1->PC1 = 0xFFFFFFFF; 	// set GPIOs to output
	if(state)
	{
		spiREG1->PC0 |= (SIMOFUN0 + CLKFUN + SCSFUN2 + SCSFUN1 + SCSFUN0); // set MOSI, SCK, and CS pins to SPI mode
	}
}

#ifdef USE_RAMFUNC
#pragma CODE_SECTION(SPI_SendByte, "TI.ramfuncs")
#endif
/******************************************************************************/
/* SPI_SendByte
 *
 * The function sends a byte of data over the SPI port.						  */
/******************************************************************************/
void SPI_SendByte(unsigned char data, unsigned char chip_select, unsigned char chip_select_hold)
{
	unsigned long temp = 0xFF;
	temp &= ~(1L << chip_select);
	spiREG1->DAT1 = data | temp << 16L | (((unsigned long)chip_select_hold & 0x1) << 28L);
}

#ifdef USE_RAMFUNC
#pragma CODE_SECTION(SPI_AddToTXBuffer, "TI.ramfuncs")
#endif
/******************************************************************************/
/* SPI_AddToTXBuffer
 *
 * The function adds a byte of data to the SPI transmit buffer.				  */
/******************************************************************************/
void SPI_AddToTXBuffer(unsigned char data, unsigned char chip_select, unsigned char chip_select_hold)
{

	if(g_SPI_TX_Buffer_Remove_place > g_SPI_TX_Buffer_Add_place)
    {
        if((g_SPI_TX_Buffer_Remove_place - g_SPI_TX_Buffer_Add_place) == 1)
        {
            /* transmit buffer is full */
        	while((g_SPI_TX_Buffer_Remove_place - g_SPI_TX_Buffer_Add_place) == 1); // the transmit is happening so wait for the buffer to make space
        }
    }

	if(g_SPI_TX_Buffer_Add_place > g_SPI_TX_Buffer_Remove_place)
    {
        if((g_SPI_TX_Buffer_Add_place - g_SPI_TX_Buffer_Remove_place) == (SPI_TX_BUFFER_SIZE - 1))
        {
            /* transmit buffer is full */
        	while((g_SPI_TX_Buffer_Add_place - g_SPI_TX_Buffer_Remove_place) == (SPI_TX_BUFFER_SIZE - 1)); // the transmit is happening so wait for the buffer to make space
        }
    }

	g_SPI_TX_Buffer[g_SPI_TX_Buffer_Add_place].Data = data;
	g_SPI_TX_Buffer[g_SPI_TX_Buffer_Add_place].Channel = chip_select;
	g_SPI_TX_Buffer[g_SPI_TX_Buffer_Add_place].HoldCS = chip_select_hold;
	g_SPI_TX_Buffer_Add_place++;

    if(g_SPI_TX_Buffer_Add_place >= SPI_TX_BUFFER_SIZE)
    {
    	g_SPI_TX_Buffer_Add_place = 0;
    }
    SPI_TransmitInterrupt1(ON);
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
