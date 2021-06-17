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
	startTestNet = tr("Agora.Setting.TestNet.Start");
	stopTestNet = tr("Agora.Setting.TestNet.Stop");

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
	
	testingNetInfo = tr("Agora.Network.Testing.Info");
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
	if (AgoraRtcEngine::GetInstance()->audioChannel == 2)
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

	ui->chkPersistSaveAppid->setText(persistSaveAppid);
	//video encoder
	ui->labelVideoEncoder->setText(tr("Agora.Settings.Video.Encoder"));
	ui->labelFPSResolution->setText(tr("Agora.Settings.Video.FPS.Resolution"));
	ui->cmbVideoEncoder->setItemText(0, tr("Agora.Settings.Video.Agora.Bitrate"));
	ui->cmbVideoEncoder->setItemText(1, tr("Agora.Settings.Video.OBS.Bitrate"));
	ui->cmbVideoEncoder->setCurrentIndex(0);

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
	

	LoadGeneralSettings();
	LoadAudioSettings();
	LoadVideoSettings();
	LoadRtmpSettings();
	//
	HookWidget(ui->lineEditUrl, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditAppid, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditToken, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditAppCertificate, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditExpiredTs, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditChannel, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->lineEditUID, EDIT_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->cmbGetMode, COMBO_CHANGED, GENERAL_CHANGED);

	HookWidget(ui->chkPersistSaving, CHECK_CHANGED, GENERAL_CHANGED);
	HookWidget(ui->chkMuteAllRemoteAV, CHECK_CHANGED, GENERAL_CHANGED);

	HookWidget(ui->playoutDevices, COMBO_CHANGED, AUDIO_CHANGED);
	HookWidget(ui->recordSampleRate, COMBO_CHANGED, AUDIO_CHANGED);
	HookWidget(ui->cmbRecordChannelSetup, COMBO_CHANGED, AUDIO_CHANGED);
	HookWidget(ui->cmbScenario, COMBO_CHANGED, AUDIO_CHANGED);
	HookWidget(ui->chkAudioHighQuality, CHECK_CHANGED, GENERAL_CHANGED);
	
	HookWidget(ui->cmbAgoraFPS, COMBO_CHANGED, VIDEO_CHANGED);
	HookWidget(ui->cmbAgoraBitrate, COMBO_CHANGED, VIDEO_CHANGED);
	HookWidget(ui->agoraResolution, COMBO_CHANGED, VIDEO_CHANGED);
	HookWidget(ui->cmbAgoraVideoDevice, COMBO_CHANGED, VIDEO_CHANGED);
	HookWidget(ui->cmbVideoEncoder, COMBO_CHANGED, VIDEO_CHANGED);


	HookWidget(ui->lineEditAgoraRTmp, EDIT_CHANGED, RTMP_CHANGED);
	HookWidget(ui->lineEditAgoraRtmpFPS, EDIT_CHANGED, RTMP_CHANGED);
	HookWidget(ui->lineEditAgoraRtmpWidth, EDIT_CHANGED, RTMP_CHANGED);
	HookWidget(ui->lineEditAgoraRtmpHeight, EDIT_CHANGED, RTMP_CHANGED);
	HookWidget(ui->lineEditAgoraRtmpBitrate, EDIT_CHANGED, RTMP_CHANGED);

	HookWidget(ui->chkPersistSaving, CHECK_CHANGED, GENERAL_CHANGED);
	connect(ui->chkPersistSaveAppid, &QCheckBox::toggled, this, &AgoraSettings::onChkSaveAppidSettings);
	connect(AgoraRtcEngine::GetInstance(), &AgoraRtcEngine::onLastmileQuality, this, &AgoraSettings::OnLastmileTest);
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
	AgoraRtcEngine::GetInstance()->getPlayoutDevices(playoutDevices);
	
	QString name = ui->playoutDevices->currentText();
	if (!name.isEmpty()) {
		for (int i = 0; i < playoutDevices.size(); ++i) {
			if (playoutDevices[i].name.compare(name.toUtf8().toStdString()) == 0) {
				AgoraRtcEngine::GetInstance()->SetPlayoutDevice(playoutDevices[i].id.c_str());
				break;
			}
		}
	}

	AgoraToolSettings settings;
	main->GetAgoraSetting(settings);
	settings.bHighQuality = ui->chkAudioHighQuality->isChecked();
	settings.scenario     = ui->cmbScenario->currentIndex();
	settings.audioChannel = ui->cmbRecordChannelSetup->currentIndex() + 1;
	main->SetAgoraSetting(settings);
	AgoraRtcEngine::GetInstance()->SetAudioProfile(settings.scenario, settings.audioChannel, settings.bHighQuality);
}

