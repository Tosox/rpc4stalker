#pragma once

#include <map>
#include <string>
#include <iostream>

namespace utils
{
	inline std::string _RED(const std::string& str) { return std::string("\x1b[31m" + str + "\x1b[0m"); }
	inline std::string _CYAN(const std::string& str) { return std::string("\x1b[36m" + str + "\x1b[0m"); }
	inline std::string _GREEN(const std::string& str) { return std::string("\x1b[32m" + str + "\x1b[0m"); }

	void ThrowError(const std::string& message);
	void ThrowErrorAndExit(const std::string& message);
	std::string FindStrStrMap(const std::map<std::string, std::string>& map, const std::string& val, const std::string& callback);
}
