#pragma once
#include "Singleton.h"
#include <vector>
#include "Component.h"

class ComponentManager : public TSingleton<ComponentManager>
{
public:
	ComponentManager();
	~ComponentManager();

	void registerComponent(Component* t_component);
	void removeComponent(Component* t_component);

	std::vector<Component*>* getComponents();
private:
	std::vector<Component*> m_components;
};

