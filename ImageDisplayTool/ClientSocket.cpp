#include "ClientSocket.h"

CTcpClient::CTcpClient()
{
    m_sockfd = 0;  // 构造函数初始化m_sockfd
}

CTcpClient::~CTcpClient()
{
    if (m_sockfd != 0) 
#ifdef _WIN32
        closesocket(m_sockfd);// 析构函数关闭m_sockfd
#else
        close(m_sockfd);
#endif
}

// 向服务器发起连接，serverip-服务端ip，port通信端口
bool CTcpClient::ConnectToServer(const char* serverip, const int port)
{
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0); // 创建客户端的socket

    struct hostent* h; // ip地址信息的数据结构
    if ((h = gethostbyname(serverip)) == 0)//客户端程序指定服务端的ip地址
    {
#ifdef _WIN32
        closesocket(m_sockfd);
#else
        close(m_sockfd);
#endif
        m_sockfd = 0;
        return false;
    }

    // 设置连接超时时间为 0 秒
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    if (setsockopt(m_sockfd, SOL_TCP, TCP_NODELAY, &tv, sizeof(tv)) < 0) 
    {
#ifdef _WIN32
        closesocket(m_sockfd);
#else
        close(m_sockfd);
#endif
        m_sockfd = 0;
        return false;
    }

    // 把服务器的地址和端口转换为数据结构
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);

    // 向服务器发起连接请求
    if (connect(m_sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    {
#ifdef _WIN32
        closesocket(m_sockfd);
#else
        close(m_sockfd);
#endif
        m_sockfd = 0; 
        return false;
    }

    return true;
}

#ifdef _WIN32
int CTcpClient::Send(const char* buf, const int buflen)
{
    return send(m_sockfd, buf, buflen, 0);
}

int CTcpClient::Recv(char* buf, const int buflen)
{
    return recv(m_sockfd, buf, buflen, 0);
}
#else
int CTcpClient::Send(const void* buf, const int buflen)
{
    return send(m_sockfd, buf, buflen, 0);
}

int CTcpClient::Recv(void* buf, const int buflen)
{
    return recv(m_sockfd, buf, buflen, 0);
}
#endif