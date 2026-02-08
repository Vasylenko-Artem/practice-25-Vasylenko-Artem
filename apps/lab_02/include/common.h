#pragma once
#include <mutex>
#include <string>

extern std::mutex coutMutex;

void safePrint(const std::string &text);
