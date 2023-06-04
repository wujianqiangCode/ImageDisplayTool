/*****************************************************************************
*  QtRenderTool
*  Copyright (C) 2023 ijianqiangwu@outlook.com
*
*  @file     ServerSocket.h
*  @brief    ���ļ��ļ���
*  Details.
*
*  @author   WuJianQiang
*  @email    ijianqiangwu@outlook.com
*  @version  1.0.0.1(�汾��)
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

    bool InitServer(int port);  // ��ʼ�������

    // �����������߳�
	int Create();
	void Destroy();
    
#ifdef _WIN32
    // ��Զ˷��ͱ���
    int  Send(const char* buf, const int buflen);
    
    // ���նԶ˵ı���
    int  Recv(char* buf, const int buflen);
#else
    // ��Զ˷��ͱ���
    int  Send(const void* buf, const int buflen);
    
    // ���նԶ˵ı���
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

    bool Accept();  // �ȴ��ͻ��˵�����

    bool ProcessReceiveInfo();

private:
	// �̵߳���ں���
	void run(); 

    SOCKET m_listenfd;   // ��������ڼ�����socket
    SOCKET m_clientfd;   // �ͻ�����������socket

    std::queue<QString> m_ServerSocketReceiveInfoQueue;
    QString m_qStrTemp;
};

