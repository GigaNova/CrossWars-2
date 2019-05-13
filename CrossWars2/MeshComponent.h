#pragma once
#include "Component.h"
#include "ModelData.h"

class MeshComponent : public Component
{
public:
	MeshComponent(ModelData* t_model);
	~MeshComponent();

	void setModel(ModelData* t_model);
	ModelData* getModel();
private:
	ModelData* m_model;
};

