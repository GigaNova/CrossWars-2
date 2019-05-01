#include "FileLoader.h"
#include <fstream>


FileLoader::FileLoader()
{
}


FileLoader::~FileLoader()
{
}

std::string FileLoader::loadFileToString(const char* t_filename)
{
	std::ifstream t(t_filename);
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	return str;
}
