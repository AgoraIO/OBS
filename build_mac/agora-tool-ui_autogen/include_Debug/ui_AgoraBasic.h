/********************************************************************************
** Form generated from reading UI file 'AgoraBasic.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGORABASIC_H
#define UI_AGORABASIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AgoraBasic
{
public:
    QAction *actionAddScene;
    QAction *actionAddSource;
    QAction *actionRemoveScene;
    QAction *actionRemoveSource;
    QAction *actionSourceProperties;
    QAction *actionSceneUp;
    QAction *actionSourceUp;
    QAction *actionSceneDown;
    QAction *actionSourceDown;
    QAction *actionShow_Recordings;
    QAction *actionRemux;
    QAction *action_Settings;
    QAction *actionE_xit;
    QAction *actionShowLogs;
    QAction *actionUploadLastLog;
    QAction *actionUploadCurrentLog;
    QAction *actionViewCurrentLog;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionEditTransform;
    QAction *actionCopyTransform;
    QAction *actionPasteTransform;
    QAction *actionRotate90CW;
    QAction *actionRotate90CCW;
    QAction *actionRotate180;
    QAction *actionFitToScreen;
    QAction *actionStretchToScreen;
    QAction *actionResetTransform;
    QAction *actionCenterToScreen;
    QAction *actionVerticalCenter;
    QAction *actionHorizontalCenter;
    QAction *actionFlipHorizontal;
    QAction *actionFlipVertical;
    QAction *actionMoveUp;
    QAction *actionMoveDown;
    QAction *actionMoveToTop;
    QAction *actionMoveToBottom;
    QAction *actionCheckForUpdates;
    QAction *actionInteract;
    QAction *actionAdvAudioProperties;
    QAction *actionWebsite;
    QAction *actionNewSceneCollection;
    QAction *actionDupSceneCollection;
    QAction *actionRenameSceneCollection;
    QAction *actionRemoveSceneCollection;
    QAction *actionImportSceneCollection;
    QAction *actionExportSceneCollection;
    QAction *actionNewProfile;
    QAction *actionDupProfile;
    QAction *actionRenameProfile;
    QAction *actionRemoveProfile;
    QAction *actionImportProfile;
    QAction *actionExportProfile;
    QAction *actionShowSettingsFolder;
    QAction *actionShowProfileFolder;
    QAction *actionAlwaysOnTop;
    QAction *toggleListboxToolbars;
    QAction *toggleStatusBar;
    QAction *actionLockPreview;
    QAction *actionScaleWindow;
    QAction *actionScaleCanvas;
    QAction *actionScaleOutput;
    QAction *actionPasteDup;
    QAction *autoConfigure2;
    QAction *autoConfigure;
    QAction *stats;
    QAction *resetUI;
    QAction *lockUI;
    QAction *toggleScenes;
    QAction *toggleSources;
    QAction *toggleMixer;
    QAction *toggleTransitions;
    QAction *toggleControls;
    QAction *actionHelpPortal;
    QAction *actionShowCrashLogs;
    QAction *actionUploadLastCrashLog;
    QAction *actionDiscord;
    QAction *toggleStats;
    QAction *actionShowAbout;
    QAction *toggleSourceIcons;
    QAction *toggleContextToolbars;
    QAction *toggleContextBar;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *previewLayout;
    QVBoxLayout *previewTextLayout;
    QWidget *preview;
    QDockWidget *controlsDock;
    QWidget *controlsDockContents;
    QVBoxLayout *buttonsVLayout;
    QHBoxLayout *horizontalLayout_AgoraControl;
    QPushButton *agoraSteramButton;
    QPushButton *settingsButton;
    QPushButton *exitButton;
    QSpacerItem *expVSpacer;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menuBasic_MainMenu_Help;
    QMenu *menuLogFiles;
    QMenu *menuCrashLogs;
    QMenu *viewMenu;
    QAction *actionFullscreenInterface;

    void setupUi(QMainWindow *AgoraBasic)
    {
        if (AgoraBasic->objectName().isEmpty())
            AgoraBasic->setObjectName(QString::fromUtf8("AgoraBasic"));
        AgoraBasic->resize(751, 598);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AgoraBasic->sizePolicy().hasHeightForWidth());
        AgoraBasic->setSizePolicy(sizePolicy);
        AgoraBasic->setMinimumSize(QSize(0, 0));
        AgoraBasic->setStyleSheet(QString::fromUtf8(""));
        AgoraBasic->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionAddScene = new QAction(AgoraBasic);
        actionAddScene->setObjectName(QString::fromUtf8("actionAddScene"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddScene->setIcon(icon);
        actionAddScene->setProperty("themeID", QVariant(QString::fromUtf8("addIconSmall")));
        actionAddSource = new QAction(AgoraBasic);
        actionAddSource->setObjectName(QString::fromUtf8("actionAddSource"));
        actionAddSource->setIcon(icon);
        actionAddSource->setProperty("themeID", QVariant(QString::fromUtf8("addIconSmall")));
        actionRemoveScene = new QAction(AgoraBasic);
        actionRemoveScene->setObjectName(QString::fromUtf8("actionRemoveScene"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/images/list_remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemoveScene->setIcon(icon1);
        actionRemoveScene->setShortcutContext(Qt::WidgetWithChildrenShortcut);
        actionRemoveScene->setProperty("themeID", QVariant(QString::fromUtf8("removeIconSmall")));
        actionRemoveSource = new QAction(AgoraBasic);
        actionRemoveSource->setObjectName(QString::fromUtf8("actionRemoveSource"));
        actionRemoveSource->setIcon(icon1);
        actionRemoveSource->setShortcutContext(Qt::WidgetWithChildrenShortcut);
        actionRemoveSource->setProperty("themeID", QVariant(QString::fromUtf8("removeIconSmall")));
        actionSourceProperties = new QAction(AgoraBasic);
        actionSourceProperties->setObjectName(QString::fromUtf8("actionSourceProperties"));
        actionSourceProperties->setEnabled(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/images/properties.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSourceProperties->setIcon(icon2);
        actionSourceProperties->setProperty("themeID", QVariant(QString::fromUtf8("propertiesIconSmall")));
        actionSceneUp = new QAction(AgoraBasic);
        actionSceneUp->setObjectName(QString::fromUtf8("actionSceneUp"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/images/up.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSceneUp->setIcon(icon3);
        actionSceneUp->setProperty("themeID", QVariant(QString::fromUtf8("upArrowIconSmall")));
        actionSourceUp = new QAction(AgoraBasic);
        actionSourceUp->setObjectName(QString::fromUtf8("actionSourceUp"));
        actionSourceUp->setEnabled(true);
        actionSourceUp->setIcon(icon3);
        actionSourceUp->setProperty("themeID", QVariant(QString::fromUtf8("upArrowIconSmall")));
        actionSceneDown = new QAction(AgoraBasic);
        actionSceneDown->setObjectName(QString::fromUtf8("actionSceneDown"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/res/images/down.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSceneDown->setIcon(icon4);
        actionSceneDown->setProperty("themeID", QVariant(QString::fromUtf8("downArrowIconSmall")));
        actionSourceDown = new QAction(AgoraBasic);
        actionSourceDown->setObjectName(QString::fromUtf8("actionSourceDown"));
        actionSourceDown->setEnabled(true);
        actionSourceDown->setIcon(icon4);
        actionSourceDown->setProperty("themeID", QVariant(QString::fromUtf8("downArrowIconSmall")));
        actionShow_Recordings = new QAction(AgoraBasic);
        actionShow_Recordings->setObjectName(QString::fromUtf8("actionShow_Recordings"));
        actionRemux = new QAction(AgoraBasic);
        actionRemux->setObjectName(QString::fromUtf8("actionRemux"));
        action_Settings = new QAction(AgoraBasic);
        action_Settings->setObjectName(QString::fromUtf8("action_Settings"));
        actionE_xit = new QAction(AgoraBasic);
        actionE_xit->setObjectName(QString::fromUtf8("actionE_xit"));
        actionShowLogs = new QAction(AgoraBasic);
        actionShowLogs->setObjectName(QString::fromUtf8("actionShowLogs"));
        actionUploadLastLog = new QAction(AgoraBasic);
        actionUploadLastLog->setObjectName(QString::fromUtf8("actionUploadLastLog"));
        actionUploadCurrentLog = new QAction(AgoraBasic);
        actionUploadCurrentLog->setObjectName(QString::fromUtf8("actionUploadCurrentLog"));
        actionViewCurrentLog = new QAction(AgoraBasic);
        actionViewCurrentLog->setObjectName(QString::fromUtf8("actionViewCurrentLog"));
        actionUndo = new QAction(AgoraBasic);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionUndo->setEnabled(false);
        actionRedo = new QAction(AgoraBasic);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionRedo->setEnabled(false);
        actionEditTransform = new QAction(AgoraBasic);
        actionEditTransform->setObjectName(QString::fromUtf8("actionEditTransform"));
        actionCopyTransform = new QAction(AgoraBasic);
        actionCopyTransform->setObjectName(QString::fromUtf8("actionCopyTransform"));
        actionPasteTransform = new QAction(AgoraBasic);
        actionPasteTransform->setObjectName(QString::fromUtf8("actionPasteTransform"));
        actionPasteTransform->setEnabled(false);
        actionRotate90CW = new QAction(AgoraBasic);
        actionRotate90CW->setObjectName(QString::fromUtf8("actionRotate90CW"));
        actionRotate90CCW = new QAction(AgoraBasic);
        actionRotate90CCW->setObjectName(QString::fromUtf8("actionRotate90CCW"));
        actionRotate180 = new QAction(AgoraBasic);
        actionRotate180->setObjectName(QString::fromUtf8("actionRotate180"));
        actionFitToScreen = new QAction(AgoraBasic);
        actionFitToScreen->setObjectName(QString::fromUtf8("actionFitToScreen"));
        actionStretchToScreen = new QAction(AgoraBasic);
        actionStretchToScreen->setObjectName(QString::fromUtf8("actionStretchToScreen"));
        actionResetTransform = new QAction(AgoraBasic);
        actionResetTransform->setObjectName(QString::fromUtf8("actionResetTransform"));
        actionCenterToScreen = new QAction(AgoraBasic);
        actionCenterToScreen->setObjectName(QString::fromUtf8("actionCenterToScreen"));
        actionVerticalCenter = new QAction(AgoraBasic);
        actionVerticalCenter->setObjectName(QString::fromUtf8("actionVerticalCenter"));
        actionHorizontalCenter = new QAction(AgoraBasic);
        actionHorizontalCenter->setObjectName(QString::fromUtf8("actionHorizontalCenter"));
        actionFlipHorizontal = new QAction(AgoraBasic);
        actionFlipHorizontal->setObjectName(QString::fromUtf8("actionFlipHorizontal"));
        actionFlipVertical = new QAction(AgoraBasic);
        actionFlipVertical->setObjectName(QString::fromUtf8("actionFlipVertical"));
        actionMoveUp = new QAction(AgoraBasic);
        actionMoveUp->setObjectName(QString::fromUtf8("actionMoveUp"));
        actionMoveDown = new QAction(AgoraBasic);
        actionMoveDown->setObjectName(QString::fromUtf8("actionMoveDown"));
        actionMoveToTop = new QAction(AgoraBasic);
        actionMoveToTop->setObjectName(QString::fromUtf8("actionMoveToTop"));
        actionMoveToBottom = new QAction(AgoraBasic);
        actionMoveToBottom->setObjectName(QString::fromUtf8("actionMoveToBottom"));
        actionCheckForUpdates = new QAction(AgoraBasic);
        actionCheckForUpdates->setObjectName(QString::fromUtf8("actionCheckForUpdates"));
        actionInteract = new QAction(AgoraBasic);
        actionInteract->setObjectName(QString::fromUtf8("actionInteract"));
        actionAdvAudioProperties = new QAction(AgoraBasic);
        actionAdvAudioProperties->setObjectName(QString::fromUtf8("actionAdvAudioProperties"));
        actionWebsite = new QAction(AgoraBasic);
        actionWebsite->setObjectName(QString::fromUtf8("actionWebsite"));
        actionNewSceneCollection = new QAction(AgoraBasic);
        actionNewSceneCollection->setObjectName(QString::fromUtf8("actionNewSceneCollection"));
        actionDupSceneCollection = new QAction(AgoraBasic);
        actionDupSceneCollection->setObjectName(QString::fromUtf8("actionDupSceneCollection"));
        actionRenameSceneCollection = new QAction(AgoraBasic);
        actionRenameSceneCollection->setObjectName(QString::fromUtf8("actionRenameSceneCollection"));
        actionRemoveSceneCollection = new QAction(AgoraBasic);
        actionRemoveSceneCollection->setObjectName(QString::fromUtf8("actionRemoveSceneCollection"));
        actionImportSceneCollection = new QAction(AgoraBasic);
        actionImportSceneCollection->setObjectName(QString::fromUtf8("actionImportSceneCollection"));
        actionExportSceneCollection = new QAction(AgoraBasic);
        actionExportSceneCollection->setObjectName(QString::fromUtf8("actionExportSceneCollection"));
        actionNewProfile = new QAction(AgoraBasic);
        actionNewProfile->setObjectName(QString::fromUtf8("actionNewProfile"));
        actionDupProfile = new QAction(AgoraBasic);
        actionDupProfile->setObjectName(QString::fromUtf8("actionDupProfile"));
        actionRenameProfile = new QAction(AgoraBasic);
        actionRenameProfile->setObjectName(QString::fromUtf8("actionRenameProfile"));
        actionRemoveProfile = new QAction(AgoraBasic);
        actionRemoveProfile->setObjectName(QString::fromUtf8("actionRemoveProfile"));
        actionImportProfile = new QAction(AgoraBasic);
        actionImportProfile->setObjectName(QString::fromUtf8("actionImportProfile"));
        actionExportProfile = new QAction(AgoraBasic);
        actionExportProfile->setObjectName(QString::fromUtf8("actionExportProfile"));
        actionShowSettingsFolder = new QAction(AgoraBasic);
        actionShowSettingsFolder->setObjectName(QString::fromUtf8("actionShowSettingsFolder"));
        actionShowProfileFolder = new QAction(AgoraBasic);
        actionShowProfileFolder->setObjectName(QString::fromUtf8("actionShowProfileFolder"));
        actionAlwaysOnTop = new QAction(AgoraBasic);
        actionAlwaysOnTop->setObjectName(QString::fromUtf8("actionAlwaysOnTop"));
        actionAlwaysOnTop->setCheckable(true);
        toggleListboxToolbars = new QAction(AgoraBasic);
        toggleListboxToolbars->setObjectName(QString::fromUtf8("toggleListboxToolbars"));
        toggleListboxToolbars->setCheckable(true);
        toggleListboxToolbars->setChecked(true);
        toggleStatusBar = new QAction(AgoraBasic);
        toggleStatusBar->setObjectName(QString::fromUtf8("toggleStatusBar"));
        toggleStatusBar->setCheckable(true);
        toggleStatusBar->setChecked(true);
        actionLockPreview = new QAction(AgoraBasic);
        actionLockPreview->setObjectName(QString::fromUtf8("actionLockPreview"));
        actionLockPreview->setCheckable(true);
        actionScaleWindow = new QAction(AgoraBasic);
        actionScaleWindow->setObjectName(QString::fromUtf8("actionScaleWindow"));
        actionScaleWindow->setCheckable(true);
        actionScaleCanvas = new QAction(AgoraBasic);
        actionScaleCanvas->setObjectName(QString::fromUtf8("actionScaleCanvas"));
        actionScaleCanvas->setCheckable(true);
        actionScaleOutput = new QAction(AgoraBasic);
        actionScaleOutput->setObjectName(QString::fromUtf8("actionScaleOutput"));
        actionScaleOutput->setCheckable(true);
        actionPasteDup = new QAction(AgoraBasic);
        actionPasteDup->setObjectName(QString::fromUtf8("actionPasteDup"));
        autoConfigure2 = new QAction(AgoraBasic);
        autoConfigure2->setObjectName(QString::fromUtf8("autoConfigure2"));
        autoConfigure = new QAction(AgoraBasic);
        autoConfigure->setObjectName(QString::fromUtf8("autoConfigure"));
        stats = new QAction(AgoraBasic);
        stats->setObjectName(QString::fromUtf8("stats"));
        resetUI = new QAction(AgoraBasic);
        resetUI->setObjectName(QString::fromUtf8("resetUI"));
        lockUI = new QAction(AgoraBasic);
        lockUI->setObjectName(QString::fromUtf8("lockUI"));
        lockUI->setCheckable(true);
        lockUI->setChecked(true);
        toggleScenes = new QAction(AgoraBasic);
        toggleScenes->setObjectName(QString::fromUtf8("toggleScenes"));
        toggleScenes->setCheckable(true);
        toggleScenes->setChecked(true);
        toggleSources = new QAction(AgoraBasic);
        toggleSources->setObjectName(QString::fromUtf8("toggleSources"));
        toggleSources->setCheckable(true);
        toggleSources->setChecked(true);
        toggleMixer = new QAction(AgoraBasic);
        toggleMixer->setObjectName(QString::fromUtf8("toggleMixer"));
        toggleMixer->setCheckable(true);
        toggleMixer->setChecked(true);
        toggleTransitions = new QAction(AgoraBasic);
        toggleTransitions->setObjectName(QString::fromUtf8("toggleTransitions"));
        toggleTransitions->setCheckable(true);
        toggleTransitions->setChecked(true);
        toggleControls = new QAction(AgoraBasic);
        toggleControls->setObjectName(QString::fromUtf8("toggleControls"));
        toggleControls->setCheckable(true);
        toggleControls->setChecked(true);
        actionHelpPortal = new QAction(AgoraBasic);
        actionHelpPortal->setObjectName(QString::fromUtf8("actionHelpPortal"));
        actionShowCrashLogs = new QAction(AgoraBasic);
        actionShowCrashLogs->setObjectName(QString::fromUtf8("actionShowCrashLogs"));
        actionUploadLastCrashLog = new QAction(AgoraBasic);
        actionUploadLastCrashLog->setObjectName(QString::fromUtf8("actionUploadLastCrashLog"));
        actionDiscord = new QAction(AgoraBasic);
        actionDiscord->setObjectName(QString::fromUtf8("actionDiscord"));
        toggleStats = new QAction(AgoraBasic);
        toggleStats->setObjectName(QString::fromUtf8("toggleStats"));
        toggleStats->setCheckable(true);
        toggleStats->setChecked(true);
        actionShowAbout = new QAction(AgoraBasic);
        actionShowAbout->setObjectName(QString::fromUtf8("actionShowAbout"));
        toggleSourceIcons = new QAction(AgoraBasic);
        toggleSourceIcons->setObjectName(QString::fromUtf8("toggleSourceIcons"));
        toggleSourceIcons->setCheckable(true);
        toggleSourceIcons->setChecked(true);
        toggleContextToolbars = new QAction(AgoraBasic);
        toggleContextToolbars->setObjectName(QString::fromUtf8("toggleContextToolbars"));
        toggleContextToolbars->setCheckable(true);
        toggleContextBar = new QAction(AgoraBasic);
        toggleContextBar->setObjectName(QString::fromUtf8("toggleContextBar"));
        toggleContextBar->setCheckable(true);
        toggleContextBar->setChecked(true);
        centralwidget = new QWidget(AgoraBasic);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        previewLayout = new QHBoxLayout();
        previewLayout->setSpacing(2);
        previewLayout->setObjectName(QString::fromUtf8("previewLayout"));
        previewTextLayout = new QVBoxLayout();
        previewTextLayout->setSpacing(0);
        previewTextLayout->setObjectName(QString::fromUtf8("previewTextLayout"));
        preview = new QWidget(centralwidget);
        preview->setObjectName(QString::fromUtf8("preview"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(preview->sizePolicy().hasHeightForWidth());
        preview->setSizePolicy(sizePolicy1);
        preview->setMinimumSize(QSize(32, 32));
        preview->setFocusPolicy(Qt::ClickFocus);
        preview->setContextMenuPolicy(Qt::CustomContextMenu);

        previewTextLayout->addWidget(preview);


        previewLayout->addLayout(previewTextLayout);


        horizontalLayout_2->addLayout(previewLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        AgoraBasic->setCentralWidget(centralwidget);
        controlsDock = new QDockWidget(AgoraBasic);
        controlsDock->setObjectName(QString::fromUtf8("controlsDock"));
        controlsDock->setContextMenuPolicy(Qt::DefaultContextMenu);
        controlsDock->setFloating(false);
        controlsDock->setFeatures(QDockWidget::DockWidgetMovable);
        controlsDockContents = new QWidget();
        controlsDockContents->setObjectName(QString::fromUtf8("controlsDockContents"));
        buttonsVLayout = new QVBoxLayout(controlsDockContents);
        buttonsVLayout->setSpacing(2);
        buttonsVLayout->setObjectName(QString::fromUtf8("buttonsVLayout"));
        buttonsVLayout->setContentsMargins(4, 4, 4, 4);
        horizontalLayout_AgoraControl = new QHBoxLayout();
        horizontalLayout_AgoraControl->setSpacing(20);
        horizontalLayout_AgoraControl->setObjectName(QString::fromUtf8("horizontalLayout_AgoraControl"));
        horizontalLayout_AgoraControl->setContentsMargins(5, 10, -1, 10);
        agoraSteramButton = new QPushButton(controlsDockContents);
        agoraSteramButton->setObjectName(QString::fromUtf8("agoraSteramButton"));
        agoraSteramButton->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(agoraSteramButton->sizePolicy().hasHeightForWidth());
        agoraSteramButton->setSizePolicy(sizePolicy2);
        agoraSteramButton->setMinimumSize(QSize(150, 0));
        agoraSteramButton->setCheckable(true);

        horizontalLayout_AgoraControl->addWidget(agoraSteramButton);

        settingsButton = new QPushButton(controlsDockContents);
        settingsButton->setObjectName(QString::fromUtf8("settingsButton"));
        sizePolicy2.setHeightForWidth(settingsButton->sizePolicy().hasHeightForWidth());
        settingsButton->setSizePolicy(sizePolicy2);
        settingsButton->setMinimumSize(QSize(150, 0));

        horizontalLayout_AgoraControl->addWidget(settingsButton);

        exitButton = new QPushButton(controlsDockContents);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        sizePolicy2.setHeightForWidth(exitButton->sizePolicy().hasHeightForWidth());
        exitButton->setSizePolicy(sizePolicy2);
        exitButton->setMinimumSize(QSize(150, 0));

        horizontalLayout_AgoraControl->addWidget(exitButton);


        buttonsVLayout->addLayout(horizontalLayout_AgoraControl);

        expVSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        buttonsVLayout->addItem(expVSpacer);

        controlsDock->setWidget(controlsDockContents);
        AgoraBasic->addDockWidget(Qt::BottomDockWidgetArea, controlsDock);
        menubar = new QMenuBar(AgoraBasic);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 751, 22));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menuBasic_MainMenu_Help = new QMenu(menubar);
        menuBasic_MainMenu_Help->setObjectName(QString::fromUtf8("menuBasic_MainMenu_Help"));
        menuLogFiles = new QMenu(menuBasic_MainMenu_Help);
        menuLogFiles->setObjectName(QString::fromUtf8("menuLogFiles"));
        menuCrashLogs = new QMenu(menuBasic_MainMenu_Help);
        menuCrashLogs->setObjectName(QString::fromUtf8("menuCrashLogs"));
        viewMenu = new QMenu(menubar);
        viewMenu->setObjectName(QString::fromUtf8("viewMenu"));
        actionFullscreenInterface = new QAction(viewMenu);
        actionFullscreenInterface->setObjectName(QString::fromUtf8("actionFullscreenInterface"));
        AgoraBasic->setMenuBar(menubar);

        preview->addAction(actionRemoveSource);
        menubar->addAction(menu_File->menuAction());
        menubar->addAction(viewMenu->menuAction());
        menubar->addAction(menuBasic_MainMenu_Help->menuAction());
        menu_File->addAction(action_Settings);
        menu_File->addAction(actionShowSettingsFolder);
        menu_File->addAction(actionShowProfileFolder);
        menu_File->addSeparator();
        menu_File->addAction(actionAlwaysOnTop);
        menu_File->addSeparator();
        menu_File->addAction(actionE_xit);
        menuBasic_MainMenu_Help->addAction(actionHelpPortal);
        menuBasic_MainMenu_Help->addAction(actionWebsite);
        menuBasic_MainMenu_Help->addAction(actionDiscord);
        menuBasic_MainMenu_Help->addSeparator();
        menuBasic_MainMenu_Help->addAction(menuLogFiles->menuAction());
        menuBasic_MainMenu_Help->addAction(menuCrashLogs->menuAction());
        menuBasic_MainMenu_Help->addSeparator();
        menuBasic_MainMenu_Help->addAction(actionCheckForUpdates);
        menuBasic_MainMenu_Help->addAction(actionShowAbout);
        menuBasic_MainMenu_Help->addSeparator();
        menuLogFiles->addAction(actionShowLogs);
        menuLogFiles->addAction(actionUploadCurrentLog);
        menuLogFiles->addAction(actionUploadLastLog);
        menuLogFiles->addAction(actionViewCurrentLog);
        menuCrashLogs->addAction(actionShowCrashLogs);
        menuCrashLogs->addAction(actionUploadLastCrashLog);
        viewMenu->addAction(actionFullscreenInterface);
        viewMenu->addSeparator();
        viewMenu->addAction(toggleListboxToolbars);
        viewMenu->addAction(toggleStatusBar);
        viewMenu->addSeparator();

        retranslateUi(AgoraBasic);
        QObject::connect(actionE_xit, SIGNAL(triggered()), AgoraBasic, SLOT(close()));
        QObject::connect(exitButton, SIGNAL(clicked()), AgoraBasic, SLOT(close()));

        QMetaObject::connectSlotsByName(AgoraBasic);
    } // setupUi

    void retranslateUi(QMainWindow *AgoraBasic)
    {
        AgoraBasic->setWindowTitle(QCoreApplication::translate("AgoraBasic", ".MainWindow", nullptr));
        actionAddScene->setText(QCoreApplication::translate("AgoraBasic", "Add", nullptr));
        actionAddSource->setText(QCoreApplication::translate("AgoraBasic", "Add", nullptr));
        actionRemoveScene->setText(QCoreApplication::translate("AgoraBasic", "Remove", nullptr));
#if QT_CONFIG(shortcut)
        actionRemoveScene->setShortcut(QCoreApplication::translate("AgoraBasic", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRemoveSource->setText(QCoreApplication::translate("AgoraBasic", "Remove", nullptr));
#if QT_CONFIG(shortcut)
        actionRemoveSource->setShortcut(QCoreApplication::translate("AgoraBasic", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSourceProperties->setText(QCoreApplication::translate("AgoraBasic", "Properties", nullptr));
        actionSceneUp->setText(QCoreApplication::translate("AgoraBasic", "MoveUp", nullptr));
        actionSourceUp->setText(QCoreApplication::translate("AgoraBasic", "MoveUp", nullptr));
        actionSceneDown->setText(QCoreApplication::translate("AgoraBasic", "MoveDown", nullptr));
        actionSourceDown->setText(QCoreApplication::translate("AgoraBasic", "MoveDown", nullptr));
        actionShow_Recordings->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.File.ShowRecordings", nullptr));
        actionRemux->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.File.Remux", nullptr));
        action_Settings->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.File.Settings", nullptr));
        actionE_xit->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.File.Exit", nullptr));
        actionShowLogs->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.Logs.ShowLogs", nullptr));
        actionUploadLastLog->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.Logs.UploadLastLog", nullptr));
        actionUploadCurrentLog->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.Logs.UploadCurrentLog", nullptr));
        actionViewCurrentLog->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.Logs.ViewCurrentLog", nullptr));
        actionUndo->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Undo", nullptr));
        actionRedo->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Redo", nullptr));
        actionEditTransform->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.EditTransform", nullptr));
#if QT_CONFIG(shortcut)
        actionEditTransform->setShortcut(QCoreApplication::translate("AgoraBasic", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopyTransform->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.CopyTransform", nullptr));
        actionPasteTransform->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.PasteTransform", nullptr));
        actionRotate90CW->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.Rotate90CW", nullptr));
        actionRotate90CCW->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.Rotate90CCW", nullptr));
        actionRotate180->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.Rotate180", nullptr));
        actionFitToScreen->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.FitToScreen", nullptr));
#if QT_CONFIG(shortcut)
        actionFitToScreen->setShortcut(QCoreApplication::translate("AgoraBasic", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionStretchToScreen->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.StretchToScreen", nullptr));
#if QT_CONFIG(shortcut)
        actionStretchToScreen->setShortcut(QCoreApplication::translate("AgoraBasic", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionResetTransform->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.ResetTransform", nullptr));
#if QT_CONFIG(shortcut)
        actionResetTransform->setShortcut(QCoreApplication::translate("AgoraBasic", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCenterToScreen->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.CenterToScreen", nullptr));
#if QT_CONFIG(shortcut)
        actionCenterToScreen->setShortcut(QCoreApplication::translate("AgoraBasic", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actionVerticalCenter->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.VerticalCenter", nullptr));
        actionHorizontalCenter->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.HorizontalCenter", nullptr));
        actionFlipHorizontal->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.FlipHorizontal", nullptr));
        actionFlipVertical->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Transform.FlipVertical", nullptr));
        actionMoveUp->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Order.MoveUp", nullptr));
#if QT_CONFIG(shortcut)
        actionMoveUp->setShortcut(QCoreApplication::translate("AgoraBasic", "Ctrl+Up", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMoveDown->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Order.MoveDown", nullptr));
#if QT_CONFIG(shortcut)
        actionMoveDown->setShortcut(QCoreApplication::translate("AgoraBasic", "Ctrl+Down", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMoveToTop->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Order.MoveToTop", nullptr));
#if QT_CONFIG(shortcut)
        actionMoveToTop->setShortcut(QCoreApplication::translate("AgoraBasic", "Ctrl+Home", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMoveToBottom->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Order.MoveToBottom", nullptr));
#if QT_CONFIG(shortcut)
        actionMoveToBottom->setShortcut(QCoreApplication::translate("AgoraBasic", "Ctrl+End", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCheckForUpdates->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.CheckForUpdates", nullptr));
        actionInteract->setText(QCoreApplication::translate("AgoraBasic", "Interact", nullptr));
        actionAdvAudioProperties->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.AdvAudio", nullptr));
        actionWebsite->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.Website", nullptr));
        actionNewSceneCollection->setText(QCoreApplication::translate("AgoraBasic", "New", nullptr));
        actionDupSceneCollection->setText(QCoreApplication::translate("AgoraBasic", "Duplicate", nullptr));
        actionRenameSceneCollection->setText(QCoreApplication::translate("AgoraBasic", "Rename", nullptr));
        actionRemoveSceneCollection->setText(QCoreApplication::translate("AgoraBasic", "Remove", nullptr));
        actionImportSceneCollection->setText(QCoreApplication::translate("AgoraBasic", "Import", nullptr));
        actionExportSceneCollection->setText(QCoreApplication::translate("AgoraBasic", "Export", nullptr));
        actionNewProfile->setText(QCoreApplication::translate("AgoraBasic", "New", nullptr));
        actionDupProfile->setText(QCoreApplication::translate("AgoraBasic", "Duplicate", nullptr));
        actionRenameProfile->setText(QCoreApplication::translate("AgoraBasic", "Rename", nullptr));
        actionRemoveProfile->setText(QCoreApplication::translate("AgoraBasic", "Remove", nullptr));
        actionImportProfile->setText(QCoreApplication::translate("AgoraBasic", "Import", nullptr));
        actionExportProfile->setText(QCoreApplication::translate("AgoraBasic", "Export", nullptr));
        actionShowSettingsFolder->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.File.ShowSettingsFolder", nullptr));
        actionShowProfileFolder->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.File.ShowProfileFolder", nullptr));
        actionAlwaysOnTop->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.AlwaysOnTop", nullptr));
        toggleListboxToolbars->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.View.ListboxToolbars", nullptr));
        toggleStatusBar->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.View.StatusBar", nullptr));
        actionLockPreview->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.LockPreview", nullptr));
        actionScaleWindow->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Scale.Window", nullptr));
        actionScaleCanvas->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Scale.Canvas", nullptr));
        actionScaleOutput->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Edit.Scale.Output", nullptr));
        actionPasteDup->setText(QCoreApplication::translate("AgoraBasic", "PasteDuplicate", nullptr));
        autoConfigure2->setText(QCoreApplication::translate("AgoraBasic", "Basic.AutoConfig", nullptr));
        autoConfigure->setText(QCoreApplication::translate("AgoraBasic", "Basic.AutoConfig", nullptr));
        stats->setText(QCoreApplication::translate("AgoraBasic", "Basic.Stats", nullptr));
        resetUI->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.View.Docks.ResetUI", nullptr));
        lockUI->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.View.Docks.LockUI", nullptr));
        toggleScenes->setText(QCoreApplication::translate("AgoraBasic", "Basic.Main.Scenes", nullptr));
        toggleSources->setText(QCoreApplication::translate("AgoraBasic", "Basic.Main.Sources", nullptr));
        toggleMixer->setText(QCoreApplication::translate("AgoraBasic", "Mixer", nullptr));
        toggleTransitions->setText(QCoreApplication::translate("AgoraBasic", "Basic.SceneTransitions", nullptr));
        toggleControls->setText(QCoreApplication::translate("AgoraBasic", "Basic.Main.Controls", nullptr));
        actionHelpPortal->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.HelpPortal", nullptr));
        actionShowCrashLogs->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.CrashLogs.ShowLogs", nullptr));
        actionUploadLastCrashLog->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.CrashLogs.UploadLastLog", nullptr));
        actionDiscord->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.Discord", nullptr));
        toggleStats->setText(QCoreApplication::translate("AgoraBasic", "Basic.Stats", nullptr));
        actionShowAbout->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.About", nullptr));
        toggleSourceIcons->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.View.SourceIcons", nullptr));
        toggleContextToolbars->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.View.Toolbars.Context", nullptr));
        toggleContextBar->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.View.ContextBar", nullptr));
        controlsDock->setWindowTitle(QCoreApplication::translate("AgoraBasic", "Agora.Main.Controls", nullptr));
        agoraSteramButton->setText(QCoreApplication::translate("AgoraBasic", "Agora.Main.Start", nullptr));
        settingsButton->setText(QCoreApplication::translate("AgoraBasic", "Settings", nullptr));
        exitButton->setText(QCoreApplication::translate("AgoraBasic", "Exit", nullptr));
        menu_File->setTitle(QCoreApplication::translate("AgoraBasic", "Agora.MainMenu.File", nullptr));
        menuBasic_MainMenu_Help->setTitle(QCoreApplication::translate("AgoraBasic", "Agora.MainMenu.Help", nullptr));
        menuLogFiles->setTitle(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.Logs", nullptr));
        menuCrashLogs->setTitle(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.Help.CrashLogs", nullptr));
        viewMenu->setTitle(QCoreApplication::translate("AgoraBasic", "Agora.MainMenu.View", nullptr));
        actionFullscreenInterface->setText(QCoreApplication::translate("AgoraBasic", "Basic.MainMenu.View.Fullscreen.Interface", nullptr));
#if QT_CONFIG(shortcut)
        actionFullscreenInterface->setShortcut(QCoreApplication::translate("AgoraBasic", "F11", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class AgoraBasic: public Ui_AgoraBasic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGORABASIC_H
