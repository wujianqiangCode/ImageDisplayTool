/*****************************************************************************
*  ImageDisplayTool
*  Copyright (C) 2023 ijianqiangwu@outlook.com
*
*  @file     ClientSocket.h
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

// TCP客户端类
class CTcpClient
{
public:
    int m_sockfd;

    CTcpClient();

    // 向服务器发起连接，serverip-服务端ip，port通信端口
    bool ConnectToServer(const char* serverip, const int port);

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



    ~CTcpClient();
};