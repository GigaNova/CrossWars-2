#include "ModelManager.h"
#include "Defines.h"
#include <GLEW/glew.h>


ModelManager::ModelManager()
{
}


ModelManager::~ModelManager()
{
}

ModelData* ModelManager::loadModelToVao(const float* t_vertex_positions, int t_amount_of_vertices)
{
	GLuint id = createVao();
	storeData(0, 3, t_vertex_positions, t_amount_of_vertices * 3);
	unbindVao();

	return new ModelData(id, t_amount_of_vertices);
}

GLuint ModelManager::createVao()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	m_vao_vector.push_back(vaoID);

	return vaoID;
}

void ModelManager::storeData(int t_attribute_num, int t_coord_size, const float* t_data, int t_amount_of_items)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, t_amount_of_items * sizeof(t_data), t_data, GL_STATIC_DRAW);
	glVertexAttribPointer(t_attribute_num, t_coord_size, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	m_vbo_vector.push_back(vboID);

	//Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelManager::unbindVao()
{
	glBindVertexArray(0);
}


void ModelManager::cleanUp()
{
	for(auto id : m_vao_vector)
	{
		glDeleteVertexArrays(1, &id);
	}

	for (auto id : m_vbo_vector)
	{
		glDeleteBuffers(1, &id);
	}
}