void AgoraSettings::SaveVideoSettings()
{
	AgoraToolSettings settings;
	main->GetAgoraSetting(settings);

	settings.agora_fps = agora_fps[ui->cmbAgoraFPS->currentIndex()];
	settings.agora_bitrate = agora_bitrate[ui->cmbAgoraBitrate->currentIndex()];
	settings.agora_width = m_vecResolution[ui->agoraResolution->currentIndex()].width;
	settings.agora_height = m_vecResolution[ui->agoraResolution->currentIndex()].height;
	settings.videoEncoder = ui->cmbVideoEncoder->currentIndex();
	main->SetAgoraSetting(settings);
}

void AgoraSettings::SaveGeneralSettings()
{
	AgoraToolSettings settings;
	main->GetAgoraSetting(settings);
	QString strAppid = ui->lineEditAppid->text().toUtf8();
	strAppid = strAppid.trimmed();
  if (AgoraRtcEngine::GetInstance()->IsInitialize()
			&& !settings.appid.empty() && settings.appid.compare(strAppid.toUtf8()) !=0)
			appid_changed = true;
		settings.appid = strAppid.toStdString();

	settings.appCerf = ui->lineEditAppCertificate->text().toStdString();
	settings.token = ui->lineEditToken->text().toStdString();
	settings.channelName = ui->lineEditChannel->text().toStdString();
	settings.information_url = ui->lineEditUrl->text().toStdString();
	settings.info_mode = ui->cmbGetMode->currentIndex();
  if (!strAppid.isEmpty())
    settings.appid = strAppid.toStdString();
  settings.appCerf = ui->lineEditAppCertificate->text().toStdString();
  settings.token = ui->lineEditToken->text().toStdString();
  settings.channelName = ui->lineEditChannel->text().toStdString();
  QString strUid = ui->lineEditUID->text();
	if (strUid.length() > 0)
		settings.uid = strtoul(strUid.toUtf8().data(), NULL, 10);
	else
		settings.uid = 0;
	QString strExpired = ui->lineEditExpiredTs->text();
	if (strExpired.length() > 0)
		settings.expiredTime =
		strtoul(strExpired.toUtf8().data(), NULL, 10);
	else
		settings.expiredTime = AGORA_SETTINGS_EXPIREDTS;
	settings.expiredTimeTs = settings.expiredTime * 60 * 60;
	settings.savePersist = ui->chkPersistSaving->isChecked();
	settings.muteAllRemoteAudioVideo = ui->chkMuteAllRemoteAV->isChecked();
	settings.savePersistAppid = ui->chkPersistSaveAppid->isChecked();
	
	main->SetAgoraSetting(settings);

	SaveCheckBox(ui->chkPersistSaving, "AgoraSettings", "PersistSave");
	if(settings.savePersistAppid && !strAppid.isEmpty())
		SaveEdit(ui->lineEditAppid, "AgoraSettings", "AppId");

	if (settings.savePersist) {
		SaveEdit(ui->lineEditUrl, "AgoraSettings", "InformationUrl");
		
		if (!strUid.isEmpty())
			SaveEdit(ui->lineEditUID, "AgoraSettings", "UID");
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
	}
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
	ui->cmbGetMode->setCurrentIndex(settings.info_mode);
	if (settings.info_mode == 0) {
		ui->labelGetInfoMode_2->hide();
		ui->labUrl->hide();
		ui->lineEditUrl->hide();
	}

	ui->chkPersistSaving->setChecked(settings.savePersist);
	ui->chkPersistSaveAppid->setChecked(settings.savePersistAppid);
	ui->chkMuteAllRemoteAV->setChecked(settings.muteAllRemoteAudioVideo);
	QString strExpired = QString("%1").arg(settings.expiredTime);
	ui->lineEditExpiredTs->setText(strExpired);
	loading = false;

	ui->lineEditAgoraRTmp->setText(
		QString::fromUtf8(settings.rtmp_url.data()));

	ui->lineEditAgoraRtmpFPS->setText(
		QString("%1").arg(settings.rtmp_fps));
	ui->lineEditAgoraRtmpBitrate->setText(
		QString("%1").arg(settings.rtmp_bitrate));

	ui->lineEditAgoraRtmpWidth->setText(QString("%1").arg(settings.rtmp_width));
	ui->lineEditAgoraRtmpHeight->setText(QString("%1").arg(settings.rtmp_height));
}

