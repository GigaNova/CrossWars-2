#pragma once
#include "BaseEntity.h"
#include "Model.h"

class SphereFactory
{
public:
	SphereFactory();
	~SphereFactory();

	BaseEntity* makeSphere();

private:
	Model* m_sphere_model;
};

