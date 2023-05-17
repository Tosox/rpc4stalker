#include "utils.hpp"

#include <iostream>

void utils::ThrowError(const std::string& message)
{
	std::cout << _F_RED("[!] ") << message << std::endl;
}

void utils::Log(const std::string& message)
{
	std::cout << _F_BLUE("[*] ") << message << std::endl;
}

std::string utils::FindStrStrMap(const std::map<std::string, std::string>& map, const std::string& val, const std::string& fallback)
{
	const std::map<std::string, std::string>::const_iterator iter = map.find(val);
	return iter != map.end() ? map.find(val)->second : fallback;
}
