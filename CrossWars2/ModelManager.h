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

	ModelData* loadModelToVao(std::vector<GLfloat> t_vertex_positions, std::vector<GLint> t_indices);

private:
	GLuint createVao();
	void storeData(int t_attribute_num, int t_coord_size, std::vector<GLfloat> t_data);
	void bindIndices(std::vector<GLint> t_indices);
	void unbindVao();

	std::vector<GLuint> m_vao_vector;
	std::vector<GLuint> m_vbo_vector;
};

