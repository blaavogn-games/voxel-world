#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <chrono>

class Timer
{
	private:
		static bool isPaused;
    static float pauseTime, lastPause, timeAdjust;
    static float GetMs();
  public:
		static float Time, DeltaTime;
		static void Tick();
		static void Pause();
		static void Resume();
		static bool IsPaused();
};

#endif
