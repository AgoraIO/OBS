#include <obs-module.h>
#include <util/circlebuf.h>
#include <util/util_uint64.h>
#include "../Agora/agorartcengine.hpp"
#ifndef SEC_TO_NSEC
#define SEC_TO_NSEC 1000000000ULL
#endif

#ifndef MSEC_TO_NSEC
#define MSEC_TO_NSEC 1000000ULL
#endif

#define SETTING_DELAY_MS "delay_ms"

#define TEXT_DELAY_MS obs_module_text("DelayMs")

struct video_plugin_data {
	obs_source_t *context;

	/* contains struct obs_source_frame* */
	struct circlebuf video_frames;

	uint64_t last_video_ts;
	uint64_t interval;
	uint64_t samplerate;
	bool video_delay_reached;
	bool reset_video;
};

static const char *video_plugin_filter_name(void *unused)
{
	UNUSED_PARAMETER(unused);
	return obs_module_text("VideoPluginFilter");
}

static void free_video_data(struct video_plugin_data *filter,
			    obs_source_t *parent)
{
	while (filter->video_frames.size) {
		struct obs_source_frame *frame;

		circlebuf_pop_front(&filter->video_frames, &frame,
				    sizeof(struct obs_source_frame *));
		obs_source_release_frame(parent, frame);
	}
}

static void video_plugin_filter_update(void *data, obs_data_t *settings)
{
	struct video_plugin_data *filter = (struct video_plugin_data *)data;
	uint64_t new_interval =
		(uint64_t)obs_data_get_int(settings, SETTING_DELAY_MS) *
		MSEC_TO_NSEC;

	if (new_interval < filter->interval)
		free_video_data(filter, obs_filter_get_parent(filter->context));

	filter->reset_video = true;
	filter->interval = new_interval;
	filter->video_delay_reached = false;
}

static void *video_plugin_filter_create(obs_data_t *settings,
				       obs_source_t *context)
{
	struct video_plugin_data *filter = (struct video_plugin_data *)bzalloc(sizeof(*filter));
	filter->context = context;
	video_plugin_filter_update(filter, settings);
	return filter;
}

static void video_plugin_filter_destroy(void *data)
{
	struct video_plugin_data *filter = (struct video_plugin_data *)data;
	circlebuf_free(&filter->video_frames);
	bfree(data);
}

static obs_properties_t *video_plugin_filter_properties(void *data)
{
	//obs_properties_t *props = obs_properties_create();

//	obs_property_t *p = obs_properties_add_int(props, SETTING_DELAY_MS,
//						   TEXT_DELAY_MS, 0, 20000, 1);
//	obs_property_int_set_suffix(p, " ms");

	UNUSED_PARAMETER(data);
	return nullptr;
}

static void video_plugin_filter_remove(void* data, obs_source_t* parent)
{
	struct video_plugin_data* filter = (struct video_plugin_data *)data;

	free_video_data(filter, parent);
}

/* due to the fact that we need timing information to be consistent in order to
 * measure the current interval of data, if there is an unexpected hiccup or
 * jump with the timestamps, reset the cached delay data and start again to
 * ensure that the timing is consistent */
static inline bool is_timestamp_jump(uint64_t ts, uint64_t prev_ts)
{
	return ts < prev_ts || (ts - prev_ts) > SEC_TO_NSEC;
}

static struct obs_source_frame *
video_plugin_filter_video(void *data, struct obs_source_frame *frame)
{
	/*struct video_plugin_data* filter = (struct video_plugin_data*)data;
	obs_source_t *parent = obs_filter_get_parent(filter->context);
	struct obs_source_frame *output;
	uint64_t cur_interval;

	if (filter->reset_video ||
	    is_timestamp_jump(frame->timestamp, filter->last_video_ts)) {
		free_video_data(filter, parent);
		filter->video_delay_reached = false;
		filter->reset_video = false;
	}

	filter->last_video_ts = frame->timestamp;
	if (!filter->video_delay_reached)
		filter->video_delay_reached = true;*/

	rtcEngine->PushCameraVideoFrame(frame);

	return frame;
}
void video_plugin_filter_load(void* data, obs_data_t* settings)
{

}
void RegistePluginVideoSource()
{
	struct obs_source_info video_plugin_filter = {};
	video_plugin_filter.id = "video_plugin_filter";
	video_plugin_filter.type = OBS_SOURCE_TYPE_FILTER;
	video_plugin_filter.output_flags = OBS_SOURCE_VIDEO | OBS_SOURCE_ASYNC;
	video_plugin_filter.get_name = video_plugin_filter_name;
	video_plugin_filter.create = video_plugin_filter_create;
	video_plugin_filter.destroy = video_plugin_filter_destroy;
	video_plugin_filter.update = video_plugin_filter_update;
	video_plugin_filter.get_properties = video_plugin_filter_properties;
	video_plugin_filter.filter_video = video_plugin_filter_video;
	video_plugin_filter.filter_remove = video_plugin_filter_remove;
	video_plugin_filter.load = video_plugin_filter_load;
	obs_register_source(&video_plugin_filter);
}