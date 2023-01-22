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
	// 运行时加载DLL库
	HMODULE module = LoadLibrary(L"ImageDisplayTool.dll");
	if (module == NULL)
	{
		printf("加载ImageDisplayTool.dll动态库失败\n");
		return -1;
	}
	
	typedef bool(*SetLogDisplayLevelAndTcpServerPortFunc)(LogLevel, int); // 定义函数指针类型
	SetLogDisplayLevelAndTcpServerPortFunc SetLogDisplayLevelAndTcpServerPort;
	// 导出函数地址
	SetLogDisplayLevelAndTcpServerPort = (SetLogDisplayLevelAndTcpServerPortFunc)GetProcAddress(module, "SetLogDisplayLevelAndTcpServerPort");

	typedef bool(*SendLogFunc)(char*, LogLevel); // 定义函数指针类型
	SendLogFunc SendLog;
	// 导出函数地址
	SendLog = (SendLogFunc)GetProcAddress(module, "SendLogFunc");

	typedef bool(*SendImageFunc)(unsigned char* , unsigned int , unsigned int , enum ImagePixelFormat ); // 定义函数指针类型
	SendImageFunc SendImage;
	// 导出函数地址
	SendImage = (SendImageFunc)GetProcAddress(module, "SendImage");

#endif
	SetLogDisplayLevelAndTcpServerPort(LOG_INFO, 5051);

	char ss[24];
	memset(ss, 0, sizeof(ss));
	sprintf_s(ss, "aaa");
	SendLog(ss, LOG_INFO);

	return 0;
}