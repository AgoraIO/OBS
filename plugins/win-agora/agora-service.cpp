#include <obs-module.h>
#include <obs-service.h>
#include "Agora/agorartcengine.hpp"
#include <map>
struct agora_data {
	char *agora_appid;
	char *agora_certificate;
	char *agora_token;
	long long uid;
	char *publish_url, *key, *channel_name;
	int out_cx, out_cy;
	int fps;
	int video_bitrate;
	std::map<uint32_t, std::pair<int, int>> user_out_resolution;
	bool enableWebSdkInteroperability;
	int audio_channel, sample_rate;
	agora::rtc::CLIENT_ROLE_TYPE client_role;
	std::string log_path;
	bool agora_sdk_capture_mic_audio;
	bool enableAgoraRawDataTimelog;
	unsigned int privilegeExpiredTs = 60;
	bool bRenewToken = false;
	bool muteAllRemoteAudioVideo = false;
	int audioProfile;
	int audioScenario;
};

const char *AgoraService_GetName(void *type_data)
{
	return obs_module_text("");
}

void AgoraService_Update(void *data, obs_data_t *settings)
{
	struct agora_data *service = static_cast<struct agora_data *>(data);
	if (service == nullptr)
		return;
	service->bRenewToken = obs_data_get_bool(settings, "bRenewToken");
	if (service->bRenewToken) {
		service->privilegeExpiredTs =
			obs_data_get_int(settings, "privilegeExpiredTs");
		std::string token =
			AgoraRtcEngine::GetInstance()->CalculateToken(
				service->agora_appid,
				service->agora_certificate,
				service->channel_name, service->uid,
				service->privilegeExpiredTs);
		AgoraRtcEngine::GetInstance()->getRtcEngine()->renewToken(
			token.c_str());
		service->bRenewToken = false;
		obs_data_set_bool(settings, "bRenewToken", false);
	} else {
		if (service->agora_appid)
			bfree(service->agora_appid);

		if (service->agora_certificate) {

			bfree(service->agora_certificate);
			service->agora_certificate = NULL;
		}
		if (service->channel_name)
			bfree(service->channel_name);

		if (service->publish_url)
			bfree(service->publish_url);

		if (service->key)
			bfree(service->key);

		if (service->agora_token)
			bfree(service->agora_token);

		service->uid = obs_data_get_int(settings, "agora_uid");
		service->agora_appid = bstrdup(
			obs_data_get_string(settings, "agora_appid")); //app_id

		service->agora_token =
			bstrdup(obs_data_get_string(settings, "agora_token"));
		if (!strlen(service->agora_token))
			service->agora_certificate = bstrdup(
				obs_data_get_string(settings,
						    "agora_certificate"));

		service->publish_url =
			bstrdup(obs_data_get_string(settings, "agora_url"));
		service->key =
			bstrdup(obs_data_get_string(settings, "agora_key"));
		service->channel_name =
			bstrdup(obs_data_get_string(settings, "agora_channel"));
		service->out_cx = obs_data_get_int(settings, "agora_out_cx");
		service->out_cy = obs_data_get_int(settings, "agora_out_cy");
		service->fps = obs_data_get_int(settings, "fps");

		service->privilegeExpiredTs =
			obs_data_get_int(settings, "privilegeExpiredTs");
		service->privilegeExpiredTs = 60;
		service->video_bitrate =
			obs_data_get_int(settings, "agora_video_bitrate");
		service->enableWebSdkInteroperability = obs_data_get_bool(
			settings, "enableWebSdkInteroperability");

		service->sample_rate =
			obs_data_get_int(settings, "agora_sample_rate");
		service->audio_channel =
			obs_data_get_int(settings, "agora_audio_channel"); //
		service->enableAgoraRawDataTimelog =
			obs_data_get_bool(settings, "agora_log_raw_data_time");

		bool agora_sdk_capture_mic_audio = obs_data_get_bool(
			settings, "agora_sdk_capture_mic_audio");
		AgoraRtcEngine::GetInstance()->agora_sdk_captrue_mic_audio =
			agora_sdk_capture_mic_audio;

		service->muteAllRemoteAudioVideo =
			obs_data_get_bool(settings, "muteAllRemoteAudioVideo");

		if (!AgoraRtcEngine::GetInstance()->bInit &&
		    service->agora_sdk_capture_mic_audio !=
			    agora_sdk_capture_mic_audio) { //
			AgoraRtcEngine::GetInstance()
				->EnableAgoraCaptureMicAudio(
					agora_sdk_capture_mic_audio);
		}

		agora::rtc::CLIENT_ROLE_TYPE role =
			(agora::rtc::CLIENT_ROLE_TYPE)obs_data_get_int(
				settings, "agora_client_role");
		//role
		if (AgoraRtcEngine::GetInstance()->bInit &&
		    service->client_role != role) { //
			AgoraRtcEngine::GetInstance()->setClientRole(role);
		}
		service->client_role = role;

		std::string path =
			obs_data_get_string(settings, "agora_log_path");
		//log
		if (AgoraRtcEngine::GetInstance()->bInit
		    /*&& !service->log_path.empty()*/
		    && service->log_path != path) {
			AgoraRtcEngine::GetInstance()->setLogPath(path);
		}
		service->log_path = path;
		AgoraRtcEngine *agora = AgoraRtcEngine::GetInstance();
		agora->agora_fps = service->fps;
		agora->agora_out_cx = service->out_cx;
		agora->agora_out_cy = service->out_cy;
		agora->agora_video_bitrate = service->video_bitrate;

		service->audioProfile =
			obs_data_get_int(settings, "agora_audio_profile");
		service->audioScenario =
			obs_data_get_int(settings, "agora_audio_scenario");

		bool bLog =
			obs_data_get_bool(settings, "LogAudioVideoTimestamp");

		if (service->enableAgoraRawDataTimelog != bLog) {
			service->enableAgoraRawDataTimelog = bLog;
			AgoraRtcEngine::GetInstance()->enableLogTimestamp(bLog);
		}
	}
}

