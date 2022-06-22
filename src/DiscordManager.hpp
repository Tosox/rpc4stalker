#pragma once

#include <Windows.h>
#include <chrono>

#include <discord.h>

class DiscordManager
{
public:
	DiscordManager();
	~DiscordManager();

	void Create(discord::ClientId);
	bool IsReady();

	void AddTimestamp();
	void SetType(discord::ActivityType type);
	void SetDetails(const char* detail);
	void SetState(const char* state);
	void SetLargeImage(const char* image, const char* text = nullptr);
	void SetSmallImage(const char* image, const char* text = nullptr);
	void Update();

private:
	discord::Core* m_Core{};
	discord::Activity m_Activity{};
	discord::Result m_Result{};
};
