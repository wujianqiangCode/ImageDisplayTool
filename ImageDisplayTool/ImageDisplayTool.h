#pragma once
#include <stdbool.h>

enum ImagePixelFormat {
	BGRA,
	RGBA,
	ARGB,
	ABGR,
	I420,
	YV12,
	NV12,
	NV21,
};
enum LogDisplayWindows {
	LOG_SERVER,
	LOG_TERMINAL,
};
enum LogLevel {
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG,
};

#ifdef _CPLUSPLUS
extern "C"
{
#endif
	void _stdcall SetLogDisplayLevel(LogLevel level);
	bool _stdcall SendLog(unsigned char* string, enum LogLevel level, enum  LogDisplayWindows target);
	bool _stdcall SendImage(unsigned char* pSrc, int width, int hight, enum ImagePixelFormat type);
#ifdef _CPLUSPLUS
}
#endif

