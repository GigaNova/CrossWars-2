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
#include "Vertex.h"

ObjFormatLoader::ObjFormatLoader()
{
}


ObjFormatLoader::~ObjFormatLoader()
{
}

ModelData* ObjFormatLoader::loadModel(std::string t_filename)
{
	std::string fileAdress = "..//Assets//Models//" + t_filename + ".obj";

	Logger::GetInstance()->logAction("Loading .obj file " + t_filename);
	if(!std::experimental::filesystem::exists(fileAdress))
	{
		Logger::GetInstance()->logError("No such file exists.", __LINE__, __FILE__);
		return nullptr;
	}

	std::ifstream model(fileAdress);

	std::vector<Vertex*> vertices = std::vector<Vertex*>();
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
			glm::vec3 vertex = glm::fvec3(atof(currentLine.at(1).c_str()), atof(currentLine.at(2).c_str()), atof(currentLine.at(3).c_str()));
			vertices.push_back(new Vertex(vertices.size(), vertex));
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
				int index = atoi(vertexData.at(0).c_str()) - 1;
				Vertex* currentVertex = vertices[index];
				int currentTex = atoi(vertexData.at(1).c_str()) - 1;
				int currentNormal = atoi(vertexData.at(2).c_str()) - 1;

				if(!currentVertex->isSet())
				{
					currentVertex->setTextureIndex(currentTex);
					currentVertex->setNormalIndex(currentNormal);
					indices.push_back(index);
				}
				else
				{
					vertexElimination(currentVertex, currentTex, currentNormal, &indices, &vertices);
				}

				vertexQueue.pop();
			}
		}
	}
	model.close();

	removeUnusedVertices(vertices);

	textureArray.resize(vertices.size() * 2);
	normalsArray.resize(vertices.size() * 3);
	verticesArray.resize(vertices.size() * 3);

	glm::vec3 position;
	glm::vec2 textureCoord;
	glm::vec3 normalVector;

	for (int i = 0; i < vertices.size(); i++) {
		Vertex* currentVertex = vertices[i];
		position = currentVertex->getPosition();
		textureCoord = textures[currentVertex->getTextureIndex()];
		normalVector = normals[currentVertex->getNormalIndex()];
		verticesArray[i * 3] = position.x;
		verticesArray[i * 3 + 1] = position.y;
		verticesArray[i * 3 + 2] = position.z;
		textureArray[i * 2] = textureCoord.x;
		textureArray[i * 2 + 1] = 1.f - textureCoord.y;
		normalsArray[i * 3] = normalVector.x;
		normalsArray[i * 3 + 1] = normalVector.y;
		normalsArray[i * 3 + 2] = normalVector.z;
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

void ObjFormatLoader::vertexElimination(Vertex* t_previous_index, int t_texture_index, int t_normal_index, std::vector<GLuint>* t_indices, std::vector<Vertex*>* t_vertices) {
	if (t_previous_index->identical(t_texture_index, t_normal_index)) {
		t_indices->push_back(t_previous_index->getIndex());
	}
	else {
		Vertex* anotherVertex = t_previous_index->getDupe();
		if (anotherVertex != nullptr) {
			vertexElimination(anotherVertex, t_texture_index, t_normal_index, t_indices, t_vertices);
		}
		else {
			Vertex* duplicateVertex = new Vertex(t_vertices->size(), t_previous_index->getPosition());
			duplicateVertex->setTextureIndex(t_texture_index);
			duplicateVertex->setNormalIndex(t_normal_index);
			t_previous_index->setDupe(duplicateVertex);
			t_vertices->push_back(duplicateVertex);
			t_indices->push_back(duplicateVertex->getIndex());
		}

	}
}

void ObjFormatLoader::removeUnusedVertices(const std::vector<Vertex*>& vertices) {
	for (Vertex* vertex : vertices) {
		if (!vertex->isSet()) {
			vertex->setTextureIndex(0);
			vertex->setNormalIndex(0);
		}
	}
}