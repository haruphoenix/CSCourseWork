#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "ArcTimer.h"

ArcTimer::ArcTimer()
{
  // Initialize the variables
  mStartTicks = 0;
  mPausedTicks = 0;
  mPaused = false;
  mStarted = false;
}

void ArcTimer::start()
{
  // Start the timer
  mStarted = true;

  // Unpause the timer;
  mPaused = false;

  // Get the current clock time
  mStartTicks = SDL_GetTicks();
}

void ArcTimer::stop()
{
  // Stop the timer
  mStarted = false;

  // Unpause the timer
  mPaused = false;
}

void ArcTimer::pause()
{
  // If the timer is running and isn't already paused
  if ((mStarted == true) && (mPaused == false))
  {
    // Pause the timer
    mPaused = true;

    // Calculate the paused ticks
    mPausedTicks = SDL_GetTicks() - mStartTicks;
  }
}

void ArcTimer::unpause()
{
  // If the timer is paused
  if (mPaused == true)
  {
    // Unpause the timer
    mPaused = false;

    // Reset the starting ticks
    mStartTicks = SDL_GetTicks() - mPausedTicks;
    
    // Reset the paused ticks
    mPausedTicks = 0;
  }
}

int ArcTimer::getTicks()
{
  // If the timer is running
  if (mStarted == true)
  {
    // If the timer is paused
    if (mPaused == true)
    {
      // Return the number of ticks when the timer was paused
      return mPausedTicks;
    }
    else
    {
      // Return the current time minus the start time
      return SDL_GetTicks() - mStartTicks;
    }
  }

  // If the timer isn't running
  return 0;
}

bool ArcTimer::isStarted()
{
  return mStarted;
}

bool ArcTimer::isPaused()
{
  return mPaused;
}

