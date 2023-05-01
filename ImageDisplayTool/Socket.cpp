#include "Socket.h"
#include <string.h>
#ifdef __linux__
#include <errno.h>
#endif
#define _CRT_SECURE_NO_WARNINGS

CTcpServer::CTcpServer()
{
    // ���캯����ʼ��socket
    m_listenfd = m_clientfd = 0;

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
    }
#endif
}

CTcpServer::~CTcpServer()
{
#ifdef _WIN32

    WSACleanup();
#endif

    if (m_listenfd != 0) {
#ifdef _WIN32
        closesocket(m_listenfd);
#else
        close(m_listenfd);  // ���������ر�socket
#endif
    }
    if (m_clientfd != 0) {
#ifdef _WIN32
        closesocket(m_clientfd);
#else
        close(m_clientfd);  // ���������ر�socket
#endif
    }
}

// ��ʼ������˵�socket��portΪͨ�Ŷ˿�
bool CTcpServer::InitServer(int port)
{
    m_listenfd = socket(AF_INET, SOCK_STREAM, 0);  // ��������˵�socket

    // �ѷ��������ͨ�ŵĵ�ַ�Ͷ˿ڰ󶨵�socket��
    struct sockaddr_in servaddr;    // ����˵�ַ��Ϣ�����ݽṹ
    memset(&servaddr, 0, sizeof(servaddr));

    //AF_INET�����������������Ŀ����ͨ�ţ�ͬ���Ŀ������ڲ�ͬ����֮���ͨ�ţ������Ϊ���ڲ�ͬ����֮��������绥���������ݶ�����
    //��AF_UNIX��ֻ�����ڱ����ڽ���֮���ͨ�š�
    servaddr.sin_family = AF_INET;  // Э���壬��socket�����ֻ����AF_INET
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  // ������������ip��ַ
    servaddr.sin_port = htons(port);  // ��ͨ�Ŷ˿�
#ifdef __linux__
    if (errno = bind(m_listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0){
#else
    if (bind(m_listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0){
#endif
#ifdef _WIN32
        closesocket(m_listenfd);
        printf("bind failed %d \n", WSAGetLastError());
#else
        close(m_listenfd);
        printf("bind failed %d \n", strerror(errno));
#endif
        m_listenfd = 0;
        return false;
    }

    // ��socket����Ϊ����ģʽ
#ifdef __linux__
   if (errno = listen(m_listenfd, 5) != 0) {
#else
    if (listen(m_listenfd, 5) != 0) {
#endif
#ifdef _WIN32
        closesocket(m_listenfd);
        printf("listen failed %d \n", WSAGetLastError());
#else
        close(m_listenfd);
        printf("bind failed %d \n", strerror(errno));
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
// ��Զ˷��ͱ���
int  CTcpServer::Send(const char* buf, const int buflen) {
    return send(m_clientfd, buf, buflen, 0);
}

// ���նԶ˵ı���
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