#pragma once
#include "Singleton.h"
#include "ModelData.h"
#include <GLEW/glew.h>
#include <vector>

class ModelManager : public TSingleton<ModelManager>
{
public:
	ModelManager();
	~ModelManager();

	void cleanUp();

	ModelData* loadModelToVao(const float* t_vertex_positions, int t_amount_of_vertices);

private:
	GLuint createVao();
	void storeData(int t_attribute_num, int t_coord_size, const float* t_data, int t_amount_of_items);
	void unbindVao();

	std::vector<GLuint> m_vao_vector;
	std::vector<GLuint> m_vbo_vector;
};

