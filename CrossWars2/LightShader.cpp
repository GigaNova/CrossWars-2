#include "LightShader.h"
#include "ShaderManager.h"
#include "StaticLight.h"

LightShader::LightShader(const glm::vec3 t_ambient_color, const StaticLight& t_light) : StandardShader(), m_ambient_color(t_ambient_color), m_light_position(t_light.getPosition()), m_light_color(t_light.getColor())
{
	LightShader::bindAttributes();
	LightShader::getAttributes();
	loadSingleLight(m_ambient_color, m_light_position, m_light_color);
}

LightShader::~LightShader()
{
}

glm::vec3 LightShader::getAmbientColor() const
{
	return m_ambient_color;
}

void LightShader::bindAttributes()
{
	ShaderManager::GetInstance()->bindAttribute(2, "normal");
}

void LightShader::getAttributes()
{
	m_ambient_color_location = ShaderManager::GetInstance()->getVariable("ambientColor");
	m_light_position_location = ShaderManager::GetInstance()->getVariable("lightPosition");
	m_light_color_location = ShaderManager::GetInstance()->getVariable("lightColor");
}

void LightShader::loadSingleLight(glm::vec3 t_ambient_color, glm::vec3 t_light_pos, glm::vec3 t_light_color)
{
	ShaderManager::GetInstance()->loadVector(m_ambient_color_location, t_ambient_color);
	ShaderManager::GetInstance()->loadVector(m_light_position_location, t_light_pos);
	ShaderManager::GetInstance()->loadVector(m_light_color_location, t_light_color);
}