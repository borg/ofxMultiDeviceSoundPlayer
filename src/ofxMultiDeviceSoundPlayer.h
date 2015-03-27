/*
 *  ofxMultiDeviceSoundPlayer.h
 *  triangluation
 *
 *  Created by Zach Gage on 7/29/08.
 *  Copyright 2008 stfj.net. All rights reserved.
 *
 */

#ifndef _OF_MULTI_DEVIC_SOUND_PLAYER
#define _OF_MULTI_DEVIC_SOUND_PLAYER

#include "ofConstants.h"

extern "C"{
	#include "fmod.h"
	#include "fmod_errors.h"
}

#include "ofMain.h"


// --------------------- global functions:
void ofSoundStopAll();
void ofSoundSetVolume(float vol);
float * ofSoundGetSpectrum(int nBands);			// max 512...




class ofxMultiDeviceSoundPlayer 
{
	
	public:
		
		ofxMultiDeviceSoundPlayer(); 
		~ofxMultiDeviceSoundPlayer(); 

		
		void  	loadSoundWithTarget(string fileName, int deviceIndex);
		static void initializeFmodWithTargetDevice(int deviceIndex);
		
		static void closeFmod(); 
		
		
		void 	unloadSound(); 
		void  	play(); 
		void  	stop(); 
		
		void 	setVolume(float vol);
		void 	setPan(float vol);
		void 	setSpeed(float spd);
		void 	setPaused(bool bP);
		void  	setLoop(bool bLp);
		void 	setMultiPlay(bool bMp);
		void 	setPosition(float pct);	// 0 = start, 1 = end;
		
		float  	getPosition();
		bool 	getIsPlaying(); 	
		float 	getSpeed();	
		float 	getPan();
		
		bool	isStreaming;
		bool 	bMultiPlay;
		bool 	bLoop;
		bool 	bLoadedOk;
		bool  	bPaused;
		float 	pan;				// 0 - 1
		float 	volume;				// 0 - 1
		float 	internalFreq;		// 44100 ?
		float 	speed;				// -n to n, 1 = normal, -1 backwards
		unsigned int 	length;		// in samples;
									
		FMOD_RESULT			result;
		FMOD_CHANNEL 		*  channel;
		FMOD_SOUND  		*  sound;
		int device;
		
};

#endif