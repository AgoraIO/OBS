#include "agorartcengine.hpp"
#if _WIN32
#include "AgoraBase.h"
#else
#include <AgoraRtcKit/AgoraBase.h>
#include <thread>
#include <chrono>
#define  DEFINE_GET_TIME_NOW(getTickCount64)   \
         int64_t getTickCount64() \
        {       \
          std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();\
          std::chrono::milliseconds mic = std::chrono::duration_cast<std::chrono::milliseconds>(d);\
          return mic.count();\
        }

DEFINE_GET_TIME_NOW(GetTickCount64)
DEFINE_GET_TIME_NOW(GetTickCount)

#define Sleep(x)          \
    std::this_thread::sleep_for(std::chrono::milliseconds(x))

#define DEFINE_MEMCPY_S(func)                                     \
      int func(void *det, size_t detSize, const void * src, size_t srcSize)                                            \
      {                                                        \
        uint8_t errorcode = 0;                                 \
        if (srcSize > detSize || src == NULL || det == NULL)   \
        {                                                       \
          if (srcSize > detSize)                                \
            errorcode = 1;                                       \
          else if (src == NULL)                                  \
            errorcode = 2;                                      \
          else if (det == NULL)                                  \
            errorcode = 3;                                       \
          fflush(stdout);                                         \
          return -1;                                              \
        }                                                           \
        else                                                          \
          memcpy(det, src, srcSize);                                  \
                                                                        \
        return 1;                                                      \
      }


DEFINE_MEMCPY_S(memcpy_s)
#endif
#include "obs.h"
#include <libyuv.h>

//#include "RtcTokenBuilder.h"
using namespace agora::rtc;
using namespace agora;



class AgoraRtcEngineEvent :public QObject,
	public IRtcEngineEventHandler
{
	AgoraRtcEngine &m_engine;

public:
	AgoraRtcEngineEvent(AgoraRtcEngine &engine) : m_engine(engine) {}

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
		Sleep(200);
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
		emit m_engine.onFirstRemoteVideoDecoded(uid, width, height, elapsed);
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

	virtual void onRtmpStreamingStateChanged(const char *url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR errCode) override
	{
		emit m_engine.onRtmpStreamingStateChanged(url,  state, errCode);
	}

	virtual void onClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole) override
	{
		emit m_engine.onClientRoleChanged(oldRole, newRole);
	}
};

AgoraRtcEngine *AgoraRtcEngine::m_agoraEngine = nullptr;
agora::media::IAudioFrameObserver::AudioFrame AgoraRtcEngine::m_externalAudioframe;

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
	: m_rtcEngine(createAgoraRtcEngine())
	, m_eventHandler(new AgoraRtcEngineEvent(*this))
	, logFirstPushVideo(false)
	, sampleRate(48000)
	, audioChannel(2)
	, m_externalAudioFrameSize(480 * 2 * 2)
	, m_externalVideoFrameSize(640 * 480 * 3 / 2)
	, m_audioDeviceManager(nullptr)
	, m_bInitialize(false)
	, m_bJoinChannel(false)
	 
{
	m_externalAudioframe.buffer = NULL;
	m_externalVideoFrame.buffer = NULL;
	qRegisterMetaType<RtcStats>();

}

AgoraRtcEngine::~AgoraRtcEngine()
{
	release();
}

void AgoraRtcEngine::release()
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

	if (m_rtcEngine) {
		m_rtcEngine->release(true);
		m_rtcEngine = NULL;
	}

	m_bInitialize = false;
}

