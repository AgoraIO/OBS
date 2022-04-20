#include "agorartcengine.hpp"

#include <chrono>
#include "obs.h"
#include <libyuv.h>

using namespace agora::rtc;
using namespace agora;

int64_t get_time_stamp()
{
	std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
	std::chrono::milliseconds mic = std::chrono::duration_cast<std::chrono::milliseconds>(d);
	return mic.count();
}

class AgoraRtcEngineEvent :public QObject,
	public IRtcEngineEventHandler
{
	AgoraRtcEngine &m_engine;
public:
	AgoraRtcEngineEvent(AgoraRtcEngine &engine) : m_engine(engine){}
	
	virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override 
	{
		emit m_engine.onJoinChannelSuccess(channel, uid, elapsed);
	}

	virtual void onLastmileQuality(int quality) override
	{
		emit m_engine.onLastmileQuality(quality);
	}
	virtual void onLeaveChannel(const RtcStats &stats) override
	{
		emit m_engine.onLeaveChannel(stats);
	}

	virtual void onError(int err, const char *msg) override
	{
		emit m_engine.onError(err, msg);
	}

	virtual void onUserJoined(uid_t uid, int elapsed) override 
	{
		emit m_engine.onUserJoined(uid, elapsed);
	}

	virtual void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) override
	{
		emit m_engine.onUserOffline(uid, reason);
	}

	virtual void onFirstRemoteVideoDecoded(uid_t uid, int width, int height,
		int elapsed) override
	{
		//emit m_engine.onFirstRemoteVideoDecoded(uid, width, height, elapsed);
	}

	virtual void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed) override
	{
		emit m_engine.onFirstRemoteVideoFrame(uid, width, height, elapsed);
	}

	virtual void onConnectionStateChanged( CONNECTION_STATE_TYPE state,	CONNECTION_CHANGED_REASON_TYPE reason) override
	{
		emit m_engine.onConnectionStateChanged((int)state, (int)reason);
	}

	virtual void onRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed) override
	{
		emit m_engine.onRemoteVideoStateChanged(uid, (int)state, (int)reason, elapsed);
	}

	virtual void onRtmpStreamingStateChanged(const char *url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR_TYPE errCode) override
	{
		emit m_engine.onRtmpStreamingStateChanged(url,  state, errCode);
	}

	virtual void onRtcStats(const RtcStats &stats) override
	{
		emit m_engine.onSystemCPU(stats.cpuTotalUsage);
	}
};

class CameraRtcEngineEvent :public QObject,
	public IRtcEngineEventHandler
{
	AgoraRtcEngine* m_engine;
public:
	CameraRtcEngineEvent(AgoraRtcEngine* engine) : m_engine(engine) {}
	virtual void onConnectionStateChanged(CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason) override
	{
		emit m_engine->onCameraConnectionStateChanged((int)state, (int)reason);
	}

	virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override
	{
		emit m_engine->onCameraJoinChannelSuccess(channel, uid, elapsed);
	}

	virtual void onError(int err, const char* msg)
	{

	}
};

AgoraRtcEngine *AgoraRtcEngine::m_agoraEngine = nullptr;
agora::media::IAudioFrameObserver::AudioFrame AgoraRtcEngine::m_externalAudioframe;


void copy_frame_data_line(uint8_t* dst, int line_size,
	const struct video_data* src,
	uint32_t plane, uint32_t y)
{
	uint32_t pos_src = y * src->linesize[plane];
	uint32_t pos_dst = y * line_size;
	uint32_t bytes = line_size < src->linesize[plane]
		? line_size
		: src->linesize[plane];

	memcpy(dst + pos_dst, src->data[plane] + pos_src, bytes);
}

void copy_frame_data_plane(uint8_t* dst, int line_size,
	const struct video_data* src,
	uint32_t plane, uint32_t lines)
{
	if (line_size != src->linesize[plane]) {
		for (uint32_t y = 0; y < lines; y++)
			copy_frame_data_line(dst, line_size, src, plane, y);
	}
	else {
		memcpy(dst, src->data[plane],
			line_size * (size_t)lines);
	}
}


void copy_frame_data_line2(uint8_t* dst, int line_size,
	const struct obs_source_frame* src,
	uint32_t plane, uint32_t y)
{
	uint32_t pos_src = y * src->linesize[plane];
	uint32_t pos_dst = y * line_size;
	uint32_t bytes = line_size < src->linesize[plane]
		? line_size
		: src->linesize[plane];

	memcpy(dst + pos_dst, src->data[plane] + pos_src, bytes);
}

void copy_frame_data_plane2(uint8_t* dst, int line_size,
	const struct obs_source_frame* src,
	uint32_t plane, uint32_t lines)
{
	if (line_size != src->linesize[plane]) {
		for (uint32_t y = 0; y < lines; y++)
			copy_frame_data_line2(dst, line_size, src, plane, y);
	}
	else {
		memcpy(dst, src->data[plane],
			line_size * (size_t)lines);
	}
}

