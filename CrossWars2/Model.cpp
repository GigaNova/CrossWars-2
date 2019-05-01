#include "Model.h"

Model::Model(ModelData* t_model_data, TextureData* t_texture_data) : m_model_data(t_model_data), m_texture_data(t_texture_data)
{
}

Model::~Model()
{
}

ModelData* Model::getModelData() const
{
	return m_model_data;
}

TextureData* Model::getTextureData() const
{
	return m_texture_data;
}
