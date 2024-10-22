#pragma once

#include "CodePageConverter.hpp"
#include "abstract/FileReader.hpp"
#include "../settings/structs.hpp"

class DataReader : public FileReader {
public:
	DataReader(std::filesystem::path path);

	bool readData(RPCContents* rpcContents);

private:
	CodePageConverter converter{ "CP1251", "UTF-8" };
};
