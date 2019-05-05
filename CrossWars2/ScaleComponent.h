#pragma once
#include "Component.h"
#include <GLEW/glew.h>

class ScaleComponent : public Component
{
public:
	ScaleComponent(GLfloat t_scale);
	~ScaleComponent();

	void setScale(GLfloat t_scale);

	GLfloat getScale() const;
private:
	GLfloat m_scale;
};

