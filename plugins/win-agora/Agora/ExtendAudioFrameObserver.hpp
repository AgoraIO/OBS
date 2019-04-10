#pragma once
#include "Agora/IAgoraMediaEngine.h"
#include <windows.h>
#include "CicleBuffer.hpp"
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
	virtual bool onRecordAudioFrame(AudioFrame& audioFrame);
	virtual bool onPlaybackAudioFrame(AudioFrame& audioFrame);
	virtual bool onMixedAudioFrame(AudioFrame& audioFrame);
	virtual bool onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame);
};

