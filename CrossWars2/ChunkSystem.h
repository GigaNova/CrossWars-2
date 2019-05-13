#pragma once
#include "System.h"
#include "ChunkManager.h"

class ChunkSystem : public System
{
public:
	const static int VIEW_DISTANCE = 12;
	constexpr static float UPDATE_INTERVAL = 0.5;

	ChunkSystem(ChunkManager* t_chunk_manager);
	~ChunkSystem();

	bool canProcessComponent(Component* t_component) override;
	void processComponents(double t_delta_time) override;

private:
	ChunkManager* m_chunk_manager;

	float m_counter;
};

