#pragma once
#include "Singleton.h"
#include <vector>
#include "FlatShader.h"

class BaseEntity;
class StandardShader;

class RenderManager : public TSingleton<RenderManager>
{
public:
	RenderManager();
	~RenderManager();

	void bindFrameBuffer(const GLuint t_buffer_fbo, const GLuint t_buffer_texture);
	void unbindFrameBuffer();

	void renderEntity(BaseEntity* t_entity, StandardShader* t_shader);
	void renderEntityFlat(BaseEntity* t_entity, FlatShader* t_shader);
};