std::string CurrentTimeString()
{
	using namespace std::chrono;

	struct tm tstruct;

	char buf[80] = { 0 };
	auto tp = system_clock::now();
	auto now = system_clock::to_time_t(tp);
	tstruct = *localtime(&now);
	asctime(&tstruct);
	sprintf(buf, "obs_agora_%d-%02d-%d_%d-%d-%d"
		, tstruct.tm_year + 1900, tstruct.tm_mon + 1, tstruct.tm_mday
		, tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec);
	return buf;
}

AgoraRtcEngine *AgoraRtcEngine::GetInstance()
{
	if (m_agoraEngine == nullptr)
		m_agoraEngine = new AgoraRtcEngine;

	return m_agoraEngine;
}

void AgoraRtcEngine::ReleaseInstance()
{
	if (nullptr != m_agoraEngine) {
		delete m_agoraEngine;
		m_agoraEngine = nullptr;
	}
}

AgoraRtcEngine::AgoraRtcEngine()
	: m_eventHandler(new AgoraRtcEngineEvent(*this))
	, m_eventHandlerCamera(new CameraRtcEngineEvent(this))
	, m_sampleRate(48000)
	, m_audioChannel(2)
	, m_externalAudioFrameSize(480 * 2 * 2)
	, m_externalVideoFrameSize(640 * 480 * 3 / 2)
	, m_audioDeviceManager(nullptr)
	, m_initialize(false)
	, m_joined(false)
{
	m_externalAudioframe.buffer = NULL;
	m_externalVideoFrame.buffer = NULL;
	qRegisterMetaType<RtcStats>();
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_I420, "VIDEO_FORMAT_I420"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_NV12, "VIDEO_FORMAT_NV12"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_YVYU, "VIDEO_FORMAT_YVYU"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_YUY2, "VIDEO_FORMAT_YUY2"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_UYVY, "VIDEO_FORMAT_UYVY"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_RGBA, "VIDEO_FORMAT_RGBA"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_BGRA, "VIDEO_FORMAT_BGRA"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_BGRX, "VIDEO_FORMAT_BGRX"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_Y800, "VIDEO_FORMAT_Y800"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_I444, "VIDEO_FORMAT_I444"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_BGR3, "VIDEO_FORMAT_BGR3"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_I422, "VIDEO_FORMAT_I422"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_I40A, "VIDEO_FORMAT_I40A"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_I42A, "VIDEO_FORMAT_I42A"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_YUVA, "VIDEO_FORMAT_YUVA"));
	mapOBSVideoFormat.insert(std::make_pair(VIDEO_FORMAT_AYUV, "VIDEO_FORMAT_AYUV"));

	mapVideoFormat.insert(std::make_pair(agora::media::base::VIDEO_PIXEL_I420, "VIDEO_PIXEL_I420"));
	mapVideoFormat.insert(std::make_pair(agora::media::base::VIDEO_PIXEL_BGRA, "VIDEO_PIXEL_BGRA"));
	mapVideoFormat.insert(std::make_pair(agora::media::base::VIDEO_PIXEL_NV21, "VIDEO_PIXEL_NV21"));
	mapVideoFormat.insert(std::make_pair(agora::media::base::VIDEO_PIXEL_RGBA, "VIDEO_PIXEL_RGBA"));
	mapVideoFormat.insert(std::make_pair(agora::media::base::VIDEO_PIXEL_NV12, "VIDEO_PIXEL_NV12"));
	mapVideoFormat.insert(std::make_pair(agora::media::base::VIDEO_TEXTURE_2D, "VIDEO_TEXTURE_2D"));
	mapVideoFormat.insert(std::make_pair(agora::media::base::VIDEO_TEXTURE_OES, "VIDEO_TEXTURE_OES"));
	mapVideoFormat.insert(std::make_pair(agora::media::base::VIDEO_PIXEL_I422, "VIDEO_PIXEL_I422"));

	audioScenarios.push_back(AUDIO_SCENARIO_DEFAULT);
	audioScenarios.push_back(AUDIO_SCENARIO_NUM);
	audioScenarios.push_back(AUDIO_SCENARIO_GAME_STREAMING);
	audioScenarios.push_back(AUDIO_SCENARIO_CHATROOM);
	audioScenarios.push_back(AUDIO_SCENARIO_HIGH_DEFINITION);
	audioScenarios.push_back(AUDIO_SCENARIO_CHORUS);
	audioScenarios.push_back(AUDIO_SCENARIO_NUM);
}

AgoraRtcEngine::~AgoraRtcEngine()
{
	Release();
}