void AgoraSettings::LoadAudioDevice()
{
	ui->playoutDevices->clear();
	std::vector<DEVICEINFO> playoutDevices;
	AgoraRtcEngine::GetInstance()->getPlayoutDevices(playoutDevices);
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
	ui->lineEditAppCertificate->setText(QString::fromUtf8(settings.appCerf.data()));
	ui->lineEditChannel->setText(
		QString::fromUtf8(settings.channelName.data()));
	if (settings.uid > 0) {
		QString strUid = QString("%1").arg(settings.uid);
		ui->lineEditUID->setText(strUid);
	}
	ui->chkPersistSaving->setChecked(settings.savePersist);
	ui->chkPersistSaveAppid->setChecked(settings.savePersistAppid);
	ui->chkMuteAllRemoteAV->setChecked(settings.muteAllRemoteAudioVideo);
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

	if (AgoraRtcEngine::GetInstance()->IsInitialize())
		return;
	QString appid = ui->lineEditAppid->text();
	if (appid.isEmpty()){
		QMessageBox::about(nullptr, title, empty_appid_info);
		return;
	}

	if (!AgoraRtcEngine::GetInstance()->InitEngine(appid.toUtf8().toStdString())) {
		QMessageBox::about(nullptr, title, init_failed_info + appid);
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
	if(!checkTestNetwork())
		return;
	
	QDialogButtonBox::ButtonRole val = ui->buttonBox->buttonRole(button);

	if (val == QDialogButtonBox::ApplyRole ||
		val == QDialogButtonBox::AcceptRole) {
		SaveSettings();
		ClearChanged();
	}

	if (val == QDialogButtonBox::AcceptRole ||
		val == QDialogButtonBox::RejectRole) {
		ClearChanged();
		if (appid_changed && AgoraRtcEngine::GetInstance()->IsInitialize()) {
			AgoraRtcEngine::GetInstance()->release();
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
	//AgoraRtcEngine::GetInstance()->setRecordingDeviceVolume(value);
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

void AgoraSettings::on_cmbGetMode_currentIndexChanged(int index)
{
	if (index == 0) {
		ui->labelGetInfoMode_2->hide();
		ui->labUrl->hide();
		ui->lineEditUrl->hide();
	}
	else {
		ui->labelGetInfoMode_2->show();
		ui->labUrl->show();
		ui->lineEditUrl->show();
	}
}

void AgoraSettings::on_playoutVolumeSld_valueChanged(int value)
{
	AgoraRtcEngine::GetInstance()->setPalyoutDeviceVolume(value);
}

void AgoraSettings::showEvent(QShowEvent *event)
{
	bool bEnabled = !AgoraRtcEngine::GetInstance()->IsJoinChannel();
	ui->loadConfigButton->setEnabled(bEnabled);
	ui->lineEditAppCertificate->setEnabled(bEnabled);
	ui->lineEditAppid->setEnabled(bEnabled);
	ui->lineEditChannel->setEnabled(bEnabled);
	ui->lineEditExpiredTs->setEnabled(bEnabled);
	ui->lineEditUID ->setEnabled(bEnabled);
	ui->chkAudioHighQuality->setEnabled(bEnabled);
	ui->cmbRecordChannelSetup->setEnabled(bEnabled);
	ui->cmbScenario->setEnabled(bEnabled);

	ui->cmbAgoraBitrate->setEnabled(bEnabled);
	ui->cmbVideoEncoder->setEnabled(bEnabled);
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
	if (!AgoraRtcEngine::GetInstance()->IsInitialize()) {
		on_buttonAppid_clicked();
		if (!AgoraRtcEngine::GetInstance()->IsInitialize())
			return;
	}
	
	if (!networkTest)
		ui->labelTestNetWork->setText(testingNet);
	else
		ui->labelTestNetWork->setText("");

	ui->btnNetworkTest->setText(networkTest ? startTestNet : stopTestNet);
	AgoraRtcEngine::GetInstance()->enableLastmileTest(!networkTest);
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