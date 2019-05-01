#pragma once
#include <string>
#include "GLEW/glew.h"
#include "FileTypes.h"
#include <vector>

class FileLoader
{
public:
	FileLoader();
	~FileLoader();

	std::string loadFileToString(std::string t_filename, FileType t_file_type);
};

