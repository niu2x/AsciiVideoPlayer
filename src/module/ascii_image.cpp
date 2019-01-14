#include "ascii_image.h"
#include "core/log.h"
#include <math.h>

static const char *charMap = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

static uint32_t lcm(uint32_t m, uint32_t n);

inline static uint8_t get_color(
	uint8_t * image, 
	uint32_t width, uint32_t height, 
	uint32_t aWidth, uint32_t aHeight, 
	uint32_t lcmWidth, uint32_t lcmHeight,
	uint32_t ax, uint32_t ay);

inline static uint8_t get_char_code(uint8_t color);


bool convert_image_to_ascii(
	uint8_t *image, 
	uint32_t width, 
	uint32_t height, 
	float scaleX,
	float scaleY,
	char *buffer,
	uint32_t bufferLen,
	uint32_t *outLen)
{

	//ascii image's width and height
	uint32_t aWidth = width * scaleX;
	uint32_t aHeight = height * scaleY;



	// extra 1 byte for \n every line. and \0 in end. 
	uint32_t desiredBufferLen = (1 + aWidth) * aHeight + 1; 


	if(outLen != nullptr){
		*outLen = desiredBufferLen;
	}

	if(bufferLen < desiredBufferLen){
		return false;
	}


	uint32_t lcmWidth = lcm(width, aWidth);
	uint32_t lcmHeight = lcm(height, aHeight);

	for(uint32_t x = 0; x < aWidth; x ++){
		for(uint32_t y = 0; y < aHeight; y ++){
			uint8_t color = get_color(image, width, height, aWidth, aHeight, lcmWidth, lcmHeight, x, y);
			uint8_t charCode = get_char_code(color);
			buffer[y * (aWidth + 1) + x] = charCode;
		}
	}



	for(uint32_t i = aWidth + 1; i <= desiredBufferLen; i += aWidth + 1)
		buffer[i-1] = '\n';
	buffer[desiredBufferLen - 1] = '\0';

	return true;
}

static uint32_t lcm(uint32_t m, uint32_t n)
{
	uint32_t a, b, c;
	a = m;
	b = n;
	while(a != b){
		if(a > b)
			a = a-b;
		else
			b = b-a;
	}
	return m * n / a;
}

inline static uint8_t get_color(
	uint8_t * image, 
	uint32_t width, uint32_t height, 
	uint32_t aWidth, uint32_t aHeight, 
	uint32_t lcmWidth, uint32_t lcmHeight,
	uint32_t ax, uint32_t ay)
{
	uint32_t colorSum = 0;
	uint32_t scaleAW = lcmWidth / aWidth;
	uint32_t scaleAH = lcmHeight / aHeight;

	uint32_t scaleW = lcmWidth / width;
	uint32_t scaleH = lcmHeight / height;

	for(uint32_t lcmX = ax * scaleAW; lcmX < (ax+1) * scaleAW; lcmX ++){
		for(uint32_t lcmY = ay * scaleAH; lcmY < (ay+1) * scaleAH; lcmY ++){
			uint32_t x = lcmX / scaleW;
			uint32_t y = lcmY / scaleH;
			colorSum += image[ y * width + x];
		}
	}
	uint8_t color = colorSum / (scaleAW * scaleAH);
	return color;
}

inline static uint8_t get_char_code(uint8_t color)
{
	static int32_t charMapLen = strlen(charMap);

	static float scale = 256.0f / charMapLen;

	int32_t index = fmax(0, fmin(float(color) / scale, charMapLen - 1));
	return charMap[index];
}