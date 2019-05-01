#pragma once
#include <GLEW/glew.h>

class TextureData
{
public:
	TextureData(GLint t_texture_id);
	~TextureData();

	GLint getTextureId() const;
private:
	GLint m_texture_id;
};

