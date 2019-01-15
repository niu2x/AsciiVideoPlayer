#include <stdio.h>
#include <string>

#include "core/type.h"

#include "gen/version.h"
#include "gen/config.h"
#include "third_party/cmdline.h"
#include "core/log.h"
#include "core/FSUtils.h"

#include <string.h>

#include <stdlib.h>
#include <stdio.h>

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
				if(scaleX < 0){
					scaleX = scale;
				}
				if(scaleY < 0){
					scaleY = scale;
				}
				return ascii_png(cPathname, scaleX, scaleY);
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