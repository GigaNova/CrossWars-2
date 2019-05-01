#include "FileLoader.h"
#include <fstream>

FileLoader::FileLoader()
{
}


FileLoader::~FileLoader()
{
}

std::string FileLoader::loadFileToString(std::string t_filename, FileType t_file_type)
{
	switch (t_file_type) { 
	case MODEL: 
		t_filename = "..\\Assets\\Models\\" + t_filename;
		break;
	case SHADER: 
		t_filename = "..\\Assets\\Shaders\\" + t_filename;
		break;
	default: 
		break;
	}

	std::ifstream t(t_filename);
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	return str;
}