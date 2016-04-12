#ifndef Timer_HEADER
#define Timer_HEADER

#include <chrono>
#include <string>
using namespace std;
class Timer
{
private:
	const long long MS = 1000000, S = 1000000000;
	std::chrono::steady_clock::time_point _start, _end;
	long long _time;
public:
	Timer()
	{
		_time = 0;
	}
	void start()
	{
		_start = std::chrono::high_resolution_clock::now();
	}
	void stop()
	{
		_end = std::chrono::high_resolution_clock::now();
		_time += std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _start).count();
	}
	double time()
	{
		return ((double)_time/S);
	}
	void reset()
	{
		_time = 0;
	}
	string to_string(string unit)
	{
		//Milliseconds
		if (unit == "ms")
			return std::to_string(_time / MS);
		//Seconds
		if (unit == "s")
			return std::to_string(_time / S);
		//Nanoseconds
		return std::to_string(_time);
	}
};

#endif