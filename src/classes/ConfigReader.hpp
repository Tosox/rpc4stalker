#pragma once

#include "abstract/FileReader.hpp"

class ConfigReader : public FileReader {
public:
	ConfigReader(std::filesystem::path path);

	override readFile()
};
