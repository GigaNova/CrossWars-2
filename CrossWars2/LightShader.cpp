#include "LightShader.h"
#include "ShaderManager.h"

LightShader::LightShader(const glm::vec3 t_ambient_color) : StandardShader(), m_ambient_color(t_ambient_color)
{
	getAttributes();
	loadAmbientColor(m_ambient_color);
}

LightShader::~LightShader()
{
}

glm::vec3 LightShader::getAmbientColor() const
{
	return m_ambient_color;
}

void LightShader::getAttributes()
{
	m_ambient_color_location = ShaderManager::GetInstance()->getVariable("ambientColor");
}

void LightShader::loadAmbientColor(glm::vec3 t_ambient_color)
{
	ShaderManager::GetInstance()->loadVector(m_ambient_color_location, t_ambient_color);
}