bool AgoraRtcEngine::InitEngine(std::string appid)
{
	agora::rtc::RtcEngineContext context;
	context.eventHandler = m_eventHandler.get();
	context.appId = appid.c_str();
	struct calldata params;
	calldata_init(&params);

	if (*context.appId == '\0') {
		calldata_set_int(&params, "error", -1); //
		return false;
	}

	if (!m_rtcEngine)
		m_rtcEngine = createAgoraRtcEngine();

	int ret = m_rtcEngine->initialize(context);
	if (0 != ret) {
		return false;
	}

	m_rtcEngine->queryInterface(agora::AGORA_IID_MEDIA_ENGINE,
				    (void **)&m_pMediaEngine);

	SetExternalVideoFrame();

	
	m_rtcEngine->setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING);
	m_rtcEngine->enableVideo();
	AgoraRtcEngine::GetInstance()->setClientRole(CLIENT_ROLE_BROADCASTER);

	m_audioDeviceManager = new AAudioDeviceManager(m_rtcEngine);
	m_pMediaEngine->setExternalVideoSource(true, false);
	m_rtcEngine->setExternalAudioSource(true, sampleRate, 2);
	m_bInitialize = true;
	return true;
}

void AgoraRtcEngine::SetExternalVideoFrame()
{
	struct obs_video_info ovi;
	obs_get_video_info(&ovi);
	agora_out_cx = ovi.output_width;
	agora_out_cy = ovi.output_height;

	m_externalVideoFrame.buffer = NULL;
	m_externalVideoFrame.cropLeft = 0;
	m_externalVideoFrame.cropTop = 0;
	m_externalVideoFrame.cropRight = 0;
	m_externalVideoFrame.cropBottom = 0;


	m_externalVideoFrame.rotation = 0;
	m_externalVideoFrame.height = agora_out_cy;
	m_externalVideoFrame.stride = (agora_out_cx << 4) >> 4;
	m_externalVideoFrame.timestamp = 0;
	m_externalVideoFrame.type = ExternalVideoFrame::VIDEO_BUFFER_RAW_DATA;
	m_format = ovi.output_format;
	if (ovi.output_format == VIDEO_FORMAT_I420) {
		m_externalVideoFrame.format =
			agora::media::ExternalVideoFrame::VIDEO_PIXEL_I420;
		m_externalVideoFrame.buffer = new uint8_t[m_externalVideoFrame.stride*m_externalVideoFrame.height * 3 / 2];
	}
	else if (ovi.output_format == VIDEO_FORMAT_NV12) {
		m_externalVideoFrame.format =
			agora::media::ExternalVideoFrame::VIDEO_PIXEL_NV12;
		m_externalVideoFrame.buffer = new uint8_t[m_externalVideoFrame.stride*m_externalVideoFrame.height * 3 / 2];
	}
	else if (ovi.output_format == VIDEO_FORMAT_RGBA) {
		m_externalVideoFrame.format =
			agora::media::ExternalVideoFrame::VIDEO_PIXEL_BGRA;
		m_externalVideoFrame.buffer = new uint8_t[m_externalVideoFrame.stride*m_externalVideoFrame.height * 4];
	}
	else if (ovi.output_format == VIDEO_FORMAT_I444) {
		m_externalVideoFrame.format =
			agora::media::ExternalVideoFrame::VIDEO_PIXEL_BGRA;
		m_externalVideoFrame.buffer = new uint8_t[m_externalVideoFrame.stride*m_externalVideoFrame.height * 4];
	}
}

BOOL AgoraRtcEngine::setLogPath(std::string path)
{

	int ret = m_rtcEngine->setLogFile(path.c_str());
	return ret == 0 ? TRUE : FALSE;
}

BOOL AgoraRtcEngine::setClientRole(agora::rtc::CLIENT_ROLE_TYPE role,
				   LPCSTR lpPermissionKey)
{
	int nRet = m_rtcEngine->setClientRole(role);

	return nRet == 0 ? TRUE : FALSE;
}

int AgoraRtcEngine::setChannelProfile(CHANNEL_PROFILE_TYPE profile)
{
	return m_rtcEngine->setChannelProfile(
		CHANNEL_PROFILE_LIVE_BROADCASTING);
}

