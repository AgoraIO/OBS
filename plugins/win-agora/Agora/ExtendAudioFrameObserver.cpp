#include "ExtendAudioFrameObserver.hpp"
#include "agorartcengine.hpp"
#include <tchar.h>
#include <util/base.h>
extern AgoraRtcEngine*	pAgoraManager;


CExtendAudioFrameObserver::CExtendAudioFrameObserver()
    :logAudioFrameTimeCount(0)
    , logAudioTimestamp(false)
    , nPlayerDataLen(0)
{
	int rate = AgoraRtcEngine::GetInstance()->sampleRate;
	int channel = AgoraRtcEngine::GetInstance()->audioChannel;
	this->pCircleBuffer = new CicleBuffer(rate* channel * 2, 0);//(44100 * 2 * 2, 0);
	pPlayerData = new BYTE[0x800000];
 ZeroMemory(pPlayerData, 0x800000);
}

CExtendAudioFrameObserver::~CExtendAudioFrameObserver()
{
    if (pPlayerData) {
        delete[] pPlayerData;
        pPlayerData = NULL;
        delete pCircleBuffer;
        pCircleBuffer = NULL;
    }
}

bool CExtendAudioFrameObserver::onRecordAudioFrame(AudioFrame& audioFrame)
{
	if (!pPlayerData || !pCircleBuffer)
		return false;

	SIZE_T nSize = audioFrame.channels*audioFrame.samples * audioFrame.bytesPerSample;
	unsigned int datalen = 0;
 int64_t audioTime = 0;
	pCircleBuffer->readBuffer(this->pPlayerData, nSize, &datalen, audioTime);

 if (nSize > 0 && datalen == nSize)
 {
     if (agora_sdk_captrue_mic_audio) {

         //int nMixLen = datalen > nSize ? nSize : datalen;
         int len = datalen / sizeof(int16_t);
         for (int i = 0; i < len; i++) {
             int16_t* buffer = (int16_t*)(audioFrame.buffer) + i * sizeof(int16_t);
             int16_t* obsbuffer = (int16_t*)(pPlayerData)+i * sizeof(int16_t);
             int mix = *buffer + *obsbuffer;
             if (mix > 32767)
                 *obsbuffer = 32767;
             else if (mix < -32768)
                 *obsbuffer = -32768;
             else
                 *obsbuffer = mix;
         }
         memcpy(audioFrame.buffer, pPlayerData, datalen);

     }
     else
         memcpy(audioFrame.buffer, pPlayerData, datalen);
 }
	/**/

 audioFrame.renderTimeMs = GetTickCount();

 if (logAudioTimestamp && logAudioFrameTimeCount < LOG_AUDIO_FRAME_TIME_COUNT) {
     blog(LOG_INFO, "Agora Info onRecordAudioFrame , agora sdk get obs audio frame time: %lld, agora audio frame time %lld(%lldms)", audioTime, audioFrame.renderTimeMs, audioFrame.renderTimeMs - audioTime);
     logAudioFrameTimeCount++;
}

	return true;
}

bool CExtendAudioFrameObserver::onPlaybackAudioFrame(AudioFrame& audioFrame)
{
	SIZE_T nSize = audioFrame.channels*audioFrame.samples * 2;
	
	return true;
}

bool CExtendAudioFrameObserver::onMixedAudioFrame(AudioFrame& audioFrame)
{
	return true;
}

bool CExtendAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame)
{
	return true;
}
