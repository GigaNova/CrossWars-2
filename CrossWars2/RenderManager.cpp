#include "RenderManager.h"
#include <GLEW/glew.h>
#include "Defines.h"
#include "ModelData.h"

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

void RenderManager::renderObject(ModelData* t_model_data)
{
	glBindVertexArray(t_model_data->getVaoId());
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, t_model_data->getVertexCount(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}