void *AgoraService_Create(obs_data_t *settings, obs_service_t *service)
{
	if (AgoraRtcEngine::GetInstance() == NULL)
		return nullptr;

	struct agora_data *data = static_cast<struct agora_data *>(
		bzalloc(sizeof(struct agora_data)));
	AgoraService_Update((void *)data, settings);

	AgoraRtcEngine::GetInstance()->agoraService = service;
	return data;
}

void AgoraService_Destroy(void *data)
{
	struct agora_data *service = static_cast<struct agora_data *>(data);
	AgoraRtcEngine::GetInstance()->ReleaseInstance();
	bfree(service->agora_appid);
	bfree(service->channel_name);
	bfree(service->publish_url);
	bfree(service->key);
}

bool AgoraService_Initialize(void *data, obs_output_t *output)
{
	struct agora_data *service_data =
		static_cast<struct agora_data *>(data);
	AgoraRtcEngine *agora_engine = AgoraRtcEngine::GetInstance();

	if (!agora_engine->bInit) {
		if (!agora_engine->InitEngine(
			    service_data
				    ->agora_appid)) // init agora engine failed
			return false;
		agora_engine->bInit = true;
	}

	agora_engine->enableVideo(true);
	agora_engine->setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING);
	agora_engine->setClientRole(
		service_data
			->client_role); //(agora::rtc::CLIENT_ROLE_BROADCASTER);
	agora_engine->enableLocalCameara(false); // stop agora camera capture
	agora_engine->enableLocalRender(false);  // stop agora local render
	agora_engine->keepPreRotation(false);

	return true;
}

void AgoraService_Activate(void *data, obs_data_t *settings)
{
	struct agora_data *service_data =
		static_cast<struct agora_data *>(data);
	AgoraRtcEngine *agora_engine = AgoraRtcEngine::GetInstance();
	agora_engine->EnableWebSdkInteroperability(
		service_data->enableWebSdkInteroperability);
	agora_engine->setVideoProfileEx(service_data->out_cx,
					service_data->out_cy, service_data->fps,
					service_data->video_bitrate);
	//agora_engine->setRecordingAudioFrameParameters(/*44100, 2*/service_data->sample_rate, service_data->audio_channel, service_data->sample_rate / AUDIO_CALLBACK_TIMES * service_data->audio_channel);
	AgoraRtcEngine::GetInstance()->getRtcEngine()->muteAllRemoteVideoStreams(
		service_data->muteAllRemoteAudioVideo);
	AgoraRtcEngine::GetInstance()->getRtcEngine()->muteAllRemoteAudioStreams(
		service_data->muteAllRemoteAudioVideo);
	std::string token = "";
	if (strlen(service_data->agora_token))
		token = service_data->agora_token;
	else if (strlen(service_data->agora_certificate))
		token = agora_engine->CalculateToken(
			service_data->agora_appid,
			service_data->agora_certificate,
			service_data->channel_name, service_data->uid,
			service_data->privilegeExpiredTs);
	agora_engine->SetAudioProfile(service_data->audioProfile, service_data->audioScenario);
	agora_engine->joinChannel(token, service_data->channel_name,
				  service_data->uid);
}

void AgoraService_Deactivate(void *data)
{
	struct agora_data *service_data =
		static_cast<struct agora_data *>(data);
	AgoraRtcEngine *agora_engine = AgoraRtcEngine::GetInstance();

	agora_engine->leaveChannel();
}

void AgoraService_GetDefaults(obs_data_t *settings) {}

obs_properties_t *AgoraService_GetProperties(void *data)
{
	return nullptr;
}

/**
* Called when getting ready to start up an output, before the encoders
* and output are initialized
*
* @param  data    Internal service data
* @param  output  Output context
* @eturn          true to allow the output to start up,
*                 false to prevent output from starting up
*/

const char *AgoraService_GetUrl(void *data)
{
	return nullptr;
}

const char *AgoraService_GetKey(void *data)
{
	return nullptr;
}

const char *AgoraService_GetUserName(void *data)
{
	return nullptr;
}

bool AgoraSetupRemoteVideo(uint32_t uid, void *view)
{
	return AgoraRtcEngine::GetInstance()->setupRemoteVideo(uid, view) == 0;
}

bool AgoraAddPublishStreamUrl(const char *url, bool transcoding)
{
	return AgoraRtcEngine::GetInstance()->AddPublishStreamUrl(
		       url, transcoding) == 0;
}

bool AgoraRemovePublishStreamUrl(const char *url)
{
	return AgoraRtcEngine::GetInstance()->RemovePublishStreamUrl(url) == 0;
}

void RegisterAgoraService()
{
	obs_service_info info = {};
	info.id = "agora_service";
	info.get_name = AgoraService_GetName;
	info.create = AgoraService_Create;
	info.destroy = AgoraService_Destroy;
	info.update = AgoraService_Update;
	info.activate = AgoraService_Activate;
	info.deactivate = AgoraService_Deactivate;
	info.initialize = AgoraService_Initialize;
	info.setup_agora_remote_video = AgoraSetupRemoteVideo;
	info.add_agora_publish_stream_url = AgoraAddPublishStreamUrl;
	info.remove_agora_publish_stream_url = AgoraRemovePublishStreamUrl;
	obs_register_service(&info);
}
