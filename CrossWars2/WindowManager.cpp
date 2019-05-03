#include "WindowManager.h"
#include <SDL/SDL.h>
#include "SDLHelpers.h"
#include <GLEW/glew.h>
#include "ModelData.h"
#include "Defines.h"
#include "Logger.h"

WindowManager::WindowManager()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDLHelpers::printSDLError("Unable to initialize.");
	}

	Logger::GetInstance()->logAction("SDL initialised.");

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

	m_main_window = SDL_CreateWindow(game_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDLHelpers::checkSDLError(__LINE__);

	m_main_context = SDL_GL_CreateContext(m_main_window);
	SDLHelpers::checkSDLError(__LINE__);

	SDL_GL_MakeCurrent(m_main_window, m_main_context);

	Logger::GetInstance()->logAction("OpenGL Context and Window created.");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BACK);

	glewExperimental = GL_TRUE;
	glewInit();

	Logger::GetInstance()->logAction("GLEW initialised.");

	m_camera = new Camera();
}


WindowManager::~WindowManager()
{
}

void WindowManager::cleanUp()
{
	SDL_GL_DeleteContext(m_main_context);
	SDL_DestroyWindow(m_main_window);
	SDL_Quit();
}

SDL_Window* WindowManager::getRenderWindow()
{
	return m_main_window;
}

Camera* WindowManager::getCamera()
{
	return m_camera;
}
