#include "ImageDisplayTool.h"
#include "Socket.h"

#include <stdio.h>

static LogLevel m_displayLevel = LOG_DEBUG;
static CTcpServer m_tcpServer;
bool m_flag = false;
bool CTcpServerInit() {
    
    if (m_tcpServer.InitServer(5051) == false){
        printf("m_tcpServer.InitServer(5051) failed,exit...\n"); 
        return false;
    }

    if (m_tcpServer.Accept() == false) {
        printf("m_tcpServer.Accept() failed,exit...\n"); 
        return false; 
    }

    printf("客户端已连接。\n");
    m_flag = true;
    return true;
}

void _stdcall SetLogDisplayLevel(LogLevel level, unsigned char* pIPAdd)
{
	m_displayLevel = level;
}


bool _stdcall SendLog(char* strbuffer, enum LogLevel level, enum  LogDisplayWindows target)
{
    while (m_flag == false) {
        m_flag = CTcpServerInit();
    }
    if (m_tcpServer.Send(strbuffer, strlen(strbuffer)) <= 0) {
        m_flag = false;
        return false;
    }
    printf("发送：%s\n", strbuffer);
	return true;
}
bool _stdcall SendImage(char* pSrc, int width, int height, enum ImagePixelFormat type)
{	
	if((pSrc == nullptr) || (width <=  0) || (height <= 0))
	{
		printf("error : SendImage  pSrc = %s, width = %d, height = %d", pSrc, width, height);
		return false;
	}

    while (m_flag == false) {
        m_flag = CTcpServerInit();
    }
    if (m_tcpServer.Send(pSrc, strlen(pSrc)) <= 0) {
        m_flag = false;
        return false;
    }
    printf("发送：%s\n", pSrc);
    return true;
	
}
