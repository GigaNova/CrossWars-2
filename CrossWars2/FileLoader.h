#pragma once
#include <string>

class FileLoader
{
public:
	FileLoader();
	~FileLoader();

	std::string loadFileToString(const char* t_filename);
};

