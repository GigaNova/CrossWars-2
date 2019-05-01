#pragma once
#include "Singleton.h"
class ModelData;

class RenderManager : public TSingleton<RenderManager>
{
public:
	RenderManager();
	~RenderManager();

	void renderObject(ModelData* t_model_data);
};

