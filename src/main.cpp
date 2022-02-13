#include <Windows.h>
#include <json/json.hpp>
#include "helpers/Discord.hpp"
#include "helpers/Console.hpp"
#include "helpers/utils.hpp"
#include "settings/factions.hpp"
#include "settings/logo.hpp"
#include "settings/language.hpp"

#define STALKER_APPLICATION_ID 890702387025702922

int main(int argc, char** argv)
{
    char bfLevel[256]{};

    // Init objects
    Console* console = new Console(false);
    DiscordRP* discordRP = new DiscordRP();

    console->doUTF8();
    console->title("rpc4stalker");
    console->println(logo::bytes);

    //---------------------------------------------------------------------------------------

    {
        // Find discord
        do
        {
            console->logln("Searching for discord...");
            discordRP->Create(STALKER_APPLICATION_ID);
            Sleep(1000);
        } while (!discordRP->IsReady());
        discordRP->Init("stalker_icon_0", "S.T.A.L.K.E.R.", discord::ActivityType::Playing);

        // Print dump-file path
        console->log("Getting dump-file path: ");
        console->println(utils::GetDumpFilePath().c_str());

        // Find dumps
        do
        {
            console->logln("Searching for dumps...");
            Sleep(1000);
        } while (!utils::IsDumpReady());
        Sleep(3000);
    }

    //---------------------------------------------------------------------------------------

    while (!GetAsyncKeyState(VK_END))
    {
        utils::LoadValues();

        console->clear();
        console->println(logo::bytes);
        utils::PrintDump();
        
        discordRP->SetSmallImage(
            utils::map_find_str(STALKER_COMMUNITIES, utils::faction_raw, "stalker_patch_stalker").c_str(),
            utils::faction.c_str()
        );

        sprintf_s(
            bfLevel, 
            utils::map_find_str(LANG_EXPLORING, utils::localization, "Exploring: %s").c_str(),
            utils::level.c_str()
        );

        discordRP->SetDetails(bfLevel);
        discordRP->SetState(utils::task.c_str());
        discordRP->Update();

        Sleep(5000);
    }
    
    delete discordRP;
    delete console;
    
    return EXIT_SUCCESS;
}
