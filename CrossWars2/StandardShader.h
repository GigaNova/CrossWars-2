#pragma once
#include "ProtoShader.h"
#include <GLM/mat4x2.hpp>

class StandardShader : public ProtoShader
{
public:
	StandardShader();
	~StandardShader();

	void loadTransformationMatrix(glm::mat4 t_matrix);
protected:
	void bindAttributes() override;
	void getAttributes() override;

	GLint m_trans_matrix;
};

