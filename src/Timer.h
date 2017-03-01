#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>

class Timer
{
	private:
		bool isPaused = false;
		float pauseTime = 0, lastPause = 0, timeAdjust;
	public:
		float GetMs();
		void Pause();
		void Resume();
		bool IsPaused();
};
  
#endif