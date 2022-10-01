#include "Dumper.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdarg.h>

#include "globals.hpp"
#include "utils.hpp"

std::string Dumper::GetLocationString(std::vector<std::string>& location)
{
	std::stringstream stream{};

	for (std::string& loc : location)
		stream << "/" << loc;

	return stream.str();
}

void Dumper::SetDumpPath(const std::string& path)
{
	std::ifstream input_file{ path };
	if (!input_file.good())
		utils::ThrowErrorAndExit("Cannot find dump file 'rpc4stalker.json'. Make sure this file exists before running this program.");

	dumpPath = path;
	try { dump = nlohmann::json::parse(input_file); }
	catch (nlohmann::detail::parse_error&) { utils::ThrowErrorAndExit("Found 'rpc4stalker.json', but something seems to be wrong with the file format."); }
}

bool Dumper::IsDumpReady()
{
	return std::filesystem::exists(dumpPath.c_str());
}

void Dumper::LoadValue(std::string& value, std::vector<std::string> location)
{
	try
	{
		nlohmann::json obj{};
		obj.update(dump);

		for (std::string& path : location)
			obj = obj[path];

		value = obj.get<std::string>();
	}
	catch (nlohmann::detail::type_error&)
	{
		utils::ThrowError("Value at '" + GetLocationString(location) + "' is invalid.");
		value = "";
	}
}

void Dumper::PrintDump(std::vector<sspair> pairs)
{
	std::stringstream stream{};

	for (sspair& pair : pairs)
	{
		pair.first.resize(20, ' ');
		if (!pair.second.empty())
		{
			// TODO: Fix this hardcoded garbage and blame cpp
			// Color green
			stream << "\033[32m" << "[.] " << "\033[00m"
				<< pair.first.c_str()
				<< " : "
				<< pair.second.c_str()
				<< "\n";
		}
	}

	std::cout << stream.str().c_str() << std::endl;
}
