#include <obs-module.h>
#include <obs-encoder.h>
#include "Agora/agorartcengine.hpp"
#include <tchar.h>
static const char *AgoraGetAudioEncoderName(void*)
{
	return obs_module_text("AgoraAudioEnc");
}

static void* AgoraPCM_Create(obs_data_t* settings, obs_encoder_t* encoder )
{
	AgoraRtcEngine::GetInstance()->audioChannel = obs_data_get_int(settings, "ChannelSetup");
	AgoraRtcEngine::GetInstance()->sampleRate = obs_data_get_int(settings, "SampleRate");
	return AgoraRtcEngine::GetInstance()->AgoraAudioObserver_Create();
}

static void AgoraPCM_Destroy(void* data)
{
	AgoraRtcEngine::GetInstance()->AgoraAudioObserver_Destroy();
}

static bool AgoraPCM_Encode(void* data, struct encoder_frame* frame,
struct encoder_packet* packet, bool *receive_packet)
{
	/*CExtendAudioFrameObserver* audioObserver = static_cast<CExtendAudioFrameObserver*>(data);

	int dataLen = frame->frames * 2 * AgoraRtcEngine::GetInstance()->audioChannel;//

	TCHAR szBuf[MAX_PATH] = { 0 };
	_stprintf_s(szBuf, MAX_PATH, _T("AgoraPCM_Encode: datalen=%d \n"), dataLen);
	//OutputDebugString(szBuf
	int64_t audioTime = GetTickCount();
	audioObserver->pCircleBuffer->writeBuffer(frame->data[0], dataLen, audioTime);
	AgoraRtcEngine::GetInstance()->logAudioFrameTimestamp();*/
	
	int dataLen = frame->frames * 2 * AgoraRtcEngine::GetInstance()->audioChannel;//
	char szInfo[MAX_PATH] = { 0 };
	sprintf_s(szInfo, MAX_PATH, "AgoraPCM_Encode: datalen=%d \n", dataLen);
	blog(LOG_INFO, szInfo);
	int64_t audioTime = GetTickCount();
	AgoraRtcEngine::GetInstance()->logAudioFrameTimestamp();
	AgoraRtcEngine::GetInstance()->AgoraAudioObserver_Encode(frame, packet, receive_packet);
	return true;
}

static void AgoraPCM_GetDefaults(obs_data_t *settings)
{
	
}


// static obs_properties_t *AgoraPCM_GetProperties(void *)
// {
// // 	obs_properties_t *props = obs_properties_create();

// // 

// // 	obs_properties_add_int(props, "bitrate",

// // 		obs_module_text("Bitrate"), 96, 192, 32);

// 
// 	return props;
// }


static bool AgoraPCM_GetExtraData(void *data, uint8_t **extra_data, size_t *size)
{
	CExtendAudioFrameObserver *enc = static_cast<CExtendAudioFrameObserver *>(data);

	UINT32 length;
// 	if (enc->ExtraData(extra_data, &length)) {
// 		*size = length;
// 		return true;
// 	}
	return false;
}

//
static void AgoraPCM_GetAudioInfo(void *, struct audio_convert_info *info)
{
	info->format          = AUDIO_FORMAT_16BIT;
	info->samples_per_sec = AgoraRtcEngine::GetInstance()->sampleRate;
	if (AgoraRtcEngine::GetInstance()->audioChannel == 2)
		info->speakers = SPEAKERS_STEREO;
	else
		info->speakers = SPEAKERS_MONO;
}

static size_t AgoraPCM_GetFrameSize(void *data)
{
	UNUSED_PARAMETER(data);
	return AgoraRtcEngine::GetInstance()->sampleRate / AUDIO_CALLBACK_TIMES;;
}

void RegisterAgoraAudioEncoder()
{
	obs_encoder_info agora_pcm_encoder = {};
	agora_pcm_encoder.id       = "agora_pcm";
	agora_pcm_encoder.type     = OBS_ENCODER_AUDIO;
	agora_pcm_encoder.codec    = "PCM";
	agora_pcm_encoder.get_name = AgoraGetAudioEncoderName;
	agora_pcm_encoder.create   = AgoraPCM_Create;
	agora_pcm_encoder.destroy  = AgoraPCM_Destroy;	
	agora_pcm_encoder.encode = AgoraPCM_Encode;
	agora_pcm_encoder.get_defaults   = AgoraPCM_GetDefaults;
//	agora_pcm_encoder.get_properties = AgoraPCM_GetProperties;
	agora_pcm_encoder.get_extra_data = AgoraPCM_GetExtraData;
	agora_pcm_encoder.get_audio_info = AgoraPCM_GetAudioInfo;
	agora_pcm_encoder.get_frame_size = AgoraPCM_GetFrameSize;

	obs_register_encoder(&agora_pcm_encoder);
}



