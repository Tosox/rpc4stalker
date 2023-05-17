#pragma once

#include <iostream>

class Console
{
public:
	void attach();
	void detach();

private:
	FILE* m_File;
};
