#include "StandardShader.h"
#include "ShaderManager.h"

StandardShader::StandardShader() : ProtoShader("vertexShader.vert", "fragmentshader.frag")
{
	getAttributes();
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
	m_trans_matrix = ShaderManager::GetInstance()->getVariable("transformationMatrix");
	m_proj_matrix = ShaderManager::GetInstance()->getVariable("projectionMatrix");
	m_view_matrix = ShaderManager::GetInstance()->getVariable("viewMatrix");
}

void StandardShader::loadTransformationMatrix(glm::mat4 t_matrix)
{
	ShaderManager::GetInstance()->loadMatrix(m_trans_matrix, t_matrix);
}

void StandardShader::loadProjectionMatrix(glm::mat4 t_matrix)
{
	ShaderManager::GetInstance()->loadMatrix(m_proj_matrix, t_matrix);
}

void StandardShader::loadViewMatrix(glm::mat4 t_matrix)
{
	ShaderManager::GetInstance()->loadMatrix(m_view_matrix, t_matrix);
}