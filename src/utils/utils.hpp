#pragma once

#include "colorstream.hpp"
#include <map>
#include <string>

namespace utils
{
	void ThrowError(const std::string& message);
	void ThrowErrorAndExit(const std::string& message);
	std::string FindStrStrMap(const std::map<std::string, std::string>& map, const std::string& val, const std::string& fallback);
}
