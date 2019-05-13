#include "CubeMarcher.h"
#include "Noise/PerlinNoise.hpp"
#include <ctime>
#include <GLM/gtx/compatibility.hpp>
#include "ModelManager.h"
#include "FastNoise.h"
#include "CubeTerrain.h"
#include "MeshComponent.h"
#include "TerrainChunk.h"
#include "ChunkData.h"

CubeMarcher::CubeMarcher(int t_seed) : m_seed(t_seed)
{
	m_noiseGen.SetSeed(t_seed);
	m_noiseGen.SetFractalOctaves(8);
}

CubeMarcher::~CubeMarcher()
{
}

TerrainChunk* CubeMarcher::generateChunk(int t_offset_x, int t_offset_y, int t_offset_z, int t_width, int t_height, int t_depth)
{
	//Generate Scalar field
	auto scalarField = initializeField(t_offset_x, t_offset_y, t_offset_z, t_width, t_height, t_depth);

	//Generate mesh.
	auto modelData = generateMesh(scalarField, t_offset_x, t_offset_y, t_offset_z, t_width, t_height, t_depth);

	//Return the chunk.
	auto terrain = new TerrainChunk(modelData, scalarField, glm::vec3(t_offset_x, t_offset_y, t_offset_z));

	//Return chunk.
	return terrain;
}

ChunkData* CubeMarcher::generateMesh(const ScalarField& t_scalar_field, int t_offset_x, int t_offset_y, int t_offset_z, int t_width, int t_height, int t_depth)
{
	//March through the scalar field.
	const auto triangles = march(t_scalar_field, t_width, t_height, t_depth);

	//Build normals for marched mesh.
	const auto normals = calculateNormals(triangles);

	//Rebuild triangles to vertices.
	const auto vertices = toTriList(triangles);

	//Load model data.
	return new ChunkData(vertices, normals);
}

ScalarField CubeMarcher::initializeField(int t_offset_x, int t_offset_y, int t_offset_z, int t_width, int t_height, int t_depth)
{
	ScalarField scalarField(0);

	for (int i = t_offset_x; i < t_offset_x + t_width + 1; ++i)
	{
		scalarField.push_back(std::vector<std::vector<glm::float4>>());
		for (int j = t_offset_y; j < t_offset_y + t_height + 1; ++j)
		{
			scalarField[i - t_offset_x].push_back(std::vector<glm::float4>());
			for (int k = t_offset_z; k < t_offset_z + t_depth + 1; ++k)
			{
				m_noiseGen.SetNoiseType(FastNoise::SimplexFractal);
				double noise = m_noiseGen.GetNoise(i, j, k) + (j * 0.0155) - 0.3;

				m_noiseGen.SetNoiseType(FastNoise::Perlin);
				noise += (m_noiseGen.GetNoise(i, j, k) + (j * (abs(sin(m_seed)) / 20)) - 0.3) / PERLIN_WEAKNESS;

				if (j == 0) noise = 0;

				scalarField[i - t_offset_x][j - t_offset_y].push_back(glm::float4(i, j, k, noise));
			}
		}
	}

	m_scalar_median = 0.1;

	return scalarField;
}

std::vector<glm::vec3> CubeMarcher::march(const ScalarField& t_scalar_field, int t_width, int t_height, int t_depth)
{
	std::vector<glm::vec3> triangles;

	glm::vec3 pos(0, 0, 0);
	for (int x = 0; x < t_width; x++)
	for (int y = 0; y < t_height; y++)
	for (int z = 0; z < t_depth; z++)
	{
		glm::float4 cubeCorners[8] = {
			t_scalar_field[x][y][z],
			t_scalar_field[x + 1][y][z],
			t_scalar_field[x + 1][y][z + 1],
			t_scalar_field[x][y][z + 1],
			t_scalar_field[x][y + 1][z],
			t_scalar_field[x + 1][y + 1][z],
			t_scalar_field[x + 1][y + 1][z + 1],
			t_scalar_field[x][y + 1][z + 1]
		};

		int cubeindex = 0;
		for (int i = 0; i < 8; i++)
		{
			if (cubeCorners[i].w <= m_scalar_median)
			{
				cubeindex |= 1 << i;
			}
		}

		if (m_edge_table[cubeindex] != 0)
		{
			glm::float3 vertexList[12];
			if (m_edge_table[cubeindex] & 1)
				vertexList[0] =
				linearInterp(m_scalar_median, cubeCorners[0], cubeCorners[1]);
			if (m_edge_table[cubeindex] & 2)
				vertexList[1] =
				linearInterp(m_scalar_median, cubeCorners[1], cubeCorners[2]);
			if (m_edge_table[cubeindex] & 4)
				vertexList[2] =
				linearInterp(m_scalar_median, cubeCorners[2], cubeCorners[3]);
			if (m_edge_table[cubeindex] & 8)
				vertexList[3] =
				linearInterp(m_scalar_median, cubeCorners[3], cubeCorners[0]);
			if (m_edge_table[cubeindex] & 16)
				vertexList[4] =
				linearInterp(m_scalar_median, cubeCorners[4], cubeCorners[5]);
			if (m_edge_table[cubeindex] & 32)
				vertexList[5] =
				linearInterp(m_scalar_median, cubeCorners[5], cubeCorners[6]);
			if (m_edge_table[cubeindex] & 64)
				vertexList[6] =
				linearInterp(m_scalar_median, cubeCorners[6], cubeCorners[7]);
			if (m_edge_table[cubeindex] & 128)
				vertexList[7] =
				linearInterp(m_scalar_median, cubeCorners[7], cubeCorners[4]);
			if (m_edge_table[cubeindex] & 256)
				vertexList[8] =
				linearInterp(m_scalar_median, cubeCorners[0], cubeCorners[4]);
			if (m_edge_table[cubeindex] & 512)
				vertexList[9] =
				linearInterp(m_scalar_median, cubeCorners[1], cubeCorners[5]);
			if (m_edge_table[cubeindex] & 1024)
				vertexList[10] =
				linearInterp(m_scalar_median, cubeCorners[2], cubeCorners[6]);
			if (m_edge_table[cubeindex] & 2048)
				vertexList[11] =
				linearInterp(m_scalar_median, cubeCorners[3], cubeCorners[7]);

			for (int i = 0; m_tri_table[cubeindex][i] != -1; i += 3) {
				triangles.push_back(vertexList[m_tri_table[cubeindex][i]]);
				triangles.push_back(vertexList[m_tri_table[cubeindex][i + 1]]);
				triangles.push_back(vertexList[m_tri_table[cubeindex][i + 2]]);
			}
		}
	}

	return triangles;
}

