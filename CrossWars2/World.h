#pragma once
#include <vector>
#include "BaseEntity.h"
#include "System.h"

class World
{
public:
	World();
	~World();

	void preUpdate();
	void update(double t_delta_time);

	std::vector<BaseEntity*>* getEntities();
private:
	std::vector<BaseEntity*> m_entity_vector;
	std::vector<System*> m_system_vector;
};

