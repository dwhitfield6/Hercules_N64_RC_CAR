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
/* Files to Include                                                           */
/******************************************************************************/
#ifndef ECAP_H
#define	ECAP_H

#include "HL_sys_common.h"    		// TMS570LC43xx Include file
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "SYSTEM.h"

/******************************************************************************/
/* Registers                                                                  */
/******************************************************************************/
/*~~~~~~~~~~~~ ECCTL2 register ~~~~~~~~~~~~*/
#define APWMPOL		(1L<<10)
#define CAP_APWM	(1L<<9)
#define SWSYNC		(1L<<8)
#define SYNCO_SEL	(0x3L<<6)
#define SYNCI_EN	(1L<<5)
#define TSCTRSTOP	(1L<<4)
#define REARM		(1L<<3)
#define STOP_WRAP	(0x3L<<1)
#define CONT_ONESHT	(1L<<0)

/*~~~~~~~~~~~~ ECCTL1 register ~~~~~~~~~~~~*/
#define FREE_SOFT	(0x3L<<14)
#define PRESCALE_E	(0x1FL<<9)
#define CAPLDEN		(1L<<8)
#define CTRRST4		(1L<<7)
#define CAP4POL		(1L<<6)
#define CTRRST3		(1L<<5)
#define CAP3POL		(1L<<4)
#define CTRRST2		(1L<<3)
#define CAP2POL		(1L<<2)
#define CTRRST1		(1L<<1)
#define CAP1POL		(1L<<0)

/*~~~~~~~~~~~~ ECFLG register ~~~~~~~~~~~~*/
#define CTR_CMP		(1L<<7)
#define CTR_PRD		(1L<<6)
#define CTROVF		(1L<<5)
#define CEVT4		(1L<<4)
#define CEVT3		(1L<<3)
#define CEVT2		(1L<<2)
#define CEVT1		(1L<<1)
#define INT			(1L<<0)

/*~~~~~~~~~~~~ ECEINT register ~~~~~~~~~~~~*/
/* same as above
#define CTR_CMP		(1L<<7)
#define CTR_PRD		(1L<<6)
#define CTROVF		(1L<<5)
#define CEVT4		(1L<<4)
#define CEVT3		(1L<<3)
#define CEVT2		(1L<<2)
#define CEVT1		(1L<<1)
#define INT			(1L<<0)
*/

/*~~~~~~~~~~~~ ECFRC register ~~~~~~~~~~~~*/
/* same as above
#define CTR_CMP		(1L<<7)
#define CTR_PRD		(1L<<6)
#define CTROVF		(1L<<5)
#define CEVT4		(1L<<4)
#define CEVT3		(1L<<3)
#define CEVT2		(1L<<2)
#define CEVT1		(1L<<1)
#define INT			(1L<<0)
*/

/*~~~~~~~~~~~~ ECCLR register ~~~~~~~~~~~~*/
/* same as above
#define CTR_CMP		(1L<<7)
#define CTR_PRD		(1L<<6)
#define CTROVF		(1L<<5)
#define CEVT4		(1L<<4)
#define CEVT3		(1L<<3)
#define CEVT2		(1L<<2)
#define CEVT1		(1L<<1)
#define INT			(1L<<0)
*/

/******************************************************************************/
/* ECAP_PRELOAD
 *
 * This is the preload number to decrease the timeout waiting period.		  */
/******************************************************************************/
#define ECAP_PRELOAD 0xFFFF8FFFL

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
void InitECAP(void);
void ECAP_Interrupt(unsigned char state);

#endif	/* ECAP_H */
