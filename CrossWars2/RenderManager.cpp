#include "RenderManager.h"
#include <GLEW/glew.h>
#include "Defines.h"
#include "BaseEntity.h"
#include "MathHelper.h"
#include "ShaderManager.h"
#include "StandardShader.h"
#include "WindowManager.h"
#include "PositionComponent.h"
#include "RotationComponent.h"
#include "ScaleComponent.h"
#include "MeshComponent.h"
#include "ColorComponent.h"

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

void RenderManager::renderEntity(BaseEntity* t_entity, StandardShader* t_shader)
{
	auto model = t_entity->getComponent<MeshComponent>()->getModel();
	auto modelData = model->getModelData();
	auto textureData = model->getTextureData();

	glUseProgram(t_shader->getProgramId());
	glBindVertexArray(modelData->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	auto transformationMatrix = MathHelper::createTransformationMatrix(
		t_entity->getComponent<PositionComponent>()->getPosition(), 
		t_entity->getComponent<RotationComponent>()->getRotation(),
		t_entity->getComponent<ScaleComponent>()->getScale()
	);
	t_shader->loadTransformationMatrix(transformationMatrix);
	t_shader->loadProjectionMatrix(MathHelper::createProjectionMatrix());
	t_shader->loadViewMatrix(MathHelper::createViewMatrix(WindowManager::GetInstance()->getCamera()));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureData->getTextureId());
	glDrawElements(GL_TRIANGLES, modelData->getVertexCount(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);

	glUseProgram(0);
}

void RenderManager::renderEntityFlat(BaseEntity* t_entity, FlatShader* t_shader)
{
	auto model = t_entity->getComponent<MeshComponent>()->getModel();
	auto modelData = model->getModelData();

	glUseProgram(t_shader->getProgramId());
	glBindVertexArray(modelData->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	auto transformationMatrix = MathHelper::createTransformationMatrix(
		t_entity->getComponent<PositionComponent>()->getPosition(),
		t_entity->getComponent<RotationComponent>()->getRotation(),
		t_entity->getComponent<ScaleComponent>()->getScale()
	);
	t_shader->loadTransformationMatrix(transformationMatrix);
	t_shader->loadProjectionMatrix(MathHelper::createProjectionMatrix());
	t_shader->loadViewMatrix(MathHelper::createViewMatrix(WindowManager::GetInstance()->getCamera()));
	t_shader->loadColor(t_entity->getComponent<ColorComponent>()->getColor());

	glDrawArrays(GL_TRIANGLES, 0, modelData->getVertexCount());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);

	glUseProgram(0);
}
