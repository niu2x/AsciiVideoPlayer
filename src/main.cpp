#include <stdio.h>
#include <string>

#include "core/type.h"

#include "gen/version.h"
#include "gen/config.h"
#include "third_party/cmdline.h"
#include "core/log.h"
#include "core/FSUtils.h"

#include <string.h>

#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern "C" {
	#include "third_party/cute_png.h"
}

#include "module/ascii_image.h"


bool try_play_video(const std::string &pathname, float scale, float scaleX, float scaleY)
{

	bool paramValid = false;

	if(pathname.length() > 0)
	{
		paramValid = true;
	}

	if(paramValid)
	{

		const char *cPathname = pathname.c_str();

		if(!FSUtils::is_exists(cPathname))
		{
			log_error("%s doesn't exist!", cPathname);
		}
		else
		{
			const char * file_ext = FSUtils::get_file_ext(cPathname);
			if(strcmp(file_ext, "png") == 0){
				cp_image_t png = cp_load_png(cPathname);
				// printf("png info width: %d heighe: %d\n", png.w, png.h);
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

				if(scaleX < 0){
					scaleX = scale;
				}

				if(scaleY < 0){
					scaleY = scale;
				}


				convert_image_to_ascii(image, png.w, png.h, scaleX, scaleY, nullptr, 0, &buffSize);
				char *buffer = (char *)malloc(buffSize);
				convert_image_to_ascii(image, png.w, png.h, scaleX, scaleY, buffer, buffSize, 0);

				// printf("%s", buffer);

				initscr();
				move(0, 0);
				waddstr(stdscr, buffer);
				refresh();
				getch();
				endwin();


				free(buffer);
				free(image);
				cp_free_png(&png);


			}
			else{
				log_error("%s is not supported!.\n", file_ext);
			}

		}
	}

	return paramValid;
}

int parse_cmdline(int argc, char *argv[])
{
	cmdline::parser parserA;

	parserA.add<std::string>("file", 'f', "video file to play.", false, "");
	parserA.add<float>("scale", 's', "video file to scale..", false, 1.0f);
	parserA.add<float>("scaleX", '\0', "video file to scale..", false, -1.0f);
	parserA.add<float>("scaleY", '\0', "video file to scale..", false, -1.0f);
	parserA.add<int>("log", '\0', "log level", false, DEFAULT_LOG_LEVEL);
	parserA.parse_check(argc, argv);

 	int logLevel = parserA.get<int>("log");
 	set_log_level(logLevel);

 	if(try_play_video(
 		parserA.get<std::string>("file")
 		, parserA.get<float>("scale")
 		, parserA.get<float>("scaleX")
 		, parserA.get<float>("scaleY")
 	)){
 		return 0;
 	}
 	return 0;
}


int main(int argc, char *argv[], char ** env)
{
	// printf("%s Version: %d.%d\n", BIN_NAME, MAJOR_VERSION, MINOR_VERSION);
	int ret = parse_cmdline(argc, argv);
	return ret;
}