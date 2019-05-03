#include "ObjFormatLoader.h"
#include <string>
#include <vector>
#include <fstream>
#include "ModelData.h"
#include "ModelManager.h"
#include <experimental/filesystem>
#include "Logger.h"
#include <queue>
#include <sstream>

ObjFormatLoader::ObjFormatLoader()
{
}


ObjFormatLoader::~ObjFormatLoader()
{
}

ModelData* ObjFormatLoader::loadModel(std::string t_filename)
{
	std::string fileAdress = "..//Assets//Models//" + t_filename + ".obj";

	Logger::GetInstance()->logAction("loading .obj file " + t_filename);
	if(!std::experimental::filesystem::exists(fileAdress))
	{
		Logger::GetInstance()->logError("No such file exists.", __LINE__, __FILE__);
		return nullptr;
	}

	std::ifstream model(fileAdress);

	std::vector<glm::fvec3> vertices = std::vector<glm::fvec3>();
	std::vector<glm::fvec2> textures = std::vector<glm::fvec2>();
	std::vector<glm::fvec3> normals = std::vector<glm::fvec3>();

	std::vector<GLuint> indices;

	std::vector<GLfloat> verticesArray = std::vector<GLfloat>();
	std::vector<GLfloat> normalsArray = std::vector<GLfloat>();
	std::vector<GLfloat> textureArray = std::vector<GLfloat>();

	std::string line;
	while (getline(model, line))
	{
		std::vector<std::string> currentLine;
		splitStringDel(line, ' ', currentLine);
		if (line.find("v ") == 0)
		{
			vertices.push_back(glm::fvec3(atof(currentLine.at(1).c_str()), atof(currentLine.at(2).c_str()), atof(currentLine.at(3).c_str())));
		}
		else if (line.find("vt ") == 0)
		{
			textures.push_back(glm::fvec2(atof(currentLine.at(1).c_str()), atof(currentLine.at(2).c_str())));
		}
		else if (line.find("vn ") == 0)
		{
			normals.push_back(glm::fvec3(atof(currentLine.at(1).c_str()), atof(currentLine.at(2).c_str()), atof(currentLine.at(3).c_str())));
		}
		else if (line.find("f ") == 0)
		{
			textureArray.resize(vertices.size() * 2);
			normalsArray.resize(vertices.size() * 3);
			break;
		}
	}

	model.clear();
	model.seekg(0, std::ios::beg);

	std::queue<std::vector<std::string>> vertexQueue;

	std::vector<std::string> currentLine;

	std::vector<std::string> vertex1;
	std::vector<std::string> vertex2;
	std::vector<std::string> vertex3;

	glm::vec2 currentTex;
	glm::vec3 currentNormal;

	while (getline(model, line))
	{
		if (line.find("f ") == 0)
		{
			currentLine.clear();
			vertex1.clear();
			vertex2.clear();
			vertex3.clear();

			splitStringDel(line, ' ', currentLine);

			splitStringDel(currentLine.at(1), '/', vertex1);
			splitStringDel(currentLine.at(2), '/', vertex2);
			splitStringDel(currentLine.at(3), '/', vertex3);

			vertexQueue.push(vertex1);
			vertexQueue.push(vertex2);
			vertexQueue.push(vertex3);

			while(!vertexQueue.empty())
			{
				auto vertexData = vertexQueue.front();
				int currentVertex = atoi(vertexData.at(0).c_str()) - 1;
				indices.push_back(currentVertex);

				currentTex = textures.at(atoi(vertexData.at(1).c_str()) - 1);
				textureArray[currentVertex * 2] = currentTex.x;
				textureArray[currentVertex * 2 + 1] = 1.0f - currentTex.y;

				currentNormal = normals.at(atoi(vertexData.at(2).c_str()) - 1);
				normalsArray[currentVertex * 3] = currentNormal.x;
				normalsArray[currentVertex * 3 + 1] = currentNormal.y;
				normalsArray[currentVertex * 3 + 2] = currentNormal.z;

				vertexQueue.pop();
			}

		}
	}
	model.close();

	verticesArray.resize(vertices.size() * 3);

	int vertexPointer = 0;
	for (glm::fvec3 Vertex : vertices)
	{
		verticesArray[vertexPointer++] = Vertex.x;
		verticesArray[vertexPointer++] = Vertex.y;
		verticesArray[vertexPointer++] = Vertex.z;
	}

	return ModelManager::GetInstance()->loadModelToVao(verticesArray, indices, textureArray);
}

std::vector<std::string> ObjFormatLoader::splitStringDel(std::string const& t_original, char t_separator, std::vector<std::string>& t_result)
{
	std::stringstream ss(t_original);
	std::string tok;

	while (getline(ss, tok, t_separator)) {
		t_result.push_back(tok);
	}

	return t_result;
}