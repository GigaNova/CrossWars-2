#pragma once
#include "System.h"

class PhysicsSystem : public System
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	bool canProcessComponent(Component* t_component) override;
	void processComponents(double t_delta_time) override;
};

