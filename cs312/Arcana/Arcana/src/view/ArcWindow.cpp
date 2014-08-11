#include <SDL2/SDL.h>
#include "ArcWindow.h"
#include "ArcApp.h"

bool ArcWindow::initialize()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

  
  mWindow = SDL_CreateWindow("Arcana", 
			     SDL_WINDOWPOS_CENTERED,
			     SDL_WINDOWPOS_CENTERED, 
			     mWidth, mHeight,
			     SDL_WINDOW_OPENGL | 
			     SDL_WINDOW_SHOWN  |
			     SDL_WINDOW_RESIZABLE);
  if (!mWindow) return false;

  mContext = SDL_GL_CreateContext(mWindow);
  if (mContext == NULL) return false;

  SDL_GL_MakeCurrent(mWindow, mContext);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  return true;
}

void ArcWindow::resize(int width, int height)
{
  mWidth  = width;
  mHeight = height;
  SDL_SetWindowSize(mWindow, mWidth, mHeight);
}

void ArcWindow::update()
{
  SDL_GL_SwapWindow(mWindow);
}

void ArcWindow::destroy()
{
  // Quit SDL
  SDL_Quit();
}

ArcWindow::ArcWindow()
{
  mHeight = 600;
  mWidth  = 800;
  mBPP    = 32;
}

SDL_Window* ArcWindow::getHandle()
{
  return mWindow;
}