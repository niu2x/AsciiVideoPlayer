#ifndef FSUtils_H
#define FSUtils_H

#include <vector>

namespace FSUtils{

	bool is_exists(const char * const pathname);
	const char * get_file_ext(const char * const pathname);
};

#endif