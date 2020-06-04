
#include "ExtendVideoFrameObserver.hpp"
#include <TCHAR.h>
//#include <timeapi.h>
#include <stdio.h>
#include <util/base.h>

//static unsigned char imageBuffer[1920 * 1080 * 4] = { 0 };
static AgoraVideoBuffer videoBuffer = { 0, {0} };
pthread_mutex_t buffer_mutex;

;;FILE* file = NULL;
CExtendVideoFrameObserver::CExtendVideoFrameObserver()
    : logVideoFrameTimeCount(0)
    , logVideoTimestamp(false)
    , m_RenderWidth(640)
    , m_RenderHeight(480)
{
    m_RenderWidth = 0;
    m_RenderHeight = 0;
    pthread_mutexattr_t attr;
    pthread_mutex_init_value(&buffer_mutex);

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&buffer_mutex, &attr);
}


CExtendVideoFrameObserver::~CExtendVideoFrameObserver()
{
    pthread_mutex_destroy(&buffer_mutex);
}

int CExtendVideoFrameObserver::_PrintObserverVideoFrame(VideoFrame* frame)
{
    unsigned char* srcBuffer = videoBuffer.imageBuffer;
    for (int planeNum = 0; planeNum < 3; ++planeNum) {
        int width = (planeNum ? (frame->width + 1) / 2 : frame->width);
        int height;
        switch (frame->type) {
        case FRAME_TYPE_YUV420:
            height = (planeNum ? (frame->height + 1) / 2 : frame->height);
            break;
            //     case FRAME_TYPE_YUV422:
            //         height = frame->height;
            //         break;
        default:
            height = (planeNum ? (frame->height + 1) / 2 : frame->height);
            break;
        }

        agora::media::IVideoFrame::PLANE_TYPE plane_type = static_cast<agora::media::IVideoFrame::PLANE_TYPE>(planeNum);
        unsigned char* plane_buffer = NULL;
        int stride = frame->yStride;
        if (planeNum == 0) {
            plane_buffer = (unsigned char*)frame->yBuffer;
            stride = frame->yStride;
        }

        else if (planeNum == 1) {
            plane_buffer = (unsigned char*)frame->uBuffer;
            stride = frame->uStride;
        }
        else if (planeNum == 2) {
            plane_buffer = (unsigned char*)frame->vBuffer;
            stride = frame->vStride;
        }

        for (int y = 0; y < height; y++) {
            memcpy_s(plane_buffer, width, srcBuffer, width);
            plane_buffer += stride;
            srcBuffer += width;
        }
    }
    return 0;
}

int timeinc = 0;
bool CExtendVideoFrameObserver::onCaptureVideoFrame(VideoFrame& videoFrame)
{
    int size = videoFrame.yStride * videoFrame.height * 3 / 2;
    int bufSize = 0;    
    pthread_mutex_lock(&buffer_mutex);
#ifdef 0
    fwrite(videoBuffer.imageBuffer, 1, size, file);
#endif
    if (videoFrame.yStride == videoFrame.width) {
        int nUvLen = videoFrame.height * videoFrame.width / 4;
        int nYLen = nUvLen * 4;

        memcpy_s(videoFrame.yBuffer, nYLen, videoBuffer.imageBuffer, nYLen);
        memcpy_s(videoFrame.uBuffer, nUvLen, videoBuffer.imageBuffer + nYLen, nUvLen);
        memcpy_s(videoFrame.vBuffer, nUvLen, videoBuffer.imageBuffer + nYLen + nUvLen, nUvLen);
    }
    else {
        _PrintObserverVideoFrame(&videoFrame);
    }
    pthread_mutex_unlock(&buffer_mutex);

    videoFrame.renderTimeMs = GetTickCount64();
    if (logVideoTimestamp && logVideoFrameTimeCount < fps * LOG_VIDEO_FRAME_TIME_DUARATION) {
        blog(LOG_INFO, "Agora Info onCaptureVideoFrame , agora sdk get obs video frame time: %lld, agora video frame time %lld.(%lldms)", videoBuffer.videoTimes, videoFrame.renderTimeMs, videoFrame.renderTimeMs - videoBuffer.videoTimes);
        logVideoFrameTimeCount++;
    }
  
    return true;
}

bool CExtendVideoFrameObserver::onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame)
{
	
	return true;
}

void CExtendVideoFrameObserver::setVideoResolution(int w, int h)
{
	m_resolutionX = w;
	m_resolutionY = h;
}

void CExtendVideoFrameObserver::pushBackVideoFrame(void* buffer, int size, int64_t videoTime)
{
    pthread_mutex_lock(&buffer_mutex);
    memcpy_s(videoBuffer.imageBuffer, size, buffer, size);
    videoBuffer.videoTimes = videoTime;
    pthread_mutex_unlock(&buffer_mutex);
}
