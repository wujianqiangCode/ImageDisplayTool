#pragma once
# ifndef LOG_H
# define LOG_H

#include "ImageDisplayTool.h"

class Log {
     
    public:
        Log();
        Log(LogDisplayWindows target, LogLevel level);
   
    private:
        LogDisplayWindows m_target;
        LogLevel m_level;
};

# endif
