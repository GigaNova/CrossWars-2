#pragma once
#include "ProtoShader.h"
#include <GLM/vec3.hpp>
#include <GLM/mat4x4.hpp>

class FlatShader : public ProtoShader
{
public:
	FlatShader();
	~FlatShader();

	void loadTransformationMatrix(glm::mat4 t_matrix);
	void loadProjectionMatrix(glm::mat4 t_matrix);
	void loadViewMatrix(glm::mat4 t_matrix);
	void loadColor(glm::vec3 t_color);

protected:
	void bindAttributes() override;
	void getAttributes() override;

private:
	GLint m_color;
	GLint m_trans_matrix;
	GLint m_proj_matrix;
	GLint m_view_matrix;
};

