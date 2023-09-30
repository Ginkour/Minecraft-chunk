#include "Timer.h"
void Timer::incBy(const float _time)
{
	timer += _time;
}

bool Timer::isOver()
{
	if (timer > time_condition)
	{
		timer = 0.f;
		return true;
	}
	else 
		return false;
}

void Timer::Restart(float toval = 0.f)
{
	timer = toval;
}

Timer::Timer(float condition_secs)
{
	time_condition = condition_secs;
}
