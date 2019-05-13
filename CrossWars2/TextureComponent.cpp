#include "TextureComponent.h"

TextureComponent::TextureComponent(TextureData* t_texture) : m_texture(t_texture)
{
}


TextureComponent::~TextureComponent()
{
}

void TextureComponent::setTexture(TextureData* t_texture)
{
	m_texture = t_texture;
}

TextureData* TextureComponent::getTexture()
{
	return m_texture;
}
