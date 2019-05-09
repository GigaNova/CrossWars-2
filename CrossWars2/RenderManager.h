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

	void renderEntity(BaseEntity* t_entity, StandardShader* t_shader);
	void renderEntityFlat(BaseEntity* t_entity, FlatShader* t_shader);
};

