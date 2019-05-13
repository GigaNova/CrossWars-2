#include "RenderSystem.h"
#include "MeshComponent.h"
#include "RenderManager.h"
#include "TextureComponent.h"
#include "ColorComponent.h"
#include "LightFlatShader.h"
#include "LightShader.h"
#include "Color.h"
#include "StaticLight.h"
#include "BaseEntity.h"

RenderSystem::RenderSystem()
{
	StaticLight light(glm::vec3(0, 1000, 0), Color::fromHex("FBF8E6"));
	m_standard_shader = new LightShader(glm::vec3(0.5f, 0.5f, 0.5f), light);
	m_flat_shader = new LightFlatShader(light);
}


RenderSystem::~RenderSystem()
{
}

bool RenderSystem::canProcessComponent(Component* t_component)
{
	const auto t = dynamic_cast<MeshComponent*>(t_component);
	return t != nullptr;
}

void RenderSystem::processComponents(double t_delta_time)
{
	while (!m_components.empty())
	{
		auto component = dynamic_cast<MeshComponent*>(m_components.front());
		auto owner = component->getOwner();

		const auto texture = owner->getComponent<TextureComponent>();
		if(texture)
		{
			RenderManager::GetInstance()->renderEntity(owner, m_standard_shader);
		}
		else
		{
			const auto color = owner->getComponent<ColorComponent>();
			if(color)
			{
				RenderManager::GetInstance()->renderEntityFlat(owner, m_flat_shader);
			}
		}

		m_components.pop();
	}
}
