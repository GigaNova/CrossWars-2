#include "TextureData.h"

TextureData::TextureData(GLint t_texture_id) : m_texture_id(t_texture_id)
{
}

TextureData::~TextureData()
{
}

GLint TextureData::getTextureId() const
{
	return m_texture_id;
}
