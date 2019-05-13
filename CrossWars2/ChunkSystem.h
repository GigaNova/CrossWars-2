#pragma once
#include "System.h"
#include "ChunkManager.h"

class ChunkSystem : public System
{
public:
	ChunkSystem(ChunkManager* t_chunk_manager);
	~ChunkSystem();

	bool canProcessComponent(Component* t_component) override;
	void processComponents(double t_delta_time) override;

private:
	ChunkManager* m_chunk_manager;
};

