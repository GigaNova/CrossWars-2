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

	CubeMarcher marcher;
	auto mesh = marcher.generateMesh(200, 200, 200);
	auto texture = ModelManager::GetInstance()->loadTexture("uv.png");
	auto model = new Model(mesh, nullptr);

	BaseEntity* terrain = new BaseEntity();

	terrain->addComponent(new PositionComponent(0, 0, 0));
	terrain->addComponent(new RotationComponent(0, 0, 0));
	terrain->addComponent(new ScaleComponent(1.0));
	terrain->addComponent(new MeshComponent(model));
	terrain->addComponent(new ColorComponent(Color::fromHex("3CB371")));

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
