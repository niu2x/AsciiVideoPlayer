#ifndef LOG_H
#define LOG_H


inline void set_log_level(int level);

inline void log_info(const char *fmt, ...);
inline void log_debug(const char *fmt, ...);
inline void log_error(const char *fmt, ...);

#include "log.inl"

#endif