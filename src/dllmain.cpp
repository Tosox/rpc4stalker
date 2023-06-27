#include <thread>

#include "classes/DiscordManager.hpp"
#include "classes/Dumper.hpp"
#include "classes/Console.hpp"
#include "utils/utils.hpp"
#include "settings/globals.hpp"

#define wait(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))

unsigned long WINAPI MainThread(void* instance)
{
	// Open console window
	Console console{};
	console.attach();

	// Init objects
	DiscordManager discordManager{};
	Dumper dumper{};

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTitleA("rpc4stalker");

	discordManager.addTimestamp();
	discordManager.setType(discord::ActivityType::Playing);
	discordManager.setLargeImage("stalker_icon_0", "S.T.A.L.K.E.R.");

	const std::filesystem::path path = std::filesystem::temp_directory_path().string() + "rpc4stalker.json";
	dumper.setDumpPath(path.string());

	while (true)
	{
		system("cls");
		std::cout << LOGO << std::endl;

		if (!discordManager.isReady())
		{
			utils::Log("Searching for Discord...");
			discordManager.create(DISCORD_APPLICATION_ID);
			wait(2500);
			continue;
		}

		if (!dumper.dumpValues())
		{
			wait(2500);
			continue;
		}

		std::string localization = dumper.loadValue({ "values", "localization" });
		std::string level = dumper.loadValue({ "values", "level" });
		std::string faction_raw = dumper.loadValue({ "values", "faction_raw" });
		std::string faction = dumper.loadValue({ "values", "faction" });
		std::string task = dumper.loadValue({ "values", "task" });

		dumper.printDump({
			std::make_pair("Localization", localization),
			std::make_pair("Level", level),
			std::make_pair("Faction (raw)", faction_raw),
			std::make_pair("Faction", faction),
			std::make_pair("Task", task)
		});

		std::string exploringLevel = utils::FindStrStrMap(LANGUAGE_TABLE, localization, "Exploring: ") + level;
		std::string patchImage = utils::FindStrStrMap(COMMUNITY_TABLE, faction_raw, "stalker_patch_stalker");

		discordManager.setSmallImage(patchImage.c_str(), faction.c_str());
		discordManager.setDetails(exploringLevel.c_str());
		discordManager.setState(task.c_str());
		discordManager.update();

		wait(2000);
	}

	discordManager.shutdown();
	dumper.shutdown();
	console.detach();

	FreeLibraryAndExitThread((HMODULE)(instance), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(const HMODULE hModule, unsigned long callReason, void* reserved)
{
	DisableThreadLibraryCalls(hModule);

	HANDLE handle{};

	switch (callReason)
	{
	case DLL_PROCESS_ATTACH:
		handle = CreateThread(nullptr, NULL, MainThread, hModule, NULL, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	if (handle)
		CloseHandle(handle);

	return TRUE;
}
