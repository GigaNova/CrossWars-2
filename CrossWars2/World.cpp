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
#include "ChunkManager.h"
#include "ChunkSystem.h"
#include "RenderSystem.h"

World::World()
{	
	SphereFactory factory;
	for(int i = 0; i < 100; ++i)
	{
		auto sphere = factory.makeSphere();
		m_entity_vector.push_back(sphere);
	}

	for (int i = -5; i < 5; ++i)
	{
		for (int j = -5; j < 5; ++j)
		{
			m_chunk_manager.createChunk(i * ChunkData::CHUNK_SIZE_X, 0, j * ChunkData::CHUNK_SIZE_Z, ChunkData::CHUNK_SIZE_X, ChunkData::CHUNK_SIZE_Y, ChunkData::CHUNK_SIZE_Z);
		}
	}

	//m_system_vector.push_back(new PhysicsSystem());
	m_system_vector.push_back(new ChunkSystem(&m_chunk_manager));
	m_system_vector.push_back(new RenderSystem());
}

World::~World()
{
}

void World::preUpdate()
{
	for(auto chunk : m_chunk_manager.getNewChunks())
	{
		const auto newChunk = m_chunk_manager.handleChunk(chunk);
		m_entity_vector.push_back(newChunk);
	}

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

void World::postUpdate()
{
	m_chunk_manager.cleanChunks();
}

std::vector<BaseEntity*>* World::getEntities()
{
	return &m_entity_vector;
}
