#include "core/FSUtils.h"
#include <unistd.h>

namespace FSUtils{
	bool is_exists(const char * const pathname){
		return access(pathname, F_OK) == 0;
	}
};