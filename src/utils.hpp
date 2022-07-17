#pragma once

#include <map>
#include <string>

namespace utils
{
	std::string FindStrStrMap(const std::map<std::string, std::string>& map, const std::string& val, const std::string& callback);
}
