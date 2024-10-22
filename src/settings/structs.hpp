#pragma once

#include <string>
#include <discord.h>

struct FileTemplate {};

struct RPCData {
	discord::ClientId applicationId;
	std::string encoding;
};

struct RPCValues {
	discord::ActivityType type;
	std::string details;
	std::string state;
	std::string largeImageUrl;
	std::string largeImageText;
	std::string smallImageUrl;
	std::string smallImageText;
};

struct RPCContents : FileTemplate {
	RPCData data;
	RPCValues values;
};
