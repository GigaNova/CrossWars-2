#pragma once
#include <vector>
#include <GLM/glm.hpp>
#include "ModelData.h"
#include "Vertex.h"
#include <string>-

class ObjFormatLoader
{
public:
	ObjFormatLoader();
	~ObjFormatLoader();

	ModelData* loadModel(std::string t_filename);
	std::vector<std::string> splitStringDel(std::string const& t_original, char t_separator, std::vector<std::string>& t_result);
	void vertexElimination(Vertex* t_previous_index, int t_texture_index, int t_normal_index, std::vector<GLuint>* t_indices, std::vector<Vertex*>* t_vertices);
	void removeUnusedVertices(const std::vector<Vertex*>& vertices);
};

