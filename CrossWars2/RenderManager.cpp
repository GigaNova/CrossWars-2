#include "RenderManager.h"
#include <GLEW/glew.h>
#include "Defines.h"
#include "Model.h"

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

void RenderManager::renderObject(Model* t_model)
{
	auto modelData = t_model->getModelData();
	auto textureData = t_model->getTextureData();

	glBindVertexArray(modelData->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureData->getTextureId());
	glDrawElements(GL_TRIANGLES, modelData->getVertexCount(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}


