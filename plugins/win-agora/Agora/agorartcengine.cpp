#include "agorartcengine.hpp"
#include "Agora/AgoraBase.h"
#include "obs.h"
using namespace agora::rtc;
using namespace agora;

class AgoraRtcEngineEvent : public agora::rtc::IRtcEngineEventHandler
{
    AgoraRtcEngine& m_engine;
public:
    AgoraRtcEngineEvent(AgoraRtcEngine& engine)
        :m_engine(engine)
    {}
    virtual void onVideoStopped() override
    {
    // emit m_engine.videoStopped();
    }
    virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override
    {
		struct calldata params;
		calldata_init(&params);
		calldata_set_string(&params, "channel", channel);
		calldata_set_int(&params, "uid", uid);
		calldata_set_int(&params, "elapsed", elapsed);
		signal_handler_signal(obs_service_get_signal_handler(m_engine.agoraService), "joinChannelSuccess", &params);
    }

	virtual void onLeaveChannel(const RtcStats& stats) override
	{
		struct calldata params;
		uint8_t stack[256] = { 0 };
		calldata_init_fixed(&params, stack, 256);

		calldata_set_int(&params, "duration", stats.duration);
		calldata_set_int(&params, "txBytes", stats.txBytes);
		calldata_set_int(&params, "rxBytes", stats.rxBytes);
		calldata_set_int(&params, "txKBitRate", stats.txKBitRate);
		calldata_set_int(&params, "rxKBitRate", stats.rxKBitRate);
		calldata_set_int(&params, "cpuAppUsage", stats.cpuAppUsage);
		calldata_set_int(&params, "cpuTotalUsage", stats.cpuTotalUsage);
		calldata_set_int(&params, "rxAudioKBitRate", stats.rxAudioKBitRate);
		calldata_set_int(&params, "txAudioKBitRate", stats.txAudioKBitRate);
		calldata_set_int(&params, "rxVideoKBitRate", stats.rxVideoKBitRate);
		calldata_set_int(&params, "txVideoKBitRate", stats.txVideoKBitRate);
		calldata_set_int(&params, "userCount", stats.userCount);
	}

	virtual void onError(int err, const char* msg) override
	{
		struct calldata params;
		calldata_init(&params);
		calldata_set_int(&params, "err_code", err);
		calldata_set_string(&params, "err_msg", msg);
		signal_handler_signal(obs_service_get_signal_handler(m_engine.agoraService), "onError", &params);
	}

    virtual void onUserJoined(uid_t uid, int elapsed) override
    {
		struct calldata params;
		calldata_init(&params);
		calldata_set_int(&params, "uid", uid);
		calldata_set_int(&params, "elapsed", elapsed);
		signal_handler_signal(obs_service_get_signal_handler(m_engine.agoraService), "userJoined", &params);
    }
    virtual void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) override
    {
		struct calldata params;
		calldata_init(&params);
		calldata_set_int(&params, "uid", uid);
		calldata_set_int(&params, "reason", reason);
		signal_handler_signal(obs_service_get_signal_handler(m_engine.agoraService), "userOffline", &params);
    }

    virtual void onFirstLocalVideoFrame(int width, int height, int elapsed) override
    {
    //   emit m_engine.firstLocalVideoFrame(width, height, elapsed);
    }
    virtual void onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed) override
	{
		struct calldata params;

		calldata_init(&params);
		calldata_set_int(&params, "uid", uid);
		calldata_set_int(&params, "width", width);
		calldata_set_int(&params, "height", height);
		calldata_set_int(&params, "elapsed", elapsed);
		signal_handler_signal(obs_service_get_signal_handler(m_engine.agoraService), "firstRemoteVideoDecoded", &params);
    }
    virtual void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed) override
    {
     //  emit m_engine.firstRemoteVideoFrameDrawn(uid, width, height, elapsed);
    }
};

AgoraRtcEngine* AgoraRtcEngine::m_agoraEngine = nullptr;
AgoraRtcEngine* AgoraRtcEngine::GetInstance()
{
	if (m_agoraEngine == nullptr)
		m_agoraEngine = new AgoraRtcEngine;

	return m_agoraEngine;
}

void AgoraRtcEngine::ReleaseInstance()
{
	if (nullptr != m_agoraEngine){
		delete m_agoraEngine;
		m_agoraEngine = nullptr;
	}
}

AgoraRtcEngine::AgoraRtcEngine()
	: m_rtcEngine(createAgoraRtcEngine())
    , m_eventHandler(new AgoraRtcEngineEvent(*this))
    , logFirstPushVideo(false)
    , logVideoFrameTimeCount(0)
    , logAudioFrameTimeCount(0)
    , logAudioVideoTimestamp(false)
{

}

