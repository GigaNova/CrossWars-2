#include "ModelManager.h"
#include "Defines.h"
#include <GLEW/glew.h>
#include <lodepng/SOIL.h>


ModelManager::ModelManager()
{
}


ModelManager::~ModelManager()
{
}

ModelData* ModelManager::loadModelToVao(std::vector<GLfloat> t_vertex_positions, std::vector<GLuint> t_indices, std::vector<GLfloat> t_texture_coords)
{
	GLuint id = createVao();
	bindIndices(t_indices);
	storeData(0, 3, t_vertex_positions);
	storeData(1, 2, t_texture_coords);
	unbindVao();

	return new ModelData(id, t_indices.size());
}

Model* ModelManager::loadModel()
{
	/*
	 * Placeholder stuff
	 */
	std::vector<GLfloat> vertices = {
	-0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f
	};

	std::vector<GLuint> indices = {
		0,1,3,
		3,1,2
	};

	std::vector<GLfloat> textureCoords = {
		0,0,
		0,1,
		1,1,
		1,0
	};

	auto textureData = loadTexture("test.jpg");
	auto modelData = loadModelToVao(vertices, indices, textureCoords);

	return new Model(modelData, textureData);
}

TextureData* ModelManager::loadTexture(std::string t_filename)
{
	GLint texture;
	std::string FileName = "..\\Assets\\Textures\\" + t_filename;
	texture = SOIL_load_OGL_texture
	(
		FileName.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	m_texture_vector.push_back(texture);
	return new TextureData(texture);
}

GLuint ModelManager::createVao()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	m_vao_vector.push_back(vaoID);

	return vaoID;
}

void ModelManager::storeData(int t_attribute_num, int t_coord_size, std::vector<GLfloat> t_data)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, t_data.size() * sizeof(GLfloat), &t_data.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(t_attribute_num, t_coord_size, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	m_vbo_vector.push_back(vboID);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelManager::bindIndices(std::vector<GLuint> t_indices)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, t_indices.size() * sizeof(GLint), &t_indices.front(), GL_STATIC_DRAW);

	m_vbo_vector.push_back(vboID);
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

	for (auto id : m_texture_vector)
	{
		glDeleteTextures(1, &id);
	}
}
