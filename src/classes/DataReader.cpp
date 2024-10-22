#include "DataReader.hpp"
#include "../utils/utils.hpp"

#include <fstream>

DataReader::DataReader(std::filesystem::path path)
	: FileReader(path) {
}

bool DataReader::readData(RPCContents* rpcContents) {
	std::ifstream inputFile{ this->path };
	if (!inputFile) {
		utils::logging::Info(std::format("Searching for data file '{}'...", this->filename));
		return false;
	}

	std::string fileContents((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
	std::string convertedFileContents = converter.convert(fileContents);

	try {
		this->data = nlohmann::json::parse(convertedFileContents);
	} catch (nlohmann::detail::parse_error& e) {
		utils::logging::Warning(std::format("Failed to parse '{}': \n" + std::string(e.what()), this->filename));
		return false;
	}

	rpcContents->data.applicationId = loadValue<discord::ClientId>(this->data, { "data", "application_id" });
	rpcContents->data.encoding = loadValue<std::string>(this->data, { "data", "encoding" });

	rpcContents->values.type = loadValue<discord::ActivityType>(this->data, { "values", "type" });
	rpcContents->values.details = loadValue<std::string>(this->data, { "values", "details" });
	rpcContents->values.state = loadValue<std::string>(this->data, { "values", "state" });
	rpcContents->values.largeImageUrl = loadValue<std::string>(this->data, { "values", "large_img",  "url"});
	rpcContents->values.largeImageText = loadValue<std::string>(this->data, { "values", "large_img", "text" });
	rpcContents->values.smallImageUrl = loadValue<std::string>(this->data, { "values", "small_img", "url" });
	rpcContents->values.smallImageText = loadValue<std::string>(this->data, { "values", "small_img", "text" });

	return true;
}
