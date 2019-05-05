#pragma once
#include "Component.h"
#include <unordered_map>
#include <typeindex>
#include <memory>

class BaseEntity
{
public:
	BaseEntity();
	~BaseEntity();

	void addComponent(std::shared_ptr<Component> t_component);

	template<typename T>
	std::shared_ptr<T> getComponent()
	{
		if(m_components.find(typeid(T)) == m_components.end())
		{
			return nullptr;
		}

		return std::dynamic_pointer_cast<T>(m_components[typeid(T)]);
	}
private:
	unsigned int id;

	std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
};

