#pragma once

#include <functional>
#include <vector>

class Console
{
public:
	Console(bool attach_console);
	~Console();

	const char* GetTimeStamp() const;
	void doUTF8() const;
	void hide() const;
	void show() const;
	void title(const char* title) const;
	void print(const char* msg) const;
	void println(const char* msg) const;
	void log(const char* msg) const;
	void logln(const char* msg) const;
	void clear() const;
	void ask(const char* msg, bool* boolean) const;
	void ask(const char* msg, const std::function<void(char* answer)>& lambda) const;
	int selection(const std::vector<const char*> options, const char* enter_msg) const;

private:
	FILE* f{};
	bool attach_console;
};