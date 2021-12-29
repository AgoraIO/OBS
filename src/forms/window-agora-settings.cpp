#include <obs.hpp>
#include <util/util.hpp>
#include <util/lexer.h>
#include <graphics/math-defs.h>
#include <initializer_list>
#include <sstream>
#include <QCompleter>
#include <QGuiApplication>
#include <QLineEdit>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDirIterator>
#include <QVariant>
#include <QTreeView>
#include <QScreen>
#include <QStandardItemModel>
#include <QSpacerItem>
#include <obs-frontend-api.h>
#include "obs-module.h"
#include "window-agora-settings.hpp"
#include "window-agora-main.hpp"
//agora
#include <QSettings>
#include <QFileDialog>
//end
#define COMBO_CHANGED   SIGNAL(currentIndexChanged(int))
#define EDIT_CHANGED    SIGNAL(textChanged(const QString &))
#define CBEDIT_CHANGED  SIGNAL(editTextChanged(const QString &))
#define CHECK_CHANGED   SIGNAL(clicked(bool))
#define SCROLL_CHANGED  SIGNAL(valueChanged(int))
#define DSCROLL_CHANGED SIGNAL(valueChanged(double))

#define TOGGLE_CHANGED  SIGNAL(toggled(bool))
#define GENERAL_CHANGED SLOT(GeneralChanged())
#define AUDIO_CHANGED   SLOT(AudioChanged())
#define VIDEO_CHANGED   SLOT(VideoChanged())
#define RTMP_CHANGED     SLOT(RtmpChanged())
#define SPINBOX_CHANGED   SIGNAL(valueChanged(int))
AgoraSettings::AgoraSettings(QWidget *parent)
	: QDialog(parent),
	main(qobject_cast<AgoraBasic *>(parent)),
	ui(new Ui::AgoraSettings)
{
	ui->setupUi(this);
	//hide 
	ui->label_45->hide();
	ui->lineEditExpiredTs->hide();
	ui->label_8->hide();
	ui->label_10->hide();
	ui->label_5->hide();

	ui->agoraResolution->hide();
	ui->cmbAgoraFPS->hide();
	ui->cmbAgoraVideoDevice->hide();
	//hide end
	//Apply button disabled until change.
	EnableApplyButton(false);
	ui->label_5->hide();
	ui->cmbAgoraVideoDevice->hide();
	ui->lineEditLogInterval->setText(QString("20"));
	//load text
	obs_frontend_push_ui_translation(obs_module_get_string);
	
	//general
	ui->labelGetInfoMode->setText(tr("Agora.Settings.GetInfo.Mode"));
	ui->cmbGetMode->setItemText(0, tr("Agora.Settings.GetInfo.Mode.Manaul"));
	ui->cmbGetMode->setItemText(1, tr("Agora.Settings.GetInfo.Mode.Http.Get"));
	ui->cmbGetMode->setCurrentIndex(0);
	ui->labelGetInfoMode_2->setText(tr("Agora.Settings.GetInfo.Mode.Information"));
	ui->generalGroupBox->setTitle(tr("Agora.Settings.General"));
	ui->loadConfigFileLabel->setText(tr("Basic.Settigs.Agora.LoadConfig"));
	ui->label_appid->setText(tr("Basic.Settings.Agora.APPID"));
	ui->labelToken->setText(tr("Basic.Settings.Agora.APPTOKEN"));
	ui->labelAppCertificate->setText(tr("Basic.Settings.Agora.APPCERTIFICATE"));
	ui->label_45->setText(tr("Basic.Settings.Agora.Token.Expired"));
	ui->labelChannelName->setText(tr("Basic.Settings.Agora.ChannelName"));
	ui->labelUID->setText(tr("Basic.Settings.Agora.UID"));
	ui->chkPersistSaving->setText(tr("Basic.Settings.Agora.PersistSave"));
	ui->chkMuteAllRemoteAV->setText(tr("Basic.Settings.Agora.MutAllRemoteAudioVideo"));
	ui->loadConfigButton->setText(tr("Basic.Settigs.Agora.LoadConfigButton"));
	ui->buttonAppid->setText(tr("Agora.General.Appid.Set"));
    ui->labUrl->setText(tr("Agora.Settings.Agora.APPTOKEN.URL"));
	ui->chkDualStream->setText(tr("Agora.Settings.DualStream"));
	ui->labelLogInterval->setText(tr("Plugin.Settings.Log.Interval"));
	startTestNet = tr("Agora.Setting.TestNet.Start");
	stopTestNet = tr("Agora.Setting.TestNet.Stop");
	ui->chkSavePCM->setText(tr("Basic.Settings.Agora.Save.PCM"));
	ui->labSystemCPU->setText(tr("Agora.CPU.Threshold"));
	qualityUnknown = tr("Agora.Test.Network.Result.Unknown");
	qualityExcellent= tr("Agora.Test.Network.Result.Excellent");
	qualityGood= tr("Agora.Test.Network.Result.Good");
	qualityPoor= tr("Agora.Test.Network.Result.Poor");
	qualityBad= tr("Agora.Test.Network.Result.Bad");
	qualityVBad= tr("Agora.Test.Network.Result.VBad");
	qualityDown= tr("Agora.Test.Network.Result.Down");
	qualityUnSupported= tr("Agora.Test.Network.Result.UnSupported");
	qualityDetecting= tr("Agora.Test.Network.Result.Detecting");
	testingNet = tr("Agora.Network.Testing");
	
	errEmptyCameraUID = tr("Plugin.OBS.Camera.UID.Empty");
	errSameUID = tr("Plugin.OBS.Camera.UID.Conflict");

	testingNetInfo = tr("Agora.Network.Testing.Info");

	ui->labeCameraUID->setText(tr("Plugin.Settings.Camera.UID"));
	ui->chkObsCamera->setText(tr("Plugin.Settings.SendObsCamera"));
	
	ui->labelCameraToken->setText(tr("Plugin.Settings.Camera.Token"));
#if WIN32
#else
	ui->labUrl->hide();
	ui->lineEditUrl->hide();
#endif
	//Audio
	ui->audioRecordingDevicesGroupBox->setTitle(tr("Agora.Settings.Recording"));
	ui->label_2->setText(tr("Agora.Record.Devices"));
	ui->label_3->setText(tr("Agora.Record.Devices.Volume"));
	ui->audioPlayGroupBox->setTitle(tr("Agora.Settings.Playout.Devices"));
	ui->playoutDeviceLabel->setText(tr("Agora.Playout.Devices"));
	ui->label->setText(tr("Agora.Payout.Devices.Volume"));
	ui->chkAudioHighQuality->setText(tr("Basic.Settings.Agora.AudioProfile.High"));
	ui->label_2->setText(tr("Basic.Settings.Audio.SampleRate")); 
	int index = 0;
	//samplerate
	ui->recordSampleRate->addItem("48kHz");
	//channel
	index = 0;
	ui->cmbRecordChannelSetup->setItemText(0, tr("Mono"));
	ui->cmbRecordChannelSetup->setItemText(1, tr("Stereo"));

	AgoraToolSettings settings;
	main->GetAgoraSetting(settings);
	if (settings.audioChannel == 2)
		ui->cmbRecordChannelSetup->setCurrentIndex(1);
	else
		ui->cmbRecordChannelSetup->setCurrentIndex(0);
	//audio profile
	index = 0; 
	ui->cmbScenario->setItemText(index++, tr("Basic.Settings.Agora.AudioProfile.DefaultScenario"));
	ui->cmbScenario->setItemText(index++, tr("Basic.Settings.Agora.AudioProfile.ChatRoomScenario"));
	ui->cmbScenario->setItemText(index++, tr("Basic.Settings.Agora.AudioProfile.EducationScenario"));
	ui->cmbScenario->setItemText(index++, tr("Basic.Settings.Agora.AudioProfile.GameStreamingScenario"));
	ui->cmbScenario->setItemText(index++, tr("Basic.Settings.Agora.AudioProfile.ShowRoomScenario"));
	ui->cmbScenario->setItemText(index++, tr("Basic.Settings.Agora.AudioProfile.ChatRoomGameScenario"));
	ui->cmbScenario->setItemText(index++, tr("Basic.Settings.Agora.AudioProfile.IOTScenario"));
	ui->cmbScenario->setItemText(index++, tr("Basic.Settings.Agora.AudioProfile.MettingScenario"));

	ui->label_3->setText(tr("Basic.Settings.Audio.Channels"));
	ui->label_6->setText(tr("Basic.Settings.Agora.AudioProfile.Scenario"));

	ui->label_8->setText(tr("Agora.Settings.Video.BaseResolution"));
	ui->label_10->setText(tr("Agora.Settings.Video.FPS"));
	ui->label_4->setText(tr("Agora.Settings.Video.Birate"));
	ui->label_5->setText(tr("Agora.Settings.Video.Devices"));
	int fps_index = 0;
	ui->cmbAgoraFPS->setItemText(fps_index++, tr("Agora.Settings.Video.FPS5"));
	ui->cmbAgoraFPS->setItemText(fps_index++, tr("Agora.Settings.Video.FPS7"));
	ui->cmbAgoraFPS->setItemText(fps_index++, tr("Agora.Settings.Video.FPS10"));
	ui->cmbAgoraFPS->setItemText(fps_index++, tr("Agora.Settings.Video.FPS15"));
	ui->cmbAgoraFPS->setItemText(fps_index++, tr("Agora.Settings.Video.FPS24"));
	ui->cmbAgoraFPS->setItemText(fps_index++, tr("Agora.Settings.Video.FPS30"));
	ui->cmbAgoraFPS->setItemText(fps_index++, tr("Agora.Settings.Video.FPS60"));

	ui->cmbAgoraBitrate->setItemText(0, tr("Agora.Bitrate.Default"));
	ui->cmbAgoraBitrate->setItemText(1, tr("Agora.Bitrate.Compatible"));
	ui->cmbAgoraBitrate->setItemText(2, tr("Agora.Bitrate.Standard"));

	fps_index = 0;
	ui->cmbCameraFPS->setItemText(fps_index++, tr("Agora.Settings.Video.FPS5"));
	ui->cmbCameraFPS->setItemText(fps_index++, tr("Agora.Settings.Video.FPS7"));
	ui->cmbCameraFPS->setItemText(fps_index++, tr("Agora.Settings.Video.FPS10"));
	ui->cmbCameraFPS->setItemText(fps_index++, tr("Agora.Settings.Video.FPS15"));

	ui->cmbCameraBitrate->setItemText(0, tr("Agora.Bitrate.Default"));
	ui->cmbCameraBitrate->setItemText(1, tr("Agora.Bitrate.Compatible"));
	ui->cmbCameraBitrate->setItemText(2, tr("Agora.Bitrate.Standard"));
	//listwidget
	ui->listWidget->item(0)->setText(tr("Agora.Settings.General"));
	ui->listWidget->item(1)->setText(tr("Agora.Settings.Audio"));
	ui->listWidget->item(2)->setText(tr("Agora.Settings.Video"));
	ui->listWidget->item(3)->setText(tr("Agora.Settings.Rtmp"));
	ui->listWidget->item(4)->setText(tr("Agora.Settings.NetworkTest"));

	ui->labelAgoraRTmp->setText(tr("Agora.Settings.Rtmp.Url")); 
	ui->labelAgoraRtmpFPS->setText(tr("Agora.Settings.Rtmp.FPS"));
	ui->labelRtmpBitrate->setText(tr("Agora.Settings.Rtmp.Bitrate"));
	ui->labelRtmpWidth->setText(tr("Agora.Settings.Rtmp.Width"));
	ui->labelRtmpHeight->setText(tr("Agora.Settings.Rtmp.Height"));

	ui->lineEditExpiredTs->hide();
	ui->label_45->hide();
	//information
	empty_appid_info = tr("Agora.General.EmptyAppid");
	init_failed_info = tr("Agora.General.Init.Failed");
	persistSaveAppid = tr("Basic.Settings.Agora.PersistSaveAppid");
	persistSaveAppidInfo = tr("Basic.Settings.Agora.PersistSaveAppidInfo");
	ui->baseAspect->setText(tr(""));
	emptyUrlError = tr("Plugin.Settings.Error.EmptyUrl");

	ui->chkPersistSaveAppid->setText(persistSaveAppid);
	//video encoder
	ui->labelVideoEncoder->setText(tr("Agora.Settings.Video.Encoder"));
	ui->labelFPSResolution->setText(tr("Agora.Settings.Video.FPS.Resolution"));
	ui->cmbVideoEncoder->setItemText(0, tr("Agora.Settings.Video.Agora.Bitrate"));
	ui->cmbVideoEncoder->setItemText(1, tr("Agora.Settings.Video.OBS.Bitrate"));
	ui->cmbVideoEncoder->setCurrentIndex(0);

	ui->labCameraEncoderRes->setText(tr("Camera.Encoder.Settings.Resolution"));
	ui->labCameraEncoderBitrate->setText(tr("Camera.Encoder.Settings.Bitrate"));
	ui->labCameraEncoderFPS->setText(tr("Camera.Encoder.Settings.FPS"));
	obs_frontend_pop_ui_translation();
	ui->btnNetworkTest->setText(startTestNet);
	ui->labelTestNetWork->setText("");
	ui->cmbAgoraFPS->setCurrentIndex(3);
	fps_index = 0;
	agora_fps[fps_index++] = 5;
	agora_fps[fps_index++] = 7;
	agora_fps[fps_index++] = 10;
	agora_fps[fps_index++] = 15;
	agora_fps[fps_index++] = 24;
	agora_fps[fps_index++] = 30;
	agora_fps[fps_index++] = 60;
	agora_bitrate[0] = DEFAULT_MIN_BITRATE;
	agora_bitrate[1] = COMPATIBLE_BITRATE;
	agora_bitrate[2] = STANDARD_BITRATE;
	
	ui->chkAutoLoadConfig->setVisible(false);
	ui->lineEditAppCertificate->setVisible(false);
	ui->labelAppCertificate->setVisible(false);
	
	RESOLUTION dimmision;
	dimmision.width = 640;
	dimmision.height = 360;
	m_vecResolution.push_back(dimmision);
	dimmision.width = 640;
	dimmision.height = 480;
	m_vecResolution.push_back(dimmision);
	dimmision.width = 960;
	dimmision.height = 540;
	m_vecResolution.push_back(dimmision);
	dimmision.width = 960;
	dimmision.height = 720;
	m_vecResolution.push_back(dimmision);
	dimmision.width = 1280;
	dimmision.height = 720;
	m_vecResolution.push_back(dimmision);
	dimmision.width = 1920;
	dimmision.height = 1080;
	m_vecResolution.push_back(dimmision);

	//camera resolution
	dimmision.width  = 320;
	dimmision.height = 180;
	m_vecCameraResolution.push_back(dimmision);
	dimmision.width  = 320;
	dimmision.height = 240;
	m_vecCameraResolution.push_back(dimmision);
	dimmision.width  = 180;
	dimmision.height = 320;
	//m_vecCameraResolution.push_back(dimmision);
	dimmision.width  = 240;
	dimmision.height = 320;
	//m_vecCameraResolution.push_back(dimmision);
	
	LoadGeneralSettings();
	LoadAudioSettings();
	LoadVideoSettings();
	LoadRtmpSettings();
	//
	HookWidget(ui->lineEditUrl, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditAppid, EDIT_CHANGED, GENERAL_CHANGED); 
	HookWidget(ui->lineEditLogInterval, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditToken, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditAppCertificate, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditExpiredTs, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditChannel, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditUID, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->cmbGetMode, COMBO_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->chkPersistSaving, CHECK_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->chkMuteAllRemoteAV, CHECK_CHANGED, GENERAL_CHANGED);

	HookWidget(ui->chkDualStream, CHECK_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->chkObsCamera, CHECK_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditCameraUID , EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditCameraToken, EDIT_CHANGED, GENERAL_CHANGED);

	HookWidget(ui->playoutDevices, COMBO_CHANGED, AUDIO_CHANGED);
	HookWidget(ui->recordSampleRate, COMBO_CHANGED, AUDIO_CHANGED);
	HookWidget(ui->cmbRecordChannelSetup, COMBO_CHANGED, AUDIO_CHANGED);
	HookWidget(ui->cmbScenario, COMBO_CHANGED, AUDIO_CHANGED);
	HookWidget(ui->chkAudioHighQuality, CHECK_CHANGED, AUDIO_CHANGED);

	HookWidget(ui->cmbAgoraFPS, COMBO_CHANGED, VIDEO_CHANGED);
	HookWidget(ui->cmbAgoraBitrate, COMBO_CHANGED, VIDEO_CHANGED);
	HookWidget(ui->agoraResolution, COMBO_CHANGED, VIDEO_CHANGED);
	HookWidget(ui->cmbAgoraVideoDevice, COMBO_CHANGED, VIDEO_CHANGED);
	HookWidget(ui->cmbVideoEncoder, COMBO_CHANGED, VIDEO_CHANGED);

	HookWidget(ui->cmbCameraBitrate, COMBO_CHANGED, VIDEO_CHANGED);
	HookWidget(ui->cmbCameraFPS, COMBO_CHANGED, VIDEO_CHANGED);
	HookWidget(ui->cmbCameraResoltuion, COMBO_CHANGED, VIDEO_CHANGED);

	HookWidget(ui->lineEditAgoraRTmp, EDIT_CHANGED, RTMP_CHANGED);
	HookWidget(ui->lineEditAgoraRtmpFPS, EDIT_CHANGED, RTMP_CHANGED);
	HookWidget(ui->lineEditAgoraRtmpWidth, EDIT_CHANGED, RTMP_CHANGED);
	HookWidget(ui->lineEditAgoraRtmpHeight, EDIT_CHANGED, RTMP_CHANGED);
	HookWidget(ui->lineEditAgoraRtmpBitrate, EDIT_CHANGED, RTMP_CHANGED);

	HookWidget(ui->chkPersistSaving, CHECK_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->chkSavePCM, CHECK_CHANGED, AUDIO_CHANGED);
	HookWidget(ui->spinCPU, SPINBOX_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->chkLoopback, CHECK_CHANGED, AUDIO_CHANGED);

	connect(ui->chkPersistSaveAppid, &QCheckBox::toggled, this, &AgoraSettings::onChkSaveAppidSettings);
	connect(ui->chkObsCamera, &QCheckBox::toggled, this, &AgoraSettings::on_chkObsCamera_check);
	connect(rtcEngine, &AgoraRtcEngine::onLastmileQuality, this, &AgoraSettings::OnLastmileTest);
}

