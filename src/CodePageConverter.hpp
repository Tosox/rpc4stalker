#pragma once

#pragma comment(lib, "libiconv.lib")

#include "utils.hpp"

#include <iconv.h>
#include <iostream>

class CodePageConverter
{
public:
    CodePageConverter(const char* to, const char* from);

    std::string convert(std::string str);
    void close();

private:
    iconv_t _cv{};
};