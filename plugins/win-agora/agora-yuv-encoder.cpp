#include <obs-module.h>
#include <obs-encoder.h>
#include "Agora/agorartcengine.hpp"

static const char *AgoraGetVideoEncoderName(void*)
{
	return obs_module_text("AgoraVideoEnc");
}

static void* AgoroYUV_Create(obs_data_t* settings, obs_encoder_t* encoder)
{
	return AgoraRtcEngine::GetInstance()->AgoraVideoObserver_Create();
}

static void AgoraYUV_Destroy(void* data)
{
	AgoraRtcEngine::GetInstance()->AgoraVideoObserver_Destroy(data);
}

static bool AgoraYUV_Encode(void* data, struct encoder_frame* frame,
struct encoder_packet* packet, bool *receive_packet)
{
//	CExtendVideoFrameObserver* videoObserver = static_cast<CExtendVideoFrameObserver*>(data);
//	AgoraRtcEngine* agora = AgoraRtcEngine::GetInstance();

	AgoraRtcEngine::GetInstance()->pushVideoFrame(frame);
//	if (agora->agora_out_cx && agora->agora_out_cy && agora->agora_out_cx == frame->linesize[0])
//	{

//		//memcpy(videoObserver->m_lpImageBuffer, frame->data[0], agora->agora_out_cx *agora->agora_out_cy * 3 / 2);
//	}
	return true;
}

static void AgoraYUV_GetDefaults(obs_data_t *settings)
{
	UNREFERENCED_PARAMETER(settings);
}

static bool AgoraYUV_GetExtraData(void *data, uint8_t **extra_data, size_t *size)
{
	CExtendAudioFrameObserver *enc = static_cast<CExtendAudioFrameObserver *>(data);
	return false;
}


static void AgoraYUV_GetVideoInfo(void *, struct audio_convert_info *info)
{
	UNREFERENCED_PARAMETER(info);
}


void RegisterAgoraVideoEncoder()
{
	obs_encoder_info agora_yuv_encoder = {};
	agora_yuv_encoder.id       = "agora_yuv";
	agora_yuv_encoder.type     = OBS_ENCODER_VIDEO;
	agora_yuv_encoder.codec    = "PCM";
	agora_yuv_encoder.get_name = AgoraGetVideoEncoderName;
	agora_yuv_encoder.create   = AgoroYUV_Create;
	agora_yuv_encoder.destroy  = AgoraYUV_Destroy;
	agora_yuv_encoder.encode   = AgoraYUV_Encode;

	agora_yuv_encoder.get_defaults   = AgoraYUV_GetDefaults;
//	agora_pcm_encoder.get_properties = AgoraPCM_GetProperties;
	agora_yuv_encoder.get_extra_data = AgoraYUV_GetExtraData;
	agora_yuv_encoder.get_audio_info = AgoraYUV_GetVideoInfo;

	obs_register_encoder(&agora_yuv_encoder);
}



