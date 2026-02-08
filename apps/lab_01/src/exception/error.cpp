#include "error.h"

ErrorRange::ErrorRange(const std::string &s) : msg(s) {}

const char *ErrorRange::what() const noexcept
{
	return msg.c_str();
}

ErrorNoFile::ErrorNoFile(const std::string &s) : msg(s) {}

const char *ErrorNoFile::what() const noexcept
{
	return msg.c_str();
}
