#define GLM_FORCE_CTOR_INIT
#include "MathHelper.h"
#include <GLM/ext.hpp>
#include "Camera.h"
#include <GLM/gtx/euler_angles.hpp> 

glm::mat4 MathHelper::createTransformationMatrix(glm::vec3 t_vector, glm::vec3 t_rotation, float t_scale)
{
	glm::mat4 matrix;
	matrix = translate(matrix, t_vector);
	matrix *= glm::eulerAngleYXZ(glm::radians(t_rotation.y), glm::radians(t_rotation.x), glm::radians(t_rotation.z));
	matrix = scale(matrix, glm::vec3(t_scale, t_scale, t_scale));
	return matrix;
}

glm::mat4 MathHelper::createViewMatrix(Camera* t_camera)
{
	const glm::mat4 transformationMatrix = createTransformationMatrix(t_camera->getPosition(), t_camera->getRotation(), 1);
	return lookAt(t_camera->getPosition(), t_camera->getPosition() + getForward(transformationMatrix), getUp(transformationMatrix));
}

glm::mat4 MathHelper::createProjectionMatrix()
{
	return glm::perspective(Camera::FOV, Camera::AspectRatio(), Camera::NEAR_PLANE, Camera::FAR_PLANE);
}

glm::vec3 MathHelper::getForward(const glm::mat4& t_transformation)
{
	return glm::vec3(t_transformation * glm::vec4(0, 0, 1, 0));
}

glm::vec3 MathHelper::getUp(const glm::mat4& t_transformation)
{
	return glm::vec3(t_transformation * glm::vec4(0, 1, 0, 0));
}