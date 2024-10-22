#include "DiscordManager.hpp"

void DiscordManager::create(const discord::ClientId clientid) {
    m_Result = discord::Core::Create(clientid, DiscordCreateFlags_NoRequireDiscord, &m_Core);
}

bool DiscordManager::isReady() const {
    return m_Result == discord::Result::Ok;
}

void DiscordManager::addTimestamp() {
    const auto timestamp = std::chrono::system_clock::now().time_since_epoch();
    m_Activity.GetTimestamps().SetStart(std::chrono::duration_cast<std::chrono::seconds>(timestamp).count());
}

void DiscordManager::setType(const discord::ActivityType type) {
    m_Activity.SetType(type);
}

void DiscordManager::setDetails(const std::string& detail) {
    if (!detail.empty()) {
        m_Activity.SetDetails(detail.c_str());
    }
}

void DiscordManager::setState(const std::string& state) {
    if (!state.empty()) {
        m_Activity.SetState(state.c_str());
    }
}

void DiscordManager::setLargeImage(const std::string& image, const std::string& text) {
    if (!image.empty()) {
        m_Activity.GetAssets().SetLargeImage(image.c_str());
    }
    if (!text.empty()) {
        m_Activity.GetAssets().SetLargeText(text.c_str());
    }
}

void DiscordManager::setSmallImage(const std::string& image, const std::string& text) {
    if (!image.empty()) {
        m_Activity.GetAssets().SetSmallImage(image.c_str());
    }
    if (!text.empty()) {
        m_Activity.GetAssets().SetSmallText(text.c_str());
    }
}

void DiscordManager::update(std::function<void(discord::Result)> callback) {
    m_Core->ActivityManager().UpdateActivity(m_Activity, callback);
    m_Result = m_Core->RunCallbacks();
}