AgoraSettings::~AgoraSettings()
{
	
}

void AgoraSettings::HookWidget(QWidget *widget, const char *signal,
	const char *slot)
{
	QObject::connect(widget, signal, this, slot);
	widget->setProperty("changed", QVariant(false));
}

void AgoraSettings::GeneralChanged()
{
	if (!loading) {
		generalChanged = true;
		sender()->setProperty("changed", QVariant(true));
		EnableApplyButton(true);
	}
}

void AgoraSettings::VideoChanged()
{
	if (!loading) {
		videoChanged = true;
		sender()->setProperty("changed", QVariant(true));
		EnableApplyButton(true);
	}
}

void AgoraSettings::AudioChanged()
{
	if (!loading) {
		audioChanged = true;
		sender()->setProperty("changed", QVariant(true));
		EnableApplyButton(true);
	}
}

void AgoraSettings::RtmpChanged()
{
	if (!loading) {
		rtmpChanged = true;
		sender()->setProperty("changed", QVariant(true));
		EnableApplyButton(true);
	}
}

void AgoraSettings::ClearChanged()
{
	generalChanged = false;
	audioChanged = false;
	videoChanged = false;
	rtmpChanged = false;
}

void AgoraSettings::SaveAudioSettings()
{
	std::vector<DEVICEINFO> playoutDevices, recordDevices;
	rtcEngine->GetPlayoutDevices(playoutDevices);
	
	QString name = ui->playoutDevices->currentText();
	if (!name.isEmpty()) {
		for (int i = 0; i < playoutDevices.size(); ++i) {
			if (playoutDevices[i].name.compare(name.toUtf8().toStdString()) == 0) {
				rtcEngine->SetPlayoutDevice(playoutDevices[i].id.c_str());
				break;
			}
		}
	}

	AgoraToolSettings settings;
	main->GetAgoraSetting(settings);
	settings.bHighQuality = ui->chkAudioHighQuality->isChecked();
	settings.scenario     = ui->cmbScenario->currentIndex();
	settings.audioChannel = ui->cmbRecordChannelSetup->currentIndex() + 1;
	settings.savePcm = ui->chkSavePCM->isChecked();
	settings.loopback = ui->chkLoopback->isChecked();
	main->SetAgoraSetting(settings);
	rtcEngine->SetAudioProfile(settings.scenario, settings.audioChannel, settings.bHighQuality);
}

