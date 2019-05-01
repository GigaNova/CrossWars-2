#pragma once
#include "GLEW/glew.h"

class ProtoShader
{
public:
	ProtoShader(const char* t_vertex, const char* t_fragment);
	virtual ~ProtoShader();

protected:
	virtual void bindAttributes() = 0;
	virtual void getAttributes() = 0;
};

