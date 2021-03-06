#include <obs-module.h>
#include <thread>
#include "../Agora/agorartcengine.hpp"

struct agora_output{
	obs_output_t* output;
	bool stop_thread_active;
};

static const char *agora_output_getname(void *unused)
{
	return "Agora Output";
}


static void *agora_output_create(obs_data_t *settings, obs_output_t *output)
{
	struct agora_output *context = static_cast<struct agora_output*>( bzalloc(sizeof(*context)));
	context->output = output;
	UNUSED_PARAMETER(settings);
	return context;
}

static void agora_output_destroy(void *data)
{
	struct agora_output *context = static_cast<struct agora_output*>(data);
	bfree(context);
}

static bool agora_output_start(void *data)
{
	struct agora_output *context = static_cast<struct agora_output*>(data);

	if (!obs_output_can_begin_data_capture(context->output, 0))
		return false;
	if (!obs_output_initialize_encoders(context->output, 0))
		return false;


	obs_output_begin_data_capture(context->output, 0);
	return true;
}

static void agora_output_stop(void *data, uint64_t ts)
{
	struct agora_output *context = static_cast<struct agora_output*>(data);
	UNUSED_PARAMETER(ts);

	obs_output_end_data_capture(context->output);
}


static void agora_receive_video(void *param, struct video_data *frame)
{

}

static void agora_receive_audio(void *param, struct audio_data *frame)
{
	
}

static uint64_t agora_output_total_bytes(void *data)
{
// 	struct  *output = data;
// 	return output->total_bytes;
}
void agora_output_encoded_packet(void *data, struct encoder_packet *packet)
{

}


//void(*raw_audio2)(void *data, size_t idx, struct audio_data *frames);
void RegisterAgoraOutput()
{
	obs_output_info info = {};
	info.id          = "agora_output";
	info.flags = OBS_OUTPUT_AUDIO | OBS_OUTPUT_ENCODED;//OBS_OUTPUT_AV;//OBS_OUTPUT_AV | OBS_OUTPUT_ENCODED | OBS_OUTPUT_SERVICE;
	info.get_name    = agora_output_getname;
	info.create      = agora_output_create;
	info.destroy     = agora_output_destroy;
	info.start       = agora_output_start;
	info.stop        = agora_output_stop;
	info.encoded_audio_codecs = "pcm";
	//info.encoded_video_codecs = "yuv";
	info.encoded_packet = agora_output_encoded_packet;
 	info.raw_video   = agora_receive_video;
 	info.raw_audio   = agora_receive_audio;
//	AGORA_LOG(LOG_DEBUG, info.id);
	obs_register_output(&info);
}