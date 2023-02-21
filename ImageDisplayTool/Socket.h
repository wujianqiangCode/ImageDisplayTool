
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

class CTcpServer
{
public:
    SOCKET m_listenfd;   // 服务端用于监听的socket
    SOCKET m_clientfd;   // 客户端连上来的socket

    CTcpServer();

    bool InitServer(int port);  // 初始化服务端

    bool Accept();  // 等待客户端的连接

    
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

    ~CTcpServer();
};

