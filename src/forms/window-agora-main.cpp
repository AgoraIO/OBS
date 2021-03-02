#include <QMessageBox>
#include <QWindow>
#include <stdio.h>
#include <obs-frontend-api.h>
#include <obs-properties.h>
#include "window-agora-main.hpp"
#include "../agora-ui-main.h"
#include "obs-module.h"
#include "window-agora-settings.hpp"
using namespace std;

bool DisplayResizeEvent::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::Resize) {
		emit DisplayResized();
		return true;
	}
	
	return QObject::eventFilter(obj, event);
}

bool ACloseEvent::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::Close) {
		emit AgoraClose();
		return true;
	}

	return QObject::eventFilter(obj, event);
}

AgoraBasic::AgoraBasic(QMainWindow *parent)
	: QMainWindow(parent, Qt::Dialog)
	, ui(new Ui::AgoraBasic)
	, current_source(nullptr)
	, output(nullptr)
	, audio_encoder(nullptr)
{
	ui->setupUi(this);
	ui->previewDisabledWidget->setVisible(false);
	ui->menubar->setVisible(false);

	setWindowTitle(QString("Agora RTC Tool"));
	setAttribute(Qt::WA_QuitOnClose, false);
	
	obs_frontend_push_ui_translation(obs_module_get_string);
	control_text  = tr("Agora.Main.Controls");
	start_text    = tr("Agora.Main.Start");
	starting_text = tr("Agora.Main.Starting");
	stop_text     = tr("Agora.Main.Stop");
	stopping_text = tr("Agora.Main.Stopping");
	settings_title = tr("Agora.Settings.DialogTitle");
	empty_appid_info = tr("Agora.General.EmptyAppid");
	empty_channel = tr("Agora.General.EmptyChannel");
	empty_uid = tr("Agora.General.EmptyUID");
	init_failed_info = tr("Agora.General.Init.Failed");
	
	invalidChannelError = tr("Basic.Main.Agora.Invalid.Channel");
	invalidTokenlError = tr("Basic.Main.Agora.Invalid.Token");
	invalidAppidError = tr("Basic.Main.Agora.Invalid.Appid");
	invalidTokenExpiredError = tr("Basic.Main.Agora.Token.Expired");
	
	obs_frontend_pop_ui_translation();

	ui->controlsDock->setWindowTitle(control_text);
	ui->agoraSteramButton->setText(start_text);

	connect(AgoraRtcEngine::GetInstance(), &AgoraRtcEngine::onJoinChannelSuccess, this, &AgoraBasic::onJoinChannelSuccess_slot);
	connect(AgoraRtcEngine::GetInstance(), &AgoraRtcEngine::onLeaveChannel, this, &AgoraBasic::onLeaveChannel_slot);
	connect(AgoraRtcEngine::GetInstance(), &AgoraRtcEngine::onError, this, &AgoraBasic::onError_slot);
	connect(AgoraRtcEngine::GetInstance(), &AgoraRtcEngine::onUserJoined, this, &AgoraBasic::onUserJoined_slot);
	connect(AgoraRtcEngine::GetInstance(), &AgoraRtcEngine::onUserOffline, this, &AgoraBasic::onUserOffline_slot);
	//connect(AgoraRtcEngine::GetInstance(), &AgoraRtcEngine::onFirstRemoteVideoDecoded, this, &AgoraBasic::onFirstRemoteVideoDecoded_slot);
	connect(AgoraRtcEngine::GetInstance(), &AgoraRtcEngine::onConnectionStateChanged, this, &AgoraBasic::onConnectionStateChanged_slot);
	connect(AgoraRtcEngine::GetInstance(), &AgoraRtcEngine::onRemoteVideoStateChanged, this, &AgoraBasic::onRemoteVideoStateChanged_slot);

	
	CreateRemoteVideos();
	auto addDrawCallback = [this]() {
		obs_display_add_draw_callback(display,
			AgoraBasic::DrawPreview, this);
	};
	connect(this, &AgoraBasic::DisplayCreated,addDrawCallback);
	auto displayResize = [this]() {
		struct obs_video_info ovi;

		if (obs_get_video_info(&ovi)) {
			QSize size = ui->preview->size() * ui->preview->devicePixelRatioF();
			obs_display_resize(display, size.width(), size.height());
		}
	};

	connect(&resizeEventHandler, &DisplayResizeEvent::DisplayResized, displayResize);

	
	ui->preview->setAttribute(Qt::WA_PaintOnScreen);
	ui->preview->setAttribute(Qt::WA_StaticContents);
	ui->preview->setAttribute(Qt::WA_NoSystemBackground);
	ui->preview->setAttribute(Qt::WA_OpaquePaintEvent);
	ui->preview->setAttribute(Qt::WA_DontCreateNativeAncestors);
	ui->preview->setAttribute(Qt::WA_NativeWindow);
	ui->preview->setUpdatesEnabled(false);
	ui->preview->installEventFilter(&resizeEventHandler);

	InitializeAgoraOutput();
	
	QMainWindow* mainWindow = (QMainWindow*)obs_frontend_get_main_window();
	auto closeEvent_slot = [this, mainWindow]() {
		this->close();
		mainWindow->removeEventFilter(&this->aCloseEventHandler);
		mainWindow->close();
	};
	connect(&aCloseEventHandler, &ACloseEvent::AgoraClose, closeEvent_slot);
	mainWindow->installEventFilter(&aCloseEventHandler);
}