void AgoraSettings::SaveVideoSettings()
{
	AgoraToolSettings settings;
	main->GetAgoraSetting(settings);

	settings.agora_fps     = agora_fps[ui->cmbAgoraFPS->currentIndex()];
	settings.agora_bitrate = agora_bitrate[ui->cmbAgoraBitrate->currentIndex()];
	settings.agora_width   = m_vecResolution[ui->agoraResolution->currentIndex()].width;
	settings.agora_height  = m_vecResolution[ui->agoraResolution->currentIndex()].height;
	settings.videoEncoder  = ui->cmbVideoEncoder->currentIndex();

	settings.plugin_camera_bitrate = agora_bitrate[ui->cmbCameraBitrate->currentIndex()];
	settings.plugin_camera_fps     = agora_fps[ui->cmbCameraFPS->currentIndex()];
	settings.plugin_camera_width   = m_vecCameraResolution[ui->cmbCameraResoltuion->currentIndex()].width;
	settings.plugin_camera_height  = m_vecCameraResolution[ui->cmbCameraResoltuion->currentIndex()].height;
	main->SetAgoraSetting(settings);
}

void AgoraSettings::SaveGeneralSettings()
{
	AgoraToolSettings settings;
	main->GetAgoraSetting(settings);
	QString strAppid = ui->lineEditAppid->text();
	strAppid = strAppid.trimmed();
	if (rtcEngine->IsInitialize() && ui->cmbGetMode->currentIndex() == 0
		&& !settings.appid.empty() && settings.appid.compare(strAppid.toStdString()) != 0)
		appid_changed = true;
	settings.appid = strAppid.toStdString();

	settings.appCerf = ui->lineEditAppCertificate->text().trimmed().toStdString();
	settings.token = ui->lineEditToken->text().trimmed().toStdString();
	settings.channelName = ui->lineEditChannel->text().trimmed().toStdString();
	settings.information_url = ui->lineEditUrl->text().trimmed().toStdString();
	settings.info_mode = ui->cmbGetMode->currentIndex();
	if (!strAppid.isEmpty())
		settings.appid = strAppid.toStdString();
	settings.cpuThreshold = ui->spinCPU->value();
	QString strUid = ui->lineEditUID->text();
	if (strUid.length() > 0)
		settings.uid = strtoul(strUid.toStdString().data(), NULL, 10);
	else
		settings.uid = 0;
	QString strExpired = ui->lineEditExpiredTs->text();
	if (strExpired.length() > 0)
		settings.expiredTime =
		strtoul(strExpired.toStdString().data(), NULL, 10);
	else
		settings.expiredTime = AGORA_SETTINGS_EXPIREDTS;
	settings.expiredTimeTs = settings.expiredTime * 60 * 60;
	settings.savePersist = ui->chkPersistSaving->isChecked();
	settings.muteAllRemoteAudioVideo = ui->chkMuteAllRemoteAV->isChecked();
	settings.savePersistAppid = ui->chkPersistSaveAppid->isChecked();

	settings.bDualStream = ui->chkDualStream->isChecked();
	QString strCameraUid = ui->lineEditCameraUID->text();
	if (strCameraUid.length() > 0)
  		settings.camera_uid = strtoul(strCameraUid.toStdString().data(), NULL, 10);
	else
		settings.camera_uid = 0;
	settings.bSendObsCamera = ui->chkObsCamera->isChecked();
	settings.camera_token = ui->lineEditCameraToken->text().toStdString();
	settings.cpuThreshold = ui->spinCPU->value();

	QString str = ui->lineEditLogInterval->text();
	if (str.isEmpty()) {
		str = QString("20");
		ui->lineEditLogInterval->setText(QString(20));
	}
	settings.logInterval = strtol(str.toStdString().data(), NULL, 10);

	SaveCheckBox(ui->chkPersistSaving, "AgoraSettings", "PersistSave");
	if (settings.savePersistAppid && !strAppid.isEmpty())
		SaveEdit(ui->lineEditAppid, "AgoraSettings", "AppId");

	if (settings.savePersist) {
		SaveEdit(ui->lineEditUrl, "AgoraSettings", "InformationUrl");

		if (!strUid.isEmpty())
			SaveEdit(ui->lineEditUID, "AgoraSettings", "uid");
		if (!strExpired.isEmpty())
			SaveEdit(ui->lineEditExpiredTs, "AgoraSettings",
				"TokenExpired");

		if (!settings.appCerf.empty())
			SaveEdit(ui->lineEditToken, "AgoraSettings",
				"AppCertificate");
		if (!settings.channelName.empty())
			SaveEdit(ui->lineEditChannel, "AgoraSettings",
				"ChannelName");

		if (!settings.rtmp_url.empty())
			SaveEdit(ui->lineEditAgoraRTmp, "AgoraSettings",
				"AgoraRtmpUrl");

		SaveEdit(ui->lineEditAgoraRtmpFPS, "AgoraSettings",
			"AgoraRtmpFPS");
		SaveEdit(ui->lineEditAgoraRtmpBitrate, "AgoraSettings",
			"AgoraRtmpBirate");

		SaveEdit(ui->lineEditAgoraRtmpWidth, "AgoraSettings",
			"AgoraRtmpWidth");
		SaveEdit(ui->lineEditAgoraRtmpHeight, "AgoraSettings",
			"AgoraRtmpHeight");

		SaveCheckBox(ui->chkMuteAllRemoteAV, "AgoraSettings",
			"MuteAllRemoteAudioVideo",
			settings.muteAllRemoteAudioVideo);

		SaveCheckBox(ui->chkDualStream, "AgoraSettings",
			"DualStream",
			settings.bDualStream);

		SaveCheckBox(ui->chkObsCamera, "AgoraSettings",
			"SendOBSCamera",
			settings.bSendObsCamera);
	}

	main->SetAgoraSetting(settings);

}


