#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "ArcTimer.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

class ArcController
{
public:
  ArcController();
  void handleKeyDown(unsigned char key, int x, int y);
  void handleKeyUp(unsigned char key);
  bool listen();
private:
  SDL_Event mEvent;
};

#endif
