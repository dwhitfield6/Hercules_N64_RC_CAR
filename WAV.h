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

// wav file info
typedef struct __attribute__((packed)) WAV_Struct
{
    unsigned char valid;
    unsigned long ChunkSize;
    unsigned long Subchunk1Size;
    unsigned int  AudioFormat;
    unsigned int  NumChannels;
    unsigned long SampleRate;
    unsigned long ByteRate;
    unsigned char BitsPerSample;
    unsigned long Subchunk2Size;
    unsigned long NumSamples;
    unsigned char SampleRepeat;
    unsigned char* BufferPointer;
    unsigned long CurrentSample;
}WAV;

/******************************************************************************/
/* WAV_PLAYING_QUEUE_SIZE
 *
 * This is the number of wav files that we can put on the queue.			  */
/******************************************************************************/
#define WAV_PLAYING_QUEUE_SIZE 4

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
extern WAV CurrentWAVFile;

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
unsigned char WAV_ParseHeader(unsigned char* buffer);

#endif	/* WAV_H */
