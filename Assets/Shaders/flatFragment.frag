#version 400 core

in vec3 pass_Color;
in vec3 surface_normal;
in vec3 to_light;

out vec4 out_Color;

void main(void){

    vec3 ambient = vec3(0.1, 0.1, 0.1) * pass_Color;
	
	vec3 normal = normalize(surface_normal);
	vec3 light = normalize(to_light);
	
	float dotP = dot(normal, light);
	float brightness = max(dotP, 0.0);
	vec3 diffuse = brightness * pass_Color;

    out_Color = vec4(diffuse, 1.0);
}