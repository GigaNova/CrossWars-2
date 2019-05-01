#pragma once
#include <GLM/glm.hpp>
#include <GLEW/glew.h>

class MathHelper
{
public:
	static glm::mat4 createTransformationMatrix(glm::vec3 t_vector, GLfloat t_rx, GLfloat t_ry, GLfloat t_rz, float t_scale);
};

