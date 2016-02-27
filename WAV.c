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

#include "BANANA_SOUND_WAV.h"
#include "MISC.h"
#include "START_SOUND_WAV.h"
#include "TIMERS.h"
#include "TURTLE_SOUND_WAV.h"
#include "USER.h"
#include "WAV.h"

/******************************************************************************/
/* Private Variable Declaration      	                                      */
/******************************************************************************/
static volatile unsigned char WAV_PlayingFlag = FALSE;
static volatile unsigned char WAV_StartedFlag = FALSE;
static volatile unsigned char WAV_FinishedFlag = FALSE;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
ENUM_WAV_FILES WAV_PlayingQueue[WAV_PLAYING_QUEUE_SIZE];
WAV CurrentWAVFile;

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
	unsigned char* WAV_Address = 0;
	double prescalerD;
	long prescalerL;

	switch (file)
	{
		case START:
			WAV_Address = (unsigned char*) Start_WAV;
			break;
		case TURTLE:
			WAV_Address = (unsigned char*) Turtle_WAV;
			break;
		default:
			WAV_Address = (unsigned char*) Banana_WAV;
			break;
	}
	if(WAV_ParseHeader(WAV_Address))
	{
	    prescalerD = MSC_Round(((double)VCLK2) / (15.0 * (double) CurrentWAVFile.SampleRate));
	    prescalerL = (long) prescalerD;
        TMR_SetTimerPeriod2(prescalerL, DAC_TIMER);
    	TMR_N2HET2_InterruptEnable(DAC_TIMER);
		return PASS;
	}
	return FAIL;
}

/******************************************************************************/
/* WAV_ParseHeader
 *
 * This function parses the header of the wav file and sets up the timer to
 *  play the audio.															  */
/******************************************************************************/
unsigned char WAV_ParseHeader(unsigned char* buffer)
{
    unsigned long tempL;
    unsigned int  tempI;
    /* ChinkID */
    if(buffer[0] != 'R' || buffer[1] != 'I' || buffer[2] != 'F' || buffer[3] != 'F')
    {
    	CurrentWAVFile.valid = FAIL;
        return FAIL;
    }

    /* ChunkSize */
    tempL = MSC_EndianLongArray(&buffer[4]);
    CurrentWAVFile.ChunkSize = tempL;

    /* Format */
    if(buffer[8] != 'W' || buffer[9] != 'A' || buffer[10] != 'V' || buffer[11] != 'E')
    {
    	CurrentWAVFile.valid = FAIL;
        return FAIL;
    }

    /* Subchunk1ID */
    if(buffer[12] != 'f' || buffer[13] != 'm' || buffer[14] != 't' || buffer[15] != ' ')
    {
    	CurrentWAVFile.valid = FAIL;
        return FAIL;
    }

    /* Subchunk1Size */
    tempL = MSC_EndianLongArray(&buffer[16]);
    CurrentWAVFile.Subchunk1Size = tempL;

    /* AudioFormat */
    tempI = MSC_EndianShortArray(&buffer[20]);
    CurrentWAVFile.AudioFormat = tempI;
    if(tempI != 0x01)
    {
        /* compressed */
    	CurrentWAVFile.valid = FAIL;
        return FAIL;
    }

    /* NumChannels */
    tempI = MSC_EndianShortArray(&buffer[22]);
    CurrentWAVFile.NumChannels = tempI;

    /* SampleRate */
    tempL = MSC_EndianLongArray(&buffer[24]);
    CurrentWAVFile.SampleRate = tempL;

    /* ByteRate */
    tempL = MSC_EndianLongArray(&buffer[28]);
    CurrentWAVFile.ByteRate = tempL;

    /* Blockalign */

    /* BitsPerSample */
    tempI = MSC_EndianShortArray(&buffer[34]);
    CurrentWAVFile.BitsPerSample = tempI;

    /* Subchunk2ID */
    if(buffer[36] != 'd' || buffer[37] != 'a' || buffer[38] != 't' || buffer[39] != 'a')
    {
    	CurrentWAVFile.valid = FAIL;
        return FAIL;
    }

    /* Subchunk2Size */
    tempL = MSC_EndianLongArray(&buffer[40]);
    CurrentWAVFile.Subchunk2Size = tempL;
    CurrentWAVFile.valid = PASS;
    CurrentWAVFile.NumSamples = (CurrentWAVFile.Subchunk2Size/(CurrentWAVFile.NumChannels * (CurrentWAVFile.BitsPerSample >> 3)));
    if(CurrentWAVFile.NumChannels == 2)
    {
        /* Stereo */
        if(CurrentWAVFile.BitsPerSample == 8)
        {
            /* 8 bit */
        	CurrentWAVFile.SampleRepeat = 2;
        }
        else
        {
            /* 16 bit */
        	CurrentWAVFile.SampleRepeat = 4;
        }
    }
    else
    {
        /* Mono */
        if(CurrentWAVFile.BitsPerSample == 8)
        {
            /* 8 bit */
        	CurrentWAVFile.SampleRepeat = 1;
        }
        else
        {
            /* 16 bit */
        	CurrentWAVFile.SampleRepeat = 2;
        }
    }
    CurrentWAVFile.CurrentSample = 0;
    CurrentWAVFile.BufferPointer = &buffer[44];
    return PASS;
}
/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
