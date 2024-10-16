#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <json.hpp>

#include "CodePageConverter.hpp"

class DataReader {
public:
	inline std::string getAbsoluteDumpPath() { return !dumpPath.empty() ? dumpPath : ""; };
	std::string getLocationString(std::vector<std::string>& location);

	void setDumpPath(const std::string& path);
	bool isDumpReady();

	bool dumpValues();
	std::string loadValue(std::vector<std::string> location);

	void printDump(std::vector<std::pair<std::string, std::string>> pairs);

private:
	std::string dumpPath{};
	nlohmann::json dump{};
	CodePageConverter converter{ "CP1251", "UTF-8" };
};
