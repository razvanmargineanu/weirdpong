#include "Timer.h"



Timer::Timer()
{
	//Initialize
	startTicks = 0;
	pausedTicks = 0;
	lastTick = 0;
	currentTick = 0;
	timeDelta = 0.0f;
	paused = false;
	started = false;
}

void Timer::start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
}

void Timer::stop()
{
	started = false;
	paused = false;
}

void Timer::pause()
{
	if ((started == true) && (paused == false)) {
		paused = true;
	}
	pausedTicks = SDL_GetTicks() - startTicks;
}

void Timer::unpause()
{
	if (paused == true) {
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

float Timer::tick()
{
	currentTick = getTicks();
	timeDelta = (currentTick - lastTick)/1000.0f;
	lastTick = currentTick;
	return timeDelta;
}



int Timer::getTicks()
{

	if (started == true) {
		if (paused == true) {
			return pausedTicks;
		}
		else {
			return SDL_GetTicks() - startTicks;
		}
	}

	return 0;
}

bool Timer::isStarted()
{
	return started;
}

bool Timer::isPaused()
{
	return paused;
}


Timer::~Timer()
{
}
