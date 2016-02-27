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
#ifndef SPI_H
#define	SPI_H

#include "HL_sys_common.h"    		// TMS570LC43xx Include file
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/
typedef enum e_master_slave
{
    master,
	slave,
}ENUM_MASTER_SLAVE;

typedef struct t_spi_buffer
{
    unsigned char Data;		// data to be transmitted
	unsigned char Channel;	// chip select channel
	unsigned char HoldCS;	// hold chip select active
}TYPE_SPI_BUFFER;

/******************************************************************************/
/* Registers                                                                  */
/******************************************************************************/
/*~~~~~~~~~~~~ SPIGCRO register ~~~~~~~~~~~~*/
#define nRESET 			(1L<<0)

/*~~~~~~~~~~~~ SPIGCR1 register ~~~~~~~~~~~~*/
#define SPIEN 			(1L<<24)
#define LOOPBACK 		(1L<<16)
#define POWERDOWN 		(1L<<8)
#define CLKMOD 			(1L<<1)
#define MASTER 			(1L<<0)

/*~~~~~~~~~~~~ SPIINT0 register ~~~~~~~~~~~~*/
#define ENABLEHIGHZ		(1L<<24)
#define DMAREQEN		(1L<<16)
#define TXINTENA		(1L<<9)
#define RXINTENA		(1L<<8)
#define RXOVRNINTENA	(1L<<6)
#define BITERRENA		(1L<<4)
#define DESYNCENA		(1L<<3)
#define PARERRENA		(1L<<2)
#define TIMEOUTENA		(1L<<1)
#define DLENERRENA		(1L<<0)

/*~~~~~~~~~~~~ SPILVL register ~~~~~~~~~~~~*/
#define TXINTLVL		(1L<<9)
#define RXINTLVL		(1L<<8)
#define RXOVRNINTLVL	(1L<<6)
#define BITERRLVL		(1L<<4)
#define DESYNCLVL		(1L<<3)
#define PARERRLVL		(1L<<2)
#define TIMEOUTLVL		(1L<<1)
#define DLENERRLVL		(1L<<0)

/*~~~~~~~~~~~~ SPIFLG register ~~~~~~~~~~~~*/
#define BUFINITACTIVE	(1L<<24)
#define TXINTFLG		(1L<<9)
#define RXINTFLG		(1L<<8)
#define RXOVRNINTFLG	(1L<<6)
#define BITERRFLG		(1L<<4)
#define DESYNCFLG		(1L<<3)
#define PARERRFLG		(1L<<2)
#define TIMEOUTFLG		(1L<<1)
#define DLENERRFLG		(1L<<0)

/*~~~~~~~~~~~~ SPIPC0 register ~~~~~~~~~~~~*/
#define SOMIFUN7	(1L<<31)
#define SOMIFUN6	(1L<<30)
#define SOMIFUN5	(1L<<29)
#define SOMIFUN4	(1L<<28)
#define SOMIFUN3	(1L<<27)
#define SOMIFUN2	(1L<<26)
#define SOMIFUN1	(1L<<25)
#define SOMIFUN0	(1L<<11)
#define SIMOFUN7	(1L<<23)
#define SIMOFUN6	(1L<<22)
#define SIMOFUN5	(1L<<21)
#define SIMOFUN4	(1L<<20)
#define SIMOFUN3	(1L<<19)
#define SIMOFUN2	(1L<<18)
#define SIMOFUN1	(1L<<17)
#define SIMOFUN0	(1L<<10)
#define CLKFUN		(1L<<9)
#define ENAFUN		(1L<<8)
#define SCSFUN7		(1L<<7)
#define SCSFUN6		(1L<<6)
#define SCSFUN5		(1L<<5)
#define SCSFUN4		(1L<<4)
#define SCSFUN3		(1L<<3)
#define SCSFUN2		(1L<<2)
#define SCSFUN1		(1L<<1)
#define SCSFUN0		(1L<<0)

