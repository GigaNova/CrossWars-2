#pragma once
#include <GLM/vec3.hpp>
#include <vector>
#include <GLM/gtx/compatibility.hpp>

typedef std::vector<std::vector<std::vector<glm::float4>>> ScalarField;

class ChunkData;

class TerrainChunk
{
public:
	TerrainChunk(ChunkData* t_chunk_mesh, const ScalarField& t_scalar_field, const glm::vec3& t_chunk_position);
	~TerrainChunk();

	ScalarField getScalarField() const;
	glm::vec3 getPosition() const;
	ChunkData* getModelData();
private:
	ScalarField m_scalar_field;
	glm::vec3 m_position;
	ChunkData* m_mesh;
};

