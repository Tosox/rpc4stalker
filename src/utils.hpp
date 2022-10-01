#pragma once

#include <Windows.h>
#include <map>
#include <string>
#include <iostream>

inline std::ostream& _F_BLUE(std::ostream& stream)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    return stream;
}

inline std::ostream& _F_RED(std::ostream& stream)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
    return stream;
}

inline std::ostream& _F_GREEN(std::ostream& stream)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return stream;
}

inline std::ostream& _F_WHITE(std::ostream& stream)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return stream;
}

struct _C_COLOR 
{
    _C_COLOR(unsigned short attribute)
    {
        m_color = attribute;
    }

    unsigned short m_color;
};

template <class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits>& operator<<(std::basic_ostream<_Elem, _Traits>& bstream, _C_COLOR& color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, color.m_color);
    return bstream;
}

namespace utils
{
	void ThrowError(const std::string& message);
	void ThrowErrorAndExit(const std::string& message);
	std::string FindStrStrMap(const std::map<std::string, std::string>& map, const std::string& val, const std::string& callback);
}