/*~~~~~~~~~~~~ SPIPC1 register ~~~~~~~~~~~~*/
#define SOMIDIR7	(1L<<31)
#define SOMIDIR6	(1L<<30)
#define SOMIDIR5	(1L<<29)
#define SOMIDIR4	(1L<<28)
#define SOMIDIR3	(1L<<27)
#define SOMIDIR2	(1L<<26)
#define SOMIDIR1	(1L<<25)
#define SOMIDIR0	(1L<<11)
#define SIMODIR7	(1L<<23)
#define SIMODIR6	(1L<<22)
#define SIMODIR5	(1L<<21)
#define SIMODIR4	(1L<<20)
#define SIMODIR3	(1L<<19)
#define SIMODIR2	(1L<<18)
#define SIMODIR1	(1L<<17)
#define SIMODIR0	(1L<<10)
#define CLKDIR		(1L<<9)
#define ENADIR		(1L<<8)
#define SCSDIR7		(1L<<7)
#define SCSDIR6		(1L<<6)
#define SCSDIR5		(1L<<5)
#define SCSDIR4		(1L<<4)
#define SCSDIR3		(1L<<3)
#define SCSDIR2		(1L<<2)
#define SCSDIR1		(1L<<1)
#define SCSDIR0		(1L<<0)

/*~~~~~~~~~~~~ SPIPC2 register ~~~~~~~~~~~~*/
#define SOMIDIN7	(1L<<31)
#define SOMIDIN6	(1L<<30)
#define SOMIDIN5	(1L<<29)
#define SOMIDIN4	(1L<<28)
#define SOMIDIN3	(1L<<27)
#define SOMIDIN2	(1L<<26)
#define SOMIDIN1	(1L<<25)
#define SOMIDIN0	(1L<<11)
#define SIMODIN7	(1L<<23)
#define SIMODIN6	(1L<<22)
#define SIMODIN5	(1L<<21)
#define SIMODIN4	(1L<<20)
#define SIMODIN3	(1L<<19)
#define SIMODIN2	(1L<<18)
#define SIMODIN1	(1L<<17)
#define SIMODIN0	(1L<<10)
#define CLKDIN		(1L<<9)
#define ENADIN		(1L<<8)
#define SCSDIN7		(1L<<7)
#define SCSDIN6		(1L<<6)
#define SCSDIN5		(1L<<5)
#define SCSDIN4		(1L<<4)
#define SCSDIN3		(1L<<3)
#define SCSDIN2		(1L<<2)
#define SCSDIN1		(1L<<1)
#define SCSDIN0		(1L<<0)

/*~~~~~~~~~~~~ SPIPC3 register ~~~~~~~~~~~~*/
#define SOMIDOUT7	(1L<<31)
#define SOMIDOUT6	(1L<<30)
#define SOMIDOUT5	(1L<<29)
#define SOMIDOUT4	(1L<<28)
#define SOMIDOUT3	(1L<<27)
#define SOMIDOUT2	(1L<<26)
#define SOMIDOUT1	(1L<<25)
#define SOMIDOUT0	(1L<<11)
#define SIMODOUT7	(1L<<23)
#define SIMODOUT6	(1L<<22)
#define SIMODOUT5	(1L<<21)
#define SIMODOUT4	(1L<<20)
#define SIMODOUT3	(1L<<19)
#define SIMODOUT2	(1L<<18)
#define SIMODOUT1	(1L<<17)
#define SIMODOUT0	(1L<<10)
#define CLKDOUT		(1L<<9)
#define ENADOUT		(1L<<8)
#define SCSDOUT7	(1L<<7)
#define SCSDOUT6	(1L<<6)
#define SCSDOUT5	(1L<<5)
#define SCSDOUT4	(1L<<4)
#define SCSDOUT3	(1L<<3)
#define SCSDOUT2	(1L<<2)
#define SCSDOUT1	(1L<<1)
#define SCSDOUT0	(1L<<0)

/*~~~~~~~~~~~~ SPIPC4 register ~~~~~~~~~~~~*/
#define SOMISET7	(1L<<31)
#define SOMISET6	(1L<<30)
#define SOMISET5	(1L<<29)
#define SOMISET4	(1L<<28)
#define SOMISET3	(1L<<27)
#define SOMISET2	(1L<<26)
#define SOMISET1	(1L<<25)
#define SOMISET0	(1L<<11)
#define SIMOSET7	(1L<<23)
#define SIMOSET6	(1L<<22)
#define SIMOSET5	(1L<<21)
#define SIMOSET4	(1L<<20)
#define SIMOSET3	(1L<<19)
#define SIMOSET2	(1L<<18)
#define SIMOSET1	(1L<<17)
#define SIMOSET0	(1L<<10)
#define CLKDSET		(1L<<9)
#define ENADSET		(1L<<8)
#define SCSSET7		(1L<<7)
#define SCSSET6		(1L<<6)
#define SCSSET5		(1L<<5)
#define SCSSET4		(1L<<4)
#define SCSSET3		(1L<<3)
#define SCSSET2		(1L<<2)
#define SCSSET1		(1L<<1)
#define SCSSET0		(1L<<0)

