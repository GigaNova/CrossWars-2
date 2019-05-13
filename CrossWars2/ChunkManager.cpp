#include "ChunkManager.h"
#include "ScaleComponent.h"
#include "ColorComponent.h"
#include "PositionComponent.h"
#include "RotationComponent.h"
#include "Color.h"
#include "MeshComponent.h"
#include "ModelManager.h"
#include "ChunkSystem.h"
#include "WindowManager.h"

ChunkManager::ChunkManager() : m_thread_pool(std::thread::hardware_concurrency())
{
	m_world_seed = time(nullptr);
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::createChunk(int t_offset_x, int t_offset_y, int t_offset_z, int t_width, int t_height, int t_depth)
{
	const int x = floor(t_offset_x / t_width);
	const int z = floor(t_offset_z / t_depth);

	auto futureChunk = m_thread_pool.addTask([=]
	{
		CubeMarcher marcher(m_world_seed);
		auto chunk = marcher.generateChunk(t_offset_x, t_offset_y, t_offset_z, t_width, t_height, t_depth);

		m_terrain_queue.enqueue(chunk);
	});

	m_jobs.push_back(glm::vec2(x, z));
}

CubeTerrain* ChunkManager::handleChunk(TerrainChunk* t_chunk)
{
	auto terrain = new CubeTerrain(t_chunk->getScalarField(), t_chunk->getPosition());

	terrain->addComponent(new PositionComponent(0, 0, 0));
	terrain->addComponent(new RotationComponent(0, 0, 0));
	terrain->addComponent(new ScaleComponent(ChunkData::CHUNK_SCALE));

	auto mesh = ModelManager::GetInstance()->loadModelToVao(t_chunk->getModelData()->getVertices(), t_chunk->getModelData()->getNormals());

	terrain->addComponent(new MeshComponent(mesh));
	terrain->addComponent(new ColorComponent(Color::fromHex("C2B280")));

	delete t_chunk;

	m_chunks.push_back(terrain);

	return terrain;
}

bool ChunkManager::chunkExists(int t_x, int t_z)
{
	for (auto job : m_jobs)
	{
		if (job.x == t_x && job.y == t_z)
		{
			return true;
		}
	}

	t_x *= ChunkData::CHUNK_SIZE_X;
	t_z *= ChunkData::CHUNK_SIZE_Z;

	for(auto chunk : m_chunks)
	{
		auto offset = chunk->getOffset();
		if(
			offset.x > t_x && offset.y > t_z &&
			offset.x < t_x + ChunkData::CHUNK_SIZE_X &&
			offset.y < t_z + ChunkData::CHUNK_SIZE_Z
		)
		{
			return true;
		}
	}

	return false;
}

moodycamel::ConcurrentQueue<TerrainChunk*>* ChunkManager::getChunkQueue()
{
	return &m_terrain_queue;
}

void ChunkManager::cleanChunks()
{
	const auto cameraPos = WindowManager::GetInstance()->getCamera()->getPosition();

	int cameraX = 0;
	int cameraZ = 0;

	if (cameraPos.x < 0)
	{
		cameraX = ceil(cameraPos.x / ChunkData::CHUNK_SIZE_X / ChunkData::CHUNK_SCALE);
	}
	{
		cameraX = floor(cameraPos.x / ChunkData::CHUNK_SIZE_X / ChunkData::CHUNK_SCALE);
	}

	if (cameraPos.z < 0)
	{
		cameraZ = ceil(cameraPos.z / ChunkData::CHUNK_SIZE_Z / ChunkData::CHUNK_SCALE);
	}
	{
		cameraZ = floor(cameraPos.z / ChunkData::CHUNK_SIZE_Z / ChunkData::CHUNK_SCALE);
	}

	for(auto it = m_chunks.begin(); it != m_chunks.end(); ++it)
	{
		const auto offset = (*it)->getOffset();

		const int chunkX = floor(offset.x / ChunkData::CHUNK_SIZE_X);
		const int chunkZ = floor(offset.z / ChunkData::CHUNK_SIZE_Z);

		const int dist = sqrt(pow(chunkX - cameraX, 2) + pow(chunkZ - cameraZ, 2));

		std::cout << dist << std::endl;

		if(dist >= ChunkSystem::VIEW_DISTANCE * 2)
		{
			delete (*it);
			m_chunks.erase(it);
			m_jobs.erase(std::remove(m_jobs.begin(), m_jobs.end(), glm::vec2(chunkX, chunkZ)), m_jobs.end());
		}
	}
}
