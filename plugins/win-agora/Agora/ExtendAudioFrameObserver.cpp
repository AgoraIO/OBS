#include "ExtendAudioFrameObserver.hpp"
#include "agorartcengine.hpp"
#include <tchar.h>
extern AgoraRtcEngine*	pAgoraManager;


CExtendAudioFrameObserver::CExtendAudioFrameObserver()
{
	this->pCircleBuffer = new CicleBuffer(44100 * 2 * 2, 0);
	pPlayerData = new BYTE[0x800000];
}

CExtendAudioFrameObserver::~CExtendAudioFrameObserver()
{
	delete[] pPlayerData;
}

static inline int16_t MixerAddS16(int16_t var1, int16_t var2) {
	static const int32_t kMaxInt16 = 32767;
	static const int32_t kMinInt16 = -32768;
	int32_t tmp = (int32_t)var1 + (int32_t)var2;
	int16_t out16;

	if (tmp > kMaxInt16) {
		out16 = kMaxInt16;
	}
	else if (tmp < kMinInt16) {
		out16 = kMinInt16;
	}
	else {
		out16 = (int16_t)tmp;
	}

	return out16;
}

void MixerAddS16(int16_t* src1, const int16_t* src2, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		src1[i] = MixerAddS16(src1[i], src2[i]);
	}
}

BOOL mixAudioData(char* psrc, char* pdst, int datalen)
{
	if (!psrc || !pdst || datalen <= 0)
	{
		return FALSE;
	}

	for (int i = 0; i < datalen; i++)
	{
		pdst[i] += psrc[i];
	}
	return TRUE;
}

bool CExtendAudioFrameObserver::onRecordAudioFrame(AudioFrame& audioFrame)
{
	SIZE_T nSize = audioFrame.channels*audioFrame.samples * 2;
	unsigned int datalen = 0;
	pCircleBuffer->readBuffer(this->pPlayerData, nSize, &datalen);

	if (nSize > 0 && datalen > 0)
	{
		int nMixLen = datalen > nSize ? nSize : datalen;
		memcpy((int16_t*)audioFrame.buffer, (int16_t*)pPlayerData, nMixLen);
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