void AgoraSettings::SaveRtmpSetting()
{
	AgoraToolSettings settings;
	main->GetAgoraSetting(settings);
	settings.rtmp_fps = ui->lineEditAgoraRtmpFPS->text().toInt();
	settings.rtmp_bitrate = ui->lineEditAgoraRtmpBitrate->text().toInt();
	settings.rtmp_width = ui->lineEditAgoraRtmpWidth->text().toInt();
	settings.rtmp_height = ui->lineEditAgoraRtmpHeight->text().toInt();

	settings.rtmp_url = ui->lineEditAgoraRTmp->text().toStdString();

	main->SetAgoraSetting(settings);
}

void AgoraSettings::SaveCheckBox(QAbstractButton *widget,
	const char *section, const char *value,
	bool invert)
{
	if (WidgetChanged(widget)) {
		bool checked = widget->isChecked();
		if (invert)
			checked = !checked;

		//config_set_bool(main->Config(), section, value, checked);
	}
}


void AgoraSettings::SaveEdit(QLineEdit *widget, const char *section,
	const char *value)
{
	if (WidgetChanged(widget)) {
		//	config_set_string(main->Config(), section, value,
		//		QT_TO_UTF8(widget->text()));
	}
}


void AgoraSettings::LoadGeneralSettings()
{
	AgoraToolSettings settings;
	main->GetAgoraSetting(settings);

	ui->lineEditAppid->setText(QString::fromUtf8(settings.appid.data()));
	ui->lineEditToken->setText(QString::fromUtf8(settings.token.data()));
	ui->lineEditUrl->setText(QString::fromUtf8(settings.information_url.data()));
	ui->lineEditAppCertificate->setText(QString::fromUtf8(settings.appCerf.data()));
	ui->lineEditChannel->setText(
		QString::fromUtf8(settings.channelName.data()));
	if (settings.uid > 0) {
		QString strUid = QString("%1").arg(settings.uid);
		ui->lineEditUID->setText(strUid);
	}
	QString str = QString("%1").arg(settings.logInterval);
	ui->lineEditLogInterval->setText(str);

	ui->cmbGetMode->setCurrentIndex(settings.info_mode);
	ui->chkPersistSaving->setChecked(settings.savePersist);
	ui->chkPersistSaveAppid->setChecked(settings.savePersistAppid);
	ui->chkMuteAllRemoteAV->setChecked(settings.muteAllRemoteAudioVideo);
	ui->chkDualStream->setChecked(settings.bDualStream);
	QString strExpired = QString("%1").arg(settings.expiredTime);
	ui->lineEditExpiredTs->setText(strExpired);
	
	ui->lineEditAgoraRTmp->setText(
		QString::fromUtf8(settings.rtmp_url.data()));

	ui->lineEditAgoraRtmpFPS->setText(
		QString("%1").arg(settings.rtmp_fps));
	ui->lineEditAgoraRtmpBitrate->setText(
		QString("%1").arg(settings.rtmp_bitrate));

	ui->lineEditAgoraRtmpWidth->setText(QString("%1").arg(settings.rtmp_width));
	ui->lineEditAgoraRtmpHeight->setText(QString("%1").arg(settings.rtmp_height));
	ui->spinCPU->setValue(settings.cpuThreshold);

	ui->chkObsCamera->setChecked(settings.bSendObsCamera);
	if (settings.camera_uid > 0) {
		QString strCameraUid = QString("%1").arg(settings.camera_uid);
		ui->lineEditCameraUID->setText(strCameraUid);
	}
	ui->lineEditCameraToken->setText(QString::fromUtf8(settings.camera_token.data()));
	loading = false;

}

