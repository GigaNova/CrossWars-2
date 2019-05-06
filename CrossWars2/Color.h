#pragma once
#include <GLM/vec3.hpp>

class Color
{
public:
	static glm::vec3 fromRgb(float t_r, float t_g, float t_b);
	static glm::vec3 fromHex(const char* t_hex);
};

