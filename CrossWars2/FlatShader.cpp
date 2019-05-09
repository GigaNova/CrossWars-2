#include "FlatShader.h"
#include <GLM/vec3.hpp>
#include "ShaderManager.h"

FlatShader::FlatShader() : ProtoShader("flatVertex.vert", "flatFragment.frag")
{
	FlatShader::bindAttributes();
	FlatShader::getAttributes();
}

FlatShader::~FlatShader()
{
}

void FlatShader::bindAttributes()
{
	ShaderManager::GetInstance()->bindAttribute(0, "position");
}

void FlatShader::getAttributes()
{
	m_trans_matrix = ShaderManager::GetInstance()->getVariable("transformationMatrix");
	m_proj_matrix = ShaderManager::GetInstance()->getVariable("projectionMatrix");
	m_view_matrix = ShaderManager::GetInstance()->getVariable("viewMatrix");
	m_color = ShaderManager::GetInstance()->getVariable("color");
}

void FlatShader::loadTransformationMatrix(glm::mat4 t_matrix)
{
	ShaderManager::GetInstance()->loadMatrix(m_trans_matrix, t_matrix);
}

void FlatShader::loadProjectionMatrix(glm::mat4 t_matrix)
{
	ShaderManager::GetInstance()->loadMatrix(m_proj_matrix, t_matrix);
}

void FlatShader::loadViewMatrix(glm::mat4 t_matrix)
{
	ShaderManager::GetInstance()->loadMatrix(m_view_matrix, t_matrix);
}

void FlatShader::loadColor(glm::vec3 t_color)
{
	ShaderManager::GetInstance()->loadVector(m_color, t_color);
}