
#pragma once

#include <QDialog>
#include <string>
#include <memory>

#include "ui_AgoraWidget.h"
class OBSBasic;

class AgoraInitWidget : public QDialog {
	Q_OBJECT
private:
	std::unique_ptr<Ui::AgoraInitWidget> ui;
	
public slots:
void on_saveButton_clicked();
public:

	AgoraInitWidget(QWidget *parent);
	virtual ~AgoraInitWidget();

	std::string app_id;
	OBSBasic* main;
	uint32_t uid = 0;
	std::string channel;
};
