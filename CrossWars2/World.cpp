#include "World.h"
#include "ComponentManager.h"
#include "ModelManager.h"
#include "MeshComponent.h"
#include "ScaleComponent.h"
#include "RotationComponent.h"
#include "PositionComponent.h"
#include "PhysicsSystem.h"
#include "SphereFactory.h"
#include "CubeMarcher.h"
#include "ColorComponent.h"
#include "Color.h"

World::World()
{	
	/*SphereFactory factory;
	for(int i = 0; i < 100; ++i)
	{
		auto sphere = factory.makeSphere();
		m_entity_vector.push_back(sphere);
	}*/

	m_cube_marcher = new CubeMarcher();
	auto terrain = m_cube_marcher->generateChunk(0, 0, 0, 200, 200, 200);

	terrain->addComponent(new PositionComponent(0, 0, 0));
	terrain->addComponent(new RotationComponent(0, 0, 0));
	terrain->addComponent(new ScaleComponent(2.0));
	terrain->addComponent(new ColorComponent(Color::fromHex("90EE90")));

	m_entity_vector.push_back(terrain);

	//m_system_vector.push_back(new PhysicsSystem());
}

World::~World()
{
}

void World::preUpdate()
{
	for(auto component : *ComponentManager::GetInstance()->getComponents())
	{
		for (System* system : m_system_vector)
		{
			if(system->canProcessComponent(component))
			{
				system->addComponent(component);
			}
		}
	}
}

void World::update(double t_delta_time)
{
	for (System* system : m_system_vector)
	{
		system->processComponents(t_delta_time);
	}
}

std::vector<BaseEntity*>* World::getEntities()
{
	return &m_entity_vector;
}
