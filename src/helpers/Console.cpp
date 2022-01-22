#include <Windows.h>
#include <iostream>
#include <sys/timeb.h>
#include <ctime>
#include "Console.hpp"

Console::Console(bool attach_console)
{
	this->attach_console = attach_console;

	if (this->attach_console)
	{
		AllocConsole();
		freopen_s(&this->f, "CONIN$", "r", stdin);
		freopen_s(&this->f, "CONOUT$", "w", stdout);
	}
}

Console::~Console()
{
	if (this->attach_console)
	{
		fclose(this->f);
		FreeConsole();
	}
}

const char* Console::GetTimeStamp() const
{
	static char* szTime = new char[128];

	time_t now = time(nullptr);
	tm tm_info{};
	localtime_s(&tm_info, &now);
	strftime(szTime, 128, "%H:%M:%S", &tm_info);

	return szTime;
}

void Console::doUTF8() const
{
	SetConsoleOutputCP(CP_UTF8);
}

void Console::hide() const
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void Console::show() const
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}

void Console::print(const char* msg) const
{
	std::cout << msg;
}

void Console::printl(const char* msg) const
{
	std::cout << msg << std::endl;
}

void Console::log(const char* msg) const
{
	std::cout << "[" << this->GetTimeStamp() << "] " << msg;
}

void Console::logl(const char* msg) const
{
	std::cout << "[" << this->GetTimeStamp() << "] " << msg << std::endl;
}

void Console::clear() const
{
	system("cls");
}

void Console::ask(const char* msg, bool* boolean) const
{
	char* input = new char[128];
	std::cout << msg << " (y/n): ";
	std::cin >> input;
	*boolean = strcmp(input, "y") == 0;
	delete[] input;
}

void Console::ask(const char* msg, const std::function<void(char* answer)>& lambda) const
{
	char* input = new char[128];
	std::cout << msg;
	std::cin.getline(input, 128);
	lambda(input);
	delete[] input;
}

int Console::selection(const std::vector<const char*> options, const char* enter_msg) const
{
	size_t input = NULL;

	for (size_t i = 0; i < options.size(); ++i)
	{
		std::cout << i + 1 << ". " << options.at(i) << std::endl;
	}
	std::cout << enter_msg;

	while (!input)
	{
		std::cin >> input;

		if ((input > 0) && (input <= options.size()))
			return input - 1;
		input = NULL;
	}

	return NULL;
}