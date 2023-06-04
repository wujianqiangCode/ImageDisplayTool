#include "ServerSocket.h"
#include <string.h>
#ifdef __linux__
#include <errno.h>
#endif
#define _CRT_SECURE_NO_WARNINGS

CTcpServer::CTcpServer(QObject *parent)
	: QThread(parent)
    , m_nImageHeight(0)
    , m_nImageWidth(0)
    , m_llImagePTS(0)
    , m_pImageData(nullptr)
{
    // ���캯����ʼ��socket
    m_listenfd = m_clientfd = 0;

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
    }
#endif

    memset(m_strLogInfo,0,sizeof(m_strLogInfo)/sizeof(char));

    //clear
    std::queue<QString> empty;
	swap(empty, m_ServerSocketReceiveInfoQueue);
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


int CTcpServer::Create()
{
	start(); // �����߳�
	return 0;
}

void CTcpServer::Destroy()
{
	wait();
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

bool CTcpServer::ProcessReceiveInfo()
{
    char buffer[1024];
    memset(buffer, '\0', strlen(buffer) );
    int num = Recv(buffer,1024);//�жϳ���\r\nΪһ����

    if(num <= 0)
    {
        return false;
    }

    int nBeginPos = 0;
    for(int i = 1; i <= num;i++)
    {
        if((buffer[i-1] == '\r') && (buffer[i] == '\n'))
        {
            char chTemp[1024];
            memset(chTemp, '\0', strlen(chTemp) );
            memcpy(chTemp,buffer + nBeginPos,i-1-nBeginPos);

            m_qStrTemp += QString(QLatin1String(chTemp)) + "\n";
            
            m_ServerSocketReceiveInfoQueue.push(m_qStrTemp);
            m_qStrTemp.clear();
            nBeginPos = i+1;
        }
    }

    if(nBeginPos != num)
    {
        char chTemp[1024];
        memcpy(chTemp,0,1024);
        memcpy(chTemp,buffer + nBeginPos,num - nBeginPos);
        
        m_qStrTemp = QString(QLatin1String(chTemp));
    }

    return true;
}

// �̵߳�������
void CTcpServer::run()
{
    while(Accept() == false)
    {
       sleep(1);
    }
    
    while(1)
    {
        if(ProcessReceiveInfo() == false)
        {
            continue;
        }

        while(m_ServerSocketReceiveInfoQueue.size() != 0)
        {
            QString qStrInfo = m_ServerSocketReceiveInfoQueue.front();
            m_ServerSocketReceiveInfoQueue.pop();

            std::string strInfo = qStrInfo.toStdString();

            char* strSetLogDisplayLevel = "SetLogDisplayLevel:";
            if(strncmp(strInfo.c_str(),strSetLogDisplayLevel,strlen(strSetLogDisplayLevel)) == 0)
            {
                m_emSetLogDisplayLevel =(LogLevel)((strInfo.c_str())[strlen(strSetLogDisplayLevel)]- '0');
            }

            char* strLogLevel = "LogLevel:";
            if(strncmp(strInfo.c_str(),strLogLevel,strlen(strLogLevel)) == 0)
            {
                m_emLogLevel =(LogLevel)((strInfo.c_str())[strlen(strLogLevel)]- '0');
                if(m_emSetLogDisplayLevel < m_emLogLevel)
                {
                    continue;
                }
                else
                {
                    memcpy(m_strLogInfo, strInfo.c_str() + strlen(strLogLevel) + 1, strlen(strInfo.c_str()) - strlen(strLogLevel) -1);
                    continue;
                }
            }
        
        char* strSendImageDataBegin = "SendImageBegin!!!";
        if(strncmp(strInfo.c_str(),strSendImageDataBegin,strlen(strSendImageDataBegin)) == 0)
        {
            bool bFlag = true;
            
            m_nImageHeight = 0;
            m_nImageWidth = 0;

            if(m_pImageData)
            {
                delete[] m_pImageData;
                m_pImageData = nullptr;
            }
            while (bFlag)
            {
                if((m_nImageHeight == 0) ||(m_nImageWidth == 0) || (m_llImagePTS == 0))
                {
                    char* strSendImageHeight = "SendImagePixelHeight=";
                    char* strSendImageWidth = "SendImagePixelWidth=";
                    char* strSendImagePTS = "SendImagePTS=";

                    QString qStrImageInfo = m_ServerSocketReceiveInfoQueue.front();
                    m_ServerSocketReceiveInfoQueue.pop();

                    std::string strImageInfo = qStrImageInfo.toStdString();

                    if(strncmp(strImageInfo.c_str(),strSendImageHeight,strlen(strSendImageHeight)) == 0)
                    {
                        std::string ss = strImageInfo.substr(strlen(strSendImageHeight),strlen(strImageInfo.c_str()));
                        m_nImageHeight = atoi(ss.c_str());
                    }
                    else if(strncmp(strImageInfo.c_str(),strSendImageWidth,strlen(strSendImageWidth)) == 0)
                    {
                        std::string ss = strImageInfo.substr(strlen(strSendImageWidth),strlen(strImageInfo.c_str()));
                        m_nImageWidth = atoi(ss.c_str());
                    }
                    else if(strncmp(strImageInfo.c_str(),strSendImagePTS,strlen(strSendImagePTS)) == 0)
                    {
                        std::string ss = strImageInfo.substr(strlen(strSendImagePTS),strlen(strImageInfo.c_str()));
                        m_llImagePTS = atoi(ss.c_str());
                    }
                }
                else
                {
                    m_pImageData = new unsigned char[m_nImageWidth*m_nImageHeight*4+1]();
                    
                    while(ProcessReceiveInfo() == false)
                    {
                        continue;
                    }

                    QString qStrImageData = m_ServerSocketReceiveInfoQueue.front();
                    m_ServerSocketReceiveInfoQueue.pop();
                    std::string strImageInfo = qStrImageData.toStdString();

                    unsigned char * pTemp = (unsigned char *)strImageInfo.c_str();
                    memcpy(m_pImageData,pTemp,m_nImageWidth*m_nImageHeight*4);

                    //��װ
                    bFlag = false;
                }
                
            }
            
        }
        }
    }
}