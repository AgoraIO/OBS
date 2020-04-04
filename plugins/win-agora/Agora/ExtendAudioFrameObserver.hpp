#pragma once
#include "Agora/IAgoraMediaEngine.h"
#include <windows.h>
#include "CicleBuffer.hpp"
#define AUDIO_CALLBACK_TIMES 100 // callback times per second, means calling callback once every 10ms
#define LOG_AUDIO_FRAME_TIME_COUNT 1000
class CExtendAudioFrameObserver :
	public agora::media::IAudioFrameObserver 
{	
public:
	CicleBuffer* pCircleBuffer;
	CExtendAudioFrameObserver();
	~CExtendAudioFrameObserver();
	LPBYTE pPlayerData;
	int    nPlayerDataLen;
	bool   bDebug;
 
	bool agora_sdk_captrue_mic_audio = false;
 void Resetlog(bool b) { logAudioTimestamp = b; logAudioFrameTimeCount = 0; }
	virtual bool onRecordAudioFrame(AudioFrame& audioFrame);
	virtual bool onPlaybackAudioFrame(AudioFrame& audioFrame);
	virtual bool onMixedAudioFrame(AudioFrame& audioFrame);
	virtual bool onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame);
private:
    int    logAudioFrameTimeCount;
    bool   logAudioTimestamp;
};

