#include "common.h"
#include <iostream>

std::mutex coutMutex;

void safePrint(const std::string &text)
{
	std::lock_guard<std::mutex> lock(coutMutex);
	std::cout << text << std::endl;
}
