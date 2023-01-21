
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
#endif

class CTcpServer
{
public:
    SOCKET m_listenfd;   // ��������ڼ�����socket
    SOCKET m_clientfd;   // �ͻ�����������socket

    CTcpServer();

    bool InitServer(int port);  // ��ʼ�������

    bool Accept();  // �ȴ��ͻ��˵�����

    
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

    ~CTcpServer();
};

