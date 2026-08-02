#include "Utils/Logger.h"


std::ostream* Logger::output_ = &std::cout;


void Logger::setStream(std::ostream& stream) 
{
	output_ = &stream;
}


void Logger::log(const std::string& message)
{
	*output_ << "[LOG] " << message << std::endl;
}


void Logger::error(const std::string& message)
{
	*output_ << "[ERROR] " << message << std::endl;
}