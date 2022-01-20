#include <Windows.h>
#include <chrono>
#include "Discord.hpp"

#pragma comment(lib, "discord_game_sdk.dll.lib")

DiscordRP::DiscordRP()
{
    this->result = discord::Result::NotRunning;
}

DiscordRP::~DiscordRP()
{
    delete this->core;
}

void DiscordRP::Create(discord::ClientId clientid)
{
    this->result = discord::Core::Create(clientid, DiscordCreateFlags_NoRequireDiscord, &this->core);
}

bool DiscordRP::IsReady()
{
    return this->result == discord::Result::Ok;
}

void DiscordRP::Init(const char* image, const char* text, discord::ActivityType type)
{
    this->SetLargeImage(image, text);
    this->activity.SetType(type);
    this->activity.GetTimestamps().SetStart(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

void DiscordRP::SetType(discord::ActivityType type)
{
    this->activity.SetType(type);
}

void DiscordRP::SetDetails(const char* detail)
{
    this->activity.SetDetails(detail);
}

void DiscordRP::SetState(const char* state)
{
    this->activity.SetState(state);
}

void DiscordRP::SetLargeImage(const char* image, const char* text)
{
    this->activity.GetAssets().SetLargeImage(image);
    this->activity.GetAssets().SetLargeText(text);
}

void DiscordRP::SetSmallImage(const char* image, const char* text)
{
    this->activity.GetAssets().SetSmallImage(image);
    this->activity.GetAssets().SetSmallText(text);
}

void DiscordRP::Update()
{
    this->core->ActivityManager().UpdateActivity(this->activity, [](discord::Result result) { });
    this->core->RunCallbacks();
}