#pragma once

#include <map>
#include <string>

#include "colorstream.hpp"

namespace utils
{
	void ThrowError(const std::string& message);
	void Log(const std::string& message);
	std::string FindStrStrMap(const std::map<std::string, std::string>& map, const std::string& val, const std::string& fallback);
}
