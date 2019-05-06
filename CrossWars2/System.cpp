#include "System.h"

System::System()
{
}

System::~System()
{
}

void System::addComponent(Component* t_component)
{
	m_components.push(t_component);
}
