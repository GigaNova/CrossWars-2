#pragma once
#include "Singleton.h"

class StandardShader;
class BaseEntity;

class RenderManager : public TSingleton<RenderManager>
{
public:
	RenderManager();
	~RenderManager();

	void renderEntity(BaseEntity* t_entity, StandardShader* t_shader);
};

