#include "Timer.h"

#include <chrono>
#include <stdio.h>

using namespace std::chrono;

float Timer::GetMs() 
{ 
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count() - timeAdjust;
}

bool Timer::IsPaused() 
{ 
  return isPaused;
}

void Timer::Pause() 
{ 
  if(!isPaused)
    lastPause = GetMs();
  isPaused = true;
}

void Timer::Resume() 
{ 
  if(isPaused)
    timeAdjust += GetMs() - lastPause;
  isPaused = false;
}