#include "Socket.h"


CTcpServer::CTcpServer()
{
    // 构造函数初始化socket
    m_listenfd = m_clientfd = 0;
}

CTcpServer::~CTcpServer()
{
    if (m_listenfd != 0)
#ifdef _WIN32
        closesocket(m_listenfd);
#else
        close(m_listenfd);  // 析构函数关闭socket
#endif
    if (m_clientfd != 0)
#ifdef _WIN32
        closesocket(m_clientfd);
#else
        close(m_clientfd);  // 析构函数关闭socket
#endif
}

// 初始化服务端的socket，port为通信端口
bool CTcpServer::InitServer(int port)
{
    m_listenfd = socket(AF_INET, SOCK_STREAM, 0);  // 创建服务端的socket

    // 把服务端用于通信的地址和端口绑定到socket上
    struct sockaddr_in servaddr;    // 服务端地址信息的数据结构
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;  // 协议族，在socket编程中只能是AF_INET
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  // 本主机的任意ip地址
    servaddr.sin_port = htons(port);  // 绑定通信端口
    if (bind(m_listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    {
#ifdef _WIN32
        closesocket(m_listenfd);
#else
        close(m_listenfd);
#endif
        m_listenfd = 0;
        return false;
    }

    // 把socket设置为监听模式
    if (listen(m_listenfd, 5) != 0) {
#ifdef _WIN32
        closesocket(m_listenfd);
#else
        close(m_listenfd);
#endif
        m_listenfd = 0;
        return false;
    }

    return true;
}

bool CTcpServer::Accept()
{
    if ((m_clientfd = accept(m_listenfd, 0, 0)) <= 0) 
        return false;

    return true;
}

#ifdef _WIN32
// 向对端发送报文
int  CTcpServer::Send(const char* buf, const int buflen) {
    return send(m_clientfd, buf, buflen, 0);
}

// 接收对端的报文
int  CTcpServer::Recv(char* buf, const int buflen) {
    return recv(m_clientfd, buf, buflen, 0);
}
#else
int CTcpServer::Send(const void* buf, const int buflen)
{
    return send(m_clientfd, buf, buflen, 0);
}

int CTcpServer::Recv(void* buf, const int buflen)
{
    return recv(m_clientfd, buf, buflen, 0);
}
#endif