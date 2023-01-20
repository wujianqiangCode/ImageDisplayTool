#include "ImageDisplayTool.h"

static LogLevel m_displayLevel = LOG_DEBUG;

void _stdcall SetLogDisplayLevel(LogLevel level)
{
	m_displayLevel = level;
}

bool _stdcall SendLog(unsigned char* string, enum LogLevel level, enum  LogDisplayWindows target)
{

	return false;
}
bool _stdcall SendImage(unsigned char* pSrc, int width, int hight, enum ImagePixelFormat type)
{
	
	return false;
}
