#include <obs-module.h>
#include <obs-frontend-api.h>
#include <QtCore/QTimer>
#include <QAction>
#include <QtWidgets/QMainWindow>
#include "forms/window-agora-main.hpp"
//#include "forms/window-init-agora-widget.hpp"

void initQT();

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("agora-tool-ui", "en-US")

extern void RegisterAgoraOutput();
extern void RegisterAgoraAudioEncoder();
extern void RegistePluginVideoSource();
bool obs_module_load(void)
{
	blog(LOG_INFO, "load agora tool plugin to communicate with agora rtc sdk");
	RegisterAgoraAudioEncoder();
	blog(LOG_INFO, "register agora audio encoder");
	RegisterAgoraOutput();
	blog(LOG_INFO, "register agora output");

	RegistePluginVideoSource();

    initQT();
	blog(LOG_INFO, "loaded agora tool!");
	return true;
}
void initQT()
{
  QMainWindow* mainWindow = (QMainWindow*)obs_frontend_get_main_window();

  const char* menuActionText =
    obs_module_text("AgoraTool.Settings.DialogTitle");
  QAction* menuAction =
    (QAction*)obs_frontend_add_tools_menu_qaction(menuActionText);

  AgoraBasic* agoraDialog = new AgoraBasic(mainWindow);
  QString mpath = "file:///../../data/obs-studio/themes/Dark.qss";
  QObject::connect(menuAction, &QAction::triggered, [agoraDialog] {
    // The settings dialog belongs to the main window. Should be ok
    // to pass the pointer to this QAction belonging to the main window
	blog(LOG_INFO, "trigger dialog");
    agoraDialog->ToggleAgoraDialog();
  });
}

#if _WIN32
void obs_module_unload() {
	blog(LOG_INFO, "unoad agora tool!");
}
#else 
__attribute__((visibility("default"))) void obs_module_unload() {
	blog(LOG_INFO, "unoad agora tool!");
}
#endif