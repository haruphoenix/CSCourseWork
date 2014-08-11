#include <GL/glew.h>
#include "SDL2/SDL.h"
//#include "SDL2/SDL_opengl.h"
#include "ArcTimer.h"
#include "ArcController.h"
#include "ArcApp.h"

ArcController::ArcController()
{
}

bool ArcController::listen()
{
  int x, y;
  // While there are events to handle
  while (SDL_PollEvent(&mEvent))
  {
    switch (mEvent.type)
    {
       case SDL_QUIT:
	 return true;
       case SDL_WINDOWEVENT:
	 switch (mEvent.window.event)
	 {
	   case SDL_WINDOWEVENT_RESIZED:
	   {
	     ArcApp::getInstance().getWindow().
	       resize(mEvent.window.data1, mEvent.window.data2);
	     ArcApp::getInstance().getEngine().
	       resize(mEvent.window.data1, mEvent.window.data2);
	     break;
	   }
	   default:
	     break;
	 }
	 break;
       case SDL_MOUSEMOTION:
	 SDL_GetMouseState(&x, &y);
	 ArcApp::getInstance().getEngine().getCamera().
	   changeDirection(x, y);
	 SDL_WarpMouseInWindow(ArcApp::getInstance().getWindow().
			       getHandle(),
			       ArcApp::getInstance().getWindow().
			       getWidth() / 2,
			       ArcApp::getInstance().getWindow().
			       getHeight() / 2);
	 break;
       case SDL_KEYDOWN:
         // Handle keypress with current mouse position
	 x = y = 0;
	 SDL_GetMouseState(&x, &y);
	 handleKeyDown(mEvent.key.keysym.sym, x, y);
         break;
       case SDL_KEYUP:
	 handleKeyUp(mEvent.key.keysym.sym);
	 break;
       case SDL_MOUSEBUTTONDOWN:
         break;
       case SDL_MOUSEBUTTONUP:
	 break;
       default:
         break;
    }
  }
  return false;
}

/*
 * Will be used to handle keys & Mouse position
 */
void ArcController::handleKeyDown(unsigned char key, int x, int y)
{

  switch (key)
  {
    case 'q':
      exit(0);
    case 'e':
      ArcApp::getInstance().getModel().moveForward();
      break;
    case 's':
      ArcApp::getInstance().getModel().moveLeft();
      break;
    case 'd':
      ArcApp::getInstance().getModel().moveBackward();
      break;
    case 'f':
      ArcApp::getInstance().getModel().moveRight();
      break;
    default:
      break;
  }

  // 
}

void ArcController::handleKeyUp(unsigned char key)
{
  // exit
  if (key == 'q')
  {
    exit(0);
  }

  switch (key)
  {
    case 'q':
      exit(0);
    case 'e':
      ArcApp::getInstance().getModel().stopForward();
      break;
    case 's':
      ArcApp::getInstance().getModel().stopLeft();
      break;
    case 'd':
      ArcApp::getInstance().getModel().stopBackward();
      break;
    case 'f':
      ArcApp::getInstance().getModel().stopRight();
      break;
    default:
      break;
  }

  // 
}

