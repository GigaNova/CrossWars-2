#version 400 core

in vec3 position;
in vec3 normal;

out vec3 pass_Color;
out vec3 surface_normal;
out vec3 to_light;

uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;
uniform vec3 color;

void main()
{
	vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	pass_Color = color;
	surface_normal = (transformationMatrix * vec4(normal, 0.0)).xyz;
	to_light = lightPosition - worldPosition.xyz;
}