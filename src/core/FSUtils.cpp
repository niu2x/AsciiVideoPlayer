#include "FSUtils.h"
#include <string.h>


namespace FSUtils{
	const char * get_file_ext(const char * const pathname){
		const char * p = strrchr(pathname, '.');
		p ++;
		return p;
	}
};
