#pragma once
#include <vector>
#include <GLM/glm.hpp>
#include "ModelData.h"

class ObjFormatLoader
{
public:
	ObjFormatLoader();
	~ObjFormatLoader();

	ModelData* loadModel(std::string t_filename);
	std::vector<std::string> splitStringDel(std::string const& t_original, char t_separator, std::vector<std::string>& t_result);
};

