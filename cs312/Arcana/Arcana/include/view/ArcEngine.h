#include "ArcTimer.h"
#include "ArcCamera.h"
#include "ArcCanvas.h"
#include "ArcShaderProgram.h"
#include "ArcUtils.h"

#ifndef ENGINE_H
#define ENGINE_H

class ArcEngine
{
public:
  ArcEngine();
  bool initialize();
  void render();
  void destroy();
  void resize(int width, int height);
  int  getFPS();
  ArcCamera& getCamera();
  void setPerspectiveMatrix(ArcMatrix m) {mProjectionMatrix = m;}
  ArcCanvas& getCanvas();
  ArcShaderProgram& getShaderProgram();
private:
  void startShaderProgram();
  void initializeCanvas();
  ArcCamera mCamera;
  ArcCanvas mCanvas;
  ArcShaderProgram mShaderProgram;
  int mFPS;
  int mWidth;
  int mHeight;
  ArcMatrix mProjectionMatrix;
};

#endif
