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
#ifndef WAV_H
#define	WAV_H

#include "HL_sys_common.h"    		// TMS570LC43xx Include file
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "SYSTEM.h"

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/
typedef enum e_wav_files
{
    EMPTY	= 0,
	START	= 1,
	TURTLE	= 2,
	BANANA	= 3,
}ENUM_WAV_FILES;

/******************************************************************************/
/* WAV_PLAYING_QUEUE_SIZE
 *
 * This is the number of wav files that we can put on the queue.			  */
/******************************************************************************/
#define WAV_PLAYING_QUEUE_SIZE 20

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern ENUM_WAV_FILES WAV_PlayingQueue[WAV_PLAYING_QUEUE_SIZE];

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitWAV(void);
unsigned char WAV_IsStarted(void);
void WAV_Started(unsigned char state);
unsigned char WAV_IsPlaying(void);
void WAV_Playing(unsigned char state);
unsigned char WAV_IsFinished(void);
void WAV_Finished(unsigned char state);
void WAV_EraseFromQueue(void);
unsigned char WAV_AddToQueue(ENUM_WAV_FILES file);
unsigned char WAV_SetupPlayback(ENUM_WAV_FILES file);

#endif	/* WAV_H */
