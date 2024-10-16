#pragma once

#ifdef _DEBUG
#pragma comment(lib, "libiconv_d.lib")
#else
#pragma comment(lib, "libiconv.lib")
#endif // _DEBUG

#include <iostream>
#include <iconv.h>
#include <vector>

class CodePageConverter {
public:
    CodePageConverter(const std::string& from, const std::string& to);
    ~CodePageConverter();

    std::string convert(const std::string& str) const;

private:
    iconv_t _cv{};
    std::string from{};
    std::string to{};
};
