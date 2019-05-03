#include "Logger.h"
#include <string>

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::logAction(std::string t_action)
{
	std::cout << t_action << std::endl;
}

void Logger::logError(std::string t_error, int t_line, const char* t_file)
{
	std::cout << "Error!" << std::endl;
	std::cout << "> " + t_error << std::endl;
	std::cout << ">> " + std::string(t_file) + " : " + std::to_string(t_line) << std::endl;
}
