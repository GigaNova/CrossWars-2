#version 400 core

in vec2 pass_textureCoords;

out vec4 out_Color;

uniform sampler2D tex0;

void main()
{
    out_Color = texture(tex0, pass_textureCoords);
}