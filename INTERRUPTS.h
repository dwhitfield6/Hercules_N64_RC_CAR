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
#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#include "HL_sys_common.h"    		// TMS570LC43xx Include file
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/******************************************************************************/
/* ISR prototypes                                                        	  */
/******************************************************************************/
void ISR_SPI1_INT0(void);
void ISR_ECAP_N64(void);
void ISR_Timer1(void);
void ISR_Timer2(void);

#endif	/* INTERRUPTS_H */
