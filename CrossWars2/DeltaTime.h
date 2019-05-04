#pragma once
#include "Singleton.h"

class DeltaTime : public TSingleton<DeltaTime>
{
public:
	DeltaTime();
	~DeltaTime();

	void update();

	double getDeltaTime() const;
private:
	double m_current_tick;
	double m_last_tick;
	double m_delta_time;
};

