#pragma once

#include <QObject>
#include <memory>
#ifdef _WIN32
#include <IAgoraRtcEngine.h>
#include <IAgoraMediaEngine.h>
#else
#include <AgoraRtcKit/IAgoraRtcEngine.h>
#include <AgoraRtcKit/IAgoraMediaEngine.h>
typedef const char * LPCSTR;
#define TRUE true
#define FALSE false
#endif
#include <string>
#include "obs.h"
#include <mutex>

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
	bool IsInitialize() { return m_bInitialize; }
	bool IsJoinChannel() { return m_bJoinChannel; }
	bool InitEngine(std::string appid);

	BOOL setLogPath(std::string path);
	BOOL setClientRole(CLIENT_ROLE_TYPE role, LPCSTR lpPermissionKey = NULL);
	int  setChannelProfile(CHANNEL_PROFILE_TYPE profile);

	int enableVideo(bool enabled);
	int  setLocalVideoMirrorMode(VIDEO_MIRROR_MODE_TYPE mirrorMode);
	void startPreview();
	void stopPreview();
	void SetRecordBoost();
	int joinChannel(const std::string &key, const std::string &channel,
			unsigned uid, bool enableDual, bool muteAudio = true, 
		    bool muteVideo = true, bool loopbackRecording = false);

	int joinChannel(const std::string& key, const std::string& channel, unsigned uid);
	int leaveChannel();
	int leaveChannelCamera();
	bool keepPreRotation(bool bRotate);
	bool setVideoProfileEx(int nWidth, int nHeight, int nFrameRate, int nBitRate, bool Agora = false);
	bool setCameraEncoderConfiguration(int w, int h, int fps, int bitrate);
	void setConnection(const std::string& channel, unsigned uid);
	void enableLastmileTest(bool bEnable);
	
	void* AgoraAudioObserver_Create();
	void  AgoraAudioObserver_Destroy();
	
	int AddPublishStreamUrl(const char *url, bool transcodingEnabled);
	int RemovePublishStreamUrl(const char *url);
	int SetLiveTranscoding(const LiveTranscoding &transcoding);

	int EnableWebSdkInteroperability(bool enabled);
	//playout device
	int  getPalyoutDeviceVolume();
	int  setPalyoutDeviceVolume(int volume);
	bool getPlayoutDevices(std::vector<DEVICEINFO>& devices);
	void SetPlayoutDevice(const char* id);
	int  testSpeaker(bool start);
	void EnableAgoraCaptureMicAudio(bool bCapture);
	void PushCameraVideoFrame(struct obs_source_frame* frame);
	void PushVideoFrame(struct video_data *frame);
	void PushAudioFrame(struct encoder_frame *frame);
	void SavePcm(bool bSave);
	
	int setupRemoteVideo(unsigned int uid, void* view);
	agora::rtc::IRtcEngine* getRtcEngine() { return m_rtcEngine; }//.get();}

	int agora_fps = 15;
	int agora_out_cx = 640;
	int agora_out_cy = 360;
	int agora_video_bitrate = 500;
	std::string pcmFolder = "";
	FILE* fpPCM = nullptr;
	bool savePcm = false;
	void joinedChannelSuccess(const char* channel, unsigned int uid, int elapsed);
	int audioChannel = 2;
	int sampleRate = 44100;
	
	void logAudioFrameTimestamp();
	void enableLogTimestamp(bool bEnable);
	std::string CalculateToken(std::string appid, const std::string &key,
				   const std::string &channel, unsigned int uid,
				   unsigned int privilegeExpiredTs);

	void SetAudioProfile(int scenario, int channels, bool bHighQuality);

	void MuteAllRemoteVideo(bool bMute);
	void MuteAllRemoteAudio(bool bMute);
	void MuteRemoteVideo(unsigned int uid, bool bMute);

	void release();
	void SetJoinChannel(bool bJoin) { m_bJoinChannel = bJoin; }
signals:
	void onJoinChannelSuccess(const char* channel, unsigned int uid, int elapsed);
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
	void onClientRoleChanged(int oldRole, int newRole);
	void onSystemCPU(int cpuUsage);
private:
	friend class AgoraRtcEngineEvent;
	void SetExternalVideoFrame();
	void SetExternalVideoFrameCamera(struct obs_source_frame* frame);
private:
	
	agora::rtc::IRtcEngineEx* m_rtcEngine = nullptr;
	static AgoraRtcEngine* m_agoraEngine;
	std::unique_ptr<agora::rtc::IRtcEngineEventHandler> m_eventHandler;
	std::unique_ptr<agora::rtc::IRtcEngineEventHandler> m_eventHandlerCamera;
	bool m_bJoinChannel = false;
	bool m_bInitialize = false;
	bool logFirstPushVideo = false;
	bool bInit = false;

	agora::media::IMediaEngine* m_pMediaEngine = nullptr;
	
	int m_externalVideoFrameSize;
	enum video_format m_format;
	enum video_format m_camera_format;
	agora::media::base::ExternalVideoFrame m_externalVideoFrame;
	agora::media::base::ExternalVideoFrame m_externalVideoFrameCamera;
	int m_externalAudioFrameSize;
	static agora::media::IAudioFrameObserver::AudioFrame m_externalAudioframe;
	
	bool m_bHighQuality = false;
	AUDIO_SCENARIO_TYPE m_scenario = AUDIO_SCENARIO_DEFAULT;
	AAudioDeviceManager* m_audioDeviceManager = nullptr;
	int count = 0;

	agora::rtc::RtcConnection connection;
	std::string channelId;
	agora::rtc::uid_t localCameraUid = 0;
};

