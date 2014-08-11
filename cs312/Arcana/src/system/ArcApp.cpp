#include "SDL2/SDL.h"
#include "ArcTimer.h"
#include "ArcApp.h"

ArcModel      ArcApp::mModel;
ArcWindow     ArcApp::mWindow;
ArcTimer      ArcApp::mTimer;
ArcEngine     ArcApp::mEngine;
ArcController ArcApp::mController;

ArcApp::ArcApp()
{
}

ArcApp::~ArcApp()
{
  destroy();
}


ArcWindow& ArcApp::getWindow()
{
  return mWindow;
}

ArcEngine& ArcApp::getEngine()
{
  return mEngine;
}

ArcApp& ArcApp::getInstance()
{
  static ArcApp        mInstance;
  return mInstance;
}

ArcModel& ArcApp::getModel()
{
  return mModel;
}

bool ArcApp::initialize()
{
  mModel.loadObjects();
  if (mWindow.initialize() == false) return false;
  if (mEngine.initialize() == false) return false;
  mModel.initialize();
  return true;
}

void ArcApp::start()
{
  bool quit = false;

  while (!quit)
  {
    quit = mController.listen();
    mEngine.getCamera().move();
    mEngine.update();
    mEngine.render();
    mWindow.update();

    // Cap the frame rate
    if (mTimer.getTicks() < 1000 / mEngine.getFPS())
      SDL_Delay((1000 / mEngine.getFPS()) - mTimer.getTicks());
  }
}

void ArcApp::destroy()
{
}
