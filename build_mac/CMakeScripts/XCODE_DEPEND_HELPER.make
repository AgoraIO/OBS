# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.agora-tool-ui.Debug:
/Users/zhanxiaochao/Desktop/obs-studio/OBS/build_mac/Debug/libagora-tool-ui.so:\
	/Users/zhanxiaochao/Desktop/obs-studio/build/libobs/libobs.0.dylib\
	/usr/local/Cellar/qt/5.15.2/lib/QtWidgets.framework/QtWidgets\
	/Users/zhanxiaochao/Desktop/obs-studio/OBS/deps/mac/libs/libyuv.a\
	/Users/zhanxiaochao/Desktop/obs-studio/OBS/deps/mac/libs/libobs-frontend-api.dylib\
	/usr/local/Cellar/qt/5.15.2/lib/QtGui.framework/QtGui\
	/usr/local/Cellar/qt/5.15.2/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/zhanxiaochao/Desktop/obs-studio/OBS/build_mac/Debug/libagora-tool-ui.so


PostBuild.agora-tool-ui.Release:
/Users/zhanxiaochao/Desktop/obs-studio/OBS/build_mac/Release/libagora-tool-ui.so:\
	/Users/zhanxiaochao/Desktop/obs-studio/build/libobs/libobs.0.dylib\
	/usr/local/Cellar/qt/5.15.2/lib/QtWidgets.framework/QtWidgets\
	/Users/zhanxiaochao/Desktop/obs-studio/OBS/deps/mac/libs/libyuv.a\
	/Users/zhanxiaochao/Desktop/obs-studio/OBS/deps/mac/libs/libobs-frontend-api.dylib\
	/usr/local/Cellar/qt/5.15.2/lib/QtGui.framework/QtGui\
	/usr/local/Cellar/qt/5.15.2/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/zhanxiaochao/Desktop/obs-studio/OBS/build_mac/Release/libagora-tool-ui.so


PostBuild.agora-tool-ui.MinSizeRel:
/Users/zhanxiaochao/Desktop/obs-studio/OBS/build_mac/MinSizeRel/libagora-tool-ui.so:\
	/Users/zhanxiaochao/Desktop/obs-studio/build/libobs/libobs.0.dylib\
	/usr/local/Cellar/qt/5.15.2/lib/QtWidgets.framework/QtWidgets\
	/Users/zhanxiaochao/Desktop/obs-studio/OBS/deps/mac/libs/libyuv.a\
	/Users/zhanxiaochao/Desktop/obs-studio/OBS/deps/mac/libs/libobs-frontend-api.dylib\
	/usr/local/Cellar/qt/5.15.2/lib/QtGui.framework/QtGui\
	/usr/local/Cellar/qt/5.15.2/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/zhanxiaochao/Desktop/obs-studio/OBS/build_mac/MinSizeRel/libagora-tool-ui.so


PostBuild.agora-tool-ui.RelWithDebInfo:
/Users/zhanxiaochao/Desktop/obs-studio/OBS/build_mac/RelWithDebInfo/libagora-tool-ui.so:\
	/Users/zhanxiaochao/Desktop/obs-studio/build/libobs/libobs.0.dylib\
	/usr/local/Cellar/qt/5.15.2/lib/QtWidgets.framework/QtWidgets\
	/Users/zhanxiaochao/Desktop/obs-studio/OBS/deps/mac/libs/libyuv.a\
	/Users/zhanxiaochao/Desktop/obs-studio/OBS/deps/mac/libs/libobs-frontend-api.dylib\
	/usr/local/Cellar/qt/5.15.2/lib/QtGui.framework/QtGui\
	/usr/local/Cellar/qt/5.15.2/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/zhanxiaochao/Desktop/obs-studio/OBS/build_mac/RelWithDebInfo/libagora-tool-ui.so




# For each target create a dummy ruleso the target does not have to exist
/Users/zhanxiaochao/Desktop/obs-studio/OBS/deps/mac/libs/libobs-frontend-api.dylib:
/Users/zhanxiaochao/Desktop/obs-studio/OBS/deps/mac/libs/libyuv.a:
/Users/zhanxiaochao/Desktop/obs-studio/build/libobs/libobs.0.dylib:
/usr/local/Cellar/qt/5.15.2/lib/QtCore.framework/QtCore:
/usr/local/Cellar/qt/5.15.2/lib/QtGui.framework/QtGui:
/usr/local/Cellar/qt/5.15.2/lib/QtWidgets.framework/QtWidgets:
