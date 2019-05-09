#include "PhysicsSystem.h"
#include "RotationComponent.h"
#include <iostream>

PhysicsSystem::PhysicsSystem()
{
}


PhysicsSystem::~PhysicsSystem()
{
}

bool PhysicsSystem::canProcessComponent(Component* t_component)
{
	const auto t = dynamic_cast<RotationComponent*>(t_component);
	return t != nullptr;
}

void PhysicsSystem::processComponents(double t_delta_time)
{
	while(!m_components.empty())
	{
		auto component = dynamic_cast<RotationComponent*>(m_components.front());
		component->increaseRotation(glm::vec3(100.f * t_delta_time, 0, 100.f * t_delta_time));
		m_components.pop();
	}
}
