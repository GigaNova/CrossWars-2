#define GLM_FORCE_CTOR_INIT
#include "MathHelper.h"
#include <GLM/ext.hpp>
#include "Camera.h"


glm::mat4 MathHelper::createTransformationMatrix(glm::vec3 t_vector, glm::vec3 t_rotation, float t_scale)
{
	glm::mat4 matrix;
	matrix = translate(matrix, t_vector);
	matrix = rotate(matrix, (float)glm::radians(t_rotation.x), glm::vec3(1, 0, 0));
	matrix = rotate(matrix, (float)glm::radians(t_rotation.y), glm::vec3(0, 1, 0));
	matrix = rotate(matrix, (float)glm::radians(t_rotation.z), glm::vec3(0, 0, 1));
	matrix = scale(matrix, glm::vec3(t_scale, t_scale, t_scale));
	return matrix;
}

glm::mat4 MathHelper::createViewMatrix(Camera* t_camera)
{
	glm::mat4 ViewMatrix;
	ViewMatrix = rotate(ViewMatrix, glm::radians(t_camera->getPitch()), glm::vec3(1, 0, 0));
	ViewMatrix = rotate(ViewMatrix, glm::radians(t_camera->getYaw()), glm::vec3(0, 1, 0));
	ViewMatrix = translate(ViewMatrix, glm::vec3(-t_camera->getPosition().x, -t_camera->getPosition().y, -t_camera->getPosition().z));
	return ViewMatrix;
}

glm::mat4 MathHelper::createProjectionMatrix()
{
	GLfloat aspectRatio = static_cast<float>(512.f / 512.f);
	GLfloat yScale = static_cast<float>(1.0f / tan(glm::radians(Camera::FOV / 2.0f)) * aspectRatio);
	GLfloat xScale = yScale / aspectRatio;
	GLfloat frustum = Camera::FAR_PLANE - Camera::NEAR_PLANE;

	glm::mat4 projectionMatrix;

	projectionMatrix[0][0] = xScale;
	projectionMatrix[1][1] = yScale;
	projectionMatrix[2][2] = -((Camera::FAR_PLANE + Camera::NEAR_PLANE) / frustum);
	projectionMatrix[2][3] = -1;
	projectionMatrix[3][2] = -(2 * Camera::NEAR_PLANE * Camera::FAR_PLANE / frustum);
	projectionMatrix[3][3] = 0;

	return projectionMatrix;
}
