#pragma once
#include <sdl.h>

class Timer
{
public:
private:
	int startTicks;
	int pausedTicks;
	bool paused;
	bool started;
	int lastTick;
	int currentTick;
	

public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	float tick();
	int getTicks();
	bool isStarted();
	bool isPaused();
	float timeDelta;
	~Timer();
};

