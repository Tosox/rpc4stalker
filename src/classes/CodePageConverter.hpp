#pragma once

#ifdef _DEBUG
#pragma comment(lib, "libiconv_d.lib")
#else
#pragma comment(lib, "libiconv.lib")
#endif // _DEBUG

#include <iostream>

#include <iconv.h>

class CodePageConverter
{
public:
    CodePageConverter(const char* from, const char* to);

    std::string convert(std::string str);
    void close();

private:
    iconv_t _cv{};
};
