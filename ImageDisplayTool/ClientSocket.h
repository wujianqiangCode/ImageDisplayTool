/*****************************************************************************
*  ImageDisplayTool
*  Copyright (C) 2023 ijianqiangwu@outlook.com
*
*  @file     ClientSocket.h
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
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h> 
#endif

// TCP�ͻ�����
class CTcpClient
{
public:
    int m_sockfd;

    CTcpClient();

    // ��������������ӣ�serverip-�����ip��portͨ�Ŷ˿�
    bool ConnectToServer(const char* serverip, const int port);

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



    ~CTcpClient();
};