void AgoraSettings::LoadAudioDevice()
{
	ui->playoutDevices->clear();
	std::vector<DEVICEINFO> playoutDevices;
	rtcEngine->GetPlayoutDevices(playoutDevices);
	for (int i = 0; i < playoutDevices.size(); ++i) {
		ui->playoutDevices->insertItem(i, QString::fromUtf8(playoutDevices[i].name.c_str()));
	}
}

void AgoraSettings::LoadAudioSettings()
{
	loading = true;
	LoadAudioDevice();


	AgoraToolSettings settings;
	main->GetAgoraSetting(settings);
	ui->chkAudioHighQuality->setChecked(settings.bHighQuality);
	
	ui->cmbScenario->setCurrentIndex(settings.scenario);
	ui->chkSavePCM->setChecked(settings.savePcm);
	ui->chkLoopback->setChecked(settings.loopback);
	ui->cmbRecordChannelSetup->setCurrentIndex(settings.audioChannel - 1);
	loading = false;
}


static std::string ResString(uint32_t cx, uint32_t cy)
{
	std::stringstream res;
	res << cx << "x" << cy;
	return res.str();
}

void AgoraSettings::LoadVideoSettings()
{
	loading = true;
	
	auto addRes = [this](int cx, int cy) {
		QString res = ResString(cx, cy).c_str();
		if (ui->agoraResolution->findText(res) == -1)
			ui->agoraResolution->addItem(res);
	};
	ui->agoraResolution->clear();
	

	AgoraToolSettings setting;
	main->GetAgoraSetting(setting);
	for (int i = 0; i < FPS_NUM; ++i) {
		if (agora_fps[i] == setting.agora_fps) {
			ui->cmbAgoraFPS->setCurrentIndex(i);
			break;
		}
	}
	
	for (int i = 0; i < 3; ++i) {
		if (agora_bitrate[i] == setting.agora_bitrate) {
			ui->cmbAgoraBitrate->setCurrentIndex(i);
			break;
		}
	}
	ui->cmbVideoEncoder->setCurrentIndex(setting.videoEncoder);
	
	for (int i = 0; i < m_vecResolution.size(); i++) {
		addRes(m_vecResolution[i].width, m_vecResolution[i].height);
		if (m_vecResolution[i].width == setting.agora_width
			&& m_vecResolution[i].height == setting.agora_height)
			ui->agoraResolution->setCurrentIndex(i);
	}
	
	//camera
	auto addCameraRes = [this](int cx, int cy) {
		QString res = ResString(cx, cy).c_str();
		if (ui->cmbCameraResoltuion->findText(res) == -1)
			ui->cmbCameraResoltuion->addItem(res);
	};
	ui->cmbCameraResoltuion->clear();
	for (int i = 0; i < m_vecCameraResolution.size(); i++) {
		addCameraRes(m_vecCameraResolution[i].width, m_vecCameraResolution[i].height);
		if (m_vecCameraResolution[i].width == setting.plugin_camera_width
			&& m_vecCameraResolution[i].height == setting.plugin_camera_height)
			ui->cmbCameraResoltuion->setCurrentIndex(i);
	}

	for (int i = 0; i < 4; ++i) {
		if (agora_fps[i] == setting.plugin_camera_fps) {
			ui->cmbCameraFPS->setCurrentIndex(i);
			break;
		}
	}

	for (int i = 0; i < 3; ++i) {
		if (agora_bitrate[i] == setting.plugin_camera_bitrate) {
			ui->cmbCameraBitrate->setCurrentIndex(i);
			break;
		}
	}

	loading = false;
}


