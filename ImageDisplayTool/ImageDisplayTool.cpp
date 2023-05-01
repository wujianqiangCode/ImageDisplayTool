#include "ImageDisplayTool.h"
#include "Socket.h"
#include "ImagePixelFormatToRGBA.h"

#include <stdio.h>
#include<string.h>

static CTcpServer m_tcpServer;
static int m_tcpServerPort = 5051;
static bool m_flag = false;
bool CTcpServerInit() {

    if (m_tcpServer.InitServer(m_tcpServerPort) == false){
        printf("m_tcpServer.InitServer(5051) failed,exit...\n");
        m_flag = false;
        return m_flag;
    }

    if (m_tcpServer.Accept() == false) {
        printf("m_tcpServer.Accept() failed,exit...\n");
        m_flag = false;
        return m_flag;
    }

    printf("客户端已连接。\n");
    m_flag = true;
    return m_flag;
}

bool _stdcall SetTcpServerPort(int tcpServerPort)
{
    m_tcpServerPort = tcpServerPort;
    while (m_flag == false) {
        m_flag = CTcpServerInit();
    }

    char strbufferSetTcpServerPort[64];
    memset(strbufferSetTcpServerPort, 0, sizeof(strbufferSetTcpServerPort));
#ifdef __linux__
	snprintf(strbufferSetTcpServerPort, sizeof("SetTcpServerPort:%d"), "SetTcpServerPort:%d", tcpServerPort);
#else
	sprintf_s(strbufferSetTcpServerPort, "SetTcpServerPort:%d", tcpServerPort);
#endif

    if (m_tcpServer.Send(strbufferSetTcpServerPort, (int)strlen(strbufferSetTcpServerPort)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    printf("SetTcpServerPort:%s\n", strbufferSetTcpServerPort);
    return m_flag;
}

bool _stdcall SetLogDisplayLevel(enum LogLevel level)
{
    char strbufferSetLogDisplayLevel[64];
    memset(strbufferSetLogDisplayLevel, 0, sizeof(strbufferSetLogDisplayLevel));
#ifdef __linux__
    snprintf(strbufferSetLogDisplayLevel,sizeof("SetLogDisplayLevel:%d"),"SetLogDisplayLevel:%d", level);
#else
	sprintf_s(strbufferSetLogDisplayLevel, "SetLogDisplayLevel:%d", level);
#endif
    if (m_tcpServer.Send(strbufferSetLogDisplayLevel, (int)strlen(strbufferSetLogDisplayLevel)) <= 0) {
        m_flag = false;
        return m_flag;
    }
    printf("SetLogDisplayLevel:%s\n", strbufferSetLogDisplayLevel);
    return m_flag;
}
bool _stdcall SendLog(char* strbuffer, enum LogLevel level)
{
    while (m_flag == false) {
        m_flag = CTcpServerInit();
    }

    char strbufferLogLevel[24];
    memset(strbufferLogLevel, 0, sizeof(strbufferLogLevel));
#ifdef __linux__
	snprintf(strbufferLogLevel, sizeof("LogLevel:%d"), "LogLevel:%d", level);
#else
	sprintf_s(strbufferLogLevel, "LogLevel:%d", level);
#endif

    if (m_tcpServer.Send(strbufferLogLevel, (int)strlen(strbufferLogLevel)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    if (m_tcpServer.Send(strbuffer, (int)strlen(strbuffer)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    printf("LogLevel:%d ,发送:%s\n", level,strbuffer);
	return m_flag;
}
bool _stdcall SendImage(IMAGE image)
{

	if((image.pixel_width <=  0) || (image.pixel_height <=  0) || (image.pts < 0))
	{
		printf("SendImage: error pixel_width = %d, pixel_height = %d, pts =%lld",image.pixel_width, image.pixel_height, image.pts);
		return false;
	}

    while (m_flag == false) {
        m_flag = CTcpServerInit();
    }

    char strbufferImageInfo[1024];
    memset(strbufferImageInfo, 0, sizeof(strbufferImageInfo));
#ifdef __linux__
    snprintf(strbufferImageInfo,1024 ,"SendImage pixel_width = %d, pixel_height = %d, pts = %lld", image.pixel_width , image.pixel_height, image.pts);
#else
	sprintf_s(strbufferImageInfo, "SendImage pixel_width = %d, pixel_height = %d", pts = %lld", pixel_width, pixel_height, pts);
#endif
	if (m_tcpServer.Send(strbufferImageInfo, (int)strlen(strbufferImageInfo)) <= 0) {
        m_flag = false;
        return m_flag;
    }
    char strbufferImageData[1024];
    memset(strbufferImageData, 0, sizeof(strbufferImageData));
#ifdef __linux__
    snprintf(strbufferImageData, sizeof("SendImageData Begin !!!"), "SendImageData Begin !!!");
#else
	sprintf_s(strbufferImageData, "SendImageData Begin !!!");
#endif
    if (m_tcpServer.Send(strbufferImageData, (int)strlen(strbufferImageData)) <= 0) {
        m_flag = false;
        return m_flag;
    }
    unsigned char* pDst = NULL;
    if (ImagePixelFormatToRGBA(image, pDst) == false) {
        printf("ImagePixelFormatToRGBA error :pixel_width = %d, pixel_height = %d,  pts = %lld", image.pixel_width, image.pixel_height, image.pts);
        return false;
    }

    if (m_tcpServer.Send((char*)pDst, (int)strlen((char*)pDst)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    printf("发送：%s\n", pDst);
    return m_flag;
}
