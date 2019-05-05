#include "Engine.h"
#include "WindowManager.h"
#include <GLEW/glew.h>
#include "ModelManager.h"
#include "Defines.h"
#include "ShaderManager.h"
#include "RenderManager.h"
#include "Logger.h"
#include "LightShader.h"
#include "MouseManager.h"
#include "DeltaTime.h"
#include "PositionComponent.h"
#include "RotationComponent.h"
#include "MeshComponent.h"
#include "ScaleComponent.h"

Engine::Engine()
{
	Logger::GetInstance()->logAction("Starting up...");

	auto windowManager = WindowManager::GetInstance();
	auto modelManager = ModelManager::GetInstance();
	auto shaderManager = ShaderManager::GetInstance();
	auto renderManager = RenderManager::GetInstance();

	Logger::GetInstance()->logAction("All managers initiated.");

	m_shader = new LightShader(glm::vec3(1.0, 1.0, 0.5));

	m_model = modelManager->loadModel();

	m_entity = new BaseEntity();
	m_entity->addComponent(std::make_shared<PositionComponent>(0, 0, -10.f));
	m_entity->addComponent(std::make_shared<RotationComponent>(0, 0, 0));
	m_entity->addComponent(std::make_shared<ScaleComponent>(1.0f));
	m_entity->addComponent(std::make_shared<MeshComponent>(m_model));

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
	m_entity->getComponent<RotationComponent>()->increaseRotation(glm::vec3(0, 1, 0));
}

void Engine::render()
{
	auto window = WindowManager::GetInstance()->getRenderWindow();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glViewport(0, 0, 512, 512);

	RenderManager::GetInstance()->renderEntity(m_entity, m_shader);

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