/*~~~~~~~~~~~~ SPIPC5 register ~~~~~~~~~~~~*/
#define SOMICLR7	(1L<<31)
#define SOMICLR6	(1L<<30)
#define SOMICLR5	(1L<<29)
#define SOMICLR4	(1L<<28)
#define SOMICLR3	(1L<<27)
#define SOMICLR2	(1L<<26)
#define SOMICLR1	(1L<<25)
#define SOMICLR0	(1L<<11)
#define SIMOCLR7	(1L<<23)
#define SIMOCLR6	(1L<<22)
#define SIMOCLR5	(1L<<21)
#define SIMOCLR4	(1L<<20)
#define SIMOCLR3	(1L<<19)
#define SIMOCLR2	(1L<<18)
#define SIMOCLR1	(1L<<17)
#define SIMOCLR0	(1L<<10)
#define CLKDCLR		(1L<<9)
#define ENADCLR		(1L<<8)
#define SCSCLR7		(1L<<7)
#define SCSCLR6		(1L<<6)
#define SCSCLR5		(1L<<5)
#define SCSCLR4		(1L<<4)
#define SCSCLR3		(1L<<3)
#define SCSCLR2		(1L<<2)
#define SCSCLR1		(1L<<1)
#define SCSCLR0		(1L<<0)

/*~~~~~~~~~~~~ SPIPC6 register ~~~~~~~~~~~~*/
#define SOMIPDR7	(1L<<31)
#define SOMIPDR6	(1L<<30)
#define SOMIPDR5	(1L<<29)
#define SOMIPDR4	(1L<<28)
#define SOMIPDR3	(1L<<27)
#define SOMIPDR2	(1L<<26)
#define SOMIPDR1	(1L<<25)
#define SOMIPDR0	(1L<<11)
#define SIMOPDR7	(1L<<23)
#define SIMOPDR6	(1L<<22)
#define SIMOPDR5	(1L<<21)
#define SIMOPDR4	(1L<<20)
#define SIMOPDR3	(1L<<19)
#define SIMOPDR2	(1L<<18)
#define SIMOPDR1	(1L<<17)
#define SIMOPDR0	(1L<<10)
#define CLKDPDR		(1L<<9)
#define ENADPDR		(1L<<8)
#define SCSPDR7		(1L<<7)
#define SCSPDR6		(1L<<6)
#define SCSPDR5		(1L<<5)
#define SCSPDR4		(1L<<4)
#define SCSPDR3		(1L<<3)
#define SCSPDR2		(1L<<2)
#define SCSPDR1		(1L<<1)
#define SCSPDR0		(1L<<0)

/*~~~~~~~~~~~~ SPIPC7 register ~~~~~~~~~~~~*/
#define SOMIDIS7	(1L<<31)
#define SOMIDIS6	(1L<<30)
#define SOMIDIS5	(1L<<29)
#define SOMIDIS4	(1L<<28)
#define SOMIDIS3	(1L<<27)
#define SOMIDIS2	(1L<<26)
#define SOMIDIS1	(1L<<25)
#define SOMIDIS0	(1L<<11)
#define SIMODIS7	(1L<<23)
#define SIMODIS6	(1L<<22)
#define SIMODIS5	(1L<<21)
#define SIMODIS4	(1L<<20)
#define SIMODIS3	(1L<<19)
#define SIMODIS2	(1L<<18)
#define SIMODIS1	(1L<<17)
#define SIMODIS0	(1L<<10)
#define CLKDDIS		(1L<<9)
#define ENADDIS		(1L<<8)
#define SCSDIS7		(1L<<7)
#define SCSDIS6		(1L<<6)
#define SCSDIS5		(1L<<5)
#define SCSDIS4		(1L<<4)
#define SCSDIS3		(1L<<3)
#define SCSDIS2		(1L<<2)
#define SCSDIS1		(1L<<1)
#define SCSDIS0		(1L<<0)

