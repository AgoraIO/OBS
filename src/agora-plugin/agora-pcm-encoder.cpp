#include <obs-module.h>
#include <obs-encoder.h>
#include "../Agora/agorartcengine.hpp"

static const char *AgoraGetAudioEncoderName(void*)
{
	return obs_module_text("AgoraAudioEnc");
}

static void* AgoraPCM_Create(obs_data_t* settings, obs_encoder_t* encoder )
{
	rtcEngine->AgoraAudioObserver_Create();
	return rtcEngine;
}

static void AgoraPCM_Destroy(void* data)
{
}

static bool AgoraPCM_Encode(void* data, struct encoder_frame* frame,
struct encoder_packet* packet, bool *receive_packet)
{
	AgoraRtcEngine* engine = (AgoraRtcEngine*)data;
	engine->PushAudioFrame(frame);
	return true;
}

static void AgoraPCM_GetDefaults(obs_data_t *settings)
{
	
}


static bool AgoraPCM_GetExtraData(void *data, uint8_t **extra_data, size_t *size)
{
	
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
	info->samples_per_sec = 48000;
	info->speakers        = SPEAKERS_STEREO;
}

static size_t AgoraPCM_GetFrameSize(void *data)
{
	UNUSED_PARAMETER(data);
	return 480;
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



