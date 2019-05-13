#pragma once
#include "Component.h"
#include "TextureData.h"

class TextureComponent : public Component
{
public:
	TextureComponent(TextureData* t_texture);
	~TextureComponent();

	void setTexture(TextureData* t_texture);
	TextureData* getTexture();
private:
	TextureData* m_texture;
};

