#include <Windows.h>
#include <json/json.hpp>
#include "helpers/Discord.hpp"
#include "helpers/Console.hpp"
#include "helpers/utils.hpp"
#include "settings/factions.hpp"
#include "settings/logo.hpp"

char bfLevel[256]{};

int main(int argc, char** argv)
{
    // Init objects
    Console* console = new Console(false);
    DiscordRP* discordRP = new DiscordRP();

    console->doUTF8();

    {
        console->printl(logo::bytes);
        do
        {
            console->logl("Searching for discord...");
            discordRP->Create(890702387025702922);
            Sleep(50);
        } while (!discordRP->IsReady());
        discordRP->Init("stalker_icon_0", "S.T.A.L.K.E.R.", discord::ActivityType::Playing);

        console->log("Found dump-file path: ");
        console->printl(utils::GetDumpFilePath().c_str());

        do
        {
            console->logl("Searching for dumps...");
            Sleep(50);
        } while (!utils::IsDumpReady());
        Sleep(3000);
    }

    while (!GetAsyncKeyState(VK_END))
    {
        utils::LoadValues();

        console->clear();
        console->printl(logo::bytes);
        utils::PrintDump();
        
        discordRP->SetSmallImage(
            utils::map_find_str(STALKER_COMMUNITIES, utils::faction_raw, "stalker_patch_stalker").c_str(),
            utils::faction.c_str()
        );

        sprintf_s(bfLevel, (strcmp(utils::localization.c_str(), "rus") == 0 ? u8"Изучает: %s" : "Exploring: %s"), utils::level.c_str());

        discordRP->SetDetails(bfLevel);
        discordRP->SetState(utils::task.c_str());
        discordRP->Update();

        Sleep(5000);
    }
    
    delete discordRP;
    
    return EXIT_SUCCESS;
}
