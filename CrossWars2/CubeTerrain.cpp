#include "CubeTerrain.h"

CubeTerrain::CubeTerrain(const ScalarField& t_scalar_field, const glm::vec3 t_offset) : m_scalar_field(t_scalar_field), m_offset(t_offset)
{
}

CubeTerrain::~CubeTerrain()
{
}

ScalarField CubeTerrain::getScalarField() const
{
	return m_scalar_field;
}

glm::vec3 CubeTerrain::getOffset() const
{
	return m_offset;
}
