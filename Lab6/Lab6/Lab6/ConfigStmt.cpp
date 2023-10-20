#include "ConfigStmt.h"

Config::Config()
{
	string dec = "";
	string hex = "";
	string bin = "";
}
void Config::loadConfig()
{
	if (config == "0")
	{
		dec = "";
		hex = "";
		bin = "";
	}
	else if (config == "1")
	{
		dec = "Active";
		hex = "Not Active";
		bin = "Not Active";
	}
	else if (config == "2")
	{
		dec = "Not Active";
		hex = "Active";
		bin = "Not Active";
	}
	else if (config == "3")
	{
		dec = "Not Active";
		hex = "Not Active";
		bin = "Active";
	}
}