AgoraBasic::~AgoraBasic()
{
	if (current_source)
		obs_source_release(current_source);

	if (output)
		obs_output_release(output);

	if (audio_encoder)
		obs_encoder_release(audio_encoder);

	AgoraRtcEngine::GetInstance()->ReleaseInstance();
}
void AgoraBasic::on_agoraSteramButton_clicked()
{
	QString str = ui->agoraSteramButton->text();

	if (!joinFailed && (starting_text.compare(str) == 0 ||
		stopping_text.compare(str) == 0)) {
		return;
	}

	if (start_text.compare(str) == 0) {

		if (m_agoraToolSettings.appid.empty()) {
			QMessageBox::about(nullptr, settings_title, empty_appid_info);
			return;
		}
		if (m_agoraToolSettings.channelName.empty()) {
			QMessageBox::about(nullptr, settings_title, empty_channel);
			return;
		}

		if (!m_agoraToolSettings.appCerf.empty() &&
			m_agoraToolSettings.uid == 0) {
			QMessageBox::information(NULL, QString(""), empty_uid);
			return;
		}
		if (!AgoraRtcEngine::GetInstance()->IsInitialize()
			&& !AgoraRtcEngine::GetInstance()->InitEngine(m_agoraToolSettings.appid)) {
			QMessageBox::information(NULL, QString(""), init_failed_info);
			return;
		}
		
		AgoraRtcEngine::GetInstance()->setClientRole(CLIENT_ROLE_BROADCASTER);

		std::string token = m_agoraToolSettings.token;

		if (current_source) {
			obs_get_video_info(&ovi);
			video_scale_info info;
			info.width = ovi.base_width;
			info.height = ovi.base_height;
			info.format = ovi.output_format;
			info.range = ovi.range;
			info.colorspace = ovi.colorspace;
			obs_add_raw_video_callback(&info, RawVideoCallback, (void*)this);
		}

		StartAgoraOutput();

		AgoraRtcEngine::GetInstance()->setVideoProfileEx(
			m_agoraToolSettings.agora_width,
			m_agoraToolSettings.agora_height,
			m_agoraToolSettings.agora_fps,
			m_agoraToolSettings.agora_bitrate);

		AgoraRtcEngine::GetInstance()->joinChannel(m_agoraToolSettings.token.c_str()
			,  m_agoraToolSettings.channelName.c_str(), m_agoraToolSettings.uid,
			!m_agoraToolSettings.muteAllRemoteAudioVideo, !m_agoraToolSettings.muteAllRemoteAudioVideo);
		ui->agoraSteramButton->setText(starting_text);
	}
	else {
		obs_remove_raw_video_callback(RawVideoCallback, this);
		StopAgoraOutput();
		AgoraRtcEngine::GetInstance()->stopPreview();
		AgoraRtcEngine::GetInstance()->leaveChannel();
		ui->agoraSteramButton->setText(stopping_text);
		ClearRemoteVideos();
	}
}

