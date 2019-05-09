#pragma once
#include <GLEW/glew.h>
#include <GLM/vec3.hpp>
#include "FlatShader.h"

class StaticLight;

class LightFlatShader : public FlatShader
{
public:
	LightFlatShader(const StaticLight& t_light);
	~LightFlatShader();

	void loadSingleLight(glm::vec3 t_light_pos);
protected:
	void bindAttributes() override;
	void getAttributes() override;

private:
	glm::vec3 m_light_position;

	GLuint m_light_position_location;
};

