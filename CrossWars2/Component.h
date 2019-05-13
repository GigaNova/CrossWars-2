#pragma once

class BaseEntity;

class Component
{
public:
	Component();
	virtual ~Component();

	void setOwner(BaseEntity* t_entity);
	BaseEntity* getOwner();
private:
	BaseEntity* m_owner;
};

