#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <json.hpp>

#include "../../settings/structs.hpp"

class FileReader {
public:
	FileReader(std::filesystem::path path);

	bool isFileReady() const;
	std::string getPathString(std::vector<std::string>& path) const;
	bool readFile(FileTemplate* f);

	template <typename T>
	T loadValue(nlohmann::json& json, std::vector<std::string> location);

protected:
	std::filesystem::path path{};
	std::string filename{};
	nlohmann::json data{};
};
