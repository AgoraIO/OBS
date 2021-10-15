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
	, logFirstPushVideo(false)
	, sampleRate(48000)
	, audioChannel(2)
	, m_externalAudioFrameSize(480 * 2 * 2)
	, m_externalVideoFrameSize(640 * 480 * 3 / 2)
	, m_audioDeviceManager(nullptr)
	, m_bInitialize(false)
	, m_bJoinChannel(false)
{
	//AParameter apm(*m_rtcEngine);

//	apm->setParameters("{\"che.audio.input.volume\": 60}");
//	apm->setParameters("{\"che.audio.current.recording.boostMode\": -1}");
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

	if (m_externalVideoFrameCamera.buffer) {
		delete[] m_externalVideoFrameCamera.buffer;
		m_externalVideoFrameCamera.buffer = nullptr;
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
		m_rtcEngine = (agora::rtc::IRtcEngineEx*)createAgoraRtcEngine();

	int ret = m_rtcEngine->initialize(context);
	if (0 != ret) {
		return false;
	}

	m_rtcEngine->queryInterface(agora::rtc::AGORA_IID_MEDIA_ENGINE,
				    (void **)&m_pMediaEngine);

	SetExternalVideoFrame();
	
	m_rtcEngine->setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING);
	m_rtcEngine->enableVideo();
	AgoraRtcEngine::GetInstance()->setClientRole(CLIENT_ROLE_BROADCASTER);
	//m_rtcEngine->enableLocalAudio(false);
	m_pMediaEngine->setExternalVideoSource(true, false);
	m_rtcEngine->setExternalAudioSource(true, 48000, 2);
	
	m_audioDeviceManager = new AAudioDeviceManager(m_rtcEngine);
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
	m_externalVideoFrame.type = agora::media::base::ExternalVideoFrame::VIDEO_BUFFER_RAW_DATA;
	m_format = ovi.output_format;
	if (ovi.output_format == VIDEO_FORMAT_I420) {
		m_externalVideoFrame.format =
			agora::media::base::VIDEO_PIXEL_I420;
		m_externalVideoFrame.buffer = new uint8_t[m_externalVideoFrame.stride*m_externalVideoFrame.height * 3 / 2];
	}
	else if (ovi.output_format == VIDEO_FORMAT_NV12) {
		m_externalVideoFrame.format =
			agora::media::base::VIDEO_PIXEL_NV12;
		m_externalVideoFrame.buffer = new uint8_t[m_externalVideoFrame.stride*m_externalVideoFrame.height * 3 / 2];
	}
	else if (ovi.output_format == VIDEO_FORMAT_RGBA) {
		m_externalVideoFrame.format =
			agora::media::base::VIDEO_PIXEL_BGRA;
		m_externalVideoFrame.buffer = new uint8_t[m_externalVideoFrame.stride*m_externalVideoFrame.height * 4];
	}
	else if (ovi.output_format == VIDEO_FORMAT_I444) {
		m_externalVideoFrame.format =
			agora::media::base::VIDEO_PIXEL_BGRA;
		m_externalVideoFrame.buffer = new uint8_t[m_externalVideoFrame.stride*m_externalVideoFrame.height * 4];
	}
}

void AgoraRtcEngine::PushVideoFrame(struct video_data* frame)
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
		//copy_frame_data_plane(dst, m_externalVideoFrame.stride * 4, frame, 0, m_externalVideoFrame.height);
		break;
	}
	m_externalVideoFrame.timestamp = GetTickCount64();
	m_pMediaEngine->pushVideoFrame(&m_externalVideoFrame);
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
	else if (frame->format == VIDEO_FORMAT_BGRA) {
		m_externalVideoFrameCamera.format =
			agora::media::base::VIDEO_PIXEL_BGRA;
		m_externalVideoFrameCamera.buffer = new uint8_t[m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height * 4];
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
	//	|| frame->format == VIDEO_FORMAT_YVYU    //
	else if (frame->format == VIDEO_FORMAT_UYVY) { //UYVYToARGB
		m_externalVideoFrameCamera.format =
			agora::media::base::VIDEO_PIXEL_RGBA;
		m_externalVideoFrameCamera.buffer = new uint8_t[m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height * 4];
	}
	m_camera_format = frame->format;
}


