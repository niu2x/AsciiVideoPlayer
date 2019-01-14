#include "core/FSUtils.h"
#include <io.h>
#include <process.h>

namespace FSUtils{
	bool is_exists(const char * const pathname){
		return access(pathname, 0) == 0;
	}
};