bool AgoraRtcEngine::InitEngine(std::string appid)
{
	agora::rtc::RtcEngineContext context;
	context.eventHandler = m_eventHandler.get();
	context.appId = appid.c_str();
	struct calldata params;
	calldata_init(&params);

	if (*context.appId == '\0') {
		calldata_set_int(&params, "error", -1);
		return false;
	}

	if (!m_rtcEngine)
		m_rtcEngine = (agora::rtc::IRtcEngineEx*)createAgoraRtcEngine();

	int ret = m_rtcEngine->initialize(context);
	if (0 != ret) {
		blog(LOG_ERROR, "rtc engine initialize failed");
		return false;
	}

	SetExternalVideoFrame();

	m_rtcEngine->queryInterface(agora::rtc::AGORA_IID_MEDIA_ENGINE,
		(void**)&m_pMediaEngine);
	m_rtcEngine->setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING);
	m_rtcEngine->enableVideo();
	m_rtcEngine->setClientRole(CLIENT_ROLE_BROADCASTER);
	m_pMediaEngine->setExternalVideoSource(true, false);
	m_pMediaEngine->setExternalAudioSource(true, 48000, 2);

	m_audioDeviceManager = new AAudioDeviceManager(m_rtcEngine);
	m_initialize = true;
	return true;
}

void AgoraRtcEngine::Release()
{
	if (m_pMediaEngine)
		m_pMediaEngine->release();

	if (m_audioDeviceManager) {
		delete m_audioDeviceManager;
		m_audioDeviceManager = NULL;
	}

	if (m_externalAudioframe.buffer) {
		delete[] m_externalAudioframe.buffer;
		m_externalAudioframe.buffer = nullptr;
	}

	if (m_externalVideoFrame.buffer) {
		delete[] m_externalVideoFrame.buffer;
		m_externalVideoFrame.buffer = nullptr;
	}

	if (m_externalVideoFrameCamera.buffer) {
		delete[] m_externalVideoFrameCamera.buffer;
		m_externalVideoFrameCamera.buffer = nullptr;
	}

	if (m_rtcEngine) {
		m_rtcEngine->release(true);
		m_rtcEngine = NULL;
	}

	m_initialize = false;
}

bool AgoraRtcEngine::SetClientRole(agora::rtc::CLIENT_ROLE_TYPE role,
				   LPCSTR lpPermissionKey)
{
	return m_rtcEngine->setClientRole(role) == 0;
}

int AgoraRtcEngine::SetChannelProfile(CHANNEL_PROFILE_TYPE profile)
{
	return m_rtcEngine->setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING) == 0;
}

int AgoraRtcEngine::JoinChannel(const std::string &key, const std::string &channel, 
	unsigned int uid, bool audioProfile, bool enableDual, bool muteAudio , bool muteVideo, bool loopbackRecording)
{
	if (m_joined)
		return 0;

	if (audioProfile) {
		agora::rtc::AUDIO_PROFILE_TYPE profile = agora::rtc::AUDIO_PROFILE_MUSIC_STANDARD;
		if (m_audioChannel == 1 && !m_bHighQuality) {
			profile = AUDIO_PROFILE_MUSIC_STANDARD;
		}
		else if (m_audioChannel == 2 && !m_bHighQuality) {
			profile = AUDIO_PROFILE_MUSIC_STANDARD_STEREO;
		}
		else if (m_audioChannel == 1 && m_bHighQuality) {
			profile = AUDIO_PROFILE_MUSIC_HIGH_QUALITY;
		}
		else if (m_audioChannel == 2 && m_bHighQuality) {
			profile = AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO;
		}
		m_rtcEngine->setAudioProfile(profile, m_scenario);
	}

	ChannelMediaOptions options;
	options.autoSubscribeAudio = muteAudio;
	options.autoSubscribeVideo = muteVideo;
	options.publishCustomAudioTrack = true;
	options.publishCustomVideoTrack = true;
	options.publishCameraTrack = false;
	options.publishAudioTrack = false;
	options.clientRoleType = CLIENT_ROLE_BROADCASTER;
	options.channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
	
	m_rtcEngine->enableDualStreamMode(VIDEO_SOURCE_CUSTOM, enableDual);
	blog(LOG_INFO, "JoinChannel: channel=%s, uid=%u", channel.c_str(), uid);
	m_rtcEngine->enableLoopbackRecording(loopbackRecording);
	int r = m_rtcEngine->joinChannel(key.c_str(), channel.c_str(), uid, options);//JoinChannel(key.data(), channel.data(), "", uid, options);//
	return r;
}