void AgoraBasic::showEvent(QShowEvent *event)
{
	if (!current_source)
		current_source = obs_frontend_get_current_scene();
	QMainWindow::showEvent(event);
}

void AgoraBasic::hideEvent(QHideEvent *event)
{
	QMainWindow::hideEvent(event);
}

void AgoraBasic::closeEvent(QCloseEvent *event)
{
	QString str = ui->agoraSteramButton->text();
	if (start_text.compare(str) == 0) {
		AgoraRtcEngine::GetInstance()->leaveChannel();
		obs_remove_raw_video_callback(RawVideoCallback, this);
		StopAgoraOutput();
	}
	
	QMainWindow::closeEvent(event);
}

void AgoraBasic::ToggleAgoraDialog() {
	if (!isVisible())
		setVisible(true);
	else
		setVisible(false);
}

void AgoraBasic::on_settingsButton_clicked()
{
	AgoraSettings settings(this);
	settings.setWindowIconText(settings_title);
	int ret= settings.exec();

	if (ret == QDialog::Accepted) {
		if (AgoraRtcEngine::GetInstance()->IsJoinChannel()) {
			AgoraRtcEngine::GetInstance()->MuteAllRemoteAudio(m_agoraToolSettings.muteAllRemoteAudioVideo);
			AgoraRtcEngine::GetInstance()->MuteAllRemoteVideo(m_agoraToolSettings.muteAllRemoteAudioVideo);

			if (m_lstRemoteVideoUids.size() > 0 && m_agoraToolSettings.muteAllRemoteAudioVideo) {
				ClearRemoteVideos();
				m_lstRemoteVideoUids.clear();
				if (!m_agoraToolSettings.rtmp_url.empty())
					SetLiveTranscoding();
			}
		}
	}
}

void AgoraBasic::on_exitButton_clicked()
{
	QString str = ui->agoraSteramButton->text();
	if (start_text.compare(str) != 0) {
		return;
	}
}

void AgoraBasic::SetLiveTranscoding()
{
	int count = m_lstUids.size() + 1;
	int row = 1;
	int col = 1;
	if (count == 2) {
		col = 2;
	}
	else if (count > 2 && count <= 4) {
		row = col = 2;
	}
	else if (count > 5 && count <= 6) {
		row = 2;
		col = 3;
	}
	else if (count > 6 && count <= 9) {
		row = 3;
		col = 3;
	}
	else if (count > 9 && count <= 12) {
		row = 3;
		col = 4;
	}
	else if (count > 12 && count <= 16) {
		row = 3;
		col = 4;
	}

	int w = m_agoraToolSettings.rtmp_width / col;
	int h = m_agoraToolSettings.rtmp_height / row;

	LiveTranscoding config;
	config.audioSampleRate = AUDIO_SAMPLE_RATE_48000;
	config.audioChannels = 2;
	config.width = m_agoraToolSettings.rtmp_width;   //;
	config.height = m_agoraToolSettings.rtmp_height; //;
	config.videoFramerate = m_agoraToolSettings.rtmp_fps;
	config.videoBitrate = m_agoraToolSettings.rtmp_height;
	config.videoGop = config.videoFramerate;
	config.userCount = count;
	config.watermark = nullptr;
	config.videoCodecProfile = VIDEO_CODEC_PROFILE_MAIN;
	config.transcodingUsers = new TranscodingUser[config.userCount];
	config.lowLatency = true;
	
	//config.backgroundColor = 0x262626;

	int index = 0;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			index = i * col + j;
			config.transcodingUsers[index].x = j * w;
			config.transcodingUsers[index].y = i * h;
			config.transcodingUsers[index].width = w;
			config.transcodingUsers[index].height = h;
			config.transcodingUsers[index].zOrder = 1;
			config.transcodingUsers[index].uid = uids[index];
			config.transcodingUsers[index].audioChannel = 2;
		}
	}

	AgoraRtcEngine::GetInstance()->SetLiveTranscoding(config);

	delete[] config.transcodingUsers;
	config.transcodingUsers = NULL;
}

