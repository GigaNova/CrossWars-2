#pragma once
#include "Singleton.h"
#include "ModelData.h"
#include <GLEW/glew.h>
#include <vector>
#include "ObjFormatLoader.h"
#include "TextureData.h"

class ModelManager : public TSingleton<ModelManager>
{
public:
	ModelManager();
	~ModelManager();

	void cleanUp();

	ModelData* loadObj(const char* t_name);
	ModelData* loadModelToVao(std::vector<GLfloat> t_vertex_positions, std::vector<GLuint> t_indices, std::vector<GLfloat> t_normals, std::vector<GLfloat> t_texture_coords);
	ModelData* loadModelToVao(std::vector<GLfloat> t_vertex_positions, std::vector<GLfloat> t_normals);
	TextureData* loadTexture(std::string t_filename);
private:
	GLuint createVao();
	void storeData(int t_attribute_num, int t_coord_size, std::vector<GLfloat> t_data);
	void bindIndices(std::vector<GLuint> t_indices);
	void unbindVao();

	std::vector<GLuint> m_vao_vector;
	std::vector<GLuint> m_vbo_vector;
	std::vector<GLuint> m_texture_vector;

	ObjFormatLoader m_obj_loader;
};

