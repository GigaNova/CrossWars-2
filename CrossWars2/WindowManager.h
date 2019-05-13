#pragma once
#include <SDL/SDL.h>
#include "Singleton.h"
#include "Camera.h"

class WindowManager : public TSingleton<WindowManager>
{
public:
	WindowManager();
	~WindowManager();

	void cleanUp();

	Camera* getCamera();
	SDL_Window* getRenderWindow();
private:
	const char* m_game_name = "Truce of Twilight";

	Camera* m_camera;

	SDL_Window* m_main_window;
	SDL_GLContext m_main_context;
};

