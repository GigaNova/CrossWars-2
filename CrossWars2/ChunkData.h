#pragma once
#include <vector>
#include "GLEW/glew.h"

class ChunkData
{
public:
	const static int CHUNK_SIZE_X = 16;
	const static int CHUNK_SIZE_Y = 64;
	const static int CHUNK_SIZE_Z = 16;
	const static int CHUNK_SCALE = 4.0;

	ChunkData(const std::vector<GLfloat>& t_vertices, const std::vector<GLfloat>& t_normals);
	~ChunkData();

	std::vector<GLfloat> getVertices() const;
	std::vector<GLfloat> getNormals() const;
private:
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_normals;
};

