#include "qt-wrappers.hpp"
#include "window-init-agora-widget.hpp"
#include "obs-app.hpp"
#include "window-basic-main.hpp"
#include <stdio.h>
using namespace std;

AgoraInitWidget::AgoraInitWidget(QWidget *parent)
	: QDialog (parent)
	, main(qobject_cast<OBSBasic*>(parent))
	, ui(new Ui::AgoraInitWidget)
{
	ui->setupUi(this);
	
	installEventFilter(CreateShortcutFilter());

// 	ui->textEdit_appid->setText(app_id);
// 	ui->textEdit_channel->setText(QT_UTF8(channel));
// 	ui->textEdit_uid->setText(QT_UTF8(text_uid.c_str()));
}

AgoraInitWidget::~AgoraInitWidget()
{
	
}
void AgoraInitWidget::on_saveButton_clicked()
{
	std::string input_uid = QT_TO_UTF8(ui->textEdit_uid->toPlainText());
	std::string input_appid = QT_TO_UTF8(ui->textEdit_appid->toPlainText());
	std::string input_channel = QT_TO_UTF8(ui->textEdit_channel->toPlainText());
	
	if (input_channel.empty()){
		QMessageBox::warning(this, QString("agora warning"), QString("please input agora channel"));
	}
	else if (input_appid.empty()){
		QMessageBox::warning(this, QString("agora warning"), QString("please input agora channel"));
	}
	else{
		app_id = input_appid;
		channel = input_channel;
		uid = strtoul(input_uid.c_str(), NULL, 10);
		//config_set_int(main->Config(), "General", "agora_uid", uid);
		//config_set_string(main->Config(), "General", "agora_channel", input_channel.c_str());
		//config_set_string(main->Config(), "General", "agora_appid", input_appid.c_str());
		QDialog::done(QDialog::Accepted);
	}
}

