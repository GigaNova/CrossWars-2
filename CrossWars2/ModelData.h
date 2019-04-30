#pragma once
#include <GLEW/glew.h>

class ModelData
{
public:
	ModelData(GLuint t_vao_id, GLuint t_vertex_count);
	~ModelData();

	GLuint getVaoId() const;
	GLuint getVertexCount() const;

private:
	GLuint m_vao_id;
	GLuint m_vertex_count;
};

