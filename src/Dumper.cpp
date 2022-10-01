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
		utils::ThrowError("Could not find value at '" + GetLocationString(location) + "'.");
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
			stream << utils::_GREEN("[.] ") 
				<< pair.first.c_str()
				<< " : "
				<< pair.second.c_str()
				<< "\n";
		}
	}

	printf_s("%s", stream.str().c_str());
}
