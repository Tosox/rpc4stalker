#pragma once

#include <functional>

class Console
{
public:
	Console(bool attach_console);
	~Console();

	const char* GetTimeStamp() const;
	void doUTF8() const;
	void hide() const;
	void show() const;
	void print(const char* msg) const;
	void printl(const char* msg) const;
	void log(const char* msg) const;
	void logl(const char* msg) const;
	void clear() const;
	void ask(const char* msg, bool* boolean) const;
	void ask(const char* msg, const std::function<void(char* answer)>& lambda) const;

private:
	FILE* f{};
	bool attach_console;
};