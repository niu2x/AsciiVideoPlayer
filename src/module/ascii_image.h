#ifndef ASCII_IMAGE_H
#define ASCII_IMAGE_H

#include "core/type.h"

bool convert_image_to_ascii(
	uint8_t *image, 
	uint32_t width, 
	uint32_t height, 
	float scaleX,
	float scaleY,
	char *buffer,
	uint32_t bufferLen,
	uint32_t *outLen);

#endif