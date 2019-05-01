#include "StandardShader.h"
#include "ShaderManager.h"

StandardShader::StandardShader() : ProtoShader("vertexShader.vert", "fragmentshader.frag")
{
}

StandardShader::~StandardShader()
{
}

void StandardShader::bindAttributes()
{
	ShaderManager::GetInstance()->bindAttribute(0, "position");
	ShaderManager::GetInstance()->bindAttribute(1, "textureCoords");
}

void StandardShader::getAttributes()
{
	m_trans_matrix = ShaderManager::GetInstance()->getVariable("transformationMat");
}

void StandardShader::loadTransformationMatrix(glm::mat4 t_matrix)
{
	ShaderManager::GetInstance()->loadMatrix(m_trans_matrix, t_matrix);
}