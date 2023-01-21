#include "ImageDisplayTool.h"
#include "Socket.h"
#include "ImagePixelFormatToRGBA.h"

#include <stdio.h>

static LogLevel m_displayLevel = LOG_DEBUG;
static CTcpServer m_tcpServer;
static bool m_flag = false;
static int m_tcpServerPort = 5051;// 为通信端口
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

void _stdcall SetLogDisplayLevel(LogLevel level, int tcpServerPort)
{
	m_displayLevel = level;
    m_tcpServerPort = tcpServerPort;
}


bool _stdcall SendLog(char* strbuffer, enum LogLevel level, enum  LogDisplayWindows target)
{
    while (m_flag == false) {
        m_flag = CTcpServerInit();
    }

    char strbufferHead[24];
    memset(strbufferHead, 0, sizeof(strbufferHead));
    sprintf_s(strbufferHead, "LogLevel:%d", level);
    if (m_tcpServer.Send(strbufferHead, (int)strlen(strbufferHead)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    if (m_tcpServer.Send(strbuffer, (int)strlen(strbuffer)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    printf("LogLevel：%s ,发送：%s\n", strbufferHead ,strbuffer);
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

    char strbufferHead[10];
    memset(strbufferHead, 0, sizeof(strbufferHead));
    sprintf_s(strbufferHead, "SendImage");
    if (m_tcpServer.Send(strbufferHead, (int)strlen(strbufferHead)) <= 0) {
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
