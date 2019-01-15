#ifndef ASCII_IMAGE_H
#define ASCII_IMAGE_H

#include "core/type.h"

bool convert_image_to_ascii(
	const uint8_t *image, 
	uint32_t width, 
	uint32_t height, 
	float scaleX,
	float scaleY,
	char *buffer,
	uint32_t bufferLen,
	uint32_t *outLen);

bool ascii_png(const char *, float sx, float sy);
bool ascii_raw_image(const uint8_t *, uint32_t w, uint32_t h, float sx, float sy);

void ascii_begin();

void ascii_end();

#endif