void AgoraBasic::CreateRemoteVideos()
{
	for (int i = 0; i < REMOTE_VIDEO_COUNT; i++) {
		remoteVideoInfos[i].remoteVideo = new QWidget;
		//remoteVideos[i] = new QWidget;
		remoteVideoInfos[i].remoteVideo->setSizePolicy(
			QSizePolicy::Expanding, QSizePolicy::Expanding);
		remoteVideoInfos[i].uid = 0;
		remoteVideoInfos[i].iRemoteVideoHLayout = -1;
		remoteVideoInfos[i].remoteVideo->setUpdatesEnabled(false);
	}

	remoteVideoLayout = new QVBoxLayout();
	for (int i = 0; i < REMOTE_VIDEO_ROW; i++) {
		remoteVideoHLayout[i] = new QHBoxLayout();
		remoteVideoLayout->addLayout(remoteVideoHLayout[i]);
	}

	ui->previewLayout->addLayout(remoteVideoLayout);
}

void AgoraBasic::DestroyRemoteVideos()
{
	for (int row = 0; row < REMOTE_VIDEO_ROW; row++) {
		for (int col = 0; col < REMOTE_VIDEO_COL; col++) {
			int i = row * REMOTE_VIDEO_COL + col;
			if (remoteVideoInfos[i].remoteVideo) {
				remoteVideoHLayout[row]->removeWidget(
					remoteVideoInfos[i].remoteVideo);
			}
		}
	}

	for (int i = 0; i < REMOTE_VIDEO_ROW; i++) {
		delete remoteVideoHLayout[i];
		remoteVideoHLayout[i] = nullptr;
	}

	delete remoteVideoLayout;
	remoteVideoLayout = nullptr;
}

void AgoraBasic::ClearRemoteVideos()
{
	for (int i = 0; i < REMOTE_VIDEO_COUNT; ++i) {
		int index = remoteVideoInfos[i].iRemoteVideoHLayout;
		if (index >= 0 && remoteVideoInfos[i].uid > 0) {
			ResetRemoteVideoWidget(i);
		}
	}
}

void AgoraBasic::ResetRemoteVideoWidget(int index)
{
	remoteVideoHLayout[remoteVideoInfos[index].iRemoteVideoHLayout]
		->removeWidget(remoteVideoInfos[index].remoteVideo);
	delete remoteVideoInfos[index].remoteVideo;
	remoteVideoInfos[index].remoteVideo = new QWidget;
	remoteVideoInfos[index].remoteVideo->setSizePolicy(
		QSizePolicy::Expanding, QSizePolicy::Expanding);
	remoteVideoInfos[index].iRemoteVideoHLayout = -1;
	remoteVideoInfos[index].uid = 0;
}

void AgoraBasic::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	
	CreateDisplay();

	if (isVisible() && display) {
		QSize size = this->size();
		obs_display_resize(display, size.width(), size.height());
	}

}

void AgoraBasic::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
}

void AgoraBasic::CreateDisplay()
{
	QWindow* window = ui->preview->windowHandle();
	if (display)
		return;

	QSize size = this->size();

	gs_init_data info = {};
	info.cx = size.width();
	info.cy = size.height();
	info.format = GS_BGRA;
	info.zsformat = GS_ZS_NONE;
	
#ifdef _WIN32
	info.window.hwnd = (HWND)ui->preview->winId();
#elif __APPLE__
	info.window.view = (id)ui->preview->winId();
#else
	info.window.id = windowId;
	info.window.display = QX11Info::display();
#endif
	display = obs_display_create(&info, backgroundColor);

	emit DisplayCreated(this);
}

