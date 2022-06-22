#include "DiscordManager.hpp"

#pragma comment(lib, "discord_game_sdk.dll.lib")

DiscordManager::DiscordManager()
{
    m_Result = discord::Result::NotRunning;
}

DiscordManager::~DiscordManager()
{
    delete m_Core;
}

void DiscordManager::Create(discord::ClientId clientid)
{
    m_Result = discord::Core::Create(clientid, DiscordCreateFlags_NoRequireDiscord, &m_Core);
}

bool DiscordManager::IsReady()
{
    return m_Result == discord::Result::Ok;
}

void DiscordManager::AddTimestamp()
{
    m_Activity.GetTimestamps().SetStart(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

void DiscordManager::SetType(discord::ActivityType type)
{
    m_Activity.SetType(type);
}

void DiscordManager::SetDetails(const char* detail)
{
    m_Activity.SetDetails(detail);
}

void DiscordManager::SetState(const char* state)
{
    m_Activity.SetState(state);
}

void DiscordManager::SetLargeImage(const char* image, const char* text)
{
    m_Activity.GetAssets().SetLargeImage(image);
    m_Activity.GetAssets().SetLargeText(text);
}

void DiscordManager::SetSmallImage(const char* image, const char* text)
{
    m_Activity.GetAssets().SetSmallImage(image);
    m_Activity.GetAssets().SetSmallText(text);
}

void DiscordManager::Update()
{
    m_Core->ActivityManager().UpdateActivity(m_Activity, [](discord::Result result) { });
    m_Core->RunCallbacks();
}
