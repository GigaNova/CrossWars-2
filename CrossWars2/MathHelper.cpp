#include "MathHelper.h"
#include <GLM/ext.hpp>


glm::mat4 MathHelper::createTransformationMatrix(glm::vec3 t_vector, GLfloat t_rx, GLfloat t_ry, GLfloat t_rz, float t_scale)
{
	glm::mat4 matrix;
	matrix = translate(matrix, t_vector);
	matrix = rotate(matrix, (float)glm::radians(t_rx), glm::vec3(1, 0, 0));
	matrix = rotate(matrix, (float)glm::radians(t_ry), glm::vec3(0, 1, 0));
	matrix = rotate(matrix, (float)glm::radians(t_rz), glm::vec3(0, 0, 1));
	matrix = scale(matrix, glm::vec3(t_scale, t_scale, t_scale));
	return matrix;
}
