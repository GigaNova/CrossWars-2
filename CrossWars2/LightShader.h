#pragma once
#include "StandardShader.h"
#include "GLM/glm.hpp"

class StaticLight;

class LightShader : public StandardShader
{
public:
	LightShader(const glm::vec3 t_ambient_color, const StaticLight& t_light);
	~LightShader();

	glm::vec3 getAmbientColor() const;

protected:
	void bindAttributes() override;
	void getAttributes() override;

	void loadSingleLight(glm::vec3 t_ambient_color, glm::vec3 t_light_pos, glm::vec3 t_light_color);

private:
	glm::vec3 m_ambient_color;
	glm::vec3 m_light_position;
	glm::vec3 m_light_color;


	GLuint m_ambient_color_location;
	GLuint m_light_position_location;
	GLuint m_light_color_location;
};
