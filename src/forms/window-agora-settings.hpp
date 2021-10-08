
#pragma once

#include <util/util.hpp>
#include <QDialog>
#include <QPointer>
#include <memory>
#include <string>
#include <obs.hpp>

class AgoraBasic;
class QAbstractButton;
class QComboBox;
class QCheckBox;
class QLabel;

#include "ui_AgoraSettings.h"
#define AGORA_SETTINGS_EXPIREDTS 24
#define FPS_NUM 7

typedef struct _RESOLUTION {
	int width = 0;
	int height = 0;
}RESOLUTION, *PRESOLUTION, *LPRESOLUTION;
class AgoraSettings : public QDialog {
	Q_OBJECT
private:
	std::unique_ptr<Ui::AgoraSettings> ui;
	AgoraBasic * main;
	bool generalChanged = false;
	bool audioChanged   = false;
	bool videoChanged   = false;
	bool rtmpChanged    = false;
	bool loading        = true;
	bool appid_changed  = false; 
	int agora_fps[FPS_NUM];
	int agora_bitrate[3];
	QString persistSaveAppid = "";
	QString persistSaveAppidInfo = "";
	QString title = "";
	QString empty_appid_info = "";
	QString init_failed_info = "";
	QString tokenUrlText = "";
	QString startTestNet = "";
	QString stopTestNet = "";
	QString qualityUnknown;
	QString qualityExcellent;
	QString qualityGood;
	QString qualityPoor;
	QString qualityBad;
	QString qualityVBad;
	QString qualityDown;
	QString qualityUnSupported;
	QString qualityDetecting;
	QString testingNet = "";
	QString testingNetInfo = "";

	QString errEmptyCameraUID = "";
	QString errSameUID = "";
	QString emptyUrlError = "";
	bool networkTest = false;

	std::vector<RESOLUTION> m_vecResolution;
	std::vector<RESOLUTION> m_vecCameraResolution;
	inline void EnableApplyButton(bool en)
	{
		ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(en);
	}

	static inline bool WidgetChanged(QWidget *widget)
	{
		return widget->property("changed").toBool();
	}

	void LoadAgoraSettings();
	
	void SaveCheckBox(QAbstractButton *widget, const char *section,
		const char *value, bool invert = false);
	void SaveEdit(QLineEdit *widget, const char *section,
		const char *value);
	void ClearChanged();
	void SaveSettings();
	void SaveAudioSettings();
	void SaveVideoSettings();
	void SaveGeneralSettings();
	void SaveRtmpSetting();

	void LoadGeneralSettings();
	void LoadAudioSettings();
	void LoadVideoSettings();
	void LoadRtmpSettings();
	void LoadAudioDevice();

	virtual void showEvent(QShowEvent *event)override;
	bool checkTestNetwork();

	virtual void closeEvent(QCloseEvent *event)override;
public:
	AgoraSettings(QWidget *parent);
	~AgoraSettings();
	void HookWidget(QWidget *widget, const char *signal,
		const char *slot);
	
private slots:
	void VideoChanged();
	void AudioChanged();
	void GeneralChanged();
	void RtmpChanged();
	void on_buttonAppid_clicked();
	void on_buttonBox_clicked(QAbstractButton *button);
	void on_loadConfigButton_clicked();
	void on_recordVolumeSld_valueChanged(int value);
	void on_playoutVolumeSld_valueChanged(int value);
	void on_cmbVideoEncoder_currentIndexChanged(int index);
	
	void onChkSaveAppidSettings(bool bCheck);
	void on_cmbGetMode_currentIndexChanged(int index);
	void on_btnNetworkTest_clicked();
	void OnLastmileTest(int quality);
	void on_chkObsCamera_check(bool check);
};