int AgoraRtcEngine::setLocalVideoMirrorMode(VIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	return m_rtcEngine->setLocalVideoMirrorMode(mirrorMode);
}

void AgoraRtcEngine::startPreview()
{
	m_rtcEngine->startPreview();
}

void AgoraRtcEngine::stopPreview()
{
	m_rtcEngine->stopPreview();
}

void *AgoraRtcEngine::AgoraAudioObserver_Create()
{	
	m_externalAudioframe.channels = audioChannel;
	m_externalAudioframe.samples =
		sampleRate /100; //samplerate/100  10ms one audio frame
	m_externalAudioframe.samplesPerSec = sampleRate;
	m_externalAudioframe.bytesPerSample = 2;
	m_externalAudioframe.type =
		agora::media::IAudioFrameObserver::FRAME_TYPE_PCM16;
	m_externalAudioframe.buffer =
		new uint8_t[m_externalAudioframe.samples * 2 * audioChannel];
	memset(m_externalAudioframe.buffer, 0, m_externalAudioframe.samples * 2 * audioChannel);
	m_externalAudioframe.avsync_type = 0;
	m_externalAudioframe.renderTimeMs = 0;

	m_externalAudioFrameSize =
		m_externalAudioframe.samples * 2 * audioChannel;
	return &m_externalAudioframe;
}

void AgoraRtcEngine::AgoraAudioObserver_Destroy()
{
	logFirstPushVideo = false;

	if (m_pMediaEngine == nullptr)
		return;

	if (m_externalAudioframe.buffer) {
		delete[] m_externalAudioframe.buffer;
		m_externalAudioframe.buffer = nullptr;
	}
}

bool AgoraRtcEngine::enableExtendPlayDevice(bool bEnable)
{
	int ret = 0;

	AParameter apm(*m_rtcEngine);

	if (bEnable)
		ret = apm->setParameters(
			"{\"che.audio.external_render\":true}");
	else
		ret = apm->setParameters(
			"{\"che.audio.external_render\":false}");
	apm->release();
	return ret == 0 ? TRUE : FALSE;
}


std::string AgoraRtcEngine::CalculateToken(std::string appid,
					   const std::string &appcertificate,
					   const std::string &channel,
					   unsigned int uid,
					   unsigned int privilegeExpiredTs)
{
	return "";
/*	std::string str;
	if (uid != 0) {
		str = std::to_string(uid);
	}
	return agora::tools::RtcTokenBuilder::buildTokenWithUserAccount(
		appid.c_str(), appcertificate.c_str(), channel.c_str(),
		str.c_str(), agora::tools::Role_Publisher, privilegeExpiredTs);*/
}

int AgoraRtcEngine::joinChannel(const std::string &key,
				const std::string &channel, unsigned int uid, bool muteAudio , bool muteVideo)
{
	if (m_bJoinChannel)
		return 0;

	AUDIO_PROFILE_TYPE profile = AUDIO_PROFILE_MUSIC_STANDARD;
	if (audioChannel == 1 && !m_bHighQuality) {
		profile = AUDIO_PROFILE_MUSIC_STANDARD;
	}
	else if (audioChannel == 2 && !m_bHighQuality) {
		profile = AUDIO_PROFILE_MUSIC_STANDARD_STEREO;
	}
	else if (audioChannel == 1 && m_bHighQuality) {
		profile = AUDIO_PROFILE_MUSIC_HIGH_QUALITY;
	}
	else if (audioChannel == 2 && m_bHighQuality) {
		profile = AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO;
	}
	
	AParameter apm(m_rtcEngine);
	//apm->setParameters("{\"che.audio.codec.name\":\"OPUS\"}");
	//m_rtcEngine->setAudioProfile(profile, (AUDIO_SCENARIO_TYPE)m_scenario);
	apm->setParameters("{\"che.audio.specify.codec\": \"OPUSFB\"}");
	ChannelMediaOptions options;
	options.autoSubscribeAudio = muteAudio;
	options.autoSubscribeVideo = muteVideo;

	int r =  m_rtcEngine->joinChannel(key.data(), channel.data(), "", uid, options);//
	return r;
}

