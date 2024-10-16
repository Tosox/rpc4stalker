#pragma once

#include <iostream>

class Console {
public:
	static void attach();
	static void detach();

private:
	inline static FILE* file;
};
