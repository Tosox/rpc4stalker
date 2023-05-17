#pragma once

#pragma comment(lib, "discord_game_sdk.dll.lib")

#include <Windows.h>
#include <chrono>

#include <discord.h>

class DiscordManager
{
public:
	DiscordManager();
	~DiscordManager();

	void create(const discord::ClientId);
	bool isReady();

	void addTimestamp();
	void setType(const discord::ActivityType type);
	void setDetails(const char* detail);
	void setState(const char* state);
	void setLargeImage(const char* image, const char* text = nullptr);
	void setSmallImage(const char* image, const char* text = nullptr);
	void update();

	void shutdown();

private:
	discord::Core* m_Core{};
	discord::Activity m_Activity{};
	discord::Result m_Result{};
};
