#include "log.h"

Log::Log() {
    m_target = LOG_TERMINAL;
    m_level = LOG_DEBUG;
 }

Log::Log(LogDisplayWindows target, LogLevel level) {
    m_target = target;
    m_level = level;
}
