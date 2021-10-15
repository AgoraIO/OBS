
#pragma once

#include <QMainWindow>
#include <string>
#include <memory>
#include "ui_AgoraBasic.h"
#include "../Agora/agorartcengine.hpp"
#include <obs-frontend-api.h>
#include <util/util.hpp>
#include <QTimer>
#include "obs.hpp"
#if WIN32
#include "curl.h"
#else
#include <curl/curl.h>
#endif

//class OBSBasic;
#define PREVIEW_EDGE_SIZE 10
#define REMOTE_VIDEO_ROW 4
#define REMOTE_VIDEO_COL 4
#define REMOTE_VIDEO_COUNT 16
#define GREY_COLOR_BACKGROUND 0xFF4C4C4C
#define AGORA_PREVIEW_EDGE_SIZE 10
typedef struct tagRemoteVideoInfo {
	int iRemoteVideoHLayout = -1;
	QWidget *remoteVideo;
	long long uid;
} RemoteVideoInfo, *PRemoteVideoInfo;

typedef struct tagAgoraToolSettings {
	std::string appid = "";
	std::string appCerf = "";
	std::string token = "";
	unsigned int uid = 0;
	std::string channelName = "";
	uint32_t expiredTime = 24;
	uint32_t expiredTimeTs = 0;
	bool savePersist = false;
	bool muteAllRemoteAudioVideo = false;
	std::string agora_url = "";
	int  agora_fps = 15;
	int  agora_bitrate = 0;
	int  agora_width = 1280;
	int  agora_height = 720;
	std::string rtmp_url = "";
	int rtmp_fps = 15;
	int rtmp_bitrate = 1000;
	int rtmp_width = 1280;
	int rtmp_height = 720;

	bool loopback = false;
	int audioChannel = 2;
	int scenario = 0;
	bool bHighQuality = false;
	
	int obs_bitrate = 2500;

	int videoEncoder = 0;//default agora bitrate

	bool savePersistAppid = false;
	std::string information_url = "";
	int info_mode = 0;//0:manually 1:http get
	bool SavePCM = false;
	int cpuThreshold = 95;
	bool bDualStream = false;
	bool bSendObsCamera = false;
	unsigned int camera_uid = 0;
	std::string camera_token = "";
	int  plugin_camera_fps = 15;
	int  plugin_camera_bitrate = 0;
	int  plugin_camera_width = 320;
	int  plugin_camera_height = 180;
} AgoraToolSettings, *PAgoraToolSettings;

class DisplayResizeEvent : public QObject
{
	Q_OBJECT

protected:
	bool eventFilter(QObject *obj, QEvent *event);
signals:
	void DisplayResized();
};

class AgoraBasic : public QMainWindow {
	Q_OBJECT
private:
	std::unique_ptr<Ui::AgoraBasic> ui;
	QString control_text;
	QString exit_info;
	QString start_text;
	QString starting_text;
	QString stop_text;
	QString stopping_text;
	QString settings_title;
	QString empty_channel;
	QString empty_appid_info;
	QString empty_uid;
	QString init_failed_info = "";

	QString invalidChannelError = "";
	QString invalidAppidError = "";
	QString invalidTokenExpiredError = "";
	QString invalidTokenlError = "";
	QString joinFailedInfo = "";
	QString requertTokenError = "";
	QString cpuInformation = "";
	QString emptyCameraToken = "";
	QString invalidCameraToken = "";
	AgoraToolSettings m_agoraToolSettings;
	//show remote video
	QVBoxLayout *remoteVideoLayout;
	QHBoxLayout *remoteVideoHLayout[REMOTE_VIDEO_ROW]; //4*4
	std::list<uint32_t> m_lstUids;
	std::list<uint32_t> m_lstRemoteVideoUids;
	uint32_t remote_uid = 0;
	uint32_t local_uid = 0;
	unsigned int uids[17];
	RemoteVideoInfo remoteVideoInfos[REMOTE_VIDEO_COUNT];
	//
	std::string app_id;
	uint32_t uid = 0;
	std::string channel;

