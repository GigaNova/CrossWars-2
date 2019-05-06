#pragma once
#include "Component.h"
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "Logger.h"
#include <string>

class BaseEntity
{
public:
	BaseEntity();
	~BaseEntity();

	void addComponent(Component* t_component);

	template<typename T>
	T* getComponent()
	{
		if(m_components.find(typeid(T)) == m_components.end())
		{
			return nullptr;
		}

		return dynamic_cast<T*>(m_components[typeid(T)]);
	}

	std::unordered_map<std::type_index, Component*>* getComponents();
private:
	unsigned int m_id;

	std::unordered_map<std::type_index, Component*> m_components;
};