static inline void GetScaleAndCenterPos(int baseCX, int baseCY, int windowCX,
	int windowCY, int &x, int &y,
	float &scale)
{
	double windowAspect, baseAspect;
	int newCX, newCY;

	windowAspect = double(windowCX) / double(windowCY);
	baseAspect = double(baseCX) / double(baseCY);

	if (windowAspect > baseAspect) {
		scale = float(windowCY) / float(baseCY);
		newCX = int(double(windowCY) * baseAspect);
		newCY = windowCY;
	}
	else {
		scale = float(windowCX) / float(baseCX);
		newCX = windowCX;
		newCY = int(float(windowCX) / baseAspect);
	}

	x = windowCX / 2 - newCX / 2;
	y = windowCY / 2 - newCY / 2;
}

void AgoraBasic::DrawPreview(void *data, uint32_t cx, uint32_t cy)
{
	AgoraBasic *window = static_cast<AgoraBasic *>(data);

	if (!window->current_source)
		return;

	uint32_t sourceCX = max(obs_source_get_width(window->current_source), 1u);
	uint32_t sourceCY = max(obs_source_get_height(window->current_source), 1u);

	int x = 0, y = 0;
	int newCX, newCY;
	float scale;

	GetScaleAndCenterPos(sourceCX, sourceCY, cx, cy, x, y, scale);

	newCX = int(scale * float(sourceCX));
	newCY = int(scale * float(sourceCY));

	gs_viewport_push();
	gs_projection_push();
	gs_ortho(0.0f, float(sourceCX), 0.0f, float(sourceCY), -100.0f, 100.0f);
	gs_set_viewport(x, y, newCX, newCY);
	obs_render_main_texture_src_color_only();
	gs_projection_pop();
	gs_viewport_pop();
}

void AgoraBasic::RawVideoCallback (void *param, struct video_data *frame)
{
	struct obs_video_info ovi;
	
	if (obs_get_video_info(&ovi)) {
		
		AgoraRtcEngine::GetInstance()->PushVideoFrame(frame);
	}
}

bool AgoraBasic::InitializeAgoraOutput()
{
	audio_encoder = obs_audio_encoder_create("agora_pcm", "agora_raw_audio", nullptr, 0, nullptr);
	obs_encoder_set_audio(audio_encoder, obs_get_audio());

	obs_data_t *audio_settings = obs_data_create();

	struct obs_audio_info ai;
	obs_get_audio_info(&ai);
	uint32_t sampleRate = ai.samples_per_sec;
	int channelSetup = ai.speakers;
	obs_data_set_int(audio_settings, "SampleRate", 44100);
	obs_data_set_int(audio_settings, "ChannelSetup", 2);
	obs_encoder_update(audio_encoder, audio_settings);

	output = obs_output_create("agora_output", "agora_output",
		nullptr, NULL);

	obs_output_set_audio_encoder(output, audio_encoder, 0);
	if (!obs_output_initialize_encoders(output, 0)) {
		blog(LOG_ERROR, "initialize agora output encoder failed");
		return false;
	}
	blog(LOG_INFO, "initialize agora output encoder success");
	obs_data_release(audio_settings);
	return true;
}

bool AgoraBasic::StartAgoraOutput()
{
	if (started)
		return true;

	started = obs_output_start(output);
	if (!started) {
		obs_output_stop(output);
		blog(LOG_ERROR, "start agora_output failed");
		return false;
	}
	blog(LOG_INFO, "start agora_output success");
	return true;
}

void AgoraBasic::StopAgoraOutput()
{
	if (!output || !started)
		return;
	obs_output_force_stop(output);
	started = false;
}

void AgoraBasic::onJoinChannelSuccess_slot(const char* channel, unsigned int uid, int elapsed)
{
	uids[0] = uid;
	ui->agoraSteramButton->setText(stop_text);
	ui->exitButton->setEnabled(false);


	if (!m_agoraToolSettings.rtmp_url.empty()) {
		if (m_agoraToolSettings.rtmp_width == 0
			|| m_agoraToolSettings.rtmp_height == 0
			|| m_agoraToolSettings.rtmp_bitrate == 0
			|| m_agoraToolSettings.rtmp_fps == 0) {
			return;
		}
		SetLiveTranscoding();
		AgoraRtcEngine::GetInstance()->AddPublishStreamUrl(m_agoraToolSettings.rtmp_url.c_str(), true);
	}
}

