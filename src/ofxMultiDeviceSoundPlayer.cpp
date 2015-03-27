/*
 *  ofxMultiDeviceSoundPlayer.cpp
 *  triangluation
 *
 *  Created by Zach Gage on 7/29/08.
 *  Copyright 2008 STFJ.NET. All rights reserved.
 *
 */

#include "ofxMultiDeviceSoundPlayer.h"

/*float MultiFftValues[8192];			//	
float MultiFftInterpValues[8192];			//	
float MultiFftSpectrum[8192];		// maximum # is 8192, in fmodex....*/


static FMOD_CHANNELGROUP * channel_Array[100];
static FMOD_SYSTEM * sys_Array[100];
static bool sys_Array_init[100];

//-------------------------------------

ofxMultiDeviceSoundPlayer::ofxMultiDeviceSoundPlayer(){
	bLoop 			= false;
	bLoadedOk 		= false;
	pan 			= 0.5f;					
	volume 			= 1.0f;
	internalFreq 	= 44100;  	
	speed 			= 1;
	bPaused 		= false;
	isStreaming		= false;	
	device			= 0;
}

ofxMultiDeviceSoundPlayer::~ofxMultiDeviceSoundPlayer(){
	unloadSound();
}

//--------------------------------------

void ofxMultiDeviceSoundPlayer::unloadSound(){
	if (bLoadedOk){
		stop();						// try to stop the sound
		if(!isStreaming)FMOD_Sound_Release(sound);
	}
}

//---------------------------------------
void ofxMultiDeviceSoundPlayer::closeFmod(){
	for(int i=0;i<100;i++)
	{
		if(sys_Array_init[i]){
			FMOD_System_Close(sys_Array[i]);
			sys_Array_init[i] = false;
		}
	}
}

// this should only be called once per device
void ofxMultiDeviceSoundPlayer::initializeFmodWithTargetDevice(int deviceIndex)
{
	if(!sys_Array_init[deviceIndex]){
		FMOD_System_Create(&sys_Array[deviceIndex]);
		
		int driverNum;
		FMOD_System_GetNumDrivers(sys_Array[deviceIndex], &driverNum);
		
		/*
		for(int i=0; i<driverNum; i++)
		{
			char name[256];
			FMOD_System_GetDriverName(sys_Array[deviceIndex], i, name, 256);
			
			printf("%d : %s\n", i, name);
		}*/
		
		FMOD_System_SetDriver(sys_Array[deviceIndex], deviceIndex);
		FMOD_System_Init(sys_Array[deviceIndex], 2000, FMOD_INIT_NORMAL, NULL);  //do we want just 32 channels?
		
		FMOD_System_GetMasterChannelGroup(sys_Array[deviceIndex], &channel_Array[deviceIndex]);
		
		sys_Array_init[deviceIndex] = true;
	}
}

//------------------------------------------------------------
void ofxMultiDeviceSoundPlayer::loadSoundWithTarget(string fileName, int deviceIndex)
{
	device = deviceIndex;
	bool stream = false;
	fileName = ofToDataPath(fileName);
	
	// fmod uses IO posix internally, might have trouble
	// with unicode paths...
	// says this code:
	// http://66.102.9.104/search?q=cache:LM47mq8hytwJ:www.cleeker.com/doxygen/audioengine__fmod_8cpp-source.html+FSOUND_Sample_Load+cpp&hl=en&ct=clnk&cd=18&client=firefox-a
	// for now we use FMODs way, but we could switch if
	// there are problems:
	
	bMultiPlay = false;
	
	// [1] init fmod, if necessary
	
	initializeFmodWithTargetDevice(deviceIndex);	
	
	// [2] try to unload any previously loaded sounds
	// & prevent user-created memory leaks
	// if they call "loadSound" repeatedly, for example
	
	unloadSound();
	
	// [3] load sound
	
	//choose if we want streaming
	int fmodFlags =  FMOD_SOFTWARE;
	if(stream)fmodFlags =  FMOD_SOFTWARE | FMOD_CREATESTREAM;
	
	result = FMOD_System_CreateSound(sys_Array[deviceIndex], fileName.c_str(),  fmodFlags, NULL, &sound);

	if (result != FMOD_OK){
		bLoadedOk = false;
		printf("ofSoundPlayer: Could not load sound file %s \n", fileName.c_str() );
	} else {
		bLoadedOk = true;
		FMOD_Sound_GetLength(sound, &length, FMOD_TIMEUNIT_PCM);
		isStreaming = stream;
	}
	
}

