#pragma once
#include <GLM/glm.hpp>
#include <GLEW/glew.h>

class Camera;

class MathHelper
{
public:
	static glm::mat4 createTransformationMatrix(glm::vec3 t_vector, glm::vec3 t_rotation, float t_scale);
	static glm::mat4 createViewMatrix(Camera * t_camera);
	static glm::mat4 createProjectionMatrix();
};

