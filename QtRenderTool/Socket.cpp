
#include "Socket.h"

CTcpClient::CTcpClient()
{
    m_sockfd = 0;  // ���캯����ʼ��m_sockfd
}

CTcpClient::~CTcpClient()
{
    if (m_sockfd != 0) 
#ifdef _WIN32
        closesocket(m_sockfd);// ���������ر�m_sockfd
#else
        close(m_sockfd);
#endif
}

// ��������������ӣ�serverip-�����ip��portͨ�Ŷ˿�
bool CTcpClient::ConnectToServer(const char* serverip, const int port)
{
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0); // �����ͻ��˵�socket

    struct hostent* h; // ip��ַ��Ϣ�����ݽṹ
    if ((h = gethostbyname(serverip)) == 0)
    {
#ifdef _WIN32
        closesocket(m_sockfd);
#else
        close(m_sockfd);
#endif
        m_sockfd = 0;
        return false;
    }

    // �ѷ������ĵ�ַ�Ͷ˿�ת��Ϊ���ݽṹ
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);

    // �������������������
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