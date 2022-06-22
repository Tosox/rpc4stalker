#include "Dumper.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdarg.h>

#include "globals.hpp"

void Dumper::SetDumpPath(std::filesystem::path path)
{
	std::ifstream input_file{ path };
	if (!input_file.good())
		throw std::runtime_error("Invalid dump file");

	dumpPath = path;
	try { input_file >> dump; } 
	catch (std::runtime_error&) { throw std::runtime_error("Invalid json format"); }
}

bool Dumper::IsDumpReady()
{
	return std::filesystem::exists(dumpPath);
}

void Dumper::LoadValue(std::string& value, std::vector<std::string> location)
{
	nlohmann::json obj{};
	obj.update(dump);

	for (auto& path : location)
		obj = obj[path];

	value = obj.get<std::string>();
}

void Dumper::PrintDump(std::vector<sspair> pairs)
{
	std::stringstream stream{};

	for (auto& pair : pairs)
	{
		pair.first.resize(20, ' ');
		if (!pair.second.empty())
			stream << pair.first.c_str()
			<< " : "
			<< pair.second.c_str()
			<< "\n";
	}

	printf_s("%s", stream.str().c_str());
}
