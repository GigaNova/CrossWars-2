#pragma once
#include <SDL/SDL.h>
#include "Singleton.h"

class ModelData;

class WindowManager : public TSingleton<WindowManager>
{
public:
	WindowManager();
	~WindowManager();

	void renderObject(ModelData* t_model_data);
	void cleanUp();

	SDL_Window* getRenderWindow();
private:
	const char* game_name = "Cross Wars 2";

	SDL_Window* m_main_window;
	SDL_GLContext m_main_context;
};