int AgoraRtcEngine::JoinChannel(const std::string & key, const std::string & channel, unsigned uid)
{
	ChannelMediaOptions options;
	options.autoSubscribeAudio = false;
	options.autoSubscribeVideo = false;
	options.publishCustomAudioTrack = false;
	options.publishCustomVideoTrack = true;
	options.publishCameraTrack = false;
	options.publishAudioTrack = false;
	options.clientRoleType = CLIENT_ROLE_BROADCASTER;
	options.channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
	blog(LOG_INFO, "joinChannelEx: connection channel=%s, uid=%d", m_connection.channelId, m_connection.localUid);
	int r = m_rtcEngine->joinChannelEx(key.c_str(), m_connection, options, m_eventHandlerCamera.get());//JoinChannel(key.data(), channel.data(), "", uid, options);//
	m_cameraJoined = true;
	return r;
}

int AgoraRtcEngine::LeaveChannel()
{
	if (!m_initialize || !m_joined)
		return -1;
	m_joined = false;
	int r = m_rtcEngine->leaveChannel();

	m_firstAudioFrame  = true;
	m_firstVideoFrame  = true;
	m_firstCameraVideo = true;
	if (m_pcm) {
		fclose(m_pcm);
		m_pcm = nullptr;
	}
	return r;
}

int AgoraRtcEngine::LeaveChannelCamera()
{
	m_cameraJoined = false;
	return m_rtcEngine->leaveChannelEx(m_connection);
}

void AgoraRtcEngine::SetConnection(const std::string& channel, unsigned uid)
{
	m_channelId = channel;
	m_connection.channelId = m_channelId.c_str();
	m_localCameraUID = uid;
	m_connection.localUid = m_localCameraUID;
}

int AgoraRtcEngine::EnableVideo(bool enabled)
{
	return enabled ? m_rtcEngine->enableVideo() : m_rtcEngine->disableVideo();
}

int AgoraRtcEngine::SetupRemoteVideo(unsigned int uid, void *view)
{
	view_t v = reinterpret_cast<view_t>(view);
	VideoCanvas canvas; 
	canvas.view = v;
	canvas.renderMode = agora::media::base::RENDER_MODE_HIDDEN;
	canvas.uid = uid;

	return m_rtcEngine->setupRemoteVideo(canvas);
}

bool AgoraRtcEngine::SetVideoEncoder(int nWidth, int nHeight, int nFrameRate,
	int nBitRate, bool Agora)
{
	VideoEncoderConfiguration config;
	config.dimensions.width = nWidth;
	config.dimensions.height = nHeight;
	config.frameRate = (FRAME_RATE)nFrameRate;
	config.bitrate = nBitRate;
	config.orientationMode = nWidth < nHeight ? ORIENTATION_MODE_FIXED_PORTRAIT : ORIENTATION_MODE_FIXED_LANDSCAPE;
	m_videoFrameRate = nFrameRate;
	return m_rtcEngine->setVideoEncoderConfiguration(config) == 0 ? true : false;
}

bool AgoraRtcEngine::SetCameraEncoderConfiguration(int w, int h, int fps, int bitrate)
{
	VideoEncoderConfiguration config;
	config.dimensions.width = w;
	config.dimensions.height = h;
	config.frameRate = (FRAME_RATE)fps;
	config.bitrate = bitrate;
	config.orientationMode = ORIENTATION_MODE_ADAPTIVE;
	int nRet = m_rtcEngine->setVideoEncoderConfigurationEx(config, m_connection);

	return nRet == 0 ? true : false;
}

void AgoraRtcEngine::SetAudioProfile(int scenario, int channels, bool bHighQuality)
{
	m_scenario = audioScenarios[scenario];
	m_audioChannel = channels;
	m_bHighQuality = bHighQuality;
}

int AgoraRtcEngine::GetPalyoutDeviceVolume()
{
	AAudioDeviceManager audioDeviceManager(m_rtcEngine);
	if (!audioDeviceManager)
		return 0;
	int vol = 0;
	if (audioDeviceManager->getPlaybackDeviceVolume(&vol) == 0)
		return vol;
	return 0;
}

int AgoraRtcEngine::SetPalyoutDeviceVolume(int volume)
{
	AAudioDeviceManager audioDeviceManager(m_rtcEngine);
	if (!audioDeviceManager)
		return -1;
	return audioDeviceManager->setPlaybackDeviceVolume(volume);
}

bool AgoraRtcEngine::GetPlayoutDevices(std::vector<DEVICEINFO>& devices)
{
	if (!m_initialize || !m_audioDeviceManager || !m_audioDeviceManager->get())
		return false;

	IAudioDeviceCollection* playoutDevice = (*m_audioDeviceManager)->enumeratePlaybackDevices();

	if (!playoutDevice)
		return false;

	for (int i = 0; i < playoutDevice->getCount(); ++i) {
		char id[MAX_DEVICE_ID_LENGTH] = { 0 };
		char name[MAX_DEVICE_ID_LENGTH] = { 0 };
		playoutDevice->getDevice(i, name, id);
		DEVICEINFO info;
		info.id = id;
		info.name = name;
		devices.push_back(info);
	}
	return true;
}

