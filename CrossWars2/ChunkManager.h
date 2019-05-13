#pragma once
#include "CubeMarcher.h"
#include "ThreadPool.h"
#include <map>
#include "concurrentqueue.h"

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

	void createChunk(int t_offset_x, int t_offset_y, int t_offset_z, int t_width, int t_height, int t_depth);
	CubeTerrain* handleChunk(TerrainChunk* t_chunk);

	bool chunkExists(int t_x, int t_z);
	moodycamel::ConcurrentQueue<TerrainChunk*>* getChunkQueue();
	void cleanChunks();
private:
	int m_world_seed;

	ThreadPool m_thread_pool;

	std::vector<TerrainChunk*> m_new_chunks;
	std::vector<CubeTerrain*> m_chunks;
	std::vector<glm::vec2> m_jobs;

	std::mutex m_lock;

	moodycamel::ConcurrentQueue<TerrainChunk*> m_terrain_queue;
};

