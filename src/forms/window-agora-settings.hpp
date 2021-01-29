
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
	bool audioChanged = false;
	bool videoChanged = false;
	bool loading = true;
	int agora_fps[FPS_NUM];
	int agora_bitrate[3];

	QString title = "";
	QString empty_appid_info = "";
	QString init_failed_info = "";

	std::vector<RESOLUTION> m_vecResolution;
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

	void LoadGeneralSettings();
	void LoadAudioSettings();
	void LoadVideoSettings();
	
	void LoadAudioDevice();

	virtual void showEvent(QShowEvent *event)override;
public:
	AgoraSettings(QWidget *parent);
	~AgoraSettings();
	void HookWidget(QWidget *widget, const char *signal,
		const char *slot);
	
private slots:
	void VideoChanged();
	void AudioChanged();
	void GeneralChanged();
	void on_buttonAppid_clicked();
	void on_buttonBox_clicked(QAbstractButton *button);
	void on_loadConfigButton_clicked();
	void on_recordVolumeSld_valueChanged(int value);
	void on_playoutVolumeSld_valueChanged(int value);
};
