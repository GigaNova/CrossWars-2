#include "CubeMarcher.h"
#include "Noise/PerlinNoise.hpp"
#include <ctime>
#include <GLM/gtx/compatibility.hpp>
#include <iostream>
#include "ModelManager.h"
#include "Logger.h"
#include "FastNoise.h"

CubeMarcher::CubeMarcher()
{
}

CubeMarcher::~CubeMarcher()
{
}

ModelData* CubeMarcher::generateMesh(int t_width, int t_height, int t_depth)
{
	//Initialize the scalar field with perlin noise.
	initializeField(t_width, t_height, t_depth);

	//March through the scalar field.
	const auto triangles = march(t_width, t_height, t_depth);

	//Build normals for marched mesh.
	const auto normals = calculateNormals(triangles);

	//Rebuild triangles to vertices.
	const auto vertices = toTriList(triangles);

	//Return model data.
	return ModelManager::GetInstance()->loadModelToVao(vertices, normals);
}

void CubeMarcher::initializeField(int t_width, int t_height, int t_depth)
{
	FastNoise noiseGen;
	noiseGen.SetNoiseType(FastNoise::SimplexFractal);
	noiseGen.SetSeed(time(nullptr));

	for (int i = 0; i < t_width; ++i)
	{
		m_scalar_field.push_back(std::vector<std::vector<glm::float4>>());
		for (int j = 0; j < t_height; ++j)
		{
			m_scalar_field[i].push_back(std::vector<glm::float4>());
			for (int k = 0; k < t_depth; ++k)
			{
				double noise = noiseGen.GetNoise(i, j, k) + (j * 0.01) - 0.3;

				if (j == t_height - 1) noise = 0.2;

				m_scalar_field[i][j].push_back(glm::float4(i, j, k, noise));
			}
		}
	}

	m_scalar_median = 0.2;
}

std::vector<glm::vec3> CubeMarcher::march(int t_width, int t_height, int t_depth)
{
	std::vector<glm::vec3> triangles;

	glm::vec3 pos(0, 0, 0);
	for (int x = 0; x < t_width - 1; x++)
	for (int y = 0; y < t_height - 1; y++)
	for (int z = 0; z < t_depth - 1; z++)
	{
		glm::float4 cubeCorners[8] = {
			m_scalar_field[x][y][z],
			m_scalar_field[x + 1][y][z],
			m_scalar_field[x + 1][y][z + 1],
			m_scalar_field[x][y][z + 1],
			m_scalar_field[x][y + 1][z],
			m_scalar_field[x + 1][y + 1][z],
			m_scalar_field[x + 1][y + 1][z + 1],
			m_scalar_field[x][y + 1][z + 1]
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
