#include "CodePageConverter.hpp"

#include <cstdio>

#include "../utils/utils.hpp"

CodePageConverter::CodePageConverter(const std::string& from, const std::string& to)
	: from(from), to(to) {
	_cv = iconv_open(to.c_str(), from.c_str());
	if (_cv == (iconv_t)(-1)) {
		utils::logging::ThrowError("Unable to initialize CodePageConverter.");
	}
}

CodePageConverter::~CodePageConverter() {
	if (_cv != (iconv_t)(-1)) {
		iconv_close(_cv);
	}
}

std::string CodePageConverter::convert(const std::string& str) const {
	std::size_t inputSize = str.size();
	std::size_t outputSize = inputSize * 4;

	std::vector<char> inputBuffer(inputSize + 1);
	std::vector<char> outputBuffer(outputSize);

	strcpy_s(inputBuffer.data(), inputBuffer.size(), str.c_str());

	char* input = inputBuffer.data();
	char* output = outputBuffer.data();
	std::size_t inBytesLeft = inputSize;
	std::size_t outBytesLeft = outputSize;

	std::size_t result = iconv(_cv, &input, &inBytesLeft, &output, &outBytesLeft);
	if ((result == (std::size_t)(-1)) || (inBytesLeft != 0)) {
		std::string errorMsg = "Error during conversion: ";
		switch (errno) {
		case EILSEQ:
			errorMsg += "Invalid multibyte sequence.";
			break;
		case EINVAL:
			errorMsg += "Incomplete multibyte sequence.";
			break;
		case E2BIG:
			errorMsg += "Output buffer too small.";
			break;
		default:
			errorMsg += "Unknown error.";
			break;
		}
		utils::logging::Critical(errorMsg);
	}

	return std::string(outputBuffer.data());
}
