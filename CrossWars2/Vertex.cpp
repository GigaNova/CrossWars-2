#include "Vertex.h"
#include <GLM/detail/func_geometric.inl>

Vertex::Vertex(int t_index, glm::vec3 t_position) : m_dupe(nullptr), m_texture_ind(-1), m_normal_ind(-1), m_index(t_index), m_position(t_position), m_length(length(t_position))
{
}

Vertex::~Vertex()
{
}

bool Vertex::isSet()
{
	return m_texture_ind != -1 && m_normal_ind != -1;
}

bool Vertex::identical(int m_texture, int m_normal)
{
	return m_texture_ind == m_texture && m_normal_ind == m_normal;
}

int Vertex::getIndex() const
{
	return m_index;
}

int Vertex::getTextureIndex() const
{
	return m_texture_ind;
}

int Vertex::getNormalIndex() const
{
	return m_normal_ind;
}

glm::vec3 Vertex::getPosition() const
{
	return m_position;
}

void Vertex::setTextureIndex(int t_texture_ind)
{
	m_texture_ind = t_texture_ind;
}

void Vertex::setNormalIndex(int t_normal_ind)
{
	m_normal_ind = t_normal_ind;
}

void Vertex::setDupe(Vertex* t_dupe)
{
	m_dupe = t_dupe;
}

Vertex* Vertex::getDupe()
{
	return m_dupe;
}
