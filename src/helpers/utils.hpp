#pragma once

#include <string>
#include <vector>

namespace utils
{
	extern std::string localization;
	extern std::string level;
	extern std::string faction_raw;
	extern std::string faction;
	extern std::string task;

	std::string GetDumpFilePath();
	bool IsDumpReady();
	void LoadValues();
	void PrintDump();

	std::string map_find_str(const std::map<std::string, std::string>& map, std::string val, std::string callback);
}