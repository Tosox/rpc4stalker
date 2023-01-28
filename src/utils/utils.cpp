#include "utils.hpp"

#include <iostream>

void utils::pause()
{
	std::cin.ignore();
	std::cin.get();
}

void utils::throwError(const std::string& message)
{
	std::cout << _F_RED("[!] ") << message << std::endl;
}

void utils::throwErrorAndExit(const std::string& message)
{
	throwError(message);
	pause();
	std::exit(EXIT_FAILURE);
}

std::string utils::findStrStrMap(const std::map<std::string, std::string>& map, const std::string& val, const std::string& fallback)
{
	const std::map<std::string, std::string>::const_iterator iter = map.find(val);
	return iter != map.end() ? map.find(val)->second : fallback;
}
