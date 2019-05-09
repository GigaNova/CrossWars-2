#include "ProtoShader.h"
#include "ShaderManager.h"

ProtoShader::ProtoShader(const char* t_vertex, const char* t_fragment) : m_vertex(t_vertex), m_fragment(t_fragment)
{
	ShaderManager::GetInstance()->loadVertexShader(m_vertex);
	ShaderManager::GetInstance()->loadFragmentShader(m_fragment);
	m_program_id = ShaderManager::GetInstance()->bindPrograms();
}

ProtoShader::~ProtoShader()
{
}

GLuint ProtoShader::getProgramId() const
{
	return m_program_id;
}
