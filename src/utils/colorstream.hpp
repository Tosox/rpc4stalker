#pragma once

#include <Windows.h>
#include <iostream>

inline void SetConsoleColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

inline void ResetConsoleColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

#define SET_COLOR_RED() SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define SET_COLOR_GREEN() SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define SET_COLOR_BLUE() SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define SET_COLOR_YELLOW() SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define SET_COLOR_WHITE() SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)

#define PRINT_RED(x) SET_COLOR_RED(); std::cout << x; ResetConsoleColor();
#define PRINT_GREEN(x) SET_COLOR_GREEN(); std::cout << x; ResetConsoleColor();
#define PRINT_BLUE(x) SET_COLOR_BLUE(); std::cout << x; ResetConsoleColor();
#define PRINT_YELLOW(x) SET_COLOR_YELLOW(); std::cout << x; ResetConsoleColor();
#define PRINT_WHITE(x) SET_COLOR_WHITE(); std::cout << x; ResetConsoleColor();
