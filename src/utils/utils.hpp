#pragma once

#include <map>
#include <string>

#include "colorstream.hpp"

namespace utils
{
	void pause();
	void throwError(const std::string& message);
	void throwErrorAndExit(const std::string& message);
	std::string findStrStrMap(const std::map<std::string, std::string>& map, const std::string& val, const std::string& fallback);
}