void AgoraBasic::onLeaveChannel_slot(const RtcStats &stats)
{
	ui->agoraSteramButton->setText(start_text);
	ui->exitButton->setEnabled(true);
}

void AgoraBasic::onError_slot(int err, const char *msg)
{

}

void AgoraBasic::onUserJoined_slot(uid_t uid, int elapsed)
{
	m_lstUids.push_back(uid);
}

void AgoraBasic::onUserOffline_slot(uid_t uid, int reason)
{
	for (auto iter = m_lstUids.begin(); iter != m_lstUids.end(); ++iter) {
		if (*iter == uid) {
			m_lstUids.erase(iter);
			break;
		}
	}

	int idx = -1;
	bool bFind = false;
	for (auto iter = m_lstRemoteVideoUids.begin();
		iter != m_lstRemoteVideoUids.end(); ++iter) {
		idx++;
		if (*iter == uid) {
			bFind = true;
			m_lstRemoteVideoUids.erase(iter);
			break;
		}
	}

	if (m_lstRemoteVideoUids.size() < 16) {
		int i = 0;
		uids[i++] = loacal_uid;
		for (auto iter : m_lstRemoteVideoUids) {
			uids[i++] = iter;
		}
		SetLiveTranscoding();
	}

	if (!bFind)
		return;

	if (idx >= REMOTE_VIDEO_COUNT)
		return;

	int count = m_lstRemoteVideoUids.size() > REMOTE_VIDEO_COUNT
		? REMOTE_VIDEO_COUNT
		: m_lstRemoteVideoUids.size();
	if (count == 0) {

		AgoraRtcEngine::GetInstance()->setupRemoteVideo(remoteVideoInfos[count].uid, nullptr);
		ResetRemoteVideoWidget(count);
		return;
	}

	int row = 1;
	int col = 1;
	if (count == 2) {
		col = 2;
	}
	else if (count == 3 || count == 4) {
		row = 2;
		col = 2;
	}
	else if (count == 5 || count == 6) {
		row = 2;
		col = 3;
	}
	else if (count > 6 && count <= 9) {
		row = 3;
		col = 3;
	}
	else if (count > 9 && count <= 12) {
		row = 3;
		col = 4;
	}
	else if (count > 12) {
		row = 4;
		col = 4;
	}

	if (count == 4 || count == 9) {
		ClearRemoteVideos();
		auto iter = m_lstRemoteVideoUids.begin();
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				int index = i * col + j;
				remoteVideoInfos[index].iRemoteVideoHLayout = i;
				remoteVideoInfos[index].uid = *iter;
				AgoraRtcEngine::GetInstance()->setupRemoteVideo(*iter,
					(view_t)remoteVideoInfos[i].remoteVideo->winId());

				remoteVideoHLayout[i]->addWidget(
					remoteVideoInfos[index].remoteVideo);
				++iter;
			}
		}
	}
	else {
		for (int i = idx; i < count; i++) {
			remoteVideoInfos[i].uid = remoteVideoInfos[i + 1].uid;
			AgoraRtcEngine::GetInstance()->setupRemoteVideo(remoteVideoInfos[i].uid, (view_t)remoteVideoInfos[i].remoteVideo->winId());
		}

		ResetRemoteVideoWidget(count);
		if (m_lstRemoteVideoUids.size() >= REMOTE_VIDEO_COUNT) {
			auto iter = m_lstRemoteVideoUids.begin();
			for (int i = 0; i < REMOTE_VIDEO_COUNT; i++) {
				++iter;
			}

			remoteVideoInfos[REMOTE_VIDEO_COUNT - 1].uid = *iter;
			remoteVideoInfos[REMOTE_VIDEO_COUNT - 1].iRemoteVideoHLayout = row - 1;
			remoteVideoInfos[REMOTE_VIDEO_COUNT - 1].remoteVideo->setUpdatesEnabled(false);
			AgoraRtcEngine::GetInstance()->setupRemoteVideo(remoteVideoInfos[REMOTE_VIDEO_COUNT - 1].uid, (view_t)remoteVideoInfos[REMOTE_VIDEO_COUNT - 1].remoteVideo->winId());

			remoteVideoHLayout[row - 1]->addWidget(
				remoteVideoInfos[REMOTE_VIDEO_COUNT - 1].remoteVideo);
		}
	}
}

