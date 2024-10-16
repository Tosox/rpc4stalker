#include "DataReader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "../utils/utils.hpp"
#include "../settings/globals.hpp"

std::string DataReader::getLocationString(std::vector<std::string>& location) {
	std::stringstream stream{};

	for (std::string& loc : location) {
		stream << "/" << loc;
	}

	return stream.str();
}

void DataReader::setDumpPath(const std::string& path) {
	dumpPath = path;
}

bool DataReader::isDumpReady() {
	return std::filesystem::exists(dumpPath);
}

bool DataReader::dumpValues() {
	std::ifstream inputFile{ dumpPath };
	if (!inputFile.good()) {
		utils::logging::Info("Searching for dump file 'rpc4stalker.json'...");
		return false;
	}

	std::stringstream fileStream{};
	fileStream << inputFile.rdbuf();
	std::string fileContents = fileStream.str();
	std::string convertedFileContents = converter.convert(fileContents);

	try {
		dump = nlohmann::json::parse(convertedFileContents);
		return true;
	} catch (nlohmann::detail::parse_error& e) {
		utils::logging::Warning("Found 'rpc4stalker.json', but something seems to be wrong with the file format. Retrying...");
		return false;
	}
}

std::string DataReader::loadValue(std::vector<std::string> location) {
	try {
		nlohmann::json obj{};
		obj.update(dump);

		for (std::string& path : location) {
			obj = obj[path];
		}

		return obj.get<std::string>();
	} catch (nlohmann::detail::type_error& e) {
		utils::logging::Warning("Value at '" + getLocationString(location) + "' is invalid.");
		return "";
	}
}

void DataReader::printDump(std::vector<std::pair<std::string, std::string>> pairs) {
	std::stringstream stream{};

	for (auto& pair : pairs) {
		pair.first.resize(20, ' ');

		// TODO: Fix this hardcoded garbage and blame cpp
		// Color green
		stream << "\033[32m" << "[.] " << "\033[00m"
			<< pair.first
			<< " : "
			<< pair.second
			<< "\n";
	}

	std::cout << stream.str();
}