void AgoraRtcEngine::SetPlayoutDevice(const char* id)
{
	(*m_audioDeviceManager)->setPlaybackDevice(id);
}

int AgoraRtcEngine::AddPublishStreamUrl(const char *url,
					bool transcodingEnabled)
{
	return m_rtcEngine->addPublishStreamUrl(url, transcodingEnabled);
}
int AgoraRtcEngine::RemovePublishStreamUrl(const char *url)
{
	return m_rtcEngine->removePublishStreamUrl(url);
}
int AgoraRtcEngine::SetLiveTranscoding(const LiveTranscoding &transcoding)
{
	return m_rtcEngine->setLiveTranscoding(transcoding);
}

void AgoraRtcEngine::EnableLastmileTest(bool bEnable)
{
	LastmileProbeConfig config;
	if (bEnable)
		m_rtcEngine->startLastmileProbeTest(config);
	else
		m_rtcEngine->stopLastmileProbeTest();
}

void AgoraRtcEngine::MuteAllRemoteVideo(bool bMute)
{
	m_rtcEngine->muteAllRemoteVideoStreams(bMute);
}

void AgoraRtcEngine::MuteAllRemoteAudio(bool bMute)
{
	m_rtcEngine->muteAllRemoteAudioStreams(bMute);
}

void AgoraRtcEngine::MuteRemoteVideo(unsigned int uid, bool bMute)
{
	m_rtcEngine->muteRemoteVideoStream(uid, bMute);
}

void AgoraRtcEngine::SetPcmInfo(bool b, std::string path)
{
	m_savePcm = b; 
	m_pcmPath = path;
	if (m_joined) {
		if (m_pcm && !m_savePcm) {
			fclose(m_pcm);
			m_pcm = nullptr;
		}
		else if (!m_pcm && m_savePcm) {
			std::string filePath = m_pcmPath + CurrentTimeString();
			filePath += ".pcm";
			m_pcm = fopen(filePath.c_str(), "ab+");
		}
	}
}

void AgoraRtcEngine::SetVideoBuffer(int second)
{
	AParameter apm(m_rtcEngine);
	char szParam[200] = { 0 };
	sprintf(szParam, "{\"rtc.media_send_delay\":%d}", second * 1000);
	apm->setParameters(szParam);
}

void* AgoraRtcEngine::AgoraAudioObserver_Create()
{
	m_externalAudioframe.channels = 2;
	m_externalAudioframe.samplesPerChannel = 480;
	m_externalAudioframe.samplesPerSec = 48000;
	m_externalAudioframe.bytesPerSample = TWO_BYTES_PER_SAMPLE;
	m_externalAudioframe.type =
		agora::media::IAudioFrameObserver::FRAME_TYPE_PCM16;
	m_externalAudioframe.buffer =
		new uint8_t[m_externalAudioframe.samplesPerChannel * 2 * 2];
	memset(m_externalAudioframe.buffer, 0, m_externalAudioframe.samplesPerChannel * 2 * 2);
	m_externalAudioframe.avsync_type = 0;
	m_externalAudioframe.renderTimeMs = 0;

	m_externalAudioFrameSize = m_externalAudioframe.samplesPerChannel * 2 * 2;
	return &m_externalAudioframe;
}

void AgoraRtcEngine::AgoraAudioObserver_Destroy()
{
	if (m_pMediaEngine == nullptr)
		return;

	if (m_externalAudioframe.buffer) {
		delete[] m_externalAudioframe.buffer;
		m_externalAudioframe.buffer = nullptr;
	}
}

void AgoraRtcEngine::PushAudioFrame(struct encoder_frame* frame)
{
	if (!m_initialize || !m_joined)
		return;

	if (m_savePcm) {
		if (!m_pcm) {
			std::string filePath = m_pcmPath + CurrentTimeString();
			filePath += ".pcm";
			m_pcm = fopen(filePath.c_str(), "ab+");
		}

		if (m_pcm) 
			fwrite(frame->data[0], 1, frame->linesize[0], m_pcm);
		else
			blog(LOG_INFO, "agora tool m_pcm save failed");
	}

	int64_t renderTimeMs = get_time_stamp();
	if (m_firstAudioFrame) {
		blog(LOG_INFO, "Agora First PushAudioFrame timestamp: %llu ms(system time)", renderTimeMs);
		m_firstAudioFrame = false;
		m_firstAudioFrameTs = renderTimeMs;
	}

	m_externalAudioframe.renderTimeMs = 0;
	memcpy(m_externalAudioframe.buffer, frame->data[0], frame->linesize[0]);
	int ret = m_pMediaEngine->pushAudioFrame(AUDIO_RECORDING_SOURCE,
		&m_externalAudioframe, false);

	m_audioFrameCount++;
	if (m_audioFrameCount % (m_logInterval * 100) == 0) {
		blog(LOG_INFO, "[%llu:] Audio PushAudioFrame timestamp: %llu ms, audio frame count: %llu,interval(time=%lfs)"
			, m_audioFrameCount / 100, renderTimeMs, m_audioFrameCount, (renderTimeMs - m_firstAudioFrameTs)/(double)1000);
	}
}

