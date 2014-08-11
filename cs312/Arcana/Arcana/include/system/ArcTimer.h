#include <iostream>

#ifndef TIMER_H
#define TIMER_H

// The timer
class ArcTimer
{
 private:
  // The clock time when the timer started
  int mStartTicks;

  // The ticks stored when the timer was paused
  int mPausedTicks;

  // The timer status
  bool mPaused;
  bool mStarted;

 public:
  // Initializes variables
  ArcTimer();

  //The various clock actions
  void start();
  void stop();
  void pause();
  void unpause();

  // Gets the timer's time
  int getTicks();
  
  // Checks the status of the timer
  bool isStarted();
  bool isPaused();
};

#endif
