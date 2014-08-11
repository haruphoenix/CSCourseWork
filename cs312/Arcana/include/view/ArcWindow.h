#ifndef ARCWINDOW_H
#define ARCWINDOW_H

#include <SDL2/SDL.h>

class ArcWindow
{
public:
  ArcWindow();
  bool initialize();
  void update();
  void resize(int width, int height);
  void destroy();
  int getWidth()  {return mWidth; };
  int getHeight() {return mHeight;};
  SDL_Window* getHandle();
private:
  SDL_Window* mWindow;
  SDL_GLContext mContext;
  int mHeight;
  int mWidth;
  int mBPP;
};

#endif
