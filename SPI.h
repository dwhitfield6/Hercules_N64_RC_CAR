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

/*~~~~~~~~~~~~ SPIPC1 register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIPC2 register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIPC3 register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIPC4 register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIPC5 register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIPC6 register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIPC7 register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIPC8 register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIDAT0 register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIDAT1 register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIBUF register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIEMU register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIDELAY register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIDEF register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIFMT register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ INTVECT0 register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ INTVECT1 register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ SPIPMCTRL register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ TGITENST register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ TGITENCR register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ TGITLVST register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ TGITLVCR register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ TGINTFLAG register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ TICKCNT register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ LTGPEND register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ TGxCTRL register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ DMAxCTRL register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ ICOUNT register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ DMACNTLEN register ~~~~~~~~~~~~*/

/*~~~~~~~~~~~~ PAR_ECC_CTRL register ~~~~~~~~~~~~*/


/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitSPI(void);
void InitSPI1(void);
void SPI_Parameters1(ENUM_MASTER_SLAVE master_slave, unsigned char mode, unsigned long speedKhz);

#endif	/* SPI_H */
