#pragma once
#include <GLM/vec3.hpp>

class Vertex
{
public:
	Vertex(int t_index, glm::vec3 t_position);
	~Vertex();

	bool isSet();
	bool identical(int m_texture, int m_normal);

	int getIndex() const;
	int getTextureIndex() const;
	int getNormalIndex() const;
	glm::vec3 getPosition() const;

	void setTextureIndex(int t_texture_ind);
	void setNormalIndex(int t_normal_ind);

	void setDupe(Vertex* m_dupe);
	Vertex* getDupe();
private:
	glm::vec3 m_position;
	int m_texture_ind;
	int m_normal_ind;
	Vertex* m_dupe;
	int m_index;
	float m_length;
};