int AgoraRtcEngine::leaveChannel()
{
	if (!m_bInitialize || !m_bJoinChannel)
		return -1;
	m_bJoinChannel = false;
	int r = m_rtcEngine->leaveChannel();
	return r;
}

int AgoraRtcEngine::enableVideo(bool enabled)
{
	return enabled ? m_rtcEngine->enableVideo()
		       : m_rtcEngine->disableVideo();
}

int AgoraRtcEngine::setupRemoteVideo(unsigned int uid, void *view)
{
	view_t v = reinterpret_cast<view_t>(view);
	VideoCanvas canvas; // (v, RENDER_MODE_FIT, uid);
	canvas.view = v;
	canvas.renderMode = RENDER_MODE_HIDDEN;
	canvas.uid = uid;

	return m_rtcEngine->setupRemoteVideo(canvas);
}

bool AgoraRtcEngine::keepPreRotation(bool bRotate)
{
	int ret = -1;
	AParameter apm(m_rtcEngine);
	if (bRotate)
		ret = apm->setParameters(
			"{\"che.video.keep_prerotation\":true}");
	else
		ret = apm->setParameters(
			"{\"che.video.keep_prerotation\":false}");
	apm.release();
	return ret == 0;
}

bool AgoraRtcEngine::setVideoProfileEx(int nWidth, int nHeight, int nFrameRate,
				       int nBitRate, bool Agora)
{
	if (!Agora) {
		AParameter apm(m_rtcEngine);
		apm->setParameters("{\"che.video.freestyle_customer\": true}");
	}
	VideoEncoderConfiguration config;
	config.dimensions.width = nWidth;
	config.dimensions.height = nHeight;
	config.frameRate = (FRAME_RATE)nFrameRate;
	config.bitrate = nBitRate;
	if (nWidth < nHeight)
		config.orientationMode = ORIENTATION_MODE_FIXED_PORTRAIT;
	else
		config.orientationMode = ORIENTATION_MODE_FIXED_LANDSCAPE;
	int nRet = m_rtcEngine->setVideoEncoderConfiguration(config);

	return nRet == 0 ? true : false;
}

bool AgoraRtcEngine::enableLocalCameara(bool bEnable)
{
	AParameter apm(*m_rtcEngine);
	int ret = -1;
	if (!apm.get())
		return false;

	if (!bEnable)
		ret = apm->setParameters(
			"{\"che.video.local.camera_index\":1024}");
	else
		ret = apm->setParameters(
			"{\"che.video.local.camera_index\":0}");

	apm.release();
	return ret == 0;
}
///////////////////////////////////////////////////////////////////////////////////////
//agora device
///////////////////////////////////////////////////////////////////////////////////////


int AgoraRtcEngine::getPalyoutDeviceVolume()
{
	AAudioDeviceManager audioDeviceManager(m_rtcEngine);
	if (!audioDeviceManager)
		return 0;
	int vol = 0;
	if (audioDeviceManager->getPlaybackDeviceVolume(&vol) == 0)
		return vol;
	return 0;
}

void AgoraRtcEngine::EnableAgoraCaptureMicAudio(bool bCapture)
{
}

int AgoraRtcEngine::setPalyoutDeviceVolume(int volume)
{
	AAudioDeviceManager audioDeviceManager(m_rtcEngine);
	if (!audioDeviceManager)
		return -1;
	return audioDeviceManager->setPlaybackDeviceVolume(volume);
}

int AgoraRtcEngine::testSpeaker(bool start)
{
	agora::rtc::AAudioDeviceManager dm(m_rtcEngine);
	if (!dm)
		return -1;
	if (start)
		return dm->startPlaybackDeviceTest("audio_sample.wav");
	else
		return dm->stopPlaybackDeviceTest();
}

