#pragma once
#include "Agora/IAgoraMediaEngine.h"
#include <Windows.h>
#include "util/threading.h"

#define VIDEO_BUF_SIZE (1920*1080*4)
#define LOG_VIDEO_FRAME_TIME_DUARATION 10 //10 second
typedef struct _AgoraVideoBuffer {
    int64_t videoTimes;
    unsigned char imageBuffer[1920 * 1080 * 4];
}AgoraVideoBuffer;

class CExtendVideoFrameObserver :
    public agora::media::IVideoFrameObserver
{
public:
    CExtendVideoFrameObserver();
    ~CExtendVideoFrameObserver();

    virtual bool onCaptureVideoFrame(VideoFrame& videoFrame);
    virtual bool onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame);

    void setVideoResolution(int w, int h);
    int					m_RenderWidth;
    int					m_RenderHeight;
    int     fps = 15;
    void Resetlog(bool b) { logVideoTimestamp = b; logVideoFrameTimeCount = 0; }

    void pushBackVideoFrame(void* buffer, int size, int64_t videoTimes);

private:
    int   _PrintObserverVideoFrame(VideoFrame* frame);
    int   m_resolutionX;
    int   m_resolutionY;
    int   logVideoFrameTimeCount;
    bool  logVideoTimestamp;
};

