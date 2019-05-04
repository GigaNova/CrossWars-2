#pragma once
#include "StandardShader.h"
#include "GLM/glm.hpp"

class LightShader : public StandardShader
{
public:
	LightShader(glm::vec3 t_ambient_color);
	~LightShader();

	glm::vec3 getAmbientColor() const;

protected:
	void getAttributes() override;

	void loadAmbientColor(glm::vec3 t_ambient_color);

private:
	glm::vec3 m_ambient_color;
	GLint m_ambient_color_location;
};