#pragma once
#include "Model.h"
#include "Component.h"

class MeshComponent : public Component
{
public:
	MeshComponent(Model* t_model);
	~MeshComponent();

	void setModel(Model* t_model);
	Model* getModel();
private:
	Model* m_model;
};

