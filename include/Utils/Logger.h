#pragma once

#include <iostream>
#include <fstream>
#include <string>


class Logger
{
private:
	static std::ostream* output_;
public:
	static void setStream(std::ostream& stream);
	static void log(const std::string& message);
	static void error(const std::string& message);
};