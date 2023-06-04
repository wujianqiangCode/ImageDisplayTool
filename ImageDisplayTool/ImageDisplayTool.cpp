#include "ImageDisplayTool.h"
#include "ClientSocket.h"
#include "ImagePixelFormatToRGBA.h"

#include <stdio.h>
#include<string.h>

static CTcpClient m_tcpClient;
static char* m_tcpServerIP;
static int m_tcpClientPort = 5051;
static bool m_flag = false;
bool InitClientTCP() {

    //向服务器（特定的IP和端口）发起请求
    if (m_tcpClient.ConnectToServer(m_tcpServerIP,m_tcpClientPort) == false){
        printf("m_tcpClient.ConnectToServer m_tcpServerIP = %s , m_tcpClientPort = %d failed,exit...\n", m_tcpServerIP,m_tcpClientPort);
        m_flag = false;
        return m_flag;
    }

    printf("客户端已成功连接服务器。\r\n");
    m_flag = true;
    return m_flag;
}

bool _stdcall SetTcpInfo(char* tcpServerIP, int tcpServerPort)
{
    m_tcpServerIP = tcpServerIP;
    m_tcpClientPort = tcpServerPort;

    // int nCunter = 100;
    while (1) //while ((m_flag == false) && (nCunter > 0))
    {
        m_flag = InitClientTCP();
        if(m_flag == false)
        {
            sleep(10);
        }
        else
        {
            break;
        }

       // --nCunter;
    }

    return m_flag;
}

bool _stdcall SetLogDisplayLevel(enum LogLevel level)
{
    char strbufferSetLogDisplayLevel[1024];
    memset(strbufferSetLogDisplayLevel, 0, sizeof(strbufferSetLogDisplayLevel));
#ifdef __linux__
    snprintf(strbufferSetLogDisplayLevel,sizeof("SetLogDisplayLevel:%d"),"SetLogDisplayLevel:%d", level);
#else
	sprintf_s(strbufferSetLogDisplayLevel, "SetLogDisplayLevel:%d", level);
#endif
    strcat(strbufferSetLogDisplayLevel, "\r\n");
    if (m_tcpClient.Send(strbufferSetLogDisplayLevel, (int)strlen(strbufferSetLogDisplayLevel)) <= 0) {
        m_flag = false;
        return m_flag;
    }
    printf("SetLogDisplayLevel:%s\n", strbufferSetLogDisplayLevel);
    return m_flag;
}
bool _stdcall SendLog(char* strbuffer, enum LogLevel level)
{
    while (m_flag == false) {
        m_flag = InitClientTCP();
    }

    char strbufferLogLevel[24];
    memset(strbufferLogLevel, 0, sizeof(strbufferLogLevel));
#ifdef __linux__
	snprintf(strbufferLogLevel, sizeof("LogLevel:%d"), "LogLevel:%d", level);
#else
	sprintf_s(strbufferLogLevel, "LogLevel:%d", level);
#endif

    // if (m_tcpClient.Send(strbufferLogLevel, (int)strlen(strbufferLogLevel)) <= 0) {
    //     m_flag = false;
    //     return m_flag;
    // }

    // if (m_tcpClient.Send(strbuffer, (int)strlen(strbuffer)) <= 0) {
    //     m_flag = false;
    //     return m_flag;
    // }

    char str[1024];
    memset(str, 0, 1024);
    strcpy(str, strbufferLogLevel);
    strcat(str, strbuffer);
    strcat(str, "\r\n");
    if (m_tcpClient.Send(str, (int)strlen(str)) <= 0) {
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
        m_flag = InitClientTCP();
    }

    //Begin
    char* strImageBegin = "SendImageBegin!!! \r\n";
	if (m_tcpClient.Send(strImageBegin, (int)strlen(strImageBegin)) <= 0) {
        m_flag = false;
        return m_flag;
    }


    //width
    char strImageWidth[1024];
    memset(strImageWidth, 0, sizeof(strImageWidth));
#ifdef __linux__
    snprintf(strImageWidth,1024 ,"SendImagePixelWidth=%d", image.pixel_width);
#else
	sprintf_s(strImageWidth, "SendImagePixelWidth=%d", image.pixel_width);
#endif
    strcat(strImageWidth, "\r\n");
	if (m_tcpClient.Send(strImageWidth, (int)strlen(strImageWidth)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    //height
    char strImageHeight[1024];
    memset(strImageHeight, 0, sizeof(strImageHeight));
#ifdef __linux__
    snprintf(strImageHeight,1024 ,"SendImagePixelHeight=%d", image.pixel_height);
#else
	sprintf_s(strImageHeight, "SendImagePixelHeight=%d", image.pixel_height);
#endif
    strcat(strImageHeight, "\r\n");
	if (m_tcpClient.Send(strImageHeight, (int)strlen(strImageHeight)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    //pts
    char strImagePTS[1024];
    memset(strImagePTS, 0, sizeof(strImagePTS));
#ifdef __linux__
    snprintf(strImagePTS,1024 ,"SendImagePTS=%d", image.pts);
#else
	sprintf_s(strImagePTS, "SendImagePTS=%d", image.pts);
#endif
    strcat(strImagePTS, "\r\n");
	if (m_tcpClient.Send(strImagePTS, (int)strlen(strImagePTS)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    //data
    unsigned char* pDst = NULL;
    if (ImagePixelFormatToRGBA(image, &pDst) == false) {
        printf("ImagePixelFormatToRGBA error :pixel_width = %d, pixel_height = %d,  pts = %lld", image.pixel_width, image.pixel_height, image.pts);
        return false;
    }
    strcat((char*)pDst, "\r\n");
    if (m_tcpClient.Send((char*)pDst, (int)strlen((char*)pDst)) <= 0) {
        m_flag = false;
        return m_flag;
    }

    printf("发送：%s\n", pDst);
    return m_flag;
}