void AgoraSettings::LoadRtmpSettings()
{
	return;
	loading = true;
	AgoraToolSettings settings;
	//main->GetAgoraSettings(settings);

	ui->lineEditAgoraRTmp->setText(QString::fromUtf8(settings.rtmp_url.data()));
	ui->lineEditAgoraRtmpBitrate->setText(QString("%1").arg(settings.rtmp_bitrate));
	ui->lineEditAgoraRtmpFPS->setText(QString("%1").arg(settings.rtmp_fps));
	ui->lineEditAgoraRtmpWidth->setText(QString("%1").arg(settings.rtmp_width));
	ui->lineEditAgoraRtmpHeight->setText(QString("%1").arg(settings.rtmp_height));
	loading = false;
}

void AgoraSettings::LoadAgoraSettings()
{
	loading = true;
	AgoraToolSettings settings;
	//main->GetAgoraSettings(settings);

	ui->lineEditAppid->setText(QString::fromUtf8(settings.appid.data()));
	ui->lineEditToken->setText(QString::fromUtf8(settings.token.data()));
	ui->lineEditCameraToken->setText(QString::fromUtf8(settings.token.data()));

	ui->lineEditChannel->setText(
		QString::fromUtf8(settings.channelName.data()));
	if (settings.uid > 0) {
		QString strUid = QString("%1").arg(settings.uid);
		ui->lineEditUID->setText(strUid);
	}

	if (settings.camera_uid > 0) {
		QString strUid = QString("%1").arg(settings.camera_uid);
		ui->lineEditCameraUID->setText(strUid);
	}

	ui->lineEditLogInterval->setText(QString("%1").arg(settings.logInterval));
	ui->chkPersistSaving->setChecked(settings.savePersist);
	ui->chkPersistSaveAppid->setChecked(settings.savePersistAppid);
	ui->chkMuteAllRemoteAV->setChecked(settings.muteAllRemoteAudioVideo);
	ui->chkDualStream->setChecked(settings.bDualStream);
	QString strExpired = QString("%1").arg(settings.expiredTime);
	ui->lineEditExpiredTs->setText(strExpired);
	
	loading = false;
}

void AgoraSettings::SaveSettings()
{
	if (audioChanged)
		SaveAudioSettings();

	if (videoChanged)
		SaveVideoSettings();

	if (generalChanged)
		SaveGeneralSettings();

	if (rtmpChanged)
		SaveRtmpSetting();
}

