#include "classes/ConfigReader.hpp"
#include "classes/Console.hpp"
#include "classes/DataReader.hpp"
#include "classes/DiscordManager.hpp"
#include "utils/utils.hpp"

void PrintValue(std::string key, const std::string& value) {
	key.resize(20, ' ');
	PRINT_GREEN("[.]");
	std::cout << " " << key << ": " << value << std::endl;
}

unsigned long WINAPI MainThread(void* instance) {
	// Console related actions
	Console::attach();
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTitleA("rpc4games");

	ConfigReader cfgReader{ "rpc4games.json" };

	// Initialize objects
	DataReader dataReader{ std::filesystem::temp_directory_path().append("rpc4stalker.json") };

	DiscordManager discordManager{};
	discordManager.addTimestamp();

	while (true) {
		system("cls");

		if (!discordManager.isReady()) {
			utils::logging::Info("Searching for Discord...");
			discordManager.create(890702387025702922);
			utils::threads::wait(2500);
			continue;
		}

		RPCContents rpcContents{};
		if (!dataReader.readData(&rpcContents)) {
			utils::threads::wait(2500);
			continue;
		}

		discordManager.setType(rpcContents.values.type);
		discordManager.setDetails(rpcContents.values.details);
		discordManager.setState(rpcContents.values.state);
		discordManager.setLargeImage(rpcContents.values.largeImageUrl, rpcContents.values.largeImageText);
		discordManager.setSmallImage(rpcContents.values.smallImageUrl, rpcContents.values.smallImageText);
		discordManager.update([&](discord::Result result){
			if (result == discord::Result::Ok) {
				PrintValue("Activity Type", std::to_string(std::int32_t(rpcContents.values.type)));
				PrintValue("Details", rpcContents.values.details);
				PrintValue("State", rpcContents.values.state);
				PrintValue("Large Image URL", rpcContents.values.largeImageUrl);
				PrintValue("Large Image Text", rpcContents.values.largeImageText);
				PrintValue("Small Image URL", rpcContents.values.smallImageUrl);
				PrintValue("Small Image Text", rpcContents.values.smallImageText);
			} else {
				utils::logging::Warning("Failed to update Discord presence: " + std::int32_t(result));
			}
		});

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
