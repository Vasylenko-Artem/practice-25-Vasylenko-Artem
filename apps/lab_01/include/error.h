#pragma once
#include <string>
#include <exception>

class ErrorRange : public std::exception
{
	std::string msg;

public:
	ErrorRange(const std::string &s);
	const char *what() const noexcept override;
};

class ErrorNoFile : public std::exception
{
	std::string msg;

public:
	ErrorNoFile(const std::string &s);
	const char *what() const noexcept override;
};
