#include "RenderManager.h"
#include <GLEW/glew.h>
#include "Defines.h"
#include "BaseEntity.h"
#include "MathHelper.h"
#include "ShaderManager.h"
#include "StandardShader.h"
#include "WindowManager.h"

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

void RenderManager::renderEntity(BaseEntity* t_entity, StandardShader* t_shader)
{
	auto model = t_entity->getModel();
	auto modelData = model->getModelData();
	auto textureData = model->getTextureData();

	glBindVertexArray(modelData->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	auto transformationMatrix = MathHelper::createTransformationMatrix(
		t_entity->getPosition(), 
		t_entity->getRotation(), 
		t_entity->getScale()
	);
	t_shader->loadTransformationMatrix(transformationMatrix);
	t_shader->loadProjectionMatrix(MathHelper::createProjectionMatrix());
	t_shader->loadViewMatrix(MathHelper::createViewMatrix(WindowManager::GetInstance()->getCamera()));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureData->getTextureId());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glDrawElements(GL_TRIANGLES, modelData->getVertexCount(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