void AgoraSettings::on_buttonAppid_clicked()
{

	if (rtcEngine->IsInitialize())
		return;
	QString appid = ui->lineEditAppid->text();
	appid.trimmed();
	if (appid.isEmpty()){
		QMessageBox::about(nullptr, title, empty_appid_info);
		return;
	}

	if (!rtcEngine->InitEngine(appid.toUtf8().toStdString())) {
		QMessageBox::about(nullptr, title, init_failed_info);
		return;
	}
	
	ui->buttonAppid->setEnabled(false);

	AgoraToolSettings setting;
	main->GetAgoraSetting(setting);
	setting.appid = appid.toUtf8().toStdString();

	LoadAudioDevice();

}

void AgoraSettings::on_buttonBox_clicked(QAbstractButton *button)
{
	QDialogButtonBox::ButtonRole val = ui->buttonBox->buttonRole(button);
	if (rtcEngine->IsJoined()) {
		AgoraToolSettings settings;
		main->GetAgoraSetting(settings);
		rtcEngine->SetPcmInfo(ui->chkSavePCM->isChecked(), settings.pcmFolder);
	}
	if (val == QDialogButtonBox::ApplyRole ||
		val == QDialogButtonBox::AcceptRole) {
		
		if (!checkTestNetwork())
			return;

		if (ui->cmbGetMode->currentIndex() == 1
			&& ui->lineEditUrl->text().isEmpty()) {
			QMessageBox::about(nullptr, title, emptyUrlError);
			return;
		}

		if (ui->cmbGetMode->currentIndex() == 0){
			if (ui->chkObsCamera->isChecked() && ui->lineEditCameraUID->text().isEmpty()) {
				QMessageBox::about(nullptr, title, errEmptyCameraUID);
				return;
			}

			if (ui->chkObsCamera->isChecked() &&
				ui->lineEditUID->text().compare(
					ui->lineEditCameraUID->text()) == 0) {
				QMessageBox::about(nullptr, title, errSameUID);
				return;
			}
		}
		SaveSettings();
		ClearChanged();
	}

	if (val == QDialogButtonBox::AcceptRole ||
		val == QDialogButtonBox::RejectRole) {
		ClearChanged();
		if (appid_changed && rtcEngine->IsInitialize()) {
			rtcEngine->Release();
		}
		accept();
		//close();
	}
}

void AgoraSettings::on_loadConfigButton_clicked()
{
	QFileDialog *fileDialog = new QFileDialog(this);
	fileDialog->setNameFilter(tr("Config File(*.ini)"));
	fileDialog->setFileMode(QFileDialog::ExistingFile);
	QStringList fileNames;
	if (fileDialog->exec()) {
		fileNames = fileDialog->selectedFiles();
	}

	for (auto iter : fileNames) {
		std::shared_ptr<QSettings> spConfig =
			std::make_shared<QSettings>(iter, QSettings::IniFormat);
		ui->loadConfiglineEdit->setText(iter);
		QString str;
		str = spConfig->value("/BaseInfo/AppId").toString();
		if (!str.isEmpty())
			ui->lineEditAppid->setText(str);

		str = spConfig->value("/BaseInfo/AppToken").toString();
		if (!str.isEmpty())
			ui->lineEditToken->setText(str);
		str = spConfig->value("/BaseInfo/ChannelName").toString();
		if (!str.isEmpty())
			ui->lineEditChannel->setText(str);

		str = spConfig->value("/BaseInfo/UID").toString();
		if (!str.isEmpty())
			ui->lineEditUID->setText(str);

		str = spConfig->value("/BaseInfo/TokenExpired").toString();
		if (!str.isEmpty())
			ui->lineEditExpiredTs->setText(str);

		str = spConfig->value("/BaseInfo/RtmpUrl").toString();
		if (!str.isEmpty())
			ui->lineEditAgoraRTmp->setText(str);

		auto addRes = [this](int cx, int cy) {
			QString res = ResString(cx, cy).c_str();
			if (ui->agoraResolution->findText(res) == -1)
				ui->agoraResolution->addItem(res);
		};
		ui->agoraResolution->clear();

		int width = spConfig->value("/BaseInfo/AgoraWidth").toInt();
		int height = spConfig->value("/BaseInfo/AgoraHeight").toInt();
		for (int i = 0; i < m_vecResolution.size(); i++) {
			addRes(m_vecResolution[i].width, m_vecResolution[i].height);
			if (m_vecResolution[i].width == width
				&& m_vecResolution[i].height == height)
				ui->agoraResolution->setCurrentIndex(i);
		}

		int fps = spConfig->value("/BaseInfo/AgoraFPS").toInt();
		int bitrate = spConfig->value("/BaseInfo/AgoraBitrate").toInt();
		for (int i = 0; i < FPS_NUM; ++i) {
			if (agora_fps[i] == fps) {
				ui->cmbAgoraFPS->setCurrentIndex(i);
				break;
			}
		}

		for (int i = 0; i < 3; ++i) {
			if (agora_bitrate[i] == bitrate) {
				ui->cmbAgoraBitrate->setCurrentIndex(i);
				break;
			}
		}
	}
}

void AgoraSettings::on_recordVolumeSld_valueChanged(int value)
{
	//rtcEngine->setRecordingDeviceVolume(value);
}

void AgoraSettings::on_cmbVideoEncoder_currentIndexChanged(int index)
{
	if (index == 0) {//Agora bitrate
		ui->label_4->show();
		ui->cmbAgoraBitrate->show();
	}
	else {
		ui->label_4->hide();
		ui->cmbAgoraBitrate->hide();
	}
}

void AgoraSettings::ShowControlByMode(int index)
{
	if (index == 0) {
		ui->labelGetInfoMode_2->hide();
		ui->labUrl->hide();
		ui->lineEditUrl->hide();
		ui->lineEditAppid->show();
		ui->lineEditToken->show();
		ui->labelToken->show();
		ui->label_appid->show();

		ui->chkPersistSaveAppid->show();
		ui->buttonAppid->show();
		ui->labUrl->hide();
		ui->lineEditUrl->hide();
	}
	else {
		ui->labelGetInfoMode_2->show();
		ui->labUrl->show();
		ui->lineEditUrl->show();
		ui->label_appid->hide();
		ui->lineEditAppid->hide();
		ui->labelToken->hide();
		ui->lineEditToken->hide();
		ui->labelCameraToken->hide();
		ui->lineEditCameraToken->hide();
		ui->chkPersistSaveAppid->hide();
		ui->buttonAppid->hide();
	}
	ui->labelCameraToken->setVisible(ui->chkObsCamera->isChecked());
	ui->lineEditCameraToken->setVisible(ui->chkObsCamera->isChecked());
	ui->lineEditAppid->setEnabled(index == 0);
	ui->lineEditCameraUID->setEnabled(index == 0);
	ui->lineEditCameraToken->setEnabled(index == 0);
	ui->lineEditUID->setEnabled(index == 0);
	ui->lineEditToken->setEnabled(index == 0);
	ui->lineEditChannel->setEnabled(index == 0);
}

