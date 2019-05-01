#include "ProtoShader.h"
#include "ShaderManager.h"

ProtoShader::ProtoShader(const char* t_vertex, const char* t_fragment)
{
	ShaderManager::GetInstance()->loadVertexShader(t_vertex);
	ShaderManager::GetInstance()->loadFragmentShader(t_fragment);
	ShaderManager::GetInstance()->bindPrograms();
}

ProtoShader::~ProtoShader()
{
}
