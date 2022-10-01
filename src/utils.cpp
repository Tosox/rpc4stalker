#include "utils.hpp"

void utils::ThrowError(const std::string& message)
{
	printf_s("%s %s\n", _RED("[!]").c_str(), message.c_str());
}

void utils::ThrowErrorAndExit(const std::string& message)
{
	ThrowError(message);
	std::cin.get();
	exit(EXIT_FAILURE);
}

std::string utils::FindStrStrMap(const std::map<std::string, std::string>& map, const std::string& val, const std::string& callback)
{
	std::map<std::string, std::string>::const_iterator iter = map.find(val);
	return iter != map.end() ? map.find(val)->second : callback;
}
