#pragma once

#include <discord_sdk/cpp/discord.h>

class DiscordRP
{
public:
	DiscordRP();
	~DiscordRP();

	void Create(discord::ClientId);
	bool IsReady();
	void Init(const char* image, const char* text, discord::ActivityType type);
	void SetType(discord::ActivityType type);
	void SetDetails(const char* detail);
	void SetState(const char* state);
	void SetLargeImage(const char* image, const char* text);
	void SetSmallImage(const char* image, const char* text);
	void Update();

private:
	discord::Core* core{};
	discord::Activity activity{};
	discord::Result result{};
};