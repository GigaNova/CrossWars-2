#pragma once
#include "Singleton.h"
class Model;

class RenderManager : public TSingleton<RenderManager>
{
public:
	RenderManager();
	~RenderManager();

	void renderObject(Model* t_model);
};

