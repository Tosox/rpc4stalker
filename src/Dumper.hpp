#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "../lib/json/json.hpp"

typedef std::pair<std::string, std::string> sspair;

class Dumper
{
public:
	inline std::string GetAbsoluteDumpPath() { return !dumpPath.empty() ? dumpPath.string() : ""; };

	void SetDumpPath(std::filesystem::path path);
	bool IsDumpReady();

	void LoadValue(std::string& value, std::vector<std::string> location);

	void PrintDump(std::vector<sspair> pairs);

private:
	std::filesystem::path dumpPath;
	nlohmann::json dump;
};
