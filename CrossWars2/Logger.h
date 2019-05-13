#pragma once
#include "Singleton.h"

class Logger : public TSingleton<Logger>
{
public:
	Logger();
	~Logger();

	void logAction(std::string t_action);
	void logError(std::string t_error, int t_line, const char* t_file);

private:
	std::mutex m_lock;
};

