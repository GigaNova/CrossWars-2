#include "WindowManager.h"
#include <SDL/SDL.h>
#include "SDLHelpers.h"
#include <GLEW/glew.h>
#include "ModelData.h"
#include "Defines.h"

WindowManager::WindowManager()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDLHelpers::printSDLError("Unable to initialize.");
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

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

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

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
