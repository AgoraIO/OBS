#pragma once

#include <QObject>
#include <memory>
#ifdef _WIN32
#include <AgoraBase.h>
#include <IAgoraRtcEngine.h>
#include <IAgoraMediaEngine.h>
#else
#include <AgoraRtcKit/IAgoraRtcEngine.h>
#include <AgoraRtcKit/IAgoraMediaEngine.h>
#include <AgoraRtcKit/AgoraBase.h>
typedef const char * LPCSTR;
#define true true
#define false false
#endif
#include <string>
#include "obs.h"
#include <mutex>
#include <map>

using namespace agora;
using namespace agora::rtc;
using namespace agora::util;
using namespace agora::base;
using namespace agora::media;

Q_DECLARE_METATYPE(RtcStats)
typedef struct _DEVICEINFO {
	std::string id;
	std::string name;
}DEVICEINFO,*PDEVICEINFO;
class AgoraRtcEngine : public QObject
{
	 Q_OBJECT
public:
	explicit AgoraRtcEngine();
	~AgoraRtcEngine();
	static AgoraRtcEngine* GetInstance();
	static void ReleaseInstance();
	bool InitEngine(std::string appid);
	void Release();
	bool SetClientRole(CLIENT_ROLE_TYPE role, LPCSTR lpPermissionKey = NULL);
	int  SetChannelProfile(CHANNEL_PROFILE_TYPE profile);
	int  EnableVideo(bool enabled);
	int  SetupRemoteVideo(unsigned int uid, void* view);

	int  JoinChannel(const std::string& key, const std::string& channel,
		 unsigned uid, bool audioProfile, bool enableDual, bool muteAudio = true,
		 bool muteVideo = true, bool loopbackRecording = false); 

	int  JoinChannel(const std::string& key, const std::string& channel, unsigned uid);
	int  LeaveChannel();
	int  LeaveChannelCamera();
	void SetConnection(const std::string& channel, unsigned uid);

	bool SetVideoEncoder(int nWidth, int nHeight, int nFrameRate, int nBitRate, bool Agora = false);
	bool SetCameraEncoderConfiguration(int w, int h, int fps, int bitrate);
	void SetAudioProfile(int scenario, int channels, bool bHighQuality);

	void EnableLastmileTest(bool bEnable);
	
	int  AddPublishStreamUrl(const char *url, bool transcodingEnabled);
	int  RemovePublishStreamUrl(const char *url);
	int  SetLiveTranscoding(const LiveTranscoding &transcoding);
	
	int  GetPalyoutDeviceVolume();
	int  SetPalyoutDeviceVolume(int volume);
	bool GetPlayoutDevices(std::vector<DEVICEINFO>& devices);
	void SetPlayoutDevice(const char* id);
	
	void* AgoraAudioObserver_Create();
	void AgoraAudioObserver_Destroy();
	void PushCameraVideoFrame(struct obs_source_frame* frame);
	void PushVideoFrame(struct video_data *frame);
	void PushAudioFrame(struct encoder_frame* frame);

	void MuteAllRemoteVideo(bool bMute);
	void MuteAllRemoteAudio(bool bMute);
	void MuteRemoteVideo(unsigned int uid, bool bMute);
	void SetPcmInfo(bool b, std::string path); 
	bool IsInitialize() { return m_initialize; }
	bool IsJoined() { return m_joined; }
	bool IsCameraJoined() { return m_cameraJoined; }
	void SetJoinFlag(bool b) { m_joined = b; }
	void SetLogInterval(int interval) {	m_logInterval = interval;}
	
	void SetVideoBuffer(int second);
	agora::rtc::IRtcEngine* getRtcEngine() { return m_rtcEngine; }
signals:
	void onJoinChannelSuccess(const char* channel, unsigned int uid, int elapsed);
	void onCameraJoinChannelSuccess(const char* channel, unsigned int uid, int elapsed);
	void onLeaveChannel(const RtcStats &stats);
	void onError(int err, const char *msg);
	void onUserJoined(unsigned int uid, int elapsed);
	void onUserOffline(unsigned int uid, int reason);
	void onFirstRemoteVideoDecoded(unsigned int uid, int width, int height,
		int elapsed);
	void onLastmileQuality(int quality);
	void onConnectionStateChanged(int state, int reason);
	void onCameraConnectionStateChanged(int state, int reason);

	void onRemoteVideoStateChanged(unsigned int uid, int state, int reason, int elapsed);
	void onFirstRemoteVideoFrame(unsigned uid, int width, int height, int elapsed);
	void onRtmpStreamingStateChanged(const char *url, int state, int errCode);
	void onSystemCPU(int cpuUsage);
private:
	friend class AgoraRtcEngineEvent;
	void SetExternalVideoFrame();
	void SetExternalVideoFrameCamera(struct obs_source_frame* frame);
private:
	
	static AgoraRtcEngine* m_agoraEngine;
	agora::rtc::IRtcEngineEx* m_rtcEngine = nullptr;
	agora::media::IMediaEngine* m_pMediaEngine = nullptr;
	std::unique_ptr<agora::rtc::IRtcEngineEventHandler> m_eventHandler;
	std::unique_ptr<agora::rtc::IRtcEngineEventHandler> m_eventHandlerCamera;
	bool m_joined = false;
	bool m_cameraJoined = false;
	bool m_initialize = false;
	// external video
	int m_externalVideoFrameSize;
	enum video_format m_format;
	enum video_format m_camera_format;
	agora::media::base::ExternalVideoFrame m_externalVideoFrame;
	agora::media::base::ExternalVideoFrame m_externalVideoFrameCamera;

	//external audio
	int m_externalAudioFrameSize;
	bool m_bHighQuality = false;
	AUDIO_SCENARIO_TYPE m_scenario = AUDIO_SCENARIO_DEFAULT;
	AAudioDeviceManager* m_audioDeviceManager = nullptr;
	static agora::media::IAudioFrameObserver::AudioFrame m_externalAudioframe;

	// camera
	agora::rtc::RtcConnection m_connection;
	std::string m_channelId;
	agora::rtc::uid_t m_localCameraUID = 0;
	
	bool m_firstVideoFrame  = true;
	bool m_firstAudioFrame  = true;
	bool m_firstCameraVideo = true;
	uint64_t m_videoFrameCount  = 0;
	uint64_t m_cameraVideoCount = 0;
	uint64_t m_audioFrameCount  = 0;

	int64_t m_firstVideoFrameTs  = 0;
	int64_t m_firstCameraFrameTs = 0;
	int64_t m_firstAudioFrameTs  = 0;

	uint64_t m_logInterval  = 20;//default 20 seconds log once

	int m_videoFrameRate = 15;
	int m_agoraOutCX = 640;
	int m_agoraOutCY = 360;
	FILE* m_pcm = nullptr;
	bool m_savePcm = false;
	std::string m_pcmPath = "";
	int m_sampleRate = 48000;
	int m_audioChannel = 2;
	
	std::map<video_format, std::string> mapOBSVideoFormat;
	std::map<agora::media::base::VIDEO_PIXEL_FORMAT, std::string> mapVideoFormat;
	std::vector<agora::rtc::AUDIO_SCENARIO_TYPE> audioScenarios;
};
#define rtcEngine AgoraRtcEngine::GetInstance() 