//------------------------------------------------------------
bool ofxMultiDeviceSoundPlayer::getIsPlaying(){
	
	if (!bLoadedOk) return false;
	
	int playing = 0;
	FMOD_Channel_IsPlaying(channel, &playing);
	return (playing != 0 ? true : false);
}

//------------------------------------------------------------
float ofxMultiDeviceSoundPlayer::getSpeed(){
	return speed;
}

//------------------------------------------------------------
float ofxMultiDeviceSoundPlayer::getPan(){
	return pan;
}

//------------------------------------------------------------
void ofxMultiDeviceSoundPlayer::setVolume(float vol){
	if (getIsPlaying() == true){
		FMOD_Channel_SetVolume(channel, vol);
	}
	volume = vol;
}

//------------------------------------------------------------
void ofxMultiDeviceSoundPlayer::setPosition(float pct){
	if (getIsPlaying() == true){
		int sampleToBeAt = (int)(length * pct);		
		FMOD_Channel_SetPosition(channel, sampleToBeAt, FMOD_TIMEUNIT_PCM);		
	}
}

//------------------------------------------------------------
float ofxMultiDeviceSoundPlayer::getPosition(){
	if (getIsPlaying() == true){
		unsigned int sampleImAt;

		FMOD_Channel_GetPosition(channel, &sampleImAt, FMOD_TIMEUNIT_PCM);

		float pct = 0.0f;
		if (length > 0){
			pct = sampleImAt / (float)length;
		}
		return pct;
	} else {
		return 0;
	}
}

//------------------------------------------------------------
void ofxMultiDeviceSoundPlayer::setPan(float p){
	if (getIsPlaying() == true){
		FMOD_Channel_SetPan(channel,p);
	}
	pan = p;
}


//------------------------------------------------------------
void ofxMultiDeviceSoundPlayer::setPaused(bool bP){
	if (getIsPlaying() == true){
		FMOD_Channel_SetPaused(channel,bP);
		bPaused = bP;
	}
}


//------------------------------------------------------------
void ofxMultiDeviceSoundPlayer::setSpeed(float spd){
	if (getIsPlaying() == true){
			FMOD_Channel_SetFrequency(channel, internalFreq * spd);
	}
	speed = spd;
}


//------------------------------------------------------------
void ofxMultiDeviceSoundPlayer::setLoop(bool bLp){
	if (getIsPlaying() == true){
		FMOD_Channel_SetMode(channel,  (bLp == true) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
	}
	bLoop = bLp;
}

// ---------------------------------------------------------------------------- 
void ofxMultiDeviceSoundPlayer::setMultiPlay(bool bMp){
	bMultiPlay = bMp;		// be careful with this...
}
		
// ---------------------------------------------------------------------------- 
void ofxMultiDeviceSoundPlayer::play(){
	
	// if it's a looping sound, we should try to kill it, no?
	// or else people will have orphan channels that are looping
	if (bLoop == true){
		FMOD_Channel_Stop(channel);
	}
	
	// if the sound is not set to multiplay, then stop the current,
	// before we start another
	if (!bMultiPlay){
		FMOD_Channel_Stop(channel);
	}
	
	FMOD_System_PlaySound(sys_Array[device], FMOD_CHANNEL_FREE, sound, bPaused, &channel);

	FMOD_Channel_GetFrequency(channel, &internalFreq);
	FMOD_Channel_SetVolume(channel,volume);
	FMOD_Channel_SetPan(channel,pan);
	FMOD_Channel_SetFrequency(channel, internalFreq * speed);
	FMOD_Channel_SetMode(channel,  (bLoop == true) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
		
	//fmod update() should be called every frame - according to the docs.
	//we have been using fmod without calling it at all which resulted in channels not being able 
	//to be reused.  we should have some sort of global update function but putting it here
	//solves the channel bug
	FMOD_System_Update(sys_Array[device]);
	
}

// ---------------------------------------------------------------------------- 
void ofxMultiDeviceSoundPlayer::stop(){
	FMOD_Channel_Stop(channel);
}