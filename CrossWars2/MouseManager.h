#pragma once
#include <GLM/vec2.hpp>
#include "Singleton.h"

class MouseManager : public TSingleton<MouseManager>
{
public:
	MouseManager();
	~MouseManager();

	void update();

	glm::vec2 getMouseDelta() const;
private:
	int m_prev_mouse_x;
	int m_prev_mouse_y;

	float m_mouse_delta_x;
	float m_mouse_delta_y;
};

