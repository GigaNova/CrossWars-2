#version 400 core

in vec2 pass_textureCoords;
in vec3 surface_normal;
in vec3 to_light;

out vec4 out_Color;

uniform sampler2D tex0;
uniform vec3 ambientColor;
uniform vec3 lightColor;

void main()
{
	vec3 ambient = vec3(0.1, 0.1, 0.1) * texture(tex0, pass_textureCoords).rgb;
	
	vec3 normal = normalize(surface_normal);
	vec3 light = normalize(to_light);
	
	float dotP = dot(normal, light);
	float brightness = max(dotP, 0.0);
	vec3 diffuse = brightness * texture(tex0, pass_textureCoords).rgb;

    out_Color = vec4(diffuse, 1.0);
}