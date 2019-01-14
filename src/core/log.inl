#include <stdio.h>
#include <stdarg.h>

static int logLevel = 0;

inline void set_log_level(int level){
	logLevel = level;
}

#define _log(level, fmt) 				\
do{										\
	if(logLevel >= (level)){ 			\
		va_list argptr;					\
		va_start(argptr, fmt);			\
		vfprintf(stderr, fmt, argptr);	\
		fprintf(stderr, "\n");			\
		va_end(argptr);					\
	}									\
}while(0);

enum {
	ERROR = 0,
	DEBUG = 1,
	INFO = 2
};

inline void log_error(const char *fmt, ...){
	_log(ERROR, fmt);	
}

inline void log_debug(const char *fmt, ...){
	_log(DEBUG, fmt);	
}

inline void log_info(const char *fmt, ...){
	_log(INFO, fmt);	
}

#undef _log