#include "../../../ImageDisplayTool/ImageDisplayTool.h"
#pragma comment(lib, "ImageDisplayTool.lib")
#ifdef _WIN32
#include <windows.h>
#else
#endif
#include <iostream>
using namespace std;
int main() {

#if 0
	// ����ʱ����DLL��
	HMODULE module = LoadLibrary(L"ImageDisplayTool.dll");
	if (module == NULL)
	{
		printf("����ImageDisplayTool.dll��̬��ʧ��\n");
		return -1;
	}
	
	typedef bool(*SetLogDisplayLevelAndTcpServerPortFunc)(LogLevel, int); // ���庯��ָ������
	SetLogDisplayLevelAndTcpServerPortFunc SetLogDisplayLevelAndTcpServerPort;
	// ����������ַ
	SetLogDisplayLevelAndTcpServerPort = (SetLogDisplayLevelAndTcpServerPortFunc)GetProcAddress(module, "SetLogDisplayLevelAndTcpServerPort");

	typedef bool(*SendLogFunc)(char*, LogLevel); // ���庯��ָ������
	SendLogFunc SendLog;
	// ����������ַ
	SendLog = (SendLogFunc)GetProcAddress(module, "SendLogFunc");

	typedef bool(*SendImageFunc)(unsigned char* , unsigned int , unsigned int , enum ImagePixelFormat ); // ���庯��ָ������
	SendImageFunc SendImage;
	// ����������ַ
	SendImage = (SendImageFunc)GetProcAddress(module, "SendImage");

#endif
	SetLogDisplayLevelAndTcpServerPort(LOG_INFO, 5051);

	char ss[24];
	memset(ss, 0, sizeof(ss));
	sprintf_s(ss, "aaa");
	SendLog(ss, LOG_INFO);

	return 0;
}