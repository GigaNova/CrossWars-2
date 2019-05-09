#pragma once
#include "BaseEntity.h"
#include <GLM/gtx/compatibility.hpp>

typedef std::vector<std::vector<std::vector<glm::float4>>> ScalarField;

class CubeTerrain : public BaseEntity
{
public:
	CubeTerrain(const ScalarField& t_scalar_field, const glm::vec3 t_offset);
	~CubeTerrain();

	ScalarField getScalarField() const;
	glm::vec3 getOffset() const;
private:
	ScalarField m_scalar_field;
	glm::vec3 m_offset;
};

