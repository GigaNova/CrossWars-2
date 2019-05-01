#pragma once
#include "ModelData.h"
#include "TextureData.h"

class Model
{
public:
	Model(ModelData* t_model_data, TextureData* t_texture_data);
	~Model();

	ModelData* getModelData() const;
	TextureData* getTextureData() const;
private:
	ModelData* m_model_data;
	TextureData* m_texture_data;
};

