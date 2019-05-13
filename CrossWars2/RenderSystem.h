#pragma once
#include "System.h"
#include "FlatShader.h"
#include "StandardShader.h"

class RenderSystem : public System
{
public:
	RenderSystem();
	~RenderSystem();

	bool canProcessComponent(Component* t_component) override;
	void processComponents(double t_delta_time) override;

private:
	StandardShader* m_standard_shader;
	FlatShader* m_flat_shader;
};

