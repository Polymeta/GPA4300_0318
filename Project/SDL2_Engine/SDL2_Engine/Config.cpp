#pragma region system include
#include <sstream>
#pragma endregion

#pragma region project include
#include "Config.h"  
#include "Helper.h"
#pragma endregion

// set static default values
int GConfig::s_ScreenWidth = 1280;
int GConfig::s_ScreenHeight = 720;

// set values of config
void GConfig::SetValues()
{
	// string from file
	string s = LoadStringFromFile("Config/config.txt");

	// create stream from string
	istringstream iss(s);

	// through all lines
	for (string line; getline(iss, line);)
	{
		// key and value of variable
		string key;
		string value;

		// string stream of line
		istringstream issLine(line);

		// get key and value
		getline(issLine, key, ':');
		getline(issLine, value);

		// if key find set variable
		if (key == "SCREEN_WIDTH")
			s_ScreenWidth = atoi(value.c_str());
		else if(key == "SCREEN_HEIGHT")
			s_ScreenHeight = atoi(value.c_str());
	}
}