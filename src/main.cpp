#include <thread>

#include "DiscordManager.hpp"
#include "Dumper.hpp"
#include "utils.hpp"
#include "globals.hpp"

int main(int argc, char** argv)
{
    // Init objects
    DiscordManager discord;
    Dumper dumper;

    std::string localization;
    std::string level;
    std::string time;
    std::string faction_raw;
    std::string faction;
    std::string task;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitleA(APPLICATION_NAME.c_str());
    printf_s("%s\n", LOGO);

    //---------------------------------------------------------------------------------------

    {
        // Find discord
        do
        {
            printf_s("%s Searching for discord...\n", utils::_CYAN("[*]").c_str());
            discord.Create(DISCORD_APPLICATION_ID);
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
        } while (!discord.IsReady());

        // Print dump file path
        printf_s("%s Getting dump file path...\n", utils::_CYAN("[*]").c_str());
        const std::filesystem::path path = std::filesystem::temp_directory_path().string() + APPLICATION_NAME + ".json";
        dumper.SetDumpPath(path.string());
        std::this_thread::sleep_for(std::chrono::milliseconds(700));

        // Find dumps
        do
        {
            printf_s("%s Searching for dumps...\n", utils::_CYAN("[*]").c_str());
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
        } while (!dumper.IsDumpReady());

        discord.AddTimestamp();
        discord.SetType(discord::ActivityType::Playing);
        discord.SetLargeImage("stalker_icon_0", "S.T.A.L.K.E.R.");

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    //---------------------------------------------------------------------------------------

    while (discord.IsReady())
    {   
        system("cls");

        printf_s("%s\n", LOGO);

        dumper.LoadValue(localization, { "values", "localization" });
        dumper.LoadValue(level, { "values", "level" });
        dumper.LoadValue(faction_raw, { "values", "faction_raw" });
        dumper.LoadValue(faction, { "values", "faction" });
        dumper.LoadValue(task, { "values", "task" });

        dumper.PrintDump({
            std::make_pair("Localization", localization),
            std::make_pair("Level", level),
            std::make_pair("Faction (raw)", faction_raw),
            std::make_pair("Faction", faction),
            std::make_pair("Task", task)
        });
        
        discord.SetSmallImage(
            utils::FindStrStrMap(COMMUNITY_TABLE, faction_raw, "stalker_patch_stalker").c_str(),
            faction.c_str()
        );

        static char szLevel[256]{};
        sprintf_s(
            szLevel,
            utils::FindStrStrMap(LANGUAGE_TABLE, localization, "Exploring: %s").c_str(),
            level.c_str()
        );

        discord.SetDetails(szLevel);
        discord.SetState(task.c_str());
        discord.Update();

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    
    return EXIT_SUCCESS;
}
