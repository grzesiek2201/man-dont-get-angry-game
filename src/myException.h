#pragma once
#include <string>
#include <exception>
class myException : public std::exception
{
private:
	std::string error;
public:
	myException(const std::string &msg) {
		error = msg;
	}
	~myException() throw() {}

	virtual const char* what() const throw() {
		return error.c_str();
	}
};

