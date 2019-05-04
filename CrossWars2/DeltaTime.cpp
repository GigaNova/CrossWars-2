#include "DeltaTime.h"
#include <SDL/SDL.h>

DeltaTime::DeltaTime() : m_current_tick(SDL_GetPerformanceFrequency()), m_last_tick(0), m_delta_time(0)
{
}

DeltaTime::~DeltaTime()
{
}

void DeltaTime::update()
{
	m_last_tick = m_current_tick;
	m_current_tick = SDL_GetPerformanceCounter();

	m_delta_time = static_cast<double>((m_current_tick - m_last_tick) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency())) * 0.001f;
}

double DeltaTime::getDeltaTime() const
{
	return m_delta_time;
}

