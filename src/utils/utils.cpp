#include "utils.hpp"

#include <iostream>
#include <thread>

void utils::logging::Log(const std::string& message, LogLevel level) {
    switch (level) {
    case LogLevel::INFO:
        PRINT_BLUE("[.] " << message << std::endl);
        break;
    case LogLevel::WARNING:
		PRINT_YELLOW("[*] " << message << std::endl);
        break;
    case LogLevel::CRITICAL:
        PRINT_RED("[!] " << message << std::endl);
        break;
    case LogLevel::DEBUG:
        PRINT_WHITE(message << std::endl);
        break;
    }
}

void utils::logging::Info(const std::string& message) {
	Log(message, LogLevel::INFO);
}

void utils::logging::Warning(const std::string& message) {
    Log(message, LogLevel::WARNING);
}

void utils::logging::Critical(const std::string& message) {
    Log(message, LogLevel::CRITICAL);
}

void utils::logging::Debug(const std::string& message) {
    Log(message, LogLevel::DEBUG);
}

void utils::logging::ThrowError(const std::string& message) {
	Log(message, LogLevel::CRITICAL);
	std::cout << std::endl << "Press <ENTER> to exit..." << std::endl;
    std::cin.get();
	throw std::runtime_error(message);
}

std::string utils::map::FindInMap(const std::map<std::string, std::string>& map, const std::string& val, const std::string& fallback) {
	auto iter = map.find(val);
	return iter != map.end() ? map.find(val)->second : fallback;
}

void utils::threads::wait(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
