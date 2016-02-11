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
/* Contains functions for decoding WAV audio files.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "HL_sys_common.h"    		// TMS570LC43xx Include file
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "USER.h"
#include "WAV.h"

/******************************************************************************/
/* Private Variable Declaration      	                                      */
/******************************************************************************/
static unsigned char WAV_PlayingFlag = FALSE;
static unsigned char WAV_StartedFlag = FALSE;
static unsigned char WAV_FinishedFlag = FALSE;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
ENUM_WAV_FILES WAV_PlayingQueue[WAV_PLAYING_QUEUE_SIZE];

/******************************************************************************/
/* Inline Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

/******************************************************************************/
/* InitWAV
 *
 * The function initializes the WAV playback functions.						  */
/******************************************************************************/
void InitWAV(void)
{
	memset(WAV_PlayingQueue, 0, sizeof(WAV_PlayingQueue));
}

/******************************************************************************/
/* WAV_IsStarted
 *
 * The function returns true if a wav file is currently started.			  */
/******************************************************************************/
unsigned char WAV_IsStarted(void)
{
	return WAV_StartedFlag;
}

/******************************************************************************/
/* WAV_Started
 *
 * The function sets the state of the WAV playback started.					  */
/******************************************************************************/
void WAV_Started(unsigned char state)
{
	WAV_StartedFlag = state;
}

/******************************************************************************/
/* WAV_IsPlaying
 *
 * The function returns true if a wav file is currently being played.		  */
/******************************************************************************/
unsigned char WAV_IsPlaying(void)
{
	return WAV_PlayingFlag;
}

/******************************************************************************/
/* WAV_Started
 *
 * The function sets the state of the WAV playback.							  */
/******************************************************************************/
void WAV_Playing(unsigned char state)
{
	WAV_PlayingFlag = state;
}

/******************************************************************************/
/* WAV_IsFinished
 *
 * The function returns true if the WAV file is currently finished.			  */
/******************************************************************************/
unsigned char WAV_IsFinished(void)
{
	return WAV_FinishedFlag;
}

/******************************************************************************/
/* WAV_Finished
 *
 * The function sets the state of the WAV playback finished.				  */
/******************************************************************************/
void WAV_Finished(unsigned char state)
{
	WAV_FinishedFlag = state;
}

/******************************************************************************/
/* WAV_EraseFromQueue
 *
 * The function erases the lowest file from the queue and shift every file to
 *  the left.																  */
/******************************************************************************/
void WAV_EraseFromQueue(void)
{
	unsigned char i;

	for(i = 0; i < (WAV_PLAYING_QUEUE_SIZE - 1); i++)
	{
		WAV_PlayingQueue[i] = WAV_PlayingQueue[i+1];
	}

	WAV_PlayingQueue[WAV_PLAYING_QUEUE_SIZE - 1] = EMPTY;
}

/******************************************************************************/
/* WAV_EraseFromQueue
 *
 * The function erases the lowest file from the queue and shift every file to
 *  the left.																  */
/******************************************************************************/
unsigned char WAV_AddToQueue(ENUM_WAV_FILES file)
{
	unsigned char i;
	unsigned char QueueSpot = WAV_PLAYING_QUEUE_SIZE;
	unsigned char status = FAIL;

	if(file > 0 && file <= BANANA)
	{
		for(i = 0; i < WAV_PLAYING_QUEUE_SIZE; i++)
		{
			if(!WAV_PlayingQueue[i])
			{
				QueueSpot = i;
				break;
			}
		}
		if(QueueSpot != WAV_PLAYING_QUEUE_SIZE)
		{
			/* there is an empty spot in the queue */
			WAV_PlayingQueue[QueueSpot] = file;
			status = PASS;
			/* file is in range */
			if(!WAV_IsPlaying())
			{
				/* start playing a file if not already */
				WAV_Playing(TRUE);
			}
		}
	}
	return status;
}

/******************************************************************************/
/* WAV_SetupPlayback
 *
 * The function searches the WAV header information for playback settings then
 *  finds the buffer starting position.										  */
/******************************************************************************/
unsigned char WAV_SetupPlayback(ENUM_WAV_FILES file)
{
	// TODO
	return PASS;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
