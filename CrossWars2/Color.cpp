#include "Color.h"
#include <cstdio>

glm::vec3 Color::fromRgb(float t_r, float t_g, float t_b)
{
	return glm::vec3(
		t_r / 255.f,
		t_g / 255.f,
		t_b / 255.f
	);
}

glm::vec3 Color::fromHex(const char* t_hex)
{
	int r, g, b;
	sscanf_s(t_hex, "%02x%02x%02x", &r, &g, &b);
	return fromRgb(r, g, b);
}
