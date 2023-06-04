/*****************************************************************************
*  QtRenderTool
*  Copyright (C) 2023 ijianqiangwu@outlook.com
*
*  @file     ServerSocket.h
*  @brief    对文件的简述
*  Details.
*
*  @author   WuJianQiang
*  @email    ijianqiangwu@outlook.com
*  @version  1.0.0.1(版本号)
*  @date     2023.05.30
*  @license  GNU General Public License (GPL)
*
*----------------------------------------------------------------------------
*  Remark         : Description
*----------------------------------------------------------------------------
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*----------------------------------------------------------------------------
*  2023/05/30 | 1.0.0.1   | WuJianQiang          | Create file
*----------------------------------------------------------------------------
*
*****************************************************************************/

#pragma once

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SOCKET int
#endif

#include <string>
#include <queue>
#include <algorithm>   

#include <QtCore/QThread>

enum LogLevel {
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG,
};


class CTcpServer: public QThread
{
    Q_OBJECT
public:

    CTcpServer(QObject *parent);
    ~CTcpServer();

    bool InitServer(int port);  // 初始化服务端

    // 创建与销毁线程
	int Create();
	void Destroy();
    
#ifdef _WIN32
    // 向对端发送报文
    int  Send(const char* buf, const int buflen);
    
    // 接收对端的报文
    int  Recv(char* buf, const int buflen);
#else
    // 向对端发送报文
    int  Send(const void* buf, const int buflen);
    
    // 接收对端的报文
    int  Recv(void* buf, const int buflen);
#endif

public:
    LogLevel m_emSetLogDisplayLevel;
    LogLevel m_emLogLevel;

    char m_strLogInfo[1024];

    int m_nImageHeight;
    int m_nImageWidth;
    long long m_llImagePTS;
    unsigned char* m_pImageData;

private:

    bool Accept();  // 等待客户端的连接

    bool ProcessReceiveInfo();

private:
	// 线程的入口函数
	void run(); 

    SOCKET m_listenfd;   // 服务端用于监听的socket
    SOCKET m_clientfd;   // 客户端连上来的socket

    std::queue<QString> m_ServerSocketReceiveInfoQueue;
    QString m_qStrTemp;
};

