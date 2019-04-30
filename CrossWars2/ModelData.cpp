#include "ModelData.h"

ModelData::ModelData(GLuint t_vao_id, GLuint t_vertex_count)
	: m_vao_id(t_vao_id), m_vertex_count(t_vertex_count)
{
}

ModelData::~ModelData()
{
}

GLuint ModelData::getVaoId() const
{
	return m_vao_id;
}

GLuint ModelData::getVertexCount() const
{
	return m_vertex_count;
}
