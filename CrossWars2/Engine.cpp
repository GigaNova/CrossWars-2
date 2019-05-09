#include "Engine.h"
#include "WindowManager.h"
#include <GLEW/glew.h>
#include "ModelManager.h"
#include "ShaderManager.h"
#include "RenderManager.h"
#include "Logger.h"
#include "LightShader.h"
#include "MouseManager.h"
#include "DeltaTime.h"
#include "Color.h"
#include "StaticLight.h"
#include "FlatShader.h"
#include "ColorComponent.h"
#include "LightFlatShader.h"

Engine::Engine()
{
	Logger::GetInstance()->logAction("Starting up...");

	auto windowManager = WindowManager::GetInstance();
	auto modelManager = ModelManager::GetInstance();
	auto shaderManager = ShaderManager::GetInstance();
	auto renderManager = RenderManager::GetInstance();

	Logger::GetInstance()->logAction("All managers initiated.");

	StaticLight light(glm::vec3(0, 1000, 0), Color::fromHex("FBF8E6"));
	m_standard_shader = new LightShader(glm::vec3(0.5f, 0.5f, 0.5f), light);
	m_flat_shader = new LightFlatShader(light);

	m_world = new World();
	m_is_running = true;
}


Engine::~Engine()
{

}

void Engine::getInput()
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			WindowManager::GetInstance()->getCamera()->move(&event.key);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_dragging = true;
			break;
		case SDL_MOUSEMOTION:
			MouseManager::GetInstance()->update();
			if (m_dragging) {
				WindowManager::GetInstance()->getCamera()->rotate(&event.button);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			m_dragging = false;
			break;
		case SDL_QUIT:
			m_is_running = false;;
			break;
		default:
			break;
		}
	}
}

void Engine::update()
{
	m_world->preUpdate();
	m_world->update(DeltaTime::GetInstance()->getDeltaTime());
}

void Engine::render()
{
	auto window = WindowManager::GetInstance()->getRenderWindow();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glViewport(0, 0, 1024, 768);

	for(auto entity : *m_world->getEntities())
	{
		if(entity->getComponent<ColorComponent>())
		{
			RenderManager::GetInstance()->renderEntityFlat(entity, m_flat_shader);
		}
		else 
		{
			RenderManager::GetInstance()->renderEntity(entity, m_standard_shader);
		}
	}

	SDL_GL_SwapWindow(window);
}

void Engine::cleanUp()
{
	WindowManager::GetInstance()->cleanUp();
	ModelManager::GetInstance()->cleanUp();
}

bool Engine::isRunning()
{
	return m_is_running;
}
