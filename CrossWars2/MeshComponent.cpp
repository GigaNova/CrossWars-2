#include "MeshComponent.h"

MeshComponent::MeshComponent(ModelData* t_model) : m_model(t_model)
{
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::setModel(ModelData* t_model)
{
	m_model = t_model;
}

ModelData* MeshComponent::getModel()
{
	return m_model;
}
