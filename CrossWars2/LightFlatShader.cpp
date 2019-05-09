#include "LightFlatShader.h"
#include "StandardShader.h"
#include "StaticLight.h"
#include "ShaderManager.h"

LightFlatShader::LightFlatShader(const StaticLight& t_light) : FlatShader(), m_light_position(t_light.getPosition())
{
	LightFlatShader::bindAttributes();
	LightFlatShader::getAttributes();
	loadSingleLight(m_light_position);
}


LightFlatShader::~LightFlatShader()
{
}

void LightFlatShader::bindAttributes()
{
	ShaderManager::GetInstance()->bindAttribute(1, "normal");
}


void LightFlatShader::getAttributes()
{
	m_light_position_location = ShaderManager::GetInstance()->getVariable("lightPosition");
}

void LightFlatShader::loadSingleLight(glm::vec3 t_light_pos)
{
	ShaderManager::GetInstance()->loadVector(m_light_position_location, t_light_pos);
}