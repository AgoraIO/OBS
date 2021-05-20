#!/bin/sh
make -C /Users/zhanxiaochao/Desktop/obs-studio/OBS/build_mac -f /Users/zhanxiaochao/Desktop/obs-studio/OBS/build_mac/CMakeScripts/ZERO_CHECK_cmakeRulesBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
