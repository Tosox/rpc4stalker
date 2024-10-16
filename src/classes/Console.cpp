#include "Console.hpp"

#include <Windows.h>

void Console::attach() {
	// Allocate a console
	if (!AllocConsole()) {
		std::cerr << "Failed to allocate console." << std::endl;
		return;
	}

	// Redirect the output streams
	if (freopen_s(&file, "CONOUT$", "w", stdout) != 0) {
		std::cerr << "Failed to redirect stdout to console." << std::endl;
		FreeConsole(); 
		return;
	}

	if (freopen_s(&file, "CONOUT$", "w", stderr) != 0) {
		std::cerr << "Failed to redirect stderr to console." << std::endl;
		if (file != nullptr) {
			fclose(file);
		}
		FreeConsole();
		return;
	}

	// Redirect the input stream
	if (freopen_s(&file, "CONIN$", "r", stdin) != 0) {
		std::cerr << "Failed to redirect stdin to console." << std::endl;
		if (file != nullptr) {
			fclose(file);
		}
		FreeConsole();
		return;
	}

	// Disable the close button
	HMENU hMenu = GetSystemMenu(GetConsoleWindow(), FALSE);
	if (hMenu != nullptr) {
		EnableMenuItem(hMenu, SC_CLOSE, MF_GRAYED);
	}
}

void Console::detach() {
	if (file) {
		// Enable the close button again
		HMENU hMenu = GetSystemMenu(GetConsoleWindow(), FALSE);
		if (hMenu != nullptr) {
			EnableMenuItem(hMenu, SC_CLOSE, MF_ENABLED);
		}

		// Free the console and close the file
		fclose(file);
		file = nullptr;
		FreeConsole();
	}
}