/*~~~~~~~~~~~~ SPIPC8 register ~~~~~~~~~~~~*/
#define SOMIPSEL7	(1L<<31)
#define SOMIPSEL6	(1L<<30)
#define SOMIPSEL5	(1L<<29)
#define SOMIPSEL4	(1L<<28)
#define SOMIPSEL3	(1L<<27)
#define SOMIPSEL2	(1L<<26)
#define SOMIPSEL1	(1L<<25)
#define SOMIPSEL0	(1L<<11)
#define SIMOPSEL7	(1L<<23)
#define SIMOPSEL6	(1L<<22)
#define SIMOPSEL5	(1L<<21)
#define SIMOPSEL4	(1L<<20)
#define SIMOPSEL3	(1L<<19)
#define SIMOPSEL2	(1L<<18)
#define SIMOPSEL1	(1L<<17)
#define SIMOPSEL0	(1L<<10)
#define CLKDPSEL	(1L<<9)
#define ENADPSEL	(1L<<8)
#define SCSPSEL7	(1L<<7)
#define SCSPSEL6	(1L<<6)
#define SCSPSEL5	(1L<<5)
#define SCSPSEL4	(1L<<4)
#define SCSPSEL3	(1L<<3)
#define SCSPSEL2	(1L<<2)
#define SCSPSEL1	(1L<<1)
#define SCSPSEL0	(1L<<0)

/*~~~~~~~~~~~~ SPIDAT0 register ~~~~~~~~~~~~*/
#define TXDATA	(0xFFFFL<<0)

/*~~~~~~~~~~~~ SPIDAT1 register ~~~~~~~~~~~~*/
#define CSHOLD	(1L<<28)
#define WDEL	(1L<<26)
#define DFSEL1	(1L<<25)
#define DFSEL0	(1L<<24)
#define CSNR7	(1L<<23)
#define CSNR6	(1L<<22)
#define CSNR5	(1L<<21)
#define CSNR4	(1L<<20)
#define CSNR3	(1L<<19)
#define CSNR2	(1L<<18)
#define CSNR1	(1L<<17)
#define CSNR0	(1L<<16)
//#define TXDATA	(0xFFFFL<<0) defined for SPIDAT0

/*~~~~~~~~~~~~ SPIBUF register ~~~~~~~~~~~~*/
#define RXEMPTY		(1L<<31)
#define RXOVR		(1L<<30)
#define TXFULL		(1L<<29)
#define BITERR		(1L<<28)
#define DESYNC		(1L<<27)
#define PARITYERR	(1L<<26)
#define TIMEOUT		(1L<<25)
#define DLENERR		(1L<<24)
#define LCSNR		(0xFFL<<16)
#define RXDATA		(0xFFFFL<<0)

/*~~~~~~~~~~~~ SPIEMU register ~~~~~~~~~~~~*/
#define EMU_RXDATA	(0xFFFFL<<0)

/*~~~~~~~~~~~~ SPIDELAY register ~~~~~~~~~~~~*/
#define C2TDELAY	(0x1FFL<<24)
#define T2CDELAY	(0x1FFL<<16)
#define T2EDELAY	(0x1FFL<<8)
#define C2EDELAY	(0x1FFL<<0)

/*~~~~~~~~~~~~ SPIDEF register ~~~~~~~~~~~~*/
#define CDEF7		(1L<<7)
#define CDEF6		(1L<<6)
#define CDEF5		(1L<<5)
#define CDEF4		(1L<<4)
#define CDEF3		(1L<<3)
#define CDEF2		(1L<<2)
#define CDEF1		(1L<<1)
#define CDEF0		(1L<<0)

/*~~~~~~~~~~~~ SPIFMT register ~~~~~~~~~~~~*/
#define WDELAY			(0xFFL<<24)
#define PARPOL			(1L<<23)
#define PARITYENA		(1L<<22)
#define WAITENA			(1L<<21)
#define SHIFTDIR		(1L<<20)
#define HDUPLEX_ENA		(1L<<19)
#define DIS_CS_TIMERS	(1L<<18)
#define POLARITY		(1L<<17)
#define PHASE			(1L<<16)
#define PRESCALE		(0xFFL<<8)
#define CHARLEN			(0x1FL<<0)

