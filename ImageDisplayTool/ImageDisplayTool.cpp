#include "ImageDisplayTool.h"
#include "Socket.h"
#include "ImagePixelFormatToRGBA.h"

#include <stdio.h>


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

bool _stdcall SetLogDisplayLevelAndTcpServerPort(LogLevel level, int tcpServerPort)
{
    m_tcpServerPort = tcpServerPort;
    while (m_flag == false) {
        m_flag = CTcpServerInit();
    }

    char strbufferSetLogDisplayLevel[64];
    memset(strbufferSetLogDisplayLevel, 0, sizeof(strbufferSetLogDisplayLevel));
    sprintf_s(strbufferSetLogDisplayLevel, "SetLogDisplayLevel:%d", level);
    if (m_tcpServer.Send(strbufferSetLogDisplayLevel, (int)strlen(strbufferSetLogDisplayLevel)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    char strbufferSetTcpServerPort[64];
    memset(strbufferSetTcpServerPort, 0, sizeof(strbufferSetTcpServerPort));
    sprintf_s(strbufferSetTcpServerPort, "SetTcpServerPort:%d", tcpServerPort);
    if (m_tcpServer.Send(strbufferSetTcpServerPort, (int)strlen(strbufferSetTcpServerPort)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    printf("SetLogDisplayLevel：%s ,SetTcpServerPortLogLevel：%s\n", strbufferSetLogDisplayLevel, strbufferSetTcpServerPort);
    return m_flag;
}


bool _stdcall SendLog(char* strbuffer, enum LogLevel level)
{
    while (m_flag == false) {
        m_flag = CTcpServerInit();
    }

    char strbufferLogLevel[24];
    memset(strbufferLogLevel, 0, sizeof(strbufferLogLevel));
    sprintf_s(strbufferLogLevel, "LogLevel:%d", level);
    if (m_tcpServer.Send(strbufferLogLevel, (int)strlen(strbufferLogLevel)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    if (m_tcpServer.Send(strbuffer, (int)strlen(strbuffer)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    printf("LogLevel：%d ,发送：%s\n", level,strbuffer);
	return m_flag;
}
bool _stdcall SendImage(unsigned char* pSrc, unsigned int pixel_width, unsigned int pixel_height, enum ImagePixelFormat type)
{	
	if((pSrc == nullptr) || (pixel_width <=  0) || (pixel_height <= 0))
	{
		printf("SendImage: error  pSrc = %s, pixel_width = %d, pixel_height = %d", pSrc, pixel_width, pixel_height);
		return false;
	}

    while (m_flag == false) {
        m_flag = CTcpServerInit();
    }

    char strbufferImageInfo[1024];
    memset(strbufferImageInfo, 0, sizeof(strbufferImageInfo));
    sprintf_s(strbufferImageInfo, "SendImage pixel_width = %d, pixel_height = %d", pixel_width , pixel_height);
    if (m_tcpServer.Send(strbufferImageInfo, (int)strlen(strbufferImageInfo)) <= 0) {
        m_flag = false;
        return m_flag;
    }
    char strbufferImageData[1024];
    memset(strbufferImageData, 0, sizeof(strbufferImageData));
    sprintf_s(strbufferImageData, "SendImageData Begin !!!");
    if (m_tcpServer.Send(strbufferImageData, (int)strlen(strbufferImageData)) <= 0) {
        m_flag = false;
        return m_flag;
    }
    unsigned char* pDst = NULL;
    if (ImagePixelFormatToRGBA(pSrc, pDst, pixel_width, pixel_height, type) == false) {
        printf("ImagePixelFormatToRGBA error :pSrc = %s, pixel_width = %d, pixel_height = %d", pSrc, pixel_width, pixel_height);
        return false;
    }

    if (m_tcpServer.Send((char*)pDst, (int)strlen((char*)pDst)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    printf("发送：%s\n", pSrc);
    return m_flag;
	
}