void AgoraSettings::ClearChannelInfo()
{
	ui->lineEditAppid->setText("");
	ui->lineEditToken->setText("");
	ui->lineEditCameraToken->setText("");
	ui->lineEditUID->setText("");
	ui->lineEditCameraUID->setText("");
	ui->lineEditChannel->setText("");
}

void AgoraSettings::on_cmbGetMode_currentIndexChanged(int index)
{
	ShowControlByMode(index);
	
	if (isVisible())
		ClearChannelInfo();
}

void AgoraSettings::on_playoutVolumeSld_valueChanged(int value)
{
	rtcEngine->SetPalyoutDeviceVolume(value);
}

void AgoraSettings::showEvent(QShowEvent *event)
{
	bool bEnabled = !rtcEngine->IsJoined();
	
	ui->loadConfigButton->setEnabled(bEnabled);
	ui->lineEditAppCertificate->setEnabled(bEnabled);
	ui->lineEditExpiredTs->setEnabled(bEnabled);
	ui->chkAudioHighQuality->setEnabled(bEnabled);
	ui->cmbRecordChannelSetup->setEnabled(bEnabled);
	ui->cmbScenario->setEnabled(bEnabled);

	ui->cmbAgoraBitrate->setEnabled(bEnabled);
	ui->cmbVideoEncoder->setEnabled(bEnabled);
	ui->btnNetworkTest->setEnabled(bEnabled);
	ui->lineEditUrl->setEnabled(bEnabled);
	ui->buttonAppid->setEnabled(!rtcEngine->IsInitialize());
	on_chkObsCamera_check(ui->chkObsCamera->isChecked());
	ShowControlByMode(ui->cmbGetMode->currentIndex());
	ui->cmbGetMode->setEnabled(bEnabled);
	ui->lineEditAppid->setEnabled(bEnabled);
	ui->lineEditChannel->setEnabled(bEnabled);
	ui->lineEditToken->setEnabled(bEnabled);
	ui->lineEditUID->setEnabled(bEnabled);
	ui->lineEditCameraUID->setEnabled(bEnabled);
	ui->lineEditCameraToken->setEnabled(bEnabled);
}

/*typedef void(*obs_source_audio_capture_t)(void *param, obs_source_t *source,
	const struct audio_data *audio_data,
	bool muted);

EXPORT void obs_source_add_audio_capture_callback(
	obs_source_t *source, obs_source_audio_capture_t callback, void *param);*/


void AgoraSettings::onChkSaveAppidSettings(bool bCheck)
{
	if (bCheck)
		ui->agoraMsg2->setText(persistSaveAppidInfo);
	else
		ui->agoraMsg2->setText("");
	AgoraToolSettings settings;
	main->GetAgoraSetting(settings);
	if (settings.savePersistAppid != bCheck) {
		generalChanged = true;
	}
}

void AgoraSettings::on_btnNetworkTest_clicked()
{
	if (!rtcEngine->IsInitialize()) {
		on_buttonAppid_clicked();
		if (!rtcEngine->IsInitialize())
			return;
	}
	
	if (!networkTest)
		ui->labelTestNetWork->setText(testingNet);
	else
		ui->labelTestNetWork->setText("");

	ui->btnNetworkTest->setText(networkTest ? startTestNet : stopTestNet);
	rtcEngine->EnableLastmileTest(!networkTest);
	networkTest = !networkTest;
}

void AgoraSettings::OnLastmileTest(int quality)
{
	agora::rtc::QUALITY_TYPE type = (agora::rtc::QUALITY_TYPE)quality;

	QString info;
	switch (type)
	{
	case agora::rtc::QUALITY_UNKNOWN:
		info = qualityUnknown;
		break;
	case agora::rtc::QUALITY_EXCELLENT:
		info = qualityExcellent;
		break;
	case agora::rtc::QUALITY_GOOD:
		info = qualityGood;
		break;
	case agora::rtc::QUALITY_POOR:
		info = qualityPoor;
		break;
	case agora::rtc::QUALITY_BAD:
		info = qualityBad;
		break;
	case agora::rtc::QUALITY_VBAD:
		info = qualityVBad;
		break;
	case agora::rtc::QUALITY_DOWN:
		info = qualityDown;
		break;
	case agora::rtc::QUALITY_UNSUPPORTED:
		info = qualityUnSupported;
		break;
	case agora::rtc::QUALITY_DETECTING:
		info = qualityDetecting;
		break;
	default:
		//info = qualityUnknown;
		break;
	}
	ui->labelTestNetWork->setText(info);
}

bool AgoraSettings::checkTestNetwork()
{
	if (networkTest) {
		QMessageBox::information(nullptr, title, testingNetInfo);
		return false;
	}

	return true;
}

void AgoraSettings::closeEvent(QCloseEvent *event)
{
	if (!checkTestNetwork()) {
		event->ignore();
		return;
	}
	close();
}
void AgoraSettings::on_chkObsCamera_check(bool check)
{
	ui->labeCameraUID->setVisible(check);
	ui->lineEditCameraUID->setVisible(check);
	if (ui->cmbGetMode->currentIndex() == 0) {
		ui->lineEditCameraToken->setVisible(check);
		ui->labelCameraToken->setVisible(check);
	}
	
	ui->labCameraEncoderBitrate->setVisible(check);
	ui->cmbCameraBitrate->setVisible(check);
	ui->labCameraEncoderFPS->setVisible(check);
	ui->cmbCameraFPS->setVisible(check);
	ui->labCameraEncoderRes->setVisible(check);
	ui->cmbCameraResoltuion->setVisible(check);
}