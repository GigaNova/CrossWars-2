#include "ChunkSystem.h"
#include "WindowManager.h"

ChunkSystem::ChunkSystem(ChunkManager* t_chunk_manager) : m_chunk_manager(t_chunk_manager)
{
}


ChunkSystem::~ChunkSystem()
{
}

bool ChunkSystem::canProcessComponent(Component* t_component)
{
	return false;
}

void ChunkSystem::processComponents(double t_delta_time)
{
	const auto cameraPos = WindowManager::GetInstance()->getCamera()->getPosition();

	int x = 0;
	int z = 0;

	if(cameraPos.x < 0)
	{
		x = ceil(cameraPos.x / ChunkData::CHUNK_SIZE_X / ChunkData::CHUNK_SCALE);
	}
	{
		x = floor(cameraPos.x / ChunkData::CHUNK_SIZE_X / ChunkData::CHUNK_SCALE);
	}
	
	if (cameraPos.z < 0)
	{
		z = ceil(cameraPos.z / ChunkData::CHUNK_SIZE_Z / ChunkData::CHUNK_SCALE);
	}
	{
		z = floor(cameraPos.z / ChunkData::CHUNK_SIZE_Z / ChunkData::CHUNK_SCALE);
	}

	if(!m_chunk_manager->chunkExists(x, z))
	{
		m_chunk_manager->createChunk(x * ChunkData::CHUNK_SIZE_X, 0, z * ChunkData::CHUNK_SIZE_Z, ChunkData::CHUNK_SIZE_X, ChunkData::CHUNK_SIZE_Y, ChunkData::CHUNK_SIZE_Z);
	}
}
