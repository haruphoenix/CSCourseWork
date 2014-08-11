#include "ArcTimer.h"
#include "ArcCamera.h"
#include "ArcCanvas.h"
#include "ArcShaderProgram.h"

#ifndef ENGINE_H
#define ENGINE_H

class ArcEngine
{
public:
  ArcEngine();
  bool initialize();
  void update();
  void render();
  void destroy();
  void resize(int width, int height);
  int  getFPS();
  ArcCamera& getCamera();
private:
  void startShaderProgram();
  void initializeCanvas();
  ArcCamera mCamera;
  ArcCanvas mCanvas;
  ArcShaderProgram mShaderProgram;
  int mFPS;
  int mWidth;
  int mHeight;
};

#endif
