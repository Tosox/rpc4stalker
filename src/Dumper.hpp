#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "../lib/json/json.hpp"

typedef std::pair<std::string, std::string> sspair;

class Dumper
{
public:
	inline std::string GetAbsoluteDumpPath() { return !dumpPath.empty() ? dumpPath : ""; };

	std::string GetLocationString(std::vector<std::string>& location);

	void SetDumpPath(const std::string& path);
	bool IsDumpReady();

	void LoadValue(std::string& value, std::vector<std::string> location);

	void PrintDump(std::vector<sspair> pairs);

private:
	std::string dumpPath;
	nlohmann::json dump;
};
