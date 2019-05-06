#pragma once
#include <queue>
#include "Component.h"
#include <memory>

class System
{
public:
	System();
	virtual ~System();

	virtual bool canProcessComponent(Component* t_component) = 0;
	virtual void processComponents(double t_delta_time) = 0;

	void addComponent(Component* t_component);
protected:
	std::queue<Component*> m_components;
};