void AgoraRtcEngine::PushCameraVideoFrame(struct obs_source_frame* frame)
{
	if (!m_bJoinChannel)
		return;

	if (m_externalVideoFrameCamera.stride != frame->width
		|| m_externalVideoFrameCamera.height != frame->height
		|| m_camera_format != frame->format) {
		if (m_externalVideoFrameCamera.buffer) {
			delete[] m_externalVideoFrameCamera.buffer;
			m_externalVideoFrameCamera.buffer = nullptr;
		}
		SetExternalVideoFrameCamera(frame);
		blog(LOG_INFO, "obs camera export to plugin: linesize 0=%d, 1=%d, 2=%d, \
             width=%d, height=%d, format = %d, external format=%d"
			 , frame->linesize[0], frame->linesize[1], frame->linesize[2]
			 , frame->width, frame->height, frame->format, m_externalVideoFrameCamera.format);
		blog(LOG_INFO, "PushVideoFrame: connection channel=%s, uid=%d", connection.channelId, connection.localUid);
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
	else if (frame->format == VIDEO_FORMAT_BGRA) {
		copy_frame_data_plane2(dst, m_externalVideoFrameCamera.stride * 4, frame, 0, m_externalVideoFrameCamera.height);
	}
	else if (frame->format == VIDEO_FORMAT_RGBA) {
		copy_frame_data_plane2(dst, m_externalVideoFrameCamera.stride * 4, frame, 0, m_externalVideoFrameCamera.height);
	}
	else if (frame->format == VIDEO_FORMAT_I444) {
		libyuv::I444ToARGB(
			frame->data[0], frame->linesize[0],
			frame->data[1], frame->linesize[1],
			frame->data[2], frame->linesize[2],
			(uint8_t*)m_externalVideoFrameCamera.buffer,
			m_externalVideoFrameCamera.stride * 4,
			frame->width, frame->height);
	}
	else if (frame->format == VIDEO_FORMAT_I422) {
		/*m_externalVideoFrameCamera.format =
			agora::media::base::VIDEO_PIXEL_I422;
		copy_frame_data_plane2(dst, m_externalVideoFrameCamera.stride, frame, 0, m_externalVideoFrameCamera.height);
		dst += m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height;
		copy_frame_data_plane2(dst, m_externalVideoFrameCamera.stride, frame, 1, m_externalVideoFrameCamera.height / 2);
		dst += m_externalVideoFrameCamera.stride * m_externalVideoFrameCamera.height / 2;
		copy_frame_data_plane2(dst, m_externalVideoFrameCamera.stride, frame, 2, m_externalVideoFrameCamera.height / 2);*/
		libyuv::I422ToARGB(
			frame->data[0], frame->linesize[0],
			frame->data[1], frame->linesize[1],
			frame->data[2], frame->linesize[2],
			(uint8_t*)m_externalVideoFrameCamera.buffer,
			m_externalVideoFrameCamera.stride * 4,
			frame->width, frame->height);
	}
	else if (frame->format == VIDEO_FORMAT_YUY2) {
		libyuv::YUY2ToARGB(
			frame->data[0], frame->linesize[0],
			(uint8_t*)m_externalVideoFrameCamera.buffer,
			m_externalVideoFrameCamera.stride * 4,
			frame->width, frame->height
		);
	}
	else if (frame->format == VIDEO_FORMAT_UYVY) {
		libyuv::UYVYToARGB(
			frame->data[0], frame->linesize[0],
			(uint8_t*)m_externalVideoFrameCamera.buffer,
			m_externalVideoFrameCamera.stride * 4,
			frame->width, frame->height
		);
	}
	connection.channelId = channelId.c_str();
	connection.localUid = localCameraUid;
	m_externalVideoFrame.timestamp = GetTickCount64();
	m_pMediaEngine->pushVideoFrame(&m_externalVideoFrameCamera, connection);
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
	m_externalAudioframe.channels = 2;
	m_externalAudioframe.samplesPerChannel = 480;
	m_externalAudioframe.samplesPerSec = 48000;//sampleRate;
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
	logFirstPushVideo = false;

	if (m_pMediaEngine == nullptr)
		return;

	if (m_externalAudioframe.buffer) {
		delete[] m_externalAudioframe.buffer;
		m_externalAudioframe.buffer = nullptr;
	}
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

void AgoraRtcEngine::SetRecordBoost()
{
	
}

void AgoraRtcEngine::MuteRemoteVideo(unsigned int uid, bool bMute)
{
	m_rtcEngine->muteRemoteVideoStream(uid, bMute);
}

int AgoraRtcEngine::joinChannel(const std::string &key, const std::string &channel, 
	unsigned int uid, bool enableDual, bool muteAudio , bool muteVideo, bool loopbackRecording)
{
	if (m_bJoinChannel)
		return 0;
	agora::rtc::AUDIO_PROFILE_TYPE profile = agora::rtc::AUDIO_PROFILE_MUSIC_STANDARD;
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
	
	//m_rtcEngine->setAudioProfile(profile, (AUDIO_SCENARIO_TYPE)m_scenario);
	//apm->setParameters("{\"che.audio.codec.name\":\"OPUSFB\"}");
	//AParameter apm(m_rtcEngine);
	//apm->setParameters("{\"che.audio.specify.codec\": \"OPUSFB\"}");
	ChannelMediaOptions options;
	options.autoSubscribeAudio = muteAudio;
	options.autoSubscribeVideo = muteVideo;
	options.publishCustomAudioTrack = true;
	options.publishCustomVideoTrack = true;
	options.publishCameraTrack = false;
	options.publishAudioTrack = false;
	options.clientRoleType = CLIENT_ROLE_BROADCASTER;
	options.channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
	if (enableDual)
		m_rtcEngine->enableDualStreamMode(true);
	blog(LOG_INFO, "joinChannel: channel=%s, uid=%u", channel.c_str(), uid);
	m_rtcEngine->enableLoopbackRecording(loopbackRecording);
	int r = m_rtcEngine->joinChannel(key.data(), channel.data(), uid, options);//joinChannel(key.data(), channel.data(), "", uid, options);//
	return r;
}

int AgoraRtcEngine::joinChannel(const std::string & key, const std::string & channel, unsigned uid)
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
	blog(LOG_INFO, "joinChannelEx: connection channel=%s, uid=%d", connection.channelId, connection.localUid);
	int r = m_rtcEngine->joinChannelEx(key.c_str(), connection, options, m_eventHandlerCamera.get());//joinChannel(key.data(), channel.data(), "", uid, options);//
	return r;
}

int AgoraRtcEngine::leaveChannel()
{
	if (!m_bInitialize || !m_bJoinChannel)
		return -1;
	m_bJoinChannel = false;
	int r = m_rtcEngine->leaveChannel();

	if (fpPCM) {
		fclose(fpPCM);
		fpPCM = nullptr;
	}
	return r;
}

int AgoraRtcEngine::leaveChannelCamera()
{
	return m_rtcEngine->leaveChannelEx(connection);
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
	canvas.renderMode = agora::media::base::RENDER_MODE_HIDDEN;
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

bool AgoraRtcEngine::setCameraEncoderConfiguration(int w, int h, int fps, int bitrate)
{
	VideoEncoderConfiguration config;
	config.dimensions.width = w;
	config.dimensions.height = h;
	config.frameRate = (FRAME_RATE)fps;
	config.bitrate = bitrate;
	if (w < h)
		config.orientationMode = ORIENTATION_MODE_FIXED_PORTRAIT;
	else
		config.orientationMode = ORIENTATION_MODE_FIXED_LANDSCAPE;
	config.orientationMode = ORIENTATION_MODE_ADAPTIVE;
	int nRet = m_rtcEngine->setVideoEncoderConfigurationEx(config, connection);

	return nRet == 0 ? true : false;
}

void AgoraRtcEngine::setConnection(const std::string& channel, unsigned uid)
{
	channelId = channel;
	connection.channelId = channelId.c_str();
	localCameraUid = uid;
	connection.localUid = localCameraUid;
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

void AgoraRtcEngine::enableLastmileTest(bool bEnable)
{
	LastmileProbeConfig config;
	if (bEnable)
		m_rtcEngine->startLastmileProbeTest(config);
	else
		m_rtcEngine->stopLastmileProbeTest();
}

void AgoraRtcEngine::SavePcm(bool bSave)
{
	savePcm = bSave;
		//AParameter apm(*m_rtcEngine);
		//apm->setParameters("{\"che.audio.external.to.apm\", true}");
		//apm->setParameters("{\"che.audio.start_debug_recording\":\"all\"}");
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

	//char buf[80];
	//asctime_s(buf, &tstruct);
	//sprintf_s(buf, 80, "obs_agora_%d-%02d-%d_%d-%d-%d"
	//	, tstruct.tm_year + 1900, tstruct.tm_mon + 1, tstruct.tm_mday
	//	, tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec);
	//size_t written = strftime(buf, sizeof(buf), "%X", &tstruct);
	return buf;
}

void AgoraRtcEngine::PushAudioFrame(struct encoder_frame *frame)
{ 
	if (!m_bInitialize || !m_bJoinChannel)
		return;
	if (count % 600 == 0) {
		blog(LOG_ERROR, "PushAudioFrame");
		count = count % 600;
		blog(LOG_INFO, "agora tool audio size: %d", frame->linesize[0]);
	}

	if (savePcm) {
		if (!fpPCM) {
			std::string filePath = pcmFolder + CurrentTimeString();
			filePath += ".pcm";
			fpPCM = fopen(filePath.c_str(), "ab+");
			//fopen_s(&fpPCM, filePath.c_str(), "ab+");
		}

		if (fpPCM) {
			fwrite(frame->data[0], 1, frame->linesize[0], fpPCM);
		}
		else
			blog(LOG_INFO, "agora tool pcm save failed");
	}
	

	count++;

	m_externalAudioframe.renderTimeMs = GetTickCount64();
	memcpy_s(m_externalAudioframe.buffer, frame->linesize[0],
		frame->data[0], frame->linesize[0]);
	
	int ret = m_pMediaEngine->pushAudioFrame(AUDIO_RECORDING_SOURCE,
		&m_externalAudioframe, false);
	
}
