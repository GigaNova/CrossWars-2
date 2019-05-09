#pragma once
#include "GLEW/glew.h"

class ProtoShader
{
public:
	ProtoShader(const char* t_vertex, const char* t_fragment);
	virtual ~ProtoShader();

	void activate();

	GLuint getProgramId() const;
protected:
	virtual void bindAttributes() = 0;
	virtual void getAttributes() = 0;

private:
	GLuint m_program_id;

	const char* m_vertex;
	const char* m_fragment;
};

