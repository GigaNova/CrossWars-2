#include "ChunkData.h"

ChunkData::ChunkData(const std::vector<GLfloat>& t_vertices, const std::vector<GLfloat>& t_normals) : m_vertices(t_vertices), m_normals(t_normals)
{
}

ChunkData::~ChunkData()
{
}

std::vector<GLfloat> ChunkData::getVertices() const
{
	return m_vertices;
}

std::vector<GLfloat> ChunkData::getNormals() const
{
	return m_normals;
}