void AgoraRtcEngine::joinedChannelSuccess(const char *channel, unsigned int uid,
					  int elapsed)
{
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

int AgoraRtcEngine::EnableWebSdkInteroperability(bool enabled)
{
	return m_rtcEngine->enableWebSdkInteroperability(true);
}

void AgoraRtcEngine::logAudioFrameTimestamp()
{
	unsigned int audioTime = GetTickCount();
}

void AgoraRtcEngine::enableLogTimestamp(bool bEnable)
{
}

bool AgoraRtcEngine::getPlayoutDevices(std::vector<DEVICEINFO>& devices)
{
	if (!m_bInitialize || !m_audioDeviceManager || !m_audioDeviceManager->get())
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

void copy_frame_data_line(uint8_t *dst, int line_size,
	const struct video_data *src,
	uint32_t plane, uint32_t y)
{
	uint32_t pos_src = y * src->linesize[plane];
	uint32_t pos_dst = y * line_size;
	uint32_t bytes = line_size < src->linesize[plane]
		? line_size
		: src->linesize[plane];

	memcpy(dst + pos_dst, src->data[plane] + pos_src, bytes);
}

 void copy_frame_data_plane(uint8_t *dst, int line_size,
	const struct video_data *src,
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

void AgoraRtcEngine::enableLastmileTest(bool bEnable)
{
	if (bEnable)
		m_rtcEngine->enableLastmileTest();
	else
		m_rtcEngine->disableLastmileTest();
}

void AgoraRtcEngine::PushVideoFrame(struct video_data *frame)
{
	if (!m_bInitialize || !m_bJoinChannel)
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
		dst += m_externalVideoFrame.stride *m_externalVideoFrame.height;
		copy_frame_data_plane(dst, m_externalVideoFrame.stride / 2, frame, 1, m_externalVideoFrame.height / 2);
		dst += m_externalVideoFrame.stride *m_externalVideoFrame.height / 4;
		copy_frame_data_plane(dst, m_externalVideoFrame.stride/2, frame, 2, m_externalVideoFrame.height / 2);
	}
		break;
	case VIDEO_FORMAT_NV12: {
		copy_frame_data_plane(dst, m_externalVideoFrame.stride, frame, 0, m_externalVideoFrame.height);

		dst += m_externalVideoFrame.stride *m_externalVideoFrame.height;
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
		//copy_frame_data_plane(dst, m_externalVideoFrame.stride * 4, frame, 0, m_externalVideoFrame.height);
		break;
	}
	m_externalVideoFrame.timestamp = GetTickCount64();
	m_pMediaEngine->pushVideoFrame(&m_externalVideoFrame);
}

void AgoraRtcEngine::SetAudioProfile(int scenario, int channels, bool bHighQuality)
{
	m_scenario = (AUDIO_SCENARIO_TYPE)scenario;
	audioChannel = channels;
	m_bHighQuality = bHighQuality;
}

void AgoraRtcEngine::MuteAllRemoteVideo(bool bMute)
{
	m_rtcEngine->muteAllRemoteVideoStreams(bMute);
}

void AgoraRtcEngine::MuteAllRemoteAudio(bool bMute)
{
	m_rtcEngine->muteAllRemoteAudioStreams(bMute);
}

void AgoraRtcEngine::PushAudioFrame(struct encoder_frame *frame)
{ 
	if (!m_bInitialize || !m_bJoinChannel)
		return;

	m_externalAudioframe.renderTimeMs = GetTickCount64();
	memcpy_s(m_externalAudioframe.buffer, frame->linesize[0],
		frame->data[0], frame->linesize[0]);
	
	int ret = m_pMediaEngine->pushAudioFrame(AUDIO_RECORDING_SOURCE,
		&m_externalAudioframe, false);
	
}
