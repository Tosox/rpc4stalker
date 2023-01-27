#include "utils.hpp"

#include <iostream>

void utils::ThrowError(const std::string& message)
{
	std::cout << _F_RED("[!] ") << message << std::endl;
}

void utils::ThrowErrorAndExit(const std::string& message)
{
	ThrowError(message);
	std::cin.get();
	std::exit(EXIT_FAILURE);
}

std::string utils::FindStrStrMap(const std::map<std::string, std::string>& map, const std::string& val, const std::string& fallback)
{
	const std::map<std::string, std::string>::const_iterator iter = map.find(val);
	return iter != map.end() ? map.find(val)->second : fallback;
}