void AgoraRtcEngine::SetExternalVideoFrame()
{
	struct obs_video_info ovi;
	obs_get_video_info(&ovi);
	m_agoraOutCX = ovi.output_width;
	m_agoraOutCY = ovi.output_height;

	m_externalVideoFrame.buffer = NULL;
	m_externalVideoFrame.cropLeft = 0;
	m_externalVideoFrame.cropTop = 0;
	m_externalVideoFrame.cropRight = 0;
	m_externalVideoFrame.cropBottom = 0;


	m_externalVideoFrame.rotation = 0;
	m_externalVideoFrame.height = m_agoraOutCY;
	m_externalVideoFrame.stride = (m_agoraOutCX << 4) >> 4;
	m_externalVideoFrame.timestamp = 0;
	m_externalVideoFrame.type = agora::media::base::ExternalVideoFrame::VIDEO_BUFFER_RAW_DATA;
	m_format = ovi.output_format;
	if (ovi.output_format == VIDEO_FORMAT_I420) {
		m_externalVideoFrame.format =
			agora::media::base::VIDEO_PIXEL_I420;
		m_externalVideoFrame.buffer = new uint8_t[m_externalVideoFrame.stride * m_externalVideoFrame.height * 3 / 2];
	}
	else if (ovi.output_format == VIDEO_FORMAT_NV12) {
		m_externalVideoFrame.format =
			agora::media::base::VIDEO_PIXEL_NV12;
		m_externalVideoFrame.buffer = new uint8_t[m_externalVideoFrame.stride * m_externalVideoFrame.height * 3 / 2];
	}
	else if (ovi.output_format == VIDEO_FORMAT_RGBA) {
		m_externalVideoFrame.format =
			agora::media::base::VIDEO_PIXEL_BGRA;
		m_externalVideoFrame.buffer = new uint8_t[m_externalVideoFrame.stride * m_externalVideoFrame.height * 4];
	}
	else if (ovi.output_format == VIDEO_FORMAT_I444) {
		m_externalVideoFrame.format =
			agora::media::base::VIDEO_PIXEL_BGRA;
		m_externalVideoFrame.buffer = new uint8_t[m_externalVideoFrame.stride * m_externalVideoFrame.height * 4];
	}
}

void AgoraRtcEngine::PushVideoFrame(struct video_data* frame)
{
	if (!m_initialize || !m_joined)
		return;

	struct obs_video_info ovi;
	obs_get_video_info(&ovi);

	if (m_externalVideoFrame.stride != ((ovi.output_width << 4) >> 4)
		|| m_externalVideoFrame.height != ovi.output_height
		|| m_format != ovi.output_format) {
		delete[] m_externalVideoFrame.buffer;
		m_externalVideoFrame.buffer = nullptr;
		SetExternalVideoFrame();
	}

	uint8_t* dst = (uint8_t*)m_externalVideoFrame.buffer;
	switch (ovi.output_format) {
	case VIDEO_FORMAT_I420: {

		copy_frame_data_plane(dst, m_externalVideoFrame.stride, frame, 0, m_externalVideoFrame.height);
		dst += m_externalVideoFrame.stride * m_externalVideoFrame.height;
		copy_frame_data_plane(dst, m_externalVideoFrame.stride / 2, frame, 1, m_externalVideoFrame.height / 2);
		dst += m_externalVideoFrame.stride * m_externalVideoFrame.height / 4;
		copy_frame_data_plane(dst, m_externalVideoFrame.stride / 2, frame, 2, m_externalVideoFrame.height / 2);
	}
	    break;
	case VIDEO_FORMAT_NV12: {
		copy_frame_data_plane(dst, m_externalVideoFrame.stride, frame, 0, m_externalVideoFrame.height);
		dst += m_externalVideoFrame.stride * m_externalVideoFrame.height;
		copy_frame_data_plane(dst, m_externalVideoFrame.stride, frame, 1, m_externalVideoFrame.height / 2);
	}
		break;
	case VIDEO_FORMAT_RGBA:
		libyuv::ABGRToARGB(frame->data[0], frame->linesize[0],
			(uint8_t*)m_externalVideoFrame.buffer, frame->linesize[0],
			ovi.output_width, ovi.output_height);
		//copy_frame_data_plane(dst, m_externalVideoFrame.stride * 4, frame, 0, m_externalVideoFrame.height);
		break;

	case VIDEO_FORMAT_I444:
		libyuv::I444ToARGB(
			frame->data[0], frame->linesize[0],
			frame->data[1], frame->linesize[1],
			frame->data[2], frame->linesize[2],
			(uint8_t*)m_externalVideoFrame.buffer,
			m_externalVideoFrame.stride * 4,
			ovi.output_width, ovi.output_height);
		break;
	}
	m_externalVideoFrame.timestamp = get_time_stamp();
	m_pMediaEngine->pushVideoFrame(&m_externalVideoFrame);
	if (m_firstVideoFrame) {
		blog(LOG_INFO, "Agora First PushVideoFrame timestamp: %llu ms(system time)", m_externalVideoFrame.timestamp);
		m_firstVideoFrame = false;
		m_firstVideoFrameTs = m_externalVideoFrame.timestamp;
	}

	m_videoFrameCount++;
	if (m_videoFrameCount % (m_logInterval * m_videoFrameRate) == 0) {
		blog(LOG_INFO, "[%llu:]Video PushVideoFrame timestamp: %llu ms, video frame count: %llu,interval(time=%lfs)"
			, m_videoFrameCount / m_videoFrameRate, m_externalVideoFrame.timestamp, m_videoFrameCount, (m_externalVideoFrame.timestamp - m_firstVideoFrameTs) / (double)1000);
	}
}

