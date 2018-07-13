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

static void Cut_I420(uint8_t* Src, int x, int y, int srcWidth, int srcHeight, uint8_t* Dst, int desWidth, int desHeight)//图片按位置裁剪    
{
	//得到B图像所在A的坐标    
	int nIndex = 0;
	int BPosX = x;//列    
	int BPosY = y;//行    
	for (int i = 0; i < desHeight; i++)//    
	{
		memcpy(Dst + desWidth * i, Src + (srcWidth*BPosY) + BPosX + nIndex, desWidth);
		nIndex += (srcWidth);
	}

	nIndex = 0;
	uint8_t *pVSour = Src + srcWidth * srcHeight * 5 / 4;
	uint8_t *pVDest = Dst + desWidth * desHeight * 5 / 4;
	for (int i = 0; i < desHeight / 2; i++)//    %
	{
		memcpy(pVDest + desWidth / 2 * i, pVSour + (srcWidth / 2 * BPosY / 2) + BPosX / 2 + nIndex, desWidth / 2);
		nIndex += (srcWidth / 2);
	}

	nIndex = 0;
	uint8_t *pUSour = Src + srcWidth * srcHeight;
	uint8_t *pUDest = Dst + desWidth * desHeight;
	for (int i = 0; i < desHeight / 2; i++)//    
	{
		memcpy(pUDest + desWidth / 2 * i, pUSour + (srcWidth / 2 * BPosY / 2) + BPosX / 2 + nIndex, desWidth / 2);
		nIndex += (srcWidth / 2);
	}
}

static bool AgoraYUV_Encode(void* data, struct encoder_frame* frame,
struct encoder_packet* packet, bool *receive_packet)
{
	CExtendVideoFrameObserver* videoObserver = static_cast<CExtendVideoFrameObserver*>(data);
	AgoraRtcEngine* agora = AgoraRtcEngine::GetInstance();

	if (agora->agora_out_cx && agora->agora_out_cy && agora->agora_out_cx == frame->linesize[0])
	{
		memcpy(videoObserver->m_lpImageBuffer, frame->data[0], agora->agora_out_cx *agora->agora_out_cy * 3 / 2);
		char buf[MAX_PATH] = { 0 };
		
		sprintf(buf, "framewidth=%d,agorawidth=%d,agoraheight=%d", frame->linesize[0], agora->agora_out_cx, agora->agora_out_cy);
		OutputDebugStringA("\nAgoraYUV_Encode:\n");
		OutputDebugStringA(buf);
	}
	//Cut_I420(frame->data[0], 0, 0, 960, 540, videoObserver->m_lpImageBuffer, 480, 270);
	//	AgoraRtcEngine::GetInstance()->AgoraVideoObserver_Encode(data, frame, packet, receive_packet);
	return true;
}

static void AgoraYUV_GetDefaults(obs_data_t *settings)
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


static bool AgoraYUV_GetExtraData(void *data, uint8_t **extra_data, size_t *size)
{
	CExtendAudioFrameObserver *enc = static_cast<CExtendAudioFrameObserver *>(data);
	return false;
}


static void AgoraYUV_GetVideoInfo(void *, struct audio_convert_info *info)
{

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



