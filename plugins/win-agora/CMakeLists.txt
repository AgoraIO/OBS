project(win-agora)

find_package(Agora REQUIRED)
include_directories(${AGORA_INCLUDE_DIR})
add_definitions(${AGORA_DEFINITIONS})

if(WIN32 AND NOT MINGW)
	set(win-agora_PLATFORM_DEPS
		w32-pthreads)
endif()

set(win-agora_HEADERS
	Agora/agorartcengine.hpp
	Agora/CicleBuffer.hpp
	Agora/ExtendAudioFrameObserver.hpp
	Agora/ExtendVideoFrameObserver.hpp)

set(win-agora_SOURCES
    agora-plugin.cpp
    agora-pcm-encoder.cpp
	agora-yuv-encoder.cpp
	agora-output.cpp
	agora-service.cpp
	Agora/agorartcengine.cpp
	Agora/CicleBuffer.cpp
	Agora/ExtendAudioFrameObserver.cpp
	Agora/ExtendVideoFrameObserver.cpp)

set(win-agora_DEPS
    agora_rtc_sdk)

add_library(win-agora MODULE
    ${win-agora_HEADERS}
    ${win-agora_SOURCES})

target_link_libraries(win-agora
    ${agora_DEPS}
	${win-agora_PLATFORM_DEPS}
    libobs
	${AGORA_LIB_DIRS})

install_obs_plugin_with_data(win-agora data)