std::vector<GLfloat> CubeMarcher::calculateNormals(const std::vector<glm::vec3> t_triangles)
{
	std::vector<GLfloat> normals;
	normals.resize(t_triangles.size() * 3);

	for(int i = 0; i < t_triangles.size(); i+= 3)
	{
		glm::vec3 normal = calulateNormal(
			t_triangles[i],
			t_triangles[i + 1],
			t_triangles[i + 2]
		);

		normals[i * 3] = normal.x;
		normals[i * 3 + 1] = normal.y;
		normals[i * 3 + 2] = normal.z;

		normals[i * 3 + 3] = normal.x;
		normals[i * 3 + 4] = normal.y;
		normals[i * 3 + 5] = normal.z;

		normals[i * 3 + 6] = normal.x;
		normals[i * 3 + 7] = normal.y;
		normals[i * 3 + 8] = normal.z;
	}

	return normals;
}

std::vector<int> CubeMarcher::calculateIndices(const std::vector<glm::vec3> t_triangles)
{
	/*for (int i = 0; i < t_triangles.size(); i++)
	{
		set<VPair>::iterator it = vertices.find(make_pair(input[i], 0));
		if (it != vertices.end()) indices.push_back(it->second);
		else
		{
			vertices.insert(make_pair(input[i], index));
			indices.push_back(index++);
		}
	}

	// Notice that the vertices in the set are not sorted by the index
	// so you'll have to rearrange them like this:
	vbuffer.resize(vertices.size());
	for (set<VPair>::iterator it = vertices.begin(); it != vertices.end(); it++)
		vbuffer[it->second] = it->first;
	*/
	return std::vector<int>();
}

glm::vec3 CubeMarcher::calulateNormal(const glm::vec3 t_vertex1, const glm::vec3 t_vertex2, const glm::vec3 t_vertex3)
{
	glm::vec3 normal;

	glm::vec3 u = t_vertex2 - t_vertex1;
	glm::vec3 v = t_vertex3 - t_vertex1;

	normal = glm::cross(u, v);

	return normal;
}

std::vector<GLfloat> CubeMarcher::toTriList(const std::vector<glm::vec3>& t_triangles)
{
	std::vector<GLfloat> vertices;

	for (int i = 0; i < t_triangles.size(); ++i)
	{
		glm::float3 triangle = t_triangles[i];

		vertices.push_back(triangle.x);
		vertices.push_back(triangle.y);
		vertices.push_back(triangle.z);
	}

	return vertices;
}

glm::float3 CubeMarcher::linearInterp(float t_val, glm::float4 t_p1, glm::float4 t_p2)
{
	if (lt(t_p2, t_p1))
	{
		glm::float4 temp;
		temp = t_p1;
		t_p1 = t_p2;
		t_p1 = temp;
	}

	glm::float3 p;
	if (fabs(t_p1.w - t_p2.w) > 0.00001)
		p = (glm::float3)t_p1 + ((glm::float3)t_p2 - (glm::float3)t_p1) / (t_p2.w - t_p1.w)*(t_val - t_p1.w);
	else
		p = (glm::float3)t_p2;
	return p;
}

bool CubeMarcher::lt(const glm::float4& t_left, const glm::float4& t_right)
{
	if (t_left.x < t_right.x)
		return true;
	if (t_left.x > t_right.x)
		return false;

	if (t_left.y < t_right.y)
		return true;
	if (t_left.y > t_right.y)
		return false;

	if (t_left.z < t_right.z)
		return true;
	if (t_left.z > t_right.z)
		return false;

	return false;
}