void AgoraRtcEngine::SetExternalVideoFrameCamera(struct obs_source_frame* frame)
{
	m_externalVideoFrameCamera.buffer = NULL;
	m_externalVideoFrameCamera.cropLeft = 0;
	m_externalVideoFrameCamera.cropTop = 0;
	m_externalVideoFrameCamera.cropRight = 0;
	m_externalVideoFrameCamera.cropBottom = 0;

	m_externalVideoFrameCamera.rotation = 0;
	m_externalVideoFrameCamera.height = frame->height;
	m_externalVideoFrameCamera.stride = frame->width;
	m_externalVideoFrameCamera.timestamp = 0;
	m_externalVideoFrameCamera.type = agora::media::base::ExternalVideoFrame::VIDEO_BUFFER_RAW_DATA;
	m_camera_format = frame->format;
	if (frame->format == VIDEO_FORMAT_I420) {
		m_externalVideoFrameCamera.format =
			agora::media::base::VIDEO_PIXEL_I420;
		m_externalVideoFrameCamera.buffer = new uint8_t[m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height * 3 / 2];
	}
	else if (frame->format == VIDEO_FORMAT_NV12) {
		m_externalVideoFrameCamera.format =
			agora::media::base::VIDEO_PIXEL_NV12;
		m_externalVideoFrameCamera.buffer = new uint8_t[m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height * 3 / 2];
	}
	else if (frame->format == VIDEO_FORMAT_BGRA
		|| frame->format == VIDEO_FORMAT_BGRX) {
		m_externalVideoFrameCamera.format =
			agora::media::base::VIDEO_PIXEL_BGRA;
		m_externalVideoFrameCamera.buffer = new uint8_t[m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height * 4];
		if (frame->format == VIDEO_FORMAT_BGRX)
			m_externalVideoFrameCamera.rotation = 180;
	}

	else if (frame->format == VIDEO_FORMAT_RGBA) {
		m_externalVideoFrameCamera.format =
			agora::media::base::VIDEO_PIXEL_RGBA;
		m_externalVideoFrameCamera.buffer = new uint8_t[m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height * 4];
	}
	else if (frame->format == VIDEO_FORMAT_I444) {
		m_externalVideoFrameCamera.format =
			agora::media::base::VIDEO_PIXEL_BGRA;
		m_externalVideoFrameCamera.buffer = new uint8_t[m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height * 4];
	}
	else if (frame->format == VIDEO_FORMAT_I422) {
		m_externalVideoFrameCamera.format =
			agora::media::base::VIDEO_PIXEL_BGRA;
		m_externalVideoFrameCamera.buffer = new uint8_t[m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height * 4];
	}
	else if (frame->format == VIDEO_FORMAT_YUY2) { //YUY2ToARGB
		m_externalVideoFrameCamera.format =
			agora::media::base::VIDEO_PIXEL_BGRA;
		m_externalVideoFrameCamera.buffer = new uint8_t[m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height * 4];

	}
	else if (frame->format == VIDEO_FORMAT_UYVY) { //UYVYToARGB
		m_externalVideoFrameCamera.format =
			agora::media::base::VIDEO_PIXEL_BGRA;
		m_externalVideoFrameCamera.buffer = new uint8_t[m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height * 4];
	}
	m_camera_format = frame->format;
}


