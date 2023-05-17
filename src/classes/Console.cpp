#include "Console.hpp"

#include <Windows.h>

void Console::attach()
{
	// Allocate a console
	AllocConsole();

	// Redirect the output streams
	freopen_s(&this->m_File, "CONOUT$", "w", stdout);
	freopen_s(&this->m_File, "CONERR$", "w", stderr);
	
	// Remove close function of the console
	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_GRAYED);
}

void Console::detach()
{
	// Restore close function
	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_ENABLED);
	
	// Free the console
	FreeConsole();
	fclose(this->m_File);
}
