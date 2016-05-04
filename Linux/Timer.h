#ifndef Timer_Linux_HEADER
#define Timer_Linux_HEADER

#include <ctime>
#include <string>

using namespace std;

class Timer
{
private:
	//const long long MS = 1000000, S = 1000000000;
	clock_t _start, _end;
	double _time;
public:
	Timer()
	{
		_time = 0;
	}
	void start()
	{
		this->_start = std::clock();
	}
	void stop()
	{
		this->_end = std::clock();
		_time += (_end - _start) / (double)CLOCKS_PER_SEC;
	}
	double time()
	{
		return _time;
	}
	void reset()
	{
		_time = 0;
	}
};

#endif
