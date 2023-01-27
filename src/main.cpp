#include <thread>

#include "classes/DiscordManager.hpp"
#include "classes/Dumper.hpp"
#include "utils/utils.hpp"
#include "settings/globals.hpp"

#define wait(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

int main(int argc, char** argv)
{
    // Init objects
    DiscordManager discordManager{};
    Dumper dumper{};

    std::string localization;
    std::string level;
    std::string faction_raw;
    std::string faction;
    std::string task;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitleA("rpc4stalker");
    std::cout << LOGO << std::endl;

    //---------------------------------------------------------------------------------------

    {
        // Find discordManager
        do
        {
            std::cout << _F_BLUE("[*] ") << "Searching for Discord..." << std::endl;
            discordManager.create(DISCORD_APPLICATION_ID);
            wait(700);
        } while (!discordManager.isReady());

        // Print dump file path
        std::cout << _F_BLUE("[*] ") << "Getting dump file path..." << std::endl;
        const std::filesystem::path path = std::filesystem::temp_directory_path().string() + "rpc4stalker.json";
        dumper.setDumpPath(path.string());

        // Find dumps
        do
        {
            std::cout << _F_BLUE("[*] ") << "Searching for dumps..." << std::endl;
            wait(700);
        } while (!dumper.isDumpReady());

        discordManager.addTimestamp();
        discordManager.setType(discord::ActivityType::Playing);
        discordManager.setLargeImage("stalker_icon_0", "S.T.A.L.K.E.R.");
    }

    //---------------------------------------------------------------------------------------

    while (discordManager.isReady())
    {   
        system("cls");

        std::cout << LOGO << std::endl;

        dumper.dumpValues();

        dumper.loadValue(localization, { "values", "localization" });
        dumper.loadValue(level, { "values", "level" });
        dumper.loadValue(faction_raw, { "values", "faction_raw" });
        dumper.loadValue(faction, { "values", "faction" });
        dumper.loadValue(task, { "values", "task" });

        dumper.printDump({
            std::make_pair("Localization", localization),
            std::make_pair("Level", level),
            std::make_pair("Faction (raw)", faction_raw),
            std::make_pair("Faction", faction),
            std::make_pair("Task", task)
        });
        
        discordManager.setSmallImage(
            utils::FindStrStrMap(COMMUNITY_TABLE, faction_raw, "stalker_patch_stalker").c_str(),
            faction.c_str()
        );

        std::string exploringLevel = utils::FindStrStrMap(LANGUAGE_TABLE, localization, "Exploring: ") + level;

        discordManager.setDetails(exploringLevel.c_str());
        discordManager.setState(task.c_str());
        discordManager.update();

        wait(2000);
    }
    
    dumper.shutdown();

    return EXIT_SUCCESS;
}
