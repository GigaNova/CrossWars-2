#include "SphereFactory.h"
#include "MeshComponent.h"
#include "ScaleComponent.h"
#include "PositionComponent.h"
#include "RotationComponent.h"
#include "ModelManager.h"
#include <random>
#include <ctime>
#include "Color.h"
#include "ColorComponent.h"

SphereFactory::SphereFactory()
{
	m_sphere_model = ModelManager::GetInstance()->loadModel();
}

SphereFactory::~SphereFactory()
{
}

BaseEntity* SphereFactory::makeSphere()
{
	static std::random_device rd;
	static std::mt19937 rng(rd());
	std::uniform_int_distribution<int> pos(-50.0f, 50.0f);
	std::uniform_int_distribution<int> rot(-90.0f, 90.0f);
	std::uniform_int_distribution<int> scale(0.1f, 2.0f);

	auto entity = new BaseEntity();

	entity->addComponent(new PositionComponent(pos(rng), pos(rng), pos(rng)));
	entity->addComponent(new RotationComponent(rot(rng), rot(rng), rot(rng)));
	entity->addComponent(new ScaleComponent(scale(rng)));
	entity->addComponent(new MeshComponent(m_sphere_model));
	//entity->addComponent(new ColorComponent(Color::fromRgb(255, 0, 255)));

	return entity;
}
