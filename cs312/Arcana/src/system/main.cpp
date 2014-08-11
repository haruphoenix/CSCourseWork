#include "ArcApp.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#undef main

int main(int argc, char** argv)
{

  if (ArcApp::getInstance().initialize() == false) return 1;
  ArcApp::getInstance().start();

  return 0;
}
