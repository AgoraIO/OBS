
#include "ExtendVideoFrameObserver.hpp"
#include <TCHAR.h>
//#include <timeapi.h>
#include <stdio.h>
FILE* fp = NULL;
CExtendVideoFrameObserver::CExtendVideoFrameObserver()
{
	fp = fopen("D:/1.yuv", "wb");
	m_lpImageBuffer = new BYTE[0x800000];

//	m_lpRenderBuffer = new BYTE[0x800000];

	m_RenderWidth = 0;
	m_RenderHeight = 0;
}


CExtendVideoFrameObserver::~CExtendVideoFrameObserver()
{
	delete[] m_lpImageBuffer;
	m_lpImageBuffer = NULL;
//	delete[] m_lpRenderBuffer;
//	m_lpRenderBuffer = NULL;
	if (fp){
		fclose(fp);
		fp = NULL;
	}
}

int timeinc = 0;
bool CExtendVideoFrameObserver::onCaptureVideoFrame(VideoFrame& videoFrame)
{
	if ((int*)m_lpImageBuffer == (int*)0xfeeefeee){
		m_lpImageBuffer = NULL;
		return false;
	}

	if (!m_lpImageBuffer)
		return false;
		
	SIZE_T nBufferSize = 0x800000;
	int nUvLen = videoFrame.height * videoFrame.width / 4;
	int nYLen = nUvLen * 4;

	m_lpY = m_lpImageBuffer;
	m_lpU = m_lpImageBuffer + nUvLen * 4;
	m_lpV = m_lpImageBuffer + 5 * nUvLen;

	memcpy_s(videoFrame.yBuffer, nYLen, m_lpY, nYLen);
	videoFrame.yStride = videoFrame.width;
	
	memcpy_s(videoFrame.uBuffer, nUvLen, m_lpU, nUvLen);
	videoFrame.uStride = videoFrame.width/2;

	memcpy_s(videoFrame.vBuffer, nUvLen, m_lpV, nUvLen);
	videoFrame.vStride = videoFrame.width/2;

	videoFrame.type = FRAME_TYPE_YUV420;
	videoFrame.rotation = 0;
	videoFrame.renderTimeMs = GetTickCount();

	fwrite(m_lpY, 1, nYLen, fp);
	fwrite(m_lpU, 1, nUvLen, fp);
	fwrite(m_lpV, 1, nUvLen, fp);
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