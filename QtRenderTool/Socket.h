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