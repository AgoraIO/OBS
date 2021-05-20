/********************************************************************************
** Form generated from reading UI file 'AgoraSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGORASETTINGS_H
#define UI_AGORASETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AgoraSettings
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QStackedWidget *settingsPages;
    QWidget *agoraPage;
    QVBoxLayout *verticalLayout_16;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_23;
    QWidget *widget_agora;
    QVBoxLayout *verticalLayout_24;
    QGroupBox *generalGroupBox;
    QFormLayout *formLayout_22;
    QLabel *loadConfigFileLabel;
    QHBoxLayout *horizontalLayout_26;
    QLineEdit *loadConfiglineEdit;
    QPushButton *loadConfigButton;
    QLabel *label_appid;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEditAppid;
    QPushButton *buttonAppid;
    QSpacerItem *horizontalSpacer_13;
    QLabel *labelToken;
    QLineEdit *lineEditToken;
    QLabel *labelAppCertificate;
    QLineEdit *lineEditAppCertificate;
    QLabel *label_45;
    QLineEdit *lineEditExpiredTs;
    QLabel *labelChannelName;
    QHBoxLayout *horizontalLayout_27;
    QLineEdit *lineEditChannel;
    QLabel *labelUID;
    QLineEdit *lineEditUID;
    QCheckBox *chkAutoLoadConfig;
    QCheckBox *chkPersistSaving;
    QCheckBox *chkMuteAllRemoteAV;
    QCheckBox *chkPersistSaveAppid;
    QGroupBox *advancedVideoContainer;
    QFormLayout *formLayout_14;
    QLabel *rendererLabel;
    QComboBox *renderer;
    QLabel *adapterLabel;
    QComboBox *adapter;
    QLabel *label_30;
    QComboBox *colorFormat;
    QLabel *label_33;
    QHBoxLayout *horizontalLayout_20;
    QComboBox *colorSpace;
    QLabel *label_34;
    QComboBox *colorRange;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_18;
    QCheckBox *disableOSXVSync;
    QCheckBox *resetOSXVSync;
    QGroupBox *groupBox_6;
    QFormLayout *formLayout_17;
    QLabel *label_7;
    QCheckBox *overwriteIfExists;
    QHBoxLayout *horizontalLayout_14;
    QLineEdit *simpleRBPrefix;
    QLabel *label_58;
    QLineEdit *simpleRBSuffix;
    QLabel *label_57;
    QSpacerItem *horizontalSpacer_10;
    QCheckBox *autoRemux;
    QSpacerItem *horizontalSpacer_16;
    QLineEdit *filenameFormatting;
    QGroupBox *groupBox_5;
    QFormLayout *formLayout_18;
    QLabel *label_56;
    QWidget *widget_12;
    QHBoxLayout *horizontalLayout_13;
    QSpinBox *streamDelaySec;
    QLabel *streamDelayInfo;
    QCheckBox *streamDelayPreserve;
    QCheckBox *streamDelayEnable;
    QSpacerItem *horizontalSpacer_9;
    QGroupBox *groupBox_7;
    QFormLayout *formLayout_19;
    QCheckBox *reconnectEnable;
    QHBoxLayout *horizontalLayout_19;
    QSpinBox *reconnectRetryDelay;
    QLabel *label_22;
    QSpinBox *reconnectMaxRetries;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer_8;
    QGroupBox *advNetworkGroupBox;
    QFormLayout *formLayout_23;
    QLabel *label_27;
    QComboBox *bindToIP;
    QCheckBox *enableNewSocketLoop;
    QCheckBox *enableLowLatencyMode;
    QSpacerItem *horizontalSpacer_7;
    QCheckBox *dynBitrate;
    QVBoxLayout *verticalLayout_agora;
    QLabel *agoraMsg;
    QLabel *agoraMsg2;
    QWidget *audioPage;
    QVBoxLayout *formLayout;
    QScrollArea *scrollArea_50;
    QWidget *scrollAreaWidgetContents_50;
    QVBoxLayout *verticalLayout_50;
    QWidget *widget_50;
    QVBoxLayout *verticalLayout_51;
    QGroupBox *audioRecordingDevicesGroupBox;
    QFormLayout *formLayout_53;
    QLabel *label_2;
    QComboBox *recordSampleRate;
    QLabel *label_3;
    QComboBox *cmbRecordChannelSetup;
    QLabel *label_6;
    QComboBox *cmbScenario;
    QCheckBox *chkAudioHighQuality;
    QGroupBox *audioPlayGroupBox;
    QFormLayout *formLayout_56;
    QLabel *playoutDeviceLabel;
    QComboBox *playoutDevices;
    QLabel *label;
    QSlider *playoutVolumeSld;
    QLabel *audioMsg;
    QLabel *audioMsg_2;
    QWidget *videoPage;
    QFormLayout *formLayout_3;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_29;
    QComboBox *agoraResolution;
    QLabel *baseAspect;
    QLabel *label_10;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *videoMsg;
    QComboBox *cmbAgoraFPS;
    QComboBox *cmbAgoraBitrate;
    QComboBox *cmbAgoraVideoDevice;
    QLabel *labelVideoEncoder;
    QComboBox *cmbVideoEncoder;
    QLabel *labelFPSResolution;
    QWidget *rtmpPage;
    QFormLayout *formLayout_31;
    QLabel *labelAgoraRTmp;
    QLabel *labelAgoraRtmpFPS;
    QLabel *labelRtmpBitrate;
    QLabel *labelRtmpWidth;
    QLabel *labelRtmpHeight;
    QLineEdit *lineEditAgoraRTmp;
    QLineEdit *lineEditAgoraRtmpFPS;
    QLineEdit *lineEditAgoraRtmpBitrate;
    QLineEdit *lineEditAgoraRtmpWidth;
    QLineEdit *lineEditAgoraRtmpHeight;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AgoraSettings)
    {
        if (AgoraSettings->objectName().isEmpty())
            AgoraSettings->setObjectName(QString::fromUtf8("AgoraSettings"));
        AgoraSettings->resize(859, 512);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AgoraSettings->sizePolicy().hasHeightForWidth());
        AgoraSettings->setSizePolicy(sizePolicy);
        AgoraSettings->setMinimumSize(QSize(700, 512));
        verticalLayout = new QVBoxLayout(AgoraSettings);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget = new QListWidget(AgoraSettings);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy1);
        listWidget->setMaximumSize(QSize(135, 16777215));
        listWidget->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(listWidget);

        settingsPages = new QStackedWidget(AgoraSettings);
        settingsPages->setObjectName(QString::fromUtf8("settingsPages"));
        agoraPage = new QWidget();
        agoraPage->setObjectName(QString::fromUtf8("agoraPage"));
        verticalLayout_16 = new QVBoxLayout(agoraPage);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(agoraPage);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 698, 403));
        verticalLayout_23 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        verticalLayout_23->setContentsMargins(0, 0, 0, 9);
        widget_agora = new QWidget(scrollAreaWidgetContents);
        widget_agora->setObjectName(QString::fromUtf8("widget_agora"));
        verticalLayout_24 = new QVBoxLayout(widget_agora);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        generalGroupBox = new QGroupBox(widget_agora);
        generalGroupBox->setObjectName(QString::fromUtf8("generalGroupBox"));
        formLayout_22 = new QFormLayout(generalGroupBox);
        formLayout_22->setObjectName(QString::fromUtf8("formLayout_22"));
        formLayout_22->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_22->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_22->setContentsMargins(-1, 2, -1, -1);
        loadConfigFileLabel = new QLabel(generalGroupBox);
        loadConfigFileLabel->setObjectName(QString::fromUtf8("loadConfigFileLabel"));

        formLayout_22->setWidget(1, QFormLayout::LabelRole, loadConfigFileLabel);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        loadConfiglineEdit = new QLineEdit(generalGroupBox);
        loadConfiglineEdit->setObjectName(QString::fromUtf8("loadConfiglineEdit"));
        loadConfiglineEdit->setReadOnly(true);

        horizontalLayout_26->addWidget(loadConfiglineEdit);

        loadConfigButton = new QPushButton(generalGroupBox);
        loadConfigButton->setObjectName(QString::fromUtf8("loadConfigButton"));
        loadConfigButton->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_26->addWidget(loadConfigButton);


        formLayout_22->setLayout(1, QFormLayout::FieldRole, horizontalLayout_26);

        label_appid = new QLabel(generalGroupBox);
        label_appid->setObjectName(QString::fromUtf8("label_appid"));

        formLayout_22->setWidget(4, QFormLayout::LabelRole, label_appid);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEditAppid = new QLineEdit(generalGroupBox);
        lineEditAppid->setObjectName(QString::fromUtf8("lineEditAppid"));

        horizontalLayout_2->addWidget(lineEditAppid);

        buttonAppid = new QPushButton(generalGroupBox);
        buttonAppid->setObjectName(QString::fromUtf8("buttonAppid"));

        horizontalLayout_2->addWidget(buttonAppid);


        formLayout_22->setLayout(4, QFormLayout::FieldRole, horizontalLayout_2);

        horizontalSpacer_13 = new QSpacerItem(170, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout_22->setItem(5, QFormLayout::LabelRole, horizontalSpacer_13);

        labelToken = new QLabel(generalGroupBox);
        labelToken->setObjectName(QString::fromUtf8("labelToken"));

        formLayout_22->setWidget(7, QFormLayout::LabelRole, labelToken);

        lineEditToken = new QLineEdit(generalGroupBox);
        lineEditToken->setObjectName(QString::fromUtf8("lineEditToken"));

        formLayout_22->setWidget(7, QFormLayout::FieldRole, lineEditToken);

        labelAppCertificate = new QLabel(generalGroupBox);
        labelAppCertificate->setObjectName(QString::fromUtf8("labelAppCertificate"));

        formLayout_22->setWidget(8, QFormLayout::LabelRole, labelAppCertificate);

        lineEditAppCertificate = new QLineEdit(generalGroupBox);
        lineEditAppCertificate->setObjectName(QString::fromUtf8("lineEditAppCertificate"));

        formLayout_22->setWidget(8, QFormLayout::FieldRole, lineEditAppCertificate);

        label_45 = new QLabel(generalGroupBox);
        label_45->setObjectName(QString::fromUtf8("label_45"));

        formLayout_22->setWidget(9, QFormLayout::LabelRole, label_45);

        lineEditExpiredTs = new QLineEdit(generalGroupBox);
        lineEditExpiredTs->setObjectName(QString::fromUtf8("lineEditExpiredTs"));

        formLayout_22->setWidget(9, QFormLayout::FieldRole, lineEditExpiredTs);

        labelChannelName = new QLabel(generalGroupBox);
        labelChannelName->setObjectName(QString::fromUtf8("labelChannelName"));

        formLayout_22->setWidget(10, QFormLayout::LabelRole, labelChannelName);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        lineEditChannel = new QLineEdit(generalGroupBox);
        lineEditChannel->setObjectName(QString::fromUtf8("lineEditChannel"));

        horizontalLayout_27->addWidget(lineEditChannel);

        labelUID = new QLabel(generalGroupBox);
        labelUID->setObjectName(QString::fromUtf8("labelUID"));

        horizontalLayout_27->addWidget(labelUID);

        lineEditUID = new QLineEdit(generalGroupBox);
        lineEditUID->setObjectName(QString::fromUtf8("lineEditUID"));

        horizontalLayout_27->addWidget(lineEditUID);


        formLayout_22->setLayout(10, QFormLayout::FieldRole, horizontalLayout_27);

        chkAutoLoadConfig = new QCheckBox(generalGroupBox);
        chkAutoLoadConfig->setObjectName(QString::fromUtf8("chkAutoLoadConfig"));

        formLayout_22->setWidget(13, QFormLayout::FieldRole, chkAutoLoadConfig);

        chkPersistSaving = new QCheckBox(generalGroupBox);
        chkPersistSaving->setObjectName(QString::fromUtf8("chkPersistSaving"));

        formLayout_22->setWidget(11, QFormLayout::FieldRole, chkPersistSaving);

        chkMuteAllRemoteAV = new QCheckBox(generalGroupBox);
        chkMuteAllRemoteAV->setObjectName(QString::fromUtf8("chkMuteAllRemoteAV"));

        formLayout_22->setWidget(11, QFormLayout::LabelRole, chkMuteAllRemoteAV);

        chkPersistSaveAppid = new QCheckBox(generalGroupBox);
        chkPersistSaveAppid->setObjectName(QString::fromUtf8("chkPersistSaveAppid"));

        formLayout_22->setWidget(12, QFormLayout::FieldRole, chkPersistSaveAppid);


        verticalLayout_24->addWidget(generalGroupBox);

        advancedVideoContainer = new QGroupBox(widget_agora);
        advancedVideoContainer->setObjectName(QString::fromUtf8("advancedVideoContainer"));
        advancedVideoContainer->setMaximumSize(QSize(0, 0));
        formLayout_14 = new QFormLayout(advancedVideoContainer);
        formLayout_14->setObjectName(QString::fromUtf8("formLayout_14"));
        formLayout_14->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_14->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_14->setContentsMargins(-1, 2, -1, -1);
        rendererLabel = new QLabel(advancedVideoContainer);
        rendererLabel->setObjectName(QString::fromUtf8("rendererLabel"));

        formLayout_14->setWidget(0, QFormLayout::LabelRole, rendererLabel);

        renderer = new QComboBox(advancedVideoContainer);
        renderer->setObjectName(QString::fromUtf8("renderer"));
        renderer->setCurrentText(QString::fromUtf8(""));

        formLayout_14->setWidget(0, QFormLayout::FieldRole, renderer);

        adapterLabel = new QLabel(advancedVideoContainer);
        adapterLabel->setObjectName(QString::fromUtf8("adapterLabel"));
        adapterLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_14->setWidget(1, QFormLayout::LabelRole, adapterLabel);

        adapter = new QComboBox(advancedVideoContainer);
        adapter->setObjectName(QString::fromUtf8("adapter"));
        adapter->setEnabled(false);
        adapter->setCurrentText(QString::fromUtf8(""));

        formLayout_14->setWidget(1, QFormLayout::FieldRole, adapter);

        label_30 = new QLabel(advancedVideoContainer);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setMinimumSize(QSize(0, 0));
        label_30->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_14->setWidget(2, QFormLayout::LabelRole, label_30);

        colorFormat = new QComboBox(advancedVideoContainer);
        colorFormat->addItem(QString::fromUtf8("NV12"));
        colorFormat->addItem(QString::fromUtf8("I420"));
        colorFormat->addItem(QString());
        colorFormat->addItem(QString::fromUtf8("RGB"));
        colorFormat->setObjectName(QString::fromUtf8("colorFormat"));

        formLayout_14->setWidget(2, QFormLayout::FieldRole, colorFormat);

        label_33 = new QLabel(advancedVideoContainer);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        formLayout_14->setWidget(3, QFormLayout::LabelRole, label_33);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        horizontalLayout_20->setContentsMargins(0, 0, 0, 0);
        colorSpace = new QComboBox(advancedVideoContainer);
        colorSpace->addItem(QString::fromUtf8("709"));
        colorSpace->addItem(QString::fromUtf8("601"));
        colorSpace->setObjectName(QString::fromUtf8("colorSpace"));

        horizontalLayout_20->addWidget(colorSpace);

        label_34 = new QLabel(advancedVideoContainer);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_34->sizePolicy().hasHeightForWidth());
        label_34->setSizePolicy(sizePolicy2);

        horizontalLayout_20->addWidget(label_34);

        colorRange = new QComboBox(advancedVideoContainer);
        colorRange->setObjectName(QString::fromUtf8("colorRange"));

        horizontalLayout_20->addWidget(colorRange);


        formLayout_14->setLayout(3, QFormLayout::FieldRole, horizontalLayout_20);

        horizontalSpacer_12 = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout_14->setItem(4, QFormLayout::LabelRole, horizontalSpacer_12);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(0, 0, 0, 0);
        disableOSXVSync = new QCheckBox(advancedVideoContainer);
        disableOSXVSync->setObjectName(QString::fromUtf8("disableOSXVSync"));

        horizontalLayout_18->addWidget(disableOSXVSync);

        resetOSXVSync = new QCheckBox(advancedVideoContainer);
        resetOSXVSync->setObjectName(QString::fromUtf8("resetOSXVSync"));

        horizontalLayout_18->addWidget(resetOSXVSync);


        formLayout_14->setLayout(4, QFormLayout::FieldRole, horizontalLayout_18);


        verticalLayout_24->addWidget(advancedVideoContainer);

        groupBox_6 = new QGroupBox(widget_agora);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setMaximumSize(QSize(0, 0));
        formLayout_17 = new QFormLayout(groupBox_6);
        formLayout_17->setObjectName(QString::fromUtf8("formLayout_17"));
        formLayout_17->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_17->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_17->setContentsMargins(-1, 2, -1, -1);
        label_7 = new QLabel(groupBox_6);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_17->setWidget(0, QFormLayout::LabelRole, label_7);

        overwriteIfExists = new QCheckBox(groupBox_6);
        overwriteIfExists->setObjectName(QString::fromUtf8("overwriteIfExists"));

        formLayout_17->setWidget(1, QFormLayout::FieldRole, overwriteIfExists);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        simpleRBPrefix = new QLineEdit(groupBox_6);
        simpleRBPrefix->setObjectName(QString::fromUtf8("simpleRBPrefix"));

        horizontalLayout_14->addWidget(simpleRBPrefix);

        label_58 = new QLabel(groupBox_6);
        label_58->setObjectName(QString::fromUtf8("label_58"));

        horizontalLayout_14->addWidget(label_58);

        simpleRBSuffix = new QLineEdit(groupBox_6);
        simpleRBSuffix->setObjectName(QString::fromUtf8("simpleRBSuffix"));

        horizontalLayout_14->addWidget(simpleRBSuffix);


        formLayout_17->setLayout(3, QFormLayout::FieldRole, horizontalLayout_14);

        label_57 = new QLabel(groupBox_6);
        label_57->setObjectName(QString::fromUtf8("label_57"));

        formLayout_17->setWidget(3, QFormLayout::LabelRole, label_57);

        horizontalSpacer_10 = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout_17->setItem(1, QFormLayout::LabelRole, horizontalSpacer_10);

        autoRemux = new QCheckBox(groupBox_6);
        autoRemux->setObjectName(QString::fromUtf8("autoRemux"));

        formLayout_17->setWidget(2, QFormLayout::FieldRole, autoRemux);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout_17->setItem(2, QFormLayout::LabelRole, horizontalSpacer_16);

        filenameFormatting = new QLineEdit(groupBox_6);
        filenameFormatting->setObjectName(QString::fromUtf8("filenameFormatting"));

        formLayout_17->setWidget(0, QFormLayout::FieldRole, filenameFormatting);


        verticalLayout_24->addWidget(groupBox_6);

        groupBox_5 = new QGroupBox(widget_agora);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setMaximumSize(QSize(0, 0));
        formLayout_18 = new QFormLayout(groupBox_5);
        formLayout_18->setObjectName(QString::fromUtf8("formLayout_18"));
        formLayout_18->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_18->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_18->setContentsMargins(-1, 2, -1, -1);
        label_56 = new QLabel(groupBox_5);
        label_56->setObjectName(QString::fromUtf8("label_56"));

        formLayout_18->setWidget(1, QFormLayout::LabelRole, label_56);

        widget_12 = new QWidget(groupBox_5);
        widget_12->setObjectName(QString::fromUtf8("widget_12"));
        widget_12->setEnabled(true);
        horizontalLayout_13 = new QHBoxLayout(widget_12);
        horizontalLayout_13->setSpacing(5);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        streamDelaySec = new QSpinBox(widget_12);
        streamDelaySec->setObjectName(QString::fromUtf8("streamDelaySec"));
        streamDelaySec->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(streamDelaySec->sizePolicy().hasHeightForWidth());
        streamDelaySec->setSizePolicy(sizePolicy3);
        streamDelaySec->setMinimumSize(QSize(80, 0));
        streamDelaySec->setSuffix(QString::fromUtf8(" s"));
        streamDelaySec->setMinimum(1);
        streamDelaySec->setMaximum(1800);

        horizontalLayout_13->addWidget(streamDelaySec);

        streamDelayInfo = new QLabel(widget_12);
        streamDelayInfo->setObjectName(QString::fromUtf8("streamDelayInfo"));
        streamDelayInfo->setText(QString::fromUtf8("Estimated RAM goes here"));

        horizontalLayout_13->addWidget(streamDelayInfo);


        formLayout_18->setWidget(1, QFormLayout::FieldRole, widget_12);

        streamDelayPreserve = new QCheckBox(groupBox_5);
        streamDelayPreserve->setObjectName(QString::fromUtf8("streamDelayPreserve"));

        formLayout_18->setWidget(2, QFormLayout::FieldRole, streamDelayPreserve);

        streamDelayEnable = new QCheckBox(groupBox_5);
        streamDelayEnable->setObjectName(QString::fromUtf8("streamDelayEnable"));
        streamDelayEnable->setChecked(true);

        formLayout_18->setWidget(0, QFormLayout::FieldRole, streamDelayEnable);

        horizontalSpacer_9 = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout_18->setItem(2, QFormLayout::LabelRole, horizontalSpacer_9);


        verticalLayout_24->addWidget(groupBox_5);

        groupBox_7 = new QGroupBox(widget_agora);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setMaximumSize(QSize(0, 0));
        formLayout_19 = new QFormLayout(groupBox_7);
        formLayout_19->setObjectName(QString::fromUtf8("formLayout_19"));
        formLayout_19->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_19->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_19->setContentsMargins(-1, 2, -1, -1);
        reconnectEnable = new QCheckBox(groupBox_7);
        reconnectEnable->setObjectName(QString::fromUtf8("reconnectEnable"));
        reconnectEnable->setChecked(true);

        formLayout_19->setWidget(0, QFormLayout::FieldRole, reconnectEnable);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
        reconnectRetryDelay = new QSpinBox(groupBox_7);
        reconnectRetryDelay->setObjectName(QString::fromUtf8("reconnectRetryDelay"));
        reconnectRetryDelay->setMaximum(30);

        horizontalLayout_19->addWidget(reconnectRetryDelay);

        label_22 = new QLabel(groupBox_7);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy2.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy2);

        horizontalLayout_19->addWidget(label_22);

        reconnectMaxRetries = new QSpinBox(groupBox_7);
        reconnectMaxRetries->setObjectName(QString::fromUtf8("reconnectMaxRetries"));
        reconnectMaxRetries->setMinimum(1);
        reconnectMaxRetries->setMaximum(10000);

        horizontalLayout_19->addWidget(reconnectMaxRetries);


        formLayout_19->setLayout(1, QFormLayout::FieldRole, horizontalLayout_19);

        label_17 = new QLabel(groupBox_7);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        formLayout_19->setWidget(1, QFormLayout::LabelRole, label_17);

        horizontalSpacer_8 = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout_19->setItem(0, QFormLayout::LabelRole, horizontalSpacer_8);


        verticalLayout_24->addWidget(groupBox_7);

        advNetworkGroupBox = new QGroupBox(widget_agora);
        advNetworkGroupBox->setObjectName(QString::fromUtf8("advNetworkGroupBox"));
        advNetworkGroupBox->setMaximumSize(QSize(0, 0));
        formLayout_23 = new QFormLayout(advNetworkGroupBox);
        formLayout_23->setObjectName(QString::fromUtf8("formLayout_23"));
        formLayout_23->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_23->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_23->setContentsMargins(-1, 2, -1, -1);
        label_27 = new QLabel(advNetworkGroupBox);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        formLayout_23->setWidget(0, QFormLayout::LabelRole, label_27);

        bindToIP = new QComboBox(advNetworkGroupBox);
        bindToIP->setObjectName(QString::fromUtf8("bindToIP"));

        formLayout_23->setWidget(0, QFormLayout::FieldRole, bindToIP);

        enableNewSocketLoop = new QCheckBox(advNetworkGroupBox);
        enableNewSocketLoop->setObjectName(QString::fromUtf8("enableNewSocketLoop"));

        formLayout_23->setWidget(2, QFormLayout::FieldRole, enableNewSocketLoop);

        enableLowLatencyMode = new QCheckBox(advNetworkGroupBox);
        enableLowLatencyMode->setObjectName(QString::fromUtf8("enableLowLatencyMode"));
        enableLowLatencyMode->setEnabled(false);

        formLayout_23->setWidget(3, QFormLayout::FieldRole, enableLowLatencyMode);

        horizontalSpacer_7 = new QSpacerItem(170, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout_23->setItem(2, QFormLayout::LabelRole, horizontalSpacer_7);

        dynBitrate = new QCheckBox(advNetworkGroupBox);
        dynBitrate->setObjectName(QString::fromUtf8("dynBitrate"));

        formLayout_23->setWidget(1, QFormLayout::FieldRole, dynBitrate);


        verticalLayout_24->addWidget(advNetworkGroupBox);


        verticalLayout_23->addWidget(widget_agora);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_16->addWidget(scrollArea);

        verticalLayout_agora = new QVBoxLayout();
        verticalLayout_agora->setObjectName(QString::fromUtf8("verticalLayout_agora"));
        verticalLayout_agora->setContentsMargins(10, 10, 10, 10);
        agoraMsg = new QLabel(agoraPage);
        agoraMsg->setObjectName(QString::fromUtf8("agoraMsg"));
        agoraMsg->setText(QString::fromUtf8(""));
        agoraMsg->setWordWrap(true);

        verticalLayout_agora->addWidget(agoraMsg);

        agoraMsg2 = new QLabel(agoraPage);
        agoraMsg2->setObjectName(QString::fromUtf8("agoraMsg2"));
        agoraMsg2->setStyleSheet(QString::fromUtf8("color: rgb(255,0,0);"));
        agoraMsg2->setText(QString::fromUtf8(""));
        agoraMsg2->setWordWrap(true);

        verticalLayout_agora->addWidget(agoraMsg2);


        verticalLayout_16->addLayout(verticalLayout_agora);

        settingsPages->addWidget(agoraPage);
        audioPage = new QWidget();
        audioPage->setObjectName(QString::fromUtf8("audioPage"));
        formLayout = new QVBoxLayout(audioPage);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea_50 = new QScrollArea(audioPage);
        scrollArea_50->setObjectName(QString::fromUtf8("scrollArea_50"));
        scrollArea_50->setFrameShape(QFrame::NoFrame);
        scrollArea_50->setFrameShadow(QFrame::Plain);
        scrollArea_50->setWidgetResizable(true);
        scrollAreaWidgetContents_50 = new QWidget();
        scrollAreaWidgetContents_50->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_50"));
        scrollAreaWidgetContents_50->setGeometry(QRect(0, 0, 650, 219));
        verticalLayout_50 = new QVBoxLayout(scrollAreaWidgetContents_50);
        verticalLayout_50->setObjectName(QString::fromUtf8("verticalLayout_50"));
        verticalLayout_50->setContentsMargins(0, 0, 0, 9);
        widget_50 = new QWidget(scrollAreaWidgetContents_50);
        widget_50->setObjectName(QString::fromUtf8("widget_50"));
        verticalLayout_51 = new QVBoxLayout(widget_50);
        verticalLayout_51->setObjectName(QString::fromUtf8("verticalLayout_51"));
        audioRecordingDevicesGroupBox = new QGroupBox(widget_50);
        audioRecordingDevicesGroupBox->setObjectName(QString::fromUtf8("audioRecordingDevicesGroupBox"));
        formLayout_53 = new QFormLayout(audioRecordingDevicesGroupBox);
        formLayout_53->setObjectName(QString::fromUtf8("formLayout_53"));
        formLayout_53->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_53->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_53->setContentsMargins(-1, 2, -1, -1);
        label_2 = new QLabel(audioRecordingDevicesGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(170, 0));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_53->setWidget(0, QFormLayout::LabelRole, label_2);

        recordSampleRate = new QComboBox(audioRecordingDevicesGroupBox);
        recordSampleRate->setObjectName(QString::fromUtf8("recordSampleRate"));
        recordSampleRate->setEnabled(true);

        formLayout_53->setWidget(0, QFormLayout::FieldRole, recordSampleRate);

        label_3 = new QLabel(audioRecordingDevicesGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_53->setWidget(1, QFormLayout::LabelRole, label_3);

        cmbRecordChannelSetup = new QComboBox(audioRecordingDevicesGroupBox);
        cmbRecordChannelSetup->addItem(QString());
        cmbRecordChannelSetup->addItem(QString());
        cmbRecordChannelSetup->setObjectName(QString::fromUtf8("cmbRecordChannelSetup"));

        formLayout_53->setWidget(1, QFormLayout::FieldRole, cmbRecordChannelSetup);

        label_6 = new QLabel(audioRecordingDevicesGroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_53->setWidget(2, QFormLayout::LabelRole, label_6);

        cmbScenario = new QComboBox(audioRecordingDevicesGroupBox);
        cmbScenario->addItem(QString());
        cmbScenario->addItem(QString());
        cmbScenario->addItem(QString());
        cmbScenario->addItem(QString());
        cmbScenario->addItem(QString());
        cmbScenario->addItem(QString());
        cmbScenario->addItem(QString());
        cmbScenario->addItem(QString());
        cmbScenario->setObjectName(QString::fromUtf8("cmbScenario"));

        formLayout_53->setWidget(2, QFormLayout::FieldRole, cmbScenario);

        chkAudioHighQuality = new QCheckBox(audioRecordingDevicesGroupBox);
        chkAudioHighQuality->setObjectName(QString::fromUtf8("chkAudioHighQuality"));

        formLayout_53->setWidget(3, QFormLayout::FieldRole, chkAudioHighQuality);


        verticalLayout_51->addWidget(audioRecordingDevicesGroupBox);

        audioPlayGroupBox = new QGroupBox(widget_50);
        audioPlayGroupBox->setObjectName(QString::fromUtf8("audioPlayGroupBox"));
        formLayout_56 = new QFormLayout(audioPlayGroupBox);
        formLayout_56->setObjectName(QString::fromUtf8("formLayout_56"));
        formLayout_56->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_56->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_56->setContentsMargins(-1, 2, -1, -1);
        playoutDeviceLabel = new QLabel(audioPlayGroupBox);
        playoutDeviceLabel->setObjectName(QString::fromUtf8("playoutDeviceLabel"));

        formLayout_56->setWidget(0, QFormLayout::LabelRole, playoutDeviceLabel);

        playoutDevices = new QComboBox(audioPlayGroupBox);
        playoutDevices->setObjectName(QString::fromUtf8("playoutDevices"));

        formLayout_56->setWidget(0, QFormLayout::FieldRole, playoutDevices);

        label = new QLabel(audioPlayGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_56->setWidget(1, QFormLayout::LabelRole, label);

        playoutVolumeSld = new QSlider(audioPlayGroupBox);
        playoutVolumeSld->setObjectName(QString::fromUtf8("playoutVolumeSld"));
        playoutVolumeSld->setMinimumSize(QSize(0, 20));
        playoutVolumeSld->setMaximum(255);
        playoutVolumeSld->setOrientation(Qt::Horizontal);

        formLayout_56->setWidget(1, QFormLayout::FieldRole, playoutVolumeSld);


        verticalLayout_51->addWidget(audioPlayGroupBox);


        verticalLayout_50->addWidget(widget_50, 0, Qt::AlignTop);

        scrollArea_50->setWidget(scrollAreaWidgetContents_50);

        formLayout->addWidget(scrollArea_50);

        audioMsg = new QLabel(audioPage);
        audioMsg->setObjectName(QString::fromUtf8("audioMsg"));
        audioMsg->setText(QString::fromUtf8(""));
        audioMsg->setWordWrap(true);

        formLayout->addWidget(audioMsg);

        audioMsg_2 = new QLabel(audioPage);
        audioMsg_2->setObjectName(QString::fromUtf8("audioMsg_2"));
        audioMsg_2->setText(QString::fromUtf8(""));
        audioMsg_2->setWordWrap(true);
        audioMsg_2->setProperty("themeID", QVariant(QString::fromUtf8("warning")));

        formLayout->addWidget(audioMsg_2);

        settingsPages->addWidget(audioPage);
        videoPage = new QWidget();
        videoPage->setObjectName(QString::fromUtf8("videoPage"));
        formLayout_3 = new QFormLayout(videoPage);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_3->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8 = new QLabel(videoPage);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(170, 0));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_8);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        agoraResolution = new QComboBox(videoPage);
        agoraResolution->setObjectName(QString::fromUtf8("agoraResolution"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(agoraResolution->sizePolicy().hasHeightForWidth());
        agoraResolution->setSizePolicy(sizePolicy4);
        agoraResolution->setEditable(true);
        agoraResolution->setCurrentText(QString::fromUtf8(""));
        agoraResolution->setDuplicatesEnabled(false);
        agoraResolution->setFrame(true);

        horizontalLayout_29->addWidget(agoraResolution);

        baseAspect = new QLabel(videoPage);
        baseAspect->setObjectName(QString::fromUtf8("baseAspect"));

        horizontalLayout_29->addWidget(baseAspect);


        formLayout_3->setLayout(3, QFormLayout::FieldRole, horizontalLayout_29);

        label_10 = new QLabel(videoPage);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_3->setWidget(4, QFormLayout::LabelRole, label_10);

        label_4 = new QLabel(videoPage);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_3->setWidget(5, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(videoPage);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_3->setWidget(6, QFormLayout::LabelRole, label_5);

        videoMsg = new QLabel(videoPage);
        videoMsg->setObjectName(QString::fromUtf8("videoMsg"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(videoMsg->sizePolicy().hasHeightForWidth());
        videoMsg->setSizePolicy(sizePolicy5);
        videoMsg->setText(QString::fromUtf8(""));
        videoMsg->setWordWrap(true);

        formLayout_3->setWidget(8, QFormLayout::FieldRole, videoMsg);

        cmbAgoraFPS = new QComboBox(videoPage);
        cmbAgoraFPS->addItem(QString());
        cmbAgoraFPS->addItem(QString());
        cmbAgoraFPS->addItem(QString());
        cmbAgoraFPS->addItem(QString());
        cmbAgoraFPS->addItem(QString());
        cmbAgoraFPS->addItem(QString());
        cmbAgoraFPS->addItem(QString());
        cmbAgoraFPS->setObjectName(QString::fromUtf8("cmbAgoraFPS"));
        sizePolicy4.setHeightForWidth(cmbAgoraFPS->sizePolicy().hasHeightForWidth());
        cmbAgoraFPS->setSizePolicy(sizePolicy4);
        cmbAgoraFPS->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        formLayout_3->setWidget(4, QFormLayout::FieldRole, cmbAgoraFPS);

        cmbAgoraBitrate = new QComboBox(videoPage);
        cmbAgoraBitrate->addItem(QString());
        cmbAgoraBitrate->addItem(QString());
        cmbAgoraBitrate->addItem(QString());
        cmbAgoraBitrate->setObjectName(QString::fromUtf8("cmbAgoraBitrate"));

        formLayout_3->setWidget(5, QFormLayout::FieldRole, cmbAgoraBitrate);

        cmbAgoraVideoDevice = new QComboBox(videoPage);
        cmbAgoraVideoDevice->setObjectName(QString::fromUtf8("cmbAgoraVideoDevice"));

        formLayout_3->setWidget(6, QFormLayout::FieldRole, cmbAgoraVideoDevice);

        labelVideoEncoder = new QLabel(videoPage);
        labelVideoEncoder->setObjectName(QString::fromUtf8("labelVideoEncoder"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, labelVideoEncoder);

        cmbVideoEncoder = new QComboBox(videoPage);
        cmbVideoEncoder->addItem(QString());
        cmbVideoEncoder->addItem(QString());
        cmbVideoEncoder->setObjectName(QString::fromUtf8("cmbVideoEncoder"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, cmbVideoEncoder);

        labelFPSResolution = new QLabel(videoPage);
        labelFPSResolution->setObjectName(QString::fromUtf8("labelFPSResolution"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, labelFPSResolution);

        settingsPages->addWidget(videoPage);
        rtmpPage = new QWidget();
        rtmpPage->setObjectName(QString::fromUtf8("rtmpPage"));
        formLayout_31 = new QFormLayout(rtmpPage);
        formLayout_31->setObjectName(QString::fromUtf8("formLayout_31"));
        formLayout_31->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_31->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelAgoraRTmp = new QLabel(rtmpPage);
        labelAgoraRTmp->setObjectName(QString::fromUtf8("labelAgoraRTmp"));

        formLayout_31->setWidget(0, QFormLayout::LabelRole, labelAgoraRTmp);

        labelAgoraRtmpFPS = new QLabel(rtmpPage);
        labelAgoraRtmpFPS->setObjectName(QString::fromUtf8("labelAgoraRtmpFPS"));

        formLayout_31->setWidget(1, QFormLayout::LabelRole, labelAgoraRtmpFPS);

        labelRtmpBitrate = new QLabel(rtmpPage);
        labelRtmpBitrate->setObjectName(QString::fromUtf8("labelRtmpBitrate"));

        formLayout_31->setWidget(2, QFormLayout::LabelRole, labelRtmpBitrate);

        labelRtmpWidth = new QLabel(rtmpPage);
        labelRtmpWidth->setObjectName(QString::fromUtf8("labelRtmpWidth"));

        formLayout_31->setWidget(3, QFormLayout::LabelRole, labelRtmpWidth);

        labelRtmpHeight = new QLabel(rtmpPage);
        labelRtmpHeight->setObjectName(QString::fromUtf8("labelRtmpHeight"));

        formLayout_31->setWidget(4, QFormLayout::LabelRole, labelRtmpHeight);

        lineEditAgoraRTmp = new QLineEdit(rtmpPage);
        lineEditAgoraRTmp->setObjectName(QString::fromUtf8("lineEditAgoraRTmp"));

        formLayout_31->setWidget(0, QFormLayout::FieldRole, lineEditAgoraRTmp);

        lineEditAgoraRtmpFPS = new QLineEdit(rtmpPage);
        lineEditAgoraRtmpFPS->setObjectName(QString::fromUtf8("lineEditAgoraRtmpFPS"));

        formLayout_31->setWidget(1, QFormLayout::FieldRole, lineEditAgoraRtmpFPS);

        lineEditAgoraRtmpBitrate = new QLineEdit(rtmpPage);
        lineEditAgoraRtmpBitrate->setObjectName(QString::fromUtf8("lineEditAgoraRtmpBitrate"));

        formLayout_31->setWidget(2, QFormLayout::FieldRole, lineEditAgoraRtmpBitrate);

        lineEditAgoraRtmpWidth = new QLineEdit(rtmpPage);
        lineEditAgoraRtmpWidth->setObjectName(QString::fromUtf8("lineEditAgoraRtmpWidth"));

        formLayout_31->setWidget(3, QFormLayout::FieldRole, lineEditAgoraRtmpWidth);

        lineEditAgoraRtmpHeight = new QLineEdit(rtmpPage);
        lineEditAgoraRtmpHeight->setObjectName(QString::fromUtf8("lineEditAgoraRtmpHeight"));

        formLayout_31->setWidget(4, QFormLayout::FieldRole, lineEditAgoraRtmpHeight);

        settingsPages->addWidget(rtmpPage);

        horizontalLayout->addWidget(settingsPages);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(AgoraSettings);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#if QT_CONFIG(shortcut)
        rendererLabel->setBuddy(renderer);
        adapterLabel->setBuddy(adapter);
        label_30->setBuddy(colorFormat);
        label_33->setBuddy(colorSpace);
        label_34->setBuddy(colorRange);
        label_7->setBuddy(filenameFormatting);
        label_58->setBuddy(simpleRBSuffix);
        label_57->setBuddy(simpleRBPrefix);
        label_56->setBuddy(streamDelaySec);
        label_22->setBuddy(reconnectMaxRetries);
        label_17->setBuddy(reconnectRetryDelay);
        label_27->setBuddy(bindToIP);
        label_2->setBuddy(recordSampleRate);
        playoutDeviceLabel->setBuddy(playoutDevices);
        label_8->setBuddy(agoraResolution);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(listWidget, recordSampleRate);
        QWidget::setTabOrder(recordSampleRate, playoutDevices);

        retranslateUi(AgoraSettings);
        QObject::connect(listWidget, SIGNAL(currentRowChanged(int)), settingsPages, SLOT(setCurrentIndex(int)));

        listWidget->setCurrentRow(-1);
        settingsPages->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AgoraSettings);
    } // setupUi

    void retranslateUi(QDialog *AgoraSettings)
    {
        AgoraSettings->setWindowTitle(QCoreApplication::translate("AgoraSettings", "Settings", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.General", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Audio", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Rtmp", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        generalGroupBox->setTitle(QCoreApplication::translate("AgoraSettings", "Agora.Settings.General", nullptr));
        loadConfigFileLabel->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settigs.Agora.LoadConfig", nullptr));
        loadConfigButton->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settigs.Agora.LoadConfigButton", nullptr));
        label_appid->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.APPID", nullptr));
        buttonAppid->setText(QCoreApplication::translate("AgoraSettings", "Agora.General.Appid.Set", nullptr));
        labelToken->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.APPTOKEN", nullptr));
        labelAppCertificate->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.APPCERTIFICATE", nullptr));
        label_45->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.Token.Expired", nullptr));
        labelChannelName->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.ChannelName", nullptr));
        labelUID->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.UID", nullptr));
        chkAutoLoadConfig->setText(QCoreApplication::translate("AgoraSettings", "Basic.Agora.AutoLoadConfig", nullptr));
        chkPersistSaving->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.PersistSave", nullptr));
        chkMuteAllRemoteAV->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.MutAllRemoteAudioVideo", nullptr));
        chkPersistSaveAppid->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.PersistSaveAppid", nullptr));
        advancedVideoContainer->setTitle(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.Video", nullptr));
        rendererLabel->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Video.Renderer", nullptr));
        adapterLabel->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Video.Adapter", nullptr));
        label_30->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Advanced.Video.ColorFormat", nullptr));
        colorFormat->setItemText(2, QCoreApplication::translate("AgoraSettings", "I444", nullptr));

        label_33->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Advanced.Video.ColorSpace", nullptr));

        label_34->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Advanced.Video.ColorRange", nullptr));
        disableOSXVSync->setText(QCoreApplication::translate("AgoraSettings", "DisableOSXVSync", nullptr));
        resetOSXVSync->setText(QCoreApplication::translate("AgoraSettings", "ResetOSXVSyncOnExit", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Settings.Agora.Audio", nullptr));
        label_7->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Output.Adv.Recording.Filename", nullptr));
        overwriteIfExists->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Output.Adv.Recording.OverwriteIfExists", nullptr));
        label_58->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Output.ReplayBuffer.Suffix", nullptr));
        label_57->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Output.ReplayBuffer.Prefix", nullptr));
        autoRemux->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Advanced.AutoRemux", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.RTMP", nullptr));
        label_56->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Advanced.StreamDelay.Duration", nullptr));
        streamDelayPreserve->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Advanced.StreamDelay.Preserve", nullptr));
        streamDelayEnable->setText(QCoreApplication::translate("AgoraSettings", "Enable", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.Reconnect", nullptr));
        reconnectEnable->setText(QCoreApplication::translate("AgoraSettings", "Enable", nullptr));
        reconnectRetryDelay->setSuffix(QCoreApplication::translate("AgoraSettings", " s", nullptr));
        label_22->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Output.MaxRetries", nullptr));
        label_17->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Output.RetryDelay", nullptr));
        advNetworkGroupBox->setTitle(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.Network", nullptr));
        label_27->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Advanced.Network.BindToIP", nullptr));
        enableNewSocketLoop->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Advanced.Network.EnableNewSocketLoop", nullptr));
        enableLowLatencyMode->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Advanced.Network.EnableLowLatencyMode", nullptr));
#if QT_CONFIG(tooltip)
        dynBitrate->setToolTip(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Output.DynamicBitrate.TT", nullptr));
#endif // QT_CONFIG(tooltip)
        dynBitrate->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Output.DynamicBitrate.Beta", nullptr));
        agoraMsg->setProperty("themeID", QVariant(QCoreApplication::translate("AgoraSettings", "error", nullptr)));
        agoraMsg2->setProperty("themeID", QVariant(QCoreApplication::translate("AgoraSettings", "error", nullptr)));
        audioRecordingDevicesGroupBox->setTitle(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Recording", nullptr));
        label_2->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Audio.SampleRate", nullptr));
        label_3->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Audio.Channels", nullptr));
        cmbRecordChannelSetup->setItemText(0, QCoreApplication::translate("AgoraSettings", "Mono", nullptr));
        cmbRecordChannelSetup->setItemText(1, QCoreApplication::translate("AgoraSettings", "Stereo", nullptr));

        label_6->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.AudioProfile.Scenario", nullptr));
        cmbScenario->setItemText(0, QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.AudioProfile.DefaultScenario", nullptr));
        cmbScenario->setItemText(1, QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.AudioProfile.ChatRoomScenario", nullptr));
        cmbScenario->setItemText(2, QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.AudioProfile.EducationScenario", nullptr));
        cmbScenario->setItemText(3, QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.AudioProfile.GameStreamingScenario", nullptr));
        cmbScenario->setItemText(4, QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.AudioProfile.ShowRoomScenario", nullptr));
        cmbScenario->setItemText(5, QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.AudioProfile.ChatRoomGameScenario", nullptr));
        cmbScenario->setItemText(6, QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.AudioProfile.IOTScenario", nullptr));
        cmbScenario->setItemText(7, QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.AudioProfile.MettingScenario", nullptr));

        chkAudioHighQuality->setText(QCoreApplication::translate("AgoraSettings", "Basic.Settings.Agora.AudioProfile.High", nullptr));
        audioPlayGroupBox->setTitle(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Playout.Devices", nullptr));
        playoutDeviceLabel->setText(QCoreApplication::translate("AgoraSettings", "Agora.Playout.Devices", nullptr));
        label->setText(QCoreApplication::translate("AgoraSettings", "Agora.Payout.Devices.Volume", nullptr));
        audioMsg->setProperty("themeID", QVariant(QCoreApplication::translate("AgoraSettings", "error", nullptr)));
        label_8->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.BaseResolution", nullptr));
        baseAspect->setText(QCoreApplication::translate("AgoraSettings", "AspectRatio", nullptr));
        label_10->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.FPS", nullptr));
        label_4->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.Birate", nullptr));
        label_5->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.Devices", nullptr));
        videoMsg->setProperty("themeID", QVariant(QCoreApplication::translate("AgoraSettings", "error", nullptr)));
        cmbAgoraFPS->setItemText(0, QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.FPS5", nullptr));
        cmbAgoraFPS->setItemText(1, QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.FPS7", nullptr));
        cmbAgoraFPS->setItemText(2, QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.FPS10", nullptr));
        cmbAgoraFPS->setItemText(3, QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.FPS15", nullptr));
        cmbAgoraFPS->setItemText(4, QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.FPS24", nullptr));
        cmbAgoraFPS->setItemText(5, QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.FPS30", nullptr));
        cmbAgoraFPS->setItemText(6, QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.FPS60", nullptr));

        cmbAgoraBitrate->setItemText(0, QCoreApplication::translate("AgoraSettings", "Agora.Bitrate.Default", nullptr));
        cmbAgoraBitrate->setItemText(1, QCoreApplication::translate("AgoraSettings", "Agora.Bitrate.Compatible", nullptr));
        cmbAgoraBitrate->setItemText(2, QCoreApplication::translate("AgoraSettings", "Agora.Bitrate.Standard", nullptr));

        labelVideoEncoder->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.Encoder", nullptr));
        cmbVideoEncoder->setItemText(0, QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.Agora.Bitrate", nullptr));
        cmbVideoEncoder->setItemText(1, QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.OBS.Bitrate", nullptr));

        labelFPSResolution->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Video.FPS.Resolution", nullptr));
        labelAgoraRTmp->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Rtmp.Url", nullptr));
        labelAgoraRtmpFPS->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Rtmp.FPS", nullptr));
        labelRtmpBitrate->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Rtmp.Bitrate", nullptr));
        labelRtmpWidth->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Rtmp.Width", nullptr));
        labelRtmpHeight->setText(QCoreApplication::translate("AgoraSettings", "Agora.Settings.Rtmp.Height", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AgoraSettings: public Ui_AgoraSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGORASETTINGS_H
