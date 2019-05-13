#include "TerrainChunk.h"
#include "Logger.h"
#include <string>
#include "ChunkData.h"

TerrainChunk::TerrainChunk(ChunkData* t_chunk_mesh, const ScalarField& t_scalar_field, const glm::vec3& t_chunk_position) : m_scalar_field(t_scalar_field), m_position(t_chunk_position), m_mesh(t_chunk_mesh)
{
	static int id = 0;
	++id;
	Logger::GetInstance()->logAction("Chunk #" + std::to_string(id) + " generated.");
}

TerrainChunk::~TerrainChunk()
{
}

ScalarField TerrainChunk::getScalarField() const
{
	return m_scalar_field;
}

glm::vec3 TerrainChunk::getPosition() const
{
	return m_position;
}

ChunkData* TerrainChunk::getModelData()
{
	return m_mesh;
}