AgoraRtcEngine::~AgoraRtcEngine()
{
	if (m_rtcEngine){
		m_rtcEngine->release();
		m_rtcEngine = NULL;
	}
}

bool AgoraRtcEngine::InitEngine(std::string appid)
{
	agora::rtc::RtcEngineContext context;
	context.eventHandler = m_eventHandler.get();
	context.appId = appid.c_str();
	struct calldata params;
	calldata_init(&params);

	if (*context.appId == '\0'){
		calldata_set_int(&params, "error", -1);//
		signal_handler_signal(obs_service_get_signal_handler(agoraService), "initRtcEngineFailed", &params);
		return false;
	}
	if (0 != m_rtcEngine->initialize(context)){
		calldata_set_int(&params, "error", -2);
		signal_handler_signal(obs_service_get_signal_handler(agoraService), "initRtcEngineFailed", &params);
		return false;
	}
	return true;
}

BOOL AgoraRtcEngine::setLogPath(std::string path)
{
	RtcEngineParameters rep(*m_rtcEngine);
	int ret = rep.setLogFile(path.c_str());
	return ret == 0 ? TRUE : FALSE;
}

BOOL AgoraRtcEngine::setClientRole(CLIENT_ROLE_TYPE role, LPCSTR lpPermissionKey)
{
	int nRet = m_rtcEngine->setClientRole(role);

	//m_nRoleType = role;

	return nRet == 0 ? TRUE : FALSE;
}

int AgoraRtcEngine::setChannelProfile(CHANNEL_PROFILE_TYPE profile)
{
	return m_rtcEngine->setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING);
}

int AgoraRtcEngine::setLocalVideoMirrorMode(VIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	RtcEngineParameters rep(*m_rtcEngine);
	return rep.setLocalVideoMirrorMode(mirrorMode);
}

bool AgoraRtcEngine::enableLocalRender(bool bEnable)
{
	int ret = -1;
	AParameter apm(*m_rtcEngine);

	if (bEnable)
		ret = apm->setParameters("{\"che.video.local.render\":true}");
	else
		ret = apm->setParameters("{\"che.video.local.render\":false}");
	apm.release();
	return ret == 0 ? true : false;
}

void AgoraRtcEngine::startPreview()
{
	m_rtcEngine->startPreview();
}

void AgoraRtcEngine::stopPreview()
{
	m_rtcEngine->stopPreview();
}

void* AgoraRtcEngine::AgoraVideoObserver_Create()
{
	agora::util::AutoPtr< agora::media::IMediaEngine> mediaEngine;
	mediaEngine.queryInterface(m_rtcEngine, agora::AGORA_IID_MEDIA_ENGINE);

	if (mediaEngine.get() == nullptr)
		return nullptr;

	m_videoObserver.reset(new CExtendVideoFrameObserver);
 m_videoObserver->fps = agora_fps;
	if (mediaEngine->registerVideoFrameObserver(m_videoObserver.get()))
	{
		mediaEngine->release();
		return nullptr;
	}

	mediaEngine->release();
	return m_videoObserver.get();
}

void AgoraRtcEngine::AgoraVideoObserver_Destroy()
{ 
	agora::util::AutoPtr< agora::media::IMediaEngine> mediaEngine;
	mediaEngine.queryInterface(m_rtcEngine, agora::AGORA_IID_MEDIA_ENGINE);

	if (mediaEngine.get() == nullptr)
		return;

	mediaEngine->registerVideoFrameObserver(nullptr);
	mediaEngine->release();

 m_videoObserver.reset();
 m_videoObserver.release();
}

bool  AgoraRtcEngine::AgoraVideoObserver_Encode(void* data, struct encoder_frame* frame, struct encoder_packet* packet, bool *receive_packet)
{
	//Cut_I420(frame->frames[0], )
	return true;
}

