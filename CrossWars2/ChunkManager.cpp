#include "ChunkManager.h"
#include "ScaleComponent.h"
#include "ColorComponent.h"
#include "PositionComponent.h"
#include "RotationComponent.h"
#include "Color.h"
#include "MeshComponent.h"
#include "ModelManager.h"

ChunkManager::ChunkManager() : m_thread_pool(std::thread::hardware_concurrency())
{
	m_world_seed = time(nullptr);
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::createChunk(int t_offset_x, int t_offset_y, int t_offset_z, int t_width, int t_height, int t_depth)
{
	auto futureChunk = m_thread_pool.addTask([=]
	{
		CubeMarcher marcher(m_world_seed);
		auto chunk = marcher.generateChunk(t_offset_x, t_offset_y, t_offset_z, t_width, t_height, t_depth);
		m_new_chunks.push_back(chunk);
	});

	const int x = floor(t_offset_x / t_width);
	const int z = floor(t_offset_z / t_depth);

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

std::vector<TerrainChunk*> ChunkManager::getNewChunks()
{
	auto vector = m_new_chunks;
	m_new_chunks.clear();
	return vector;
}
