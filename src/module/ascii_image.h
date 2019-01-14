#ifndef ASCII_IMAGE_H
#define ASCII_IMAGE_H

#include "core/type.h"

void convert_image_to_ascii(
	uint8_t *image, 
	uint32_t width, 
	uint32_t height, 
	float scale,
	uint8_t *buffer,
	uint32_t bufferLen
	uint32_t *outLen);

#endif