void AgoraRtcEngine::PushCameraVideoFrame(struct obs_source_frame* frame)
{
	if (!m_cameraJoined)
		return;

	if (m_externalVideoFrameCamera.stride != frame->width
		|| m_externalVideoFrameCamera.height != frame->height
		|| m_camera_format != frame->format) {
		if (m_externalVideoFrameCamera.buffer) {
			delete[] m_externalVideoFrameCamera.buffer;
			m_externalVideoFrameCamera.buffer = nullptr;
		}
		SetExternalVideoFrameCamera(frame);
		blog(LOG_INFO, "obs camera export to plugin: linesize[0]=%d, linesize[1]=%d,"
			"linesize[2]=%d,width=%d, height=%d,obs format = %s, external format=%s"
			, frame->linesize[0], frame->linesize[1], frame->linesize[2]
			, frame->width, frame->height, mapOBSVideoFormat[frame->format].c_str()
			, mapVideoFormat[m_externalVideoFrameCamera.format].c_str());
		blog(LOG_INFO, "PushVideoFrame: m_connection channel=%s, uid=%d", m_connection.channelId, m_connection.localUid);
	}

	uint8_t* dst = (uint8_t*)m_externalVideoFrameCamera.buffer;
	if (frame->format == VIDEO_FORMAT_I420) {
		copy_frame_data_plane2(dst, m_externalVideoFrameCamera.stride, frame, 0, m_externalVideoFrameCamera.height);
		dst += m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height;
		copy_frame_data_plane2(dst, m_externalVideoFrameCamera.stride / 2, frame, 1, m_externalVideoFrameCamera.height / 2);
		dst += m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height / 4;
		copy_frame_data_plane2(dst, m_externalVideoFrameCamera.stride / 2, frame, 2, m_externalVideoFrameCamera.height / 2);
	}
	else if (frame->format == VIDEO_FORMAT_NV12) {
		copy_frame_data_plane2(dst, m_externalVideoFrameCamera.stride, frame, 0, m_externalVideoFrameCamera.height);
		dst += m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height;
		copy_frame_data_plane2(dst, m_externalVideoFrameCamera.stride, frame, 1, m_externalVideoFrameCamera.height / 2);
	}
	else if (frame->format == VIDEO_FORMAT_BGRA) 
		copy_frame_data_plane2(dst, m_externalVideoFrameCamera.stride * 4, frame, 0, m_externalVideoFrameCamera.height);
	else if (frame->format == VIDEO_FORMAT_BGRX)
		libyuv::ARGBMirror(frame->data[0], frame->linesize[0], dst, m_externalVideoFrameCamera.stride * 4
			, m_externalVideoFrameCamera.stride, m_externalVideoFrameCamera.height);
	else if (frame->format == VIDEO_FORMAT_RGBA) 
		copy_frame_data_plane2(dst, m_externalVideoFrameCamera.stride * 4, frame, 0, m_externalVideoFrameCamera.height);
	else if (frame->format == VIDEO_FORMAT_I444) 
		libyuv::I444ToARGB(
			frame->data[0], frame->linesize[0],
			frame->data[1], frame->linesize[1],
			frame->data[2], frame->linesize[2],
			(uint8_t*)m_externalVideoFrameCamera.buffer,
			m_externalVideoFrameCamera.stride * 4,
			frame->width, frame->height);
	else if (frame->format == VIDEO_FORMAT_I422)
		libyuv::I422ToARGB(
			frame->data[0], frame->linesize[0],
			frame->data[1], frame->linesize[1],
			frame->data[2], frame->linesize[2],
			(uint8_t*)m_externalVideoFrameCamera.buffer,
			m_externalVideoFrameCamera.stride * 4,
			frame->width, frame->height);
	else if (frame->format == VIDEO_FORMAT_YUY2)
		libyuv::YUY2ToARGB(
			frame->data[0], frame->linesize[0],
			(uint8_t*)m_externalVideoFrameCamera.buffer,
			m_externalVideoFrameCamera.stride * 4,
			frame->width, frame->height
		);
	else if (frame->format == VIDEO_FORMAT_UYVY)
		libyuv::UYVYToARGB(
			frame->data[0], frame->linesize[0],
			(uint8_t*)m_externalVideoFrameCamera.buffer,
			m_externalVideoFrameCamera.stride * 4,
			frame->width, frame->height
		);
	else 
		blog(LOG_INFO, "PushCameraFrame: format:%d no support yet", frame->format);

	m_connection.channelId = m_channelId.c_str();
	m_connection.localUid = m_localCameraUID;
	m_externalVideoFrameCamera.timestamp = get_time_stamp();
	m_pMediaEngine->pushVideoFrame(&m_externalVideoFrameCamera, m_connection);

	if (m_firstCameraVideo) {
		blog(LOG_INFO, "Agora First Camera PushVideoFrame timestamp: %llu ms", m_externalVideoFrameCamera.timestamp);
		m_firstCameraVideo = false;
		m_firstCameraFrameTs = m_externalVideoFrameCamera.timestamp;
	}
}