/*~~~~~~~~~~~~ INTVECT0 & INTVECT1register ~~~~~~~~~~~~*/
#define INTVECT	(0x1FL<<1)
#define SUSPEND	(1L<<0)

/*~~~~~~~~~~~~ SPIPMCTRL register ~~~~~~~~~~~~*/
#define MODCLKPOL3	(1L<<29)
#define MMODE3		(0x7L<<26)
#define PMODE3		(0x3L<<24)
#define MODCLKPOL2	(1L<<21)
#define MMODE2		(0x7L<<18)
#define PMODE2		(0x3L<<16)
#define MODCLKPOL1	(1L<<13)
#define MMODE1		(0x7L<<10)
#define PMODE1		(0x3L<<8)
#define MODCLKPOL0	(1L<<5)
#define MMODE0		(0x7L<<2)
#define PMODE0		(0x3L<<0)

/*~~~~~~~~~~~~ TGITENST register ~~~~~~~~~~~~*/
#define SETINTENRDY	(0xFFFFL<<16)
#define SETINTENSUS	(0xFFFFL<<0)

/*~~~~~~~~~~~~ TGITENCR register ~~~~~~~~~~~~*/
#define CLRINTENRDY	(0xFFFFL<<16)
#define CLRINTENSUS	(0xFFFFL<<0)

/*~~~~~~~~~~~~ TGITLVST register ~~~~~~~~~~~~*/
#define SETINTLVLRDY	(0xFFFFL<<16)
#define SETINTLVLSUS	(0xFFFFL<<0)

/*~~~~~~~~~~~~ TGITLVCR register ~~~~~~~~~~~~*/
#define CLRINTLVLRDY	(0xFFFFL<<16)
#define CLRINTLVLSUS	(0xFFFFL<<0)

/*~~~~~~~~~~~~ TGINTFLAG register ~~~~~~~~~~~~*/
#define INTFLGRDY	(0xFFFFL<<16)
#define INTFLGSUS	(0xFFFFL<<0)

/*~~~~~~~~~~~~ TICKCNT register ~~~~~~~~~~~~*/
#define TICKENA		(1L<<31)
#define RELOAD		(1L<<30)
#define CLKCTRL		(0x3L<<28)
#define TICKVALUE	(0xFFFFL<<0)

/*~~~~~~~~~~~~ LTGPEND register ~~~~~~~~~~~~*/
#define TG_IN_SERVICE	(0x1FL<<24)
#define LPEND			(0x7FL<<8)

/*~~~~~~~~~~~~ TGxCTRL register ~~~~~~~~~~~~*/
#define TGENA		(1L<<31)
#define ONESHOT		(1L<<30)
#define PRST		(1L<<29)
#define TGTD		(1L<<28)
#define TRIGEVT		(0x7L<<20)
#define TRIGSRC		(0xFL<<16)
#define PSTART		(0x7FL<<8)
#define PCURRENT	(0x7FL<<0)

/*~~~~~~~~~~~~ Other SPI registers not needed ~~~~~~~~~~~~*/

/******************************************************************************/
/* SPI_TX_BUFFER_SIZE
 *
 * This is the number of SPI strutures that fit in the SPI transmit buffer.	  */
/******************************************************************************/
#define SPI_TX_BUFFER_SIZE 1000L

/******************************************************************************/
/* Chip selects for decives
 *
 * This defines the chip selects for each module.							  */
/******************************************************************************/
#define CS_DAC 				0
#define CS_POT_GAS	 		1
#define CS_POT_STEERING 	2

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern TYPE_SPI_BUFFER SPI_TX_Buffer[SPI_TX_BUFFER_SIZE];
extern volatile long SPI_TX_Buffer_Add_place;
extern volatile long SPI_TX_Buffer_Remove_place;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitSPI(void);
void InitSPI1(void);
void SPI_Parameters1(ENUM_MASTER_SLAVE master_slave, unsigned char mode, unsigned long speedKhz);
void SPI_TransmitInterrupt1(unsigned char state);
void SPI_ReceiveInterrupt1(unsigned char state);
unsigned char SPI_IsTransmitBufferFull(void);
void SPI_SetPins(unsigned char state);
void SPI_SendByte(unsigned char data, unsigned char chip_select, unsigned char chip_select_hold);
void SPI_AddToTXBuffer(unsigned char data, unsigned char chip_select, unsigned char chip_select_hold);

#endif	/* SPI_H */
