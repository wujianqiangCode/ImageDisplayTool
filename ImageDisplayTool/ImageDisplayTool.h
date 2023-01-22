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
	YUYV,
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
	bool _stdcall SetLogDisplayLevelAndTcpServerPort(enum LogLevel level = LOG_DEBUG, int tcpServerPort = 5051);
	bool _stdcall SendLog(char* strbuffer, enum LogLevel level);
	bool _stdcall SendImage(unsigned char* pSrc, unsigned int pixel_width, unsigned int pixel_height, enum ImagePixelFormat type);
#ifdef _CPLUSPLUS
}
#endif

