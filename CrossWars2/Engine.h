#pragma once
#include "Singleton.h"
#include "ModelManager.h"
#include <GLEW/glew.h>
#include "StandardShader.h"
#include "BaseEntity.h"
#include "World.h"
#include "FlatShader.h"

class Engine : public TSingleton<Engine>
{
public:
	Engine();
	~Engine();

	void getInput();
	void update();
	void render();
	void cleanUp();

	bool isRunning();
private:
	bool m_is_running;

	StandardShader* m_standard_shader;
	FlatShader* m_flat_shader;
	World* m_world;
	bool m_dragging;
};

