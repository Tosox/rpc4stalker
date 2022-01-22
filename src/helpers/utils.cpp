#include <Windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <json/json.hpp>
#include <map>
#include "utils.hpp"

#define DUMPFILENAME "rpc4stalker.json"

std::string DUMP_FILE_PATH = std::filesystem::temp_directory_path().string() + DUMPFILENAME;

std::string utils::localization;
std::string utils::level;
std::string utils::faction_raw;
std::string utils::faction;
std::string utils::task;

//---------------------------------------------------------------------------------------

template <typename T>
static void read_value(const nlohmann::json& src, T& dest)
{
	if (src.is_null())
		return;
	dest = src.get<T>();
}

//---------------------------------------------------------------------------------------

void utils::LoadValues()
{
	std::ifstream input_file{ DUMP_FILE_PATH };
	if (!input_file.good())
		throw std::runtime_error("Invalid dump file");

	nlohmann::json json;
	input_file >> json;

	read_value(json["values"]["localization"], utils::localization);
	read_value(json["values"]["level"], utils::level);
	read_value(json["values"]["faction_raw"], utils::faction_raw);
	read_value(json["values"]["faction"], utils::faction);
	read_value(json["values"]["task"], utils::task);
}

//---------------------------------------------------------------------------------------

std::string utils::GetDumpFilePath()
{
	return (!DUMP_FILE_PATH.empty() ? DUMP_FILE_PATH : "");
}

//---------------------------------------------------------------------------------------

bool utils::IsDumpReady()
{
	return std::filesystem::exists(DUMP_FILE_PATH);
}

//---------------------------------------------------------------------------------------

void utils::PrintDump()
{
	std::cout << "Localization    : " << utils::localization.c_str() << std::endl;
	std::cout << "Level           : " << utils::level.c_str() << std::endl;
	std::cout << "Faction (raw)   : " << utils::faction_raw.c_str() << std::endl;
	std::cout << "Faction         : " << utils::faction.c_str() << std::endl;
	std::cout << "Task            : " << utils::task.c_str() << std::endl;
}

//---------------------------------------------------------------------------------------

std::string utils::map_find_str(const std::map<std::string, std::string>& map, std::string val, std::string callback)
{
	std::map<std::string, std::string>::const_iterator iter = map.find(val);
	return (iter != map.end() ? map.find(val)->second : callback);
}