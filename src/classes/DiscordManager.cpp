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

void DiscordManager::create(const discord::ClientId clientid)
{
    m_Result = discord::Core::Create(clientid, DiscordCreateFlags_NoRequireDiscord, &m_Core);
}

bool DiscordManager::isReady()
{
    return m_Result == discord::Result::Ok;
}

void DiscordManager::addTimestamp()
{
    const std::chrono::system_clock::duration timestamp = std::chrono::system_clock::now().time_since_epoch();
    m_Activity.GetTimestamps().SetStart(std::chrono::duration_cast<std::chrono::seconds>(timestamp).count());
}

void DiscordManager::setType(const discord::ActivityType type)
{
    m_Activity.SetType(type);
}

void DiscordManager::setDetails(const char* detail)
{
    m_Activity.SetDetails(detail);
}

void DiscordManager::setState(const char* state)
{
    m_Activity.SetState(state);
}

void DiscordManager::setLargeImage(const char* image, const char* text)
{
    m_Activity.GetAssets().SetLargeImage(image);
    m_Activity.GetAssets().SetLargeText(text);
}

void DiscordManager::setSmallImage(const char* image, const char* text)
{
    m_Activity.GetAssets().SetSmallImage(image);
    m_Activity.GetAssets().SetSmallText(text);
}

void DiscordManager::update()
{
    m_Core->ActivityManager().UpdateActivity(m_Activity, [](discord::Result result) { });
    m_Core->RunCallbacks();
}
