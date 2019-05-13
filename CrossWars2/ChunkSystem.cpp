#include "ChunkSystem.h"
#include "WindowManager.h"

ChunkSystem::ChunkSystem(ChunkManager* t_chunk_manager) : m_chunk_manager(t_chunk_manager), m_counter(0)
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
	m_counter += t_delta_time;
	if(m_counter > UPDATE_INTERVAL)
	{
		const auto cameraPos = WindowManager::GetInstance()->getCamera()->getPosition();

		int x = 0;
		int z = 0;

		if (cameraPos.x < 0)
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

		for (int i = x - (VIEW_DISTANCE / 2); i < x + (VIEW_DISTANCE / 2); ++i)
		{
			for (int j = z - (VIEW_DISTANCE / 2); j < z + (VIEW_DISTANCE / 2); ++j)
			{
				if (!m_chunk_manager->chunkExists(i, j))
				{
					m_chunk_manager->createChunk(i * ChunkData::CHUNK_SIZE_X, 0, j * ChunkData::CHUNK_SIZE_Z, ChunkData::CHUNK_SIZE_X, ChunkData::CHUNK_SIZE_Y, ChunkData::CHUNK_SIZE_Z);
				}
			}
		}

		m_counter = 0;
	}
}
