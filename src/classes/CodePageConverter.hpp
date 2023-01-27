#pragma once

#pragma comment(lib, "libiconv.lib")

#include <iconv.h>
#include <iostream>

class CodePageConverter
{
public:
    CodePageConverter(const char* from, const char* to);

    std::string convert(std::string str);
    void close();

private:
    iconv_t _cv{};
};
