#include "MeshComponent.h"

MeshComponent::MeshComponent(Model* t_model) : m_model(t_model)
{
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::setModel(Model* t_model)
{
	m_model = t_model;
}

Model* MeshComponent::getModel()
{
	return m_model;
}
