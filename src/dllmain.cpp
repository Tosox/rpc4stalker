#include "classes/DiscordManager.hpp"
#include "classes/DataReader.hpp"
#include "classes/Console.hpp"
#include "utils/utils.hpp"
#include "settings/globals.hpp"

unsigned long WINAPI MainThread(void* instance) {
	// Open console window
	Console::attach();

	// Init objects
	DiscordManager discordManager{};
	DataReader reader{};

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTitleA("rpc4games");

	discordManager.addTimestamp();
	discordManager.setType(discord::ActivityType::Playing);
	discordManager.setLargeImage("stalker_icon_0", "S.T.A.L.K.E.R.");

	const std::filesystem::path path = std::filesystem::temp_directory_path().string() + "rpc4stalker.json";
	reader.setDumpPath(path.string());

	while (true) {
		system("cls");
		utils::logging::Debug(LOGO);

		if (!discordManager.isReady()) {
			utils::logging::Info("Searching for Discord...");
			discordManager.create(DISCORD_APPLICATION_ID);
			utils::threads::wait(2500);
			continue;
		}

		if (!reader.dumpValues()) {
			utils::threads::wait(2500);
			continue;
		}

		std::string localization = reader.loadValue({ "values", "localization" });
		std::string level = reader.loadValue({ "values", "level" });
		std::string faction_raw = reader.loadValue({ "values", "faction_raw" });
		std::string faction = reader.loadValue({ "values", "faction" });
		std::string task = reader.loadValue({ "values", "task" });

		reader.printDump({
			std::make_pair("Localization", localization),
			std::make_pair("Level", level),
			std::make_pair("Faction (raw)", faction_raw),
			std::make_pair("Faction", faction),
			std::make_pair("Task", task)
		});

		std::string exploringLevel = utils::map::FindInMap(LANGUAGE_TABLE, localization, "Exploring: ") + level;
		std::string patchImage = utils::map::FindInMap(COMMUNITY_TABLE, faction_raw, "stalker_patch_stalker");

		discordManager.setSmallImage(patchImage.c_str(), faction.c_str());
		discordManager.setDetails(exploringLevel.c_str());
		discordManager.setState(task.c_str());
		discordManager.update([&](discord::Result result){});

		utils::threads::wait(2000);
	}
}

BOOL APIENTRY DllMain(const HMODULE hModule, unsigned long callReason, void* reserved) {
	DisableThreadLibraryCalls(hModule);

	HANDLE handle = nullptr;

	switch (callReason) {
	case DLL_PROCESS_ATTACH:
		handle = CreateThread(nullptr, NULL, MainThread, hModule, NULL, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	if (handle != nullptr) {
		CloseHandle(handle);
	}

	return TRUE;
}
