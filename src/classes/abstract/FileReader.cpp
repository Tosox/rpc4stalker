#include "FileReader.hpp"

FileReader::FileReader(std::filesystem::path path)
	: path(path) {
	this->filename = path.filename().string();
}

bool FileReader::isFileReady() const {
	return std::filesystem::exists(this->path);
}

std::string FileReader::getPathString(std::vector<std::string>& path) const {
	std::string result;
	for (const auto& loc : path) {
		result += "/" + loc;
	}
	return result;
}

template <typename T>
T FileReader::loadValue(nlohmann::json& json, std::vector<std::string> location) {
	try {
		const nlohmann::json* obj = &json;
		for (const auto& path : location) {
			if (!obj->contains(path)) {
				throw nlohmann::json::out_of_range::create(404, "Path not found: " + getPathString(location), obj);
			}
			obj = &(*obj)[path];
		}
		return obj->get<T>();
	} catch (nlohmann::json::exception& e) {
		utils::logging::Warning("Error retrieving value: \n" + std::string(e.what()));
		return T{};
	}
}
