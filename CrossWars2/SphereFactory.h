#pragma once
#include "BaseEntity.h"
#include "ModelData.h"
#include "TextureData.h"

class SphereFactory
{
public:
	SphereFactory();
	~SphereFactory();

	BaseEntity* makeSphere();

private:
	ModelData* m_sphere_model;
	TextureData* m_sphere_texture;
};

