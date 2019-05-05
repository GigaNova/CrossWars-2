#version 400 core

in vec2 pass_textureCoords;

out vec4 out_Color;

uniform sampler2D tex0;
uniform vec3 ambientColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * ambientColor;

    out_Color = vec4(ambient, 1.0) * texture(tex0, pass_textureCoords);
}