void AgoraBasic::onFirstRemoteVideoDecoded_slot(uid_t uid, int width, int height, int elapsed)
{
	m_lstRemoteVideoUids.push_back(uid);
	int count = m_lstRemoteVideoUids.size();
	if (count > REMOTE_VIDEO_COUNT)
		return;

	if (count == 5 || count == 10) {
		ClearRemoteVideos();
		int row = 2;
		int col = 3;
		if (count == 5) {
			row = 2;
			col = 3;
		}
		else if (count == 10) {
			row = 3;
			col = 4;
		}

		auto iter = m_lstRemoteVideoUids.begin();
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				int index = i * col + j;
				if (index >= m_lstRemoteVideoUids.size())
					break;
				remoteVideoInfos[index].iRemoteVideoHLayout = i;
				remoteVideoInfos[index].uid = *iter;

				AgoraRtcEngine::GetInstance()->setupRemoteVideo(uid, (view_t)remoteVideoInfos[index].remoteVideo->winId());
				remoteVideoHLayout[i]->addWidget(
					remoteVideoInfos[index].remoteVideo);
				++iter;
			}
		}
	}
	else {
		int row = 1;
		if (count > 2 && count <= 6) {
			row = 2;
		}
		else if (count > 6 && count <= 12)
			row = 3;
		else if (count > 12)
			row = 4;

		remoteVideoHLayout[row - 1]->addWidget(
			remoteVideoInfos[count - 1].remoteVideo);
		remoteVideoInfos[count - 1].iRemoteVideoHLayout = row - 1;
		remoteVideoInfos[count - 1].uid = uid;
		AgoraRtcEngine::GetInstance()->setupRemoteVideo(uid, (view_t)remoteVideoInfos[count - 1].remoteVideo->winId());
	}

	//set live transcoding
	if (m_lstRemoteVideoUids.size() > 15)
		return;
	int i = 0;
	uids[i++] = loacal_uid;
	for (auto iter : m_lstRemoteVideoUids) {
		uids[i++] = iter;
	}
	SetLiveTranscoding();
}

void AgoraBasic::onConnectionStateChanged_slot(int state, int reason)
{
	if (reason == 8 || reason == 9 ||
		reason == 6 || reason == 7) {
		joinFailed = true;
		std::string info = "";
		switch (reason)
		{
		case 8: //CONNECTION_CHANGED_INVALID_TOKEN
			info = invalidTokenlError.toStdString();
			break;
		case 9: //CONNECTION_CHANGED_TOKEN_EXPIRED
			info = invalidTokenExpiredError.toStdString();
			break;
		case 6: //CONNECTION_CHANGED_INVALID_APP_ID
			info = invalidAppidError.toStdString();
			break;
		case 7: //CONNECTION_CHANGED_INVALID_CHANNEL_NAME
			info = invalidChannelError.toStdString();
			break;
		default:
			break;
		}
		
		QMessageBox::critical(NULL, "Error", info.c_str());

		on_agoraSteramButton_clicked();
		joinFailed = false;
	}
}

void AgoraBasic::onRemoteVideoStateChanged_slot(unsigned int uid, int state, int reason, int elapsed)
{
	if (state == REMOTE_VIDEO_STATE_DECODING) {
		onFirstRemoteVideoDecoded_slot(uid, 0, 0, elapsed);
	}
}
