#include "CodePageConverter.hpp"

#include <cstdio>

#include "../utils/utils.hpp"

CodePageConverter::CodePageConverter(const char* from, const char* to)
{
	_cv = iconv_open(to, from);
	if (_cv == (iconv_t)(-1))
		utils::throwErrorAndExit("Unable to initialize CodePageConverter.");
}

std::string CodePageConverter::convert(std::string str)
{
	std::size_t inputSize = str.length();
	char inputBuffer[1024]{};
	strcpy_s(inputBuffer, sizeof(inputBuffer), str.c_str());
	
	std::size_t outputSize = 1024;
	char outputBuffer[1024]{};

	char* input = &inputBuffer[0];
	char* output = &outputBuffer[0];
	const std::size_t result = iconv(_cv, &input, &inputSize, &output, &outputSize);
	if ((result == -1) || (inputSize != 0))
		utils::throwError("Unable to convert CP1251 to UTF-8.");

	return std::string(outputBuffer);
}

void CodePageConverter::close()
{
	if (_cv != (iconv_t)(-1))
		iconv_close(_cv);
}
