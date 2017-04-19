#include "Timer.h"

using namespace std::chrono;

bool Timer::isPaused = false;
float Timer::pauseTime = 0.0f, Timer::lastPause = 0.0f, Timer::timeAdjust = 0.0f;
float Timer::Time = Timer::GetMs();
float Timer::DeltaTime = 0.0f;

float Timer::GetMs()
{
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count() - timeAdjust;
}

void Timer::Tick()
{
  auto curTime = GetMs() / 1000.0f;
  DeltaTime = curTime - Time;
  Time = curTime;
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
