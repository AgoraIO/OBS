# Once done these will be defined:
#
#  AGORA_FOUND
#  AGORA_INCLUDE_DIRS
#  AGORA_LIB_DIRS
#
# For use win-agora plugin:
#
#  AGORA_INCLUDE_DIR

find_package(PkgConfig QUIET)


if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(_lib_suffix 64)
else()
	set(_lib_suffix 32)
endif()

if (PKG_CONFIG_FOUND)
	pkg_check_modules(_AGORA QUIET agora agora_rtc_sdk agora_sig_sdk libeay32)
endif()

find_path(AGORA_INCLUDE_DIR
	NAMES agora/IAgoraRtcEngine.h agora/IAgoraMediaEngine.h agora/IAgoraRtcEngine2 agora/IAgoraService.h
	HINTS
		ENV agoraPath${_lib_suffix}
		ENV agoraPath
		ENV DepsPath${_lib_suffix}
		ENV DepsPath
		${agoraPath${_lib_suffix}}
		${agoraPath}
		${DepsPath${_lib_suffix}}
		${DepsPath}
		${_AGORA_INCLUDE_DIRS}
	PATH_SUFFIXES
		include)

find_library(AGORA_LIB
	NAMES ${_AGORA_LIBRARIES} agora agora_rtc_sdk agora_sig_sdk
	HINTS
		ENV agoraPath${_lib_suffix}
		ENV agoraPath
		ENV DepsPath${_lib_suffix}
		ENV DepsPath
		${agoraPath${_lib_suffix}}
		${agoraPath}
		${DepsPath${_lib_suffix}}
		${DepsPath}
		${AGORA_LIB_DIRS}
	PATHS
		/usr/lib /usr/local/lib /opt/local/lib /sw/lib
	PATH_SUFFIXES
		lib${_lib_suffix} lib
		libs${_lib_suffix} libs
		bin${_lib_suffix} bin
		../lib${_lib_suffix} ../lib
		../libs${_lib_suffix} ../libs
		../bin${_lib_suffix} ../bin)

find_library(OPENSSL_LIB
	NAMES ${_OPENSSL_LIBRARIES} libeay32
	HINTS
	        ENV DepsPath${_lib_suffix}
		ENV DepsPath
		${DepsPath${_lib_suffix}}
		${DepsPath}
	        ${OPENSSL_LIB_DIRS}
	PATH_SUFFIXES
		lib${_lib_suffix} lib
		libs${_lib_suffix} libs
		bin${_lib_suffix} bin
		../lib${_lib_suffix} ../lib
		../libs${_lib_suffix} ../libs
		../bin${_lib_suffix} ../bin)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Agora DEFAULT_MSG AGORA_LIB AGORA_INCLUDE_DIR)
mark_as_advanced(AGORA_INCLUDE_DIR AGORA_LIB)

if(Agora_FOUND)
	set(AGORA_INCLUDE_DIRS ${AGORA_INCLUDE_DIR})
	set(AGORA_LIB_DIRS ${AGORA_LIB})
	set(OPENSSL_LIB_DIRS ${OPENSSL_LIB})
endif()
