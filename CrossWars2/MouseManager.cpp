#include "MouseManager.h"
#include <SDL/SDL.h>

MouseManager::MouseManager() : m_prev_mouse_x(0), m_prev_mouse_y(0), m_mouse_delta_x(0), m_mouse_delta_y(0)
{
}


MouseManager::~MouseManager()
{
}

void MouseManager::update()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	m_mouse_delta_x = m_prev_mouse_x - mouseX;
	m_mouse_delta_y = m_prev_mouse_y - mouseY;

	m_prev_mouse_x = mouseX;
	m_prev_mouse_y = mouseY;
}

glm::vec2 MouseManager::getMouseDelta() const
{
	return glm::vec2(m_mouse_delta_x, m_mouse_delta_y);
}
