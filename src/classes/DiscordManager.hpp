#pragma once

#pragma comment(lib, "discord_game_sdk.dll.lib")

#include <Windows.h>
#include <chrono>
#include <discord.h>

class DiscordManager {
public:
	DiscordManager() : m_Result(discord::Result::NotRunning) {}

	void create(const discord::ClientId clientId);
	bool isReady() const;
	void addTimestamp();
	void setType(const discord::ActivityType type);
	void setDetails(const std::string& detail);
	void setState(const std::string& state);
	void setLargeImage(const std::string& image, const std::string& text);
	void setSmallImage(const std::string& image, const std::string& text);
	void update(std::function<void(discord::Result)> callback);

private:
	discord::Core* m_Core{};
	discord::Activity m_Activity{};
	discord::Result m_Result{};
};
