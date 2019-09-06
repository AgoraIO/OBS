#pragma once
#include "Agora/IAgoraMediaEngine.h"
#include <Windows.h>
#include "util/threading.h"

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

    void pushBackVideoFrame(void* buffer, int size);
private:
    int   _PrintObserverVideoFrame(VideoFrame* frame);
    int                m_resolutionX;
    int                m_resolutionY;

};