void* AgoraRtcEngine::AgoraAudioObserver_Create()
{
    logFirstPushVideo = false;
    logVideoFrameTimeCount = 0;
    logAudioFrameTimeCount = 0;
	agora::util::AutoPtr< agora::media::IMediaEngine> mediaEngine;
	mediaEngine.queryInterface(m_rtcEngine, agora::AGORA_IID_MEDIA_ENGINE);

	if (mediaEngine.get() == nullptr)
		return nullptr;

 std::unique_ptr<CExtendAudioFrameObserver> obServer = std::unique_ptr<CExtendAudioFrameObserver>(new CExtendAudioFrameObserver);
 //m_audioObserver.reset(new CExtendAudioFrameObserver);
 m_audioObserver = std::move(obServer);
 m_audioObserver->agora_sdk_captrue_mic_audio = agora_sdk_captrue_mic_audio;

	if (mediaEngine->registerAudioFrameObserver(m_audioObserver.get()))
	{
		mediaEngine->release();
		return nullptr;
	}
 m_audioObserver->Resetlog(logAudioVideoTimestamp);
	mediaEngine->release();
	return m_audioObserver.get();
}

void AgoraRtcEngine::AgoraAudioObserver_Destroy()
{
    logFirstPushVideo = false;
    logVideoFrameTimeCount = 0;
    logAudioFrameTimeCount = 0;
 
	agora::util::AutoPtr< agora::media::IMediaEngine> mediaEngine;
	mediaEngine.queryInterface(m_rtcEngine, agora::AGORA_IID_MEDIA_ENGINE);

	if (mediaEngine.get() == nullptr)
		return;
 
	mediaEngine->registerAudioFrameObserver(0);
	mediaEngine->release();
 m_audioObserver.reset();
 m_audioObserver.release();
}

bool AgoraRtcEngine::AgoraAudioObserver_Encode(void* data, struct encoder_frame* frame,
    struct encoder_packet* packet, bool *receive_packet)
{
	CExtendAudioFrameObserver* audioObserver = static_cast<CExtendAudioFrameObserver*>(data);

	if (audioObserver == nullptr)
		return false;

	//resample

	//uint32_t dataLen = frame->frames * 2 * 2;//2:16 int
//	audioObserver->pCircleBuffer->writeBuffer(frame->data[0], dataLen);
	return true;
}

bool AgoraRtcEngine::enableExtendPlayDevice(bool bEnable)
{
	int ret = 0;

	AParameter apm(*m_rtcEngine);

	if (bEnable)
		ret = apm->setParameters("{\"che.audio.external_render\":true}");
	else
		ret = apm->setParameters("{\"che.audio.external_render\":false}");
	apm->release();
	return ret == 0 ? TRUE : FALSE;
}

bool AgoraRtcEngine::setExternalAudioSource(bool bEnabled, int nSampleRate, int nChannels)
{
	RtcEngineParameters rep(m_rtcEngine);

	int nRet = rep.setExternalAudioSource(bEnabled, nSampleRate, nChannels);

	return nRet == 0 ? true : false;
}

bool AgoraRtcEngine::setRecordingAudioFrameParameters(int nSampleRate, int nChannels, int nSamplesPerCall)
{
	RtcEngineParameters rep(m_rtcEngine);
	int ret = rep.setRecordingAudioFrameParameters(nSampleRate, nChannels,  RAW_AUDIO_FRAME_OP_MODE_READ_WRITE, nSamplesPerCall);
	return ret == 0 ? true : false;
}

int AgoraRtcEngine::joinChannel(const std::string& key, const std::string& channel, unsigned int uid)
{
    int r = m_rtcEngine->joinChannel(key.data(), channel.data(), nullptr, uid);
//     if (!r)
//         emit joiningChannel();
    return r;
}

int AgoraRtcEngine::leaveChannel()
{
    int r = m_rtcEngine->leaveChannel();
//     if (!r)
//         emit leavingChannel();
    return r;
}

// int AgoraRtcEngine::muteLocalAudioStream(bool muted)
// {
//     RtcEngineParameters rep(*m_rtcEngine);
//     return rep.muteLocalAudioStream(muted);
// }

int AgoraRtcEngine::enableVideo(bool enabled)
{
    return enabled ? m_rtcEngine->enableVideo() : m_rtcEngine->disableVideo();
}

// int AgoraRtcEngine::setupLocalVideo(QWidget* view)
// {
// 	agora::rtc::view_t v = NULL;
// 	if (view != NULL)
// 	    v = reinterpret_cast<agora::rtc::view_t>(view->winId());
// 
// 	VideoCanvas canvas(v, RENDER_MODE_FIT, 0);
//     return m_rtcEngine->setupLocalVideo(canvas);
// }

int AgoraRtcEngine::setupRemoteVideo(unsigned int uid, void* view)
{
 
	agora::rtc::view_t v = reinterpret_cast<agora::rtc::view_t>(view);
	VideoCanvas canvas;// (v, RENDER_MODE_FIT, uid);
	canvas.view = v;
	canvas.renderMode = RENDER_MODE_FIT;
	canvas.uid = uid;
    return m_rtcEngine->setupRemoteVideo(canvas);
}



