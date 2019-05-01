#pragma once
#include "Singleton.h"
#include "ModelManager.h"
#include <GLEW/glew.h>

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
	Model* m_model;
};

