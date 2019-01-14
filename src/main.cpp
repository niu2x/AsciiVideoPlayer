#include <stdio.h>
#include <string>

#include "gen/version.h"
#include "gen/config.h"
#include "third_party/cmdline.h"
#include "core/log.h"
#include "core/FSUtils.h"




bool tryNew(const std::string &pathname)
{

	bool paramValid = false;

	if(pathname.length() > 0)
	{
		paramValid = true;
	}

	if(paramValid)
	{

		const char *cPathname = pathname.c_str();

		if(FSUtils::is_exists(cPathname))
		{
			log_error("%s already exist!", cPathname);
		}
		else
		{
			if(false)
			{
				printf("a new ped is created in %s\n", cPathname);
			}
			else
			{
				log_error("failed to create a new ped.");
			}
		}
	}

	return paramValid;
}

int parse_cmdline(int argc, char *argv[])
{
	cmdline::parser parserA;

	parserA.add<std::string>("config", 'c', "pathname of the virtual machine config file.", false, "");
	parserA.add<std::string>("new", 'n', "a directory for creating a new virtual machine.", false, "");
	parserA.add<int>("log", '\0', "log level", false, DEFAULT_LOG_LEVEL);
	parserA.parse_check(argc, argv);

 	int logLevel = parserA.get<int>("log");
 	set_log_level(logLevel);

 	if(tryNew(parserA.get<std::string>("new")))
 	{
 		return 0;
 	}

 	return 0;
}


int main(int argc, char *argv[], char ** env)
{

	printf("PED Version: %d.%d\n", MAJOR_VERSION, MINOR_VERSION);
	int ret = parse_cmdline(argc, argv);
	return ret;
}