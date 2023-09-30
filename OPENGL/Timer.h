#pragma once
class Timer
{
private:
	float timer = 0.f;
	float time_condition = 0.f;
public:
	inline float getSeconds() { return timer; };
	inline float getTimeCond() { return time_condition; };
	void incBy(const float _time);
	bool isOver();
	void Restart(float toval);
public:
	Timer(float condition_secs = 0.f);
};