#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <json.hpp>

#include "CodePageConverter.hpp"

typedef std::pair<std::string, std::string> sspair;

class Dumper
{
public:
	inline std::string getAbsoluteDumpPath() { return !dumpPath.empty() ? dumpPath : ""; };
	std::string getLocationString(std::vector<std::string>& location);

	void setDumpPath(const std::string& path);
	bool isDumpReady();

	void dumpValues();
	void loadValue(std::string& value, std::vector<std::string> location);

	void printDump(std::vector<sspair> pairs);

	void shutdown();

private:
	std::string dumpPath{};
	nlohmann::json dump{};
	CodePageConverter converter{ "CP1251", "UTF-8" };
};