	void SetLiveTranscoding();

	obs_source_t *current_source;

	video_t *video_queue;
	gs_texrender_t *texrender;
	gs_stagesurf_t *stagesurface;
	uint8_t *video_data;
	uint32_t video_linesize;

	obs_video_info ovi;
	OBSDisplay display;
	uint32_t backgroundColor = GREY_COLOR_BACKGROUND;

	DisplayResizeEvent resizeEventHandler;

	obs_output_t *output;
	obs_encoder_t *audio_encoder;

	QTimer transcodingTimer;
	QTimer showRemoteTimer;
	QTimer joinFailedTimer;//token invalid ,exapired, joinChannel second time. no callback OnConnectionStateChanged for these reasons.

	bool joinFailed = false;
	bool started = false;
	//token url
	CURL *curl = nullptr;

	std::vector<int> first2MinCpu;
	std::vector<int> lastMinCpu;

	std::vector<obs_source*> m_vecCameraSources;
	//obs_source* source_camera = nullptr;
	obs_source_t *camera_filter;
	ConfigFile globalConfig;
	ConfigFile basicConfig;
	ConfigFile globalAgoraConfig;
	void InitGlobalConfig();
	void InitBasicConfig();
	void ResetBasicConfig();
	int GetOBSBitrate();
	int GetProfilePath(char *path, size_t size, const char *file);
	//HANDLE stopSignal = NULL;
	virtual void showEvent(QShowEvent *event)override;
	virtual void hideEvent(QHideEvent *event)override;
	virtual void closeEvent(QCloseEvent *event)override;
	static bool EnumSources(void* data, obs_source_t* source);
private:
	void CreateRemoteVideos();
	void DestroyRemoteVideos();
	void ClearRemoteVideos();
	void ResetRemoteVideoWidget(int index);
	void CreateDisplay();
	bool InitializeAgoraOutput();
	bool StartAgoraOutput();
	void StopAgoraOutput();
	void joinChannel(std::string token);
	void RemoveVideoPluginFilters();
	static void OBSEvent(obs_frontend_event event, void *);
public slots:
	void on_agoraSteramButton_clicked();
	void on_settingsButton_clicked();
	void on_exitButton_clicked();
	
	// rtc envetn handler slot
	void onJoinChannelSuccess_slot(const char* channel, unsigned int uid, int elapsed);
	void onLeaveChannel_slot(const RtcStats &stats);
	void onError_slot(int err, const char *msg);
	void onUserJoined_slot(uid_t uid, int elapsed);
	void onUserOffline_slot(uid_t uid, int reason);
	void onFirstRemoteVideoDecoded_slot(uid_t uid, int width, int height, int elapsed);
	void onConnectionStateChanged_slot(int state, int reason);
	void onCameraConnectionStateChanged_slot(int state, int reason);
	void onRemoteVideoStateChanged_slot(unsigned int uid, int state, int reason, int elapsed);
	void onFirstRemoteVideoFrame_slot(unsigned uid, int width, int height, int elapsed);
	void transcoding_slot();
	void showRemote_slot();
	void onClientRoleChanged_slot(int oldRole, int newRole);
	void joinFailed_slot();
	void reuquestToken_slot(QString json, int err);
	void onSystemCPU_slot(int cpuUsage);
public:
	void ToggleAgoraDialog();
	AgoraBasic(QMainWindow *parent);
	virtual ~AgoraBasic();
	void GetAgoraSetting(AgoraToolSettings& setting) {setting = m_agoraToolSettings;};
	void SetAgoraSetting(AgoraToolSettings setting) 
	{
		m_agoraToolSettings = setting; 
	}

	void resizeEvent(QResizeEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	static void DrawPreview(void *data, uint32_t cx, uint32_t cy);
	static void RawVideoCallback(void *param, struct video_data *frame);
	
signals:
	void DisplayCreated(AgoraBasic* agora);
	void requestTokenSignal(QString, int err);
};
