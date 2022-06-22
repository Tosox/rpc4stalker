#include "utils.hpp"

std::string utils::FindStrStrMap(const std::map<std::string, std::string>& map, std::string val, std::string callback)
{
	std::map<std::string, std::string>::const_iterator iter = map.find(val);
	return iter != map.end() ? map.find(val)->second : callback;
}
