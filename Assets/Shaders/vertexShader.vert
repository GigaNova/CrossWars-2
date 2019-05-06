#version 400 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surface_normal;
out vec3 to_light;

uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

void main()
{
  vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
  gl_Position = projectionMatrix * viewMatrix * worldPosition;
  pass_textureCoords = textureCoords;
  surface_normal = (transformationMatrix * vec4(normal, 0.0)).xyz;
  to_light = lightPosition - worldPosition.xyz;
}