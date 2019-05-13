#include "ModelManager.h"
#include "Defines.h"
#include <GLEW/glew.h>
#include <lodepng/SOIL.h>
#include "Logger.h"
#include <experimental/filesystem>


ModelManager::ModelManager() : m_obj_loader(ObjFormatLoader())
{
}


ModelManager::~ModelManager()
{
}

ModelData* ModelManager::loadModelToVao(std::vector<GLfloat> t_vertex_positions, std::vector<GLuint> t_indices, std::vector<GLfloat> t_normals, std::vector<GLfloat> t_texture_coords)
{
	GLuint id = createVao();
	bindIndices(t_indices);
	storeData(0, 3, t_vertex_positions);
	storeData(1, 2, t_texture_coords);
	storeData(2, 3, t_normals);
	unbindVao();

	return new ModelData(id, t_indices.size());
}

ModelData* ModelManager::loadModelToVao(std::vector<GLfloat> t_vertex_positions, std::vector<GLfloat> t_normals)
{
	GLuint id = createVao();
	storeData(0, 3, t_vertex_positions);
	storeData(1, 3, t_normals);
	unbindVao();

	return new ModelData(id, t_vertex_positions.size() / 3);
}

ModelData* ModelManager::loadObj(const char* t_name)
{
	return m_obj_loader.loadModel(t_name);
}

TextureData* ModelManager::loadTexture(std::string t_filename)
{
	unsigned char* texture;
	GLuint textureId;

	std::string path = "..\\Assets\\Textures\\" + t_filename;
	const char* fileName = path.c_str();

	Logger::GetInstance()->logAction("Loading texture file " + t_filename);
	if (!std::experimental::filesystem::exists(path))
	{
		Logger::GetInstance()->logError("No such file exists.", __LINE__, __FILE__);
		return new TextureData(-1);
	}

	glGenTextures(1, &textureId);

	int width;
	int height;
	int channel;

	texture = SOIL_load_image(fileName, &width, &height, &channel, SOIL_LOAD_RGB);

	if (texture == NULL) {
		Logger::GetInstance()->logError("An error occured loading image.", __LINE__, __FILE__);
		return new TextureData(-1);
	}

	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);

	SOIL_free_image_data(texture);

	m_texture_vector.push_back(textureId);
	return new TextureData(textureId);
}

GLuint ModelManager::createShadowMap()
{
	GLuint depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);

	return depthMapFBO;
}

GLuint ModelManager::createDepthBufferAttachment()
{
	GLuint depthMap;
	glGenTextures(1, &depthMap);

	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return depthMap;
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
