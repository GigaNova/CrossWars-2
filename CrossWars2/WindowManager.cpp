#include "WindowManager.h"
#include <SDL/SDL.h>
#include "SDLHelpers.h"
#include <GLEW/glew.h>
#include "ModelData.h"

WindowManager::WindowManager()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDLHelpers::printSDLError("Unable to initialize.");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	m_main_window = SDL_CreateWindow(game_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDLHelpers::checkSDLError(__LINE__);

	m_main_context = SDL_GL_CreateContext(m_main_window);
	SDLHelpers::checkSDLError(__LINE__);

	SDL_GL_SetSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glewExperimental = GL_TRUE;
	glewInit();
}


WindowManager::~WindowManager()
{
}

void WindowManager::renderObject(ModelData* t_model_data)
{
	glBindVertexArray(t_model_data->getVaoId());
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, t_model_data->getVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
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
