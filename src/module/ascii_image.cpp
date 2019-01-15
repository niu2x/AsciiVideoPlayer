#include "ascii_image.h"
#include "core/log.h"
#include <math.h>

#ifdef LINUX
	#include <curses.h>
#endif //LINUX


#ifdef WIN32
	#include <windows.h>
#endif 

extern "C" {
	#include "third_party/cute_png.h"
}


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
	// uint32_t colorSum = 0;
	// uint32_t scaleAW = lcmWidth / aWidth;
	// uint32_t scaleAH = lcmHeight / aHeight;

	// uint32_t scaleW = lcmWidth / width;
	// uint32_t scaleH = lcmHeight / height;

	// for(uint32_t lcmX = ax * scaleAW; lcmX < (ax+1) * scaleAW; lcmX ++){
	// 	for(uint32_t lcmY = ay * scaleAH; lcmY < (ay+1) * scaleAH; lcmY ++){
	// 		uint32_t x = lcmX / scaleW;
	// 		uint32_t y = lcmY / scaleH;
	// 		colorSum += image[ y * width + x];
	// 	}
	// }
	// uint8_t color = colorSum / (scaleAW * scaleAH);


	float colorSum = 0;
	float areaSum = 0;

	float sw = float(width) / aWidth;
	float sh = float(height) / aHeight;

	float x1 = sw * ax;
	float y1 = sh * ay;

	float x2 = x1 + sw;
	float y2 = y1 + sh;

	for(int xx = x1; xx <= x2; xx ++){
		for(int yy = y1; yy <= y2; yy ++){

			float l = x1;
			float r = l + 1.0f;
			float t = y1;
			float b = t + 1.0f;

			if(l < x1) l = x1;
			if(t < y1) t = y1;
			if(r > x2) r = x2;
			if(b > y2) b = y2;

			float area = (r - l) * (b - t);
			areaSum += area;
			colorSum += area * image[ yy * width + xx];
		}
	}

	uint32_t color = colorSum / areaSum;

	return color;
}

inline static uint8_t get_char_code(uint8_t color)
{
	static int32_t charMapLen = strlen(charMap);

	static float scale = 256.0f / charMapLen;

	int32_t index = fmax(0, fmin(float(color) / scale, charMapLen - 1));
	return charMap[index];
}

bool ascii_png(const char *pathname, float scaleX, float scaleY)
{
	cp_image_t png = cp_load_png(pathname);
	int imageSize = png.w * png.h;
	uint8_t *image = (uint8_t *)malloc(imageSize);
	memset(image, 0, imageSize);
	for(int x = 0; x < png.w; x ++){
		for(int y = 0; y < png.h; y ++){
			cp_pixel_t pixel = png.pix[y * png.w + x];
			uint8_t color = pixel.r*0.299 + pixel.g*0.587 + pixel.b*0.114;
			image[y * png.w + x] = color;
		}
	}

	uint32_t buffSize;

	convert_image_to_ascii(image, png.w, png.h, scaleX, scaleY, nullptr, 0, &buffSize);
	char *buffer = (char *)malloc(buffSize);
	convert_image_to_ascii(image, png.w, png.h, scaleX, scaleY, buffer, buffSize, 0);

	#ifdef LINUX
		initscr();
		move(0, 0);
		waddstr(stdscr, buffer);
		refresh();
		getch();
		endwin();
	#else
		system("cls");
		printf("%s", buffer);
	#endif //LINUX

	free(buffer);
	free(image);
	cp_free_png(&png);

	return true;
}