bool AgoraRtcEngine::keepPreRotation(bool bRotate)
{
	int ret = -1;
	AParameter apm(m_rtcEngine);
	if (bRotate)
		ret = apm->setParameters("{\"che.video.keep_prerotation\":true}");
	else
		ret = apm->setParameters("{\"che.video.keep_prerotation\":false}");
	apm.release();
	return ret == 0;
}

bool AgoraRtcEngine::setVideoProfileEx(int nWidth, int nHeight, int nFrameRate, int nBitRate)
{
    AParameter apm(m_rtcEngine);
    apm->setParameters("{\"che.video.freestyle_customer\": true}");
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
	if (!apm.get()) return false;

	if (!bEnable)
		ret = apm->setParameters("{\"che.video.local.camera_index\":1024}");
	else
		ret = apm->setParameters("{\"che.video.local.camera_index\":0}");

	apm.release();
	return ret == 0;
}
///////////////////////////////////////////////////////////////////////////////////////
//agora device
///////////////////////////////////////////////////////////////////////////////////////
int AgoraRtcEngine::getRecordingDeviceVolume()
{
    AAudioDeviceManager audioDeviceManager(m_rtcEngine);
    if (!audioDeviceManager)
        return 0;
    int vol = 0;
    if (audioDeviceManager->getRecordingDeviceVolume(&vol) == 0)
        return vol;
    return 0;
}

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

int AgoraRtcEngine::setRecordingDeviceVolume(int volume)
{
    AAudioDeviceManager audioDeviceManager(m_rtcEngine);
    if (!audioDeviceManager)
        return -1;
    return audioDeviceManager->setRecordingDeviceVolume(volume);
}

void  AgoraRtcEngine::EnableAgoraCaptureMicAudio(bool bCapture)
{
    if (m_audioObserver)
        m_audioObserver->agora_sdk_captrue_mic_audio = bCapture;
}

int AgoraRtcEngine::setPalyoutDeviceVolume(int volume)
{
    AAudioDeviceManager audioDeviceManager(m_rtcEngine);
    if (!audioDeviceManager)
        return -1;
    return audioDeviceManager->setPlaybackDeviceVolume(volume);
}

int AgoraRtcEngine::testMicrophone(bool start, int interval)
{
    agora::rtc::AAudioDeviceManager dm(m_rtcEngine);
    if (!dm)
        return -1;
    if (start)
        return dm->startRecordingDeviceTest(interval);
    else
        return dm->stopRecordingDeviceTest();
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

void AgoraRtcEngine::joinedChannelSuccess(const char* channel, unsigned int uid, int elapsed)
{
	
}

int AgoraRtcEngine::AddPublishStreamUrl(const char *url, bool transcodingEnabled)
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
	RtcEngineParameters rep(*m_rtcEngine);
	return rep.enableWebSdkInteroperability(true);
}

void AgoraRtcEngine::pushVideoFrame(struct encoder_frame* frame)
{
	if (agora_out_cx && agora_out_cy && agora_out_cx == frame->linesize[0]){
     int64_t time = GetTickCount();

     if (logAudioVideoTimestamp && logVideoFrameTimeCount < agora_fps * LOG_VIDEO_FRAME_TIME_DUARATION) {
         blog(LOG_INFO, "win-agora pushVideoFrame , obs output video frame time: %ld", time);
         logVideoFrameTimeCount++;
     }
   
	   	m_videoObserver->pushBackVideoFrame(frame->data[0], agora_out_cx*agora_out_cy * 3 / 2, time);
 }
 else {
     if (!logFirstPushVideo) {
         blog(LOG_INFO, "win-agora: pushVideoFrame failed because of width is not equal,"
             "agora:width=%d,obs width=%d\n", agora_out_cx, frame->linesize[0]);
         logFirstPushVideo = true;
     }
 }

}

void AgoraRtcEngine::logAudioFrameTimestamp()
{
    unsigned int audioTime = GetTickCount();
    if (logAudioVideoTimestamp && logAudioFrameTimeCount < LOG_AUDIO_FRAME_TIME_COUNT) {
        blog(LOG_INFO, "win-agora pushAudioFrame , obs output audio frame time: %u", audioTime);
        logAudioFrameTimeCount++;
    }
}

void AgoraRtcEngine::enableLogTimestamp(bool bEnable)
{
    logAudioVideoTimestamp = bEnable;
    m_videoObserver->Resetlog(bEnable);
    m_audioObserver->Resetlog(bEnable);
}