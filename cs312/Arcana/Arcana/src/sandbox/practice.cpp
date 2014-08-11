#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
#include "ArcTimer.h"

class ArcModel
{
public:
  ArcModel();
private:
};


class ArcWindow
{
public:
  ArcWindow();
  bool initialize();
  void destroy();
private:
  int mHeight;
  int mWidth;
  int mBPP;
};

class ArcEngine
{
public:
  ArcEngine();
  bool initialize();
  void update();
  void render();
  void destroy();
  int  getFPS();
private:
  int mFPS;
};

class ArcController
{
public:
  ArcController();
  void handleKeys(unsigned char key, int x, int y);
  bool listen();
private:
  SDL_Event mEvent; 
};




class ArcApp
{
public:

  static ArcApp* getInstance();
  static bool initialize();
  static void start();
  static void destroy();
  static ArcWindow* getWindow();
  static ArcEngine* getEngine();

  ~ArcApp();

private:

  ArcApp();

  static ArcWindow* mWindow;
  static ArcEngine* mEngine;
  static ArcApp*    mInstance;

  static ArcTimer      mTimer;
  static ArcController mController;
};


ArcModel::ArcModel()
{
}


/*
 * Initialize SDL, Window, and OpenGL
 *
 */
bool ArcWindow::initialize()
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    return false;
  }

  // Create Window
  if (SDL_SetVideoMode(mWidth, mHeight, mBPP, SDL_OPENGL) == NULL) 
    return false;

  // Initialize Unicode
  SDL_EnableUNICODE(SDL_ENABLE);

  // Set caption
  SDL_WM_SetCaption("OpenGL Test", NULL);

  return true;
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


ArcEngine::ArcEngine()
{
  mFPS = 60;
}

/*
 * Initialize OpenGL
 */
bool ArcEngine::initialize()
{

  //Initialize Projection Matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Initialize Modelview Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Initialize clear color
  glClearColor(0.f, 0.f, 0.f, 1.f);

  //Check for error
  GLenum error = glGetError();
  if (error != GL_NO_ERROR)
  {
    printf("Error initializing OpenGL! %s\n", gluErrorString(error));
    return false;
  }

  return true;
}

void ArcEngine::update()
{
}

/*
 * Clears screen, then re-renders
 */
void ArcEngine::render()
{
  // Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_QUADS);
  //
  glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
  glVertex2f(-0.5f, -0.5f);
  glVertex2f( 0.5f, -0.5f);
  glVertex2f( 0.5f,  0.5f);
  glVertex2f(-0.5f,  0.5f);
  //
  glEnd();
  
  // Update screen
  SDL_GL_SwapBuffers();
}


ArcController::ArcController()
{
}

bool ArcController::listen()
{
  // While there are events to handle
  while (SDL_PollEvent(&mEvent))
  {
    if (mEvent.type == SDL_QUIT)
    {
      return true;
    }
    else if (mEvent.type == SDL_KEYDOWN)
    {
      // Handle keypress with current mouse position
      int x = 0;
      int y = 0;
      SDL_GetMouseState(&x, &y);
      handleKeys(mEvent.key.keysym.unicode, x, y);
    }
  }
  return false;
}

/*
 * Will be used to handle keys & Mouse position
 */
void ArcController::handleKeys(unsigned char key, int x, int y)
{
  // Toggle quad
  if (key == 'q')
  {
  }
}



ArcApp::ArcApp()
{
  mWindow = new ArcWindow();
  mEngine = new ArcEngine();
}

ArcApp::~ArcApp()
{
  delete mWindow;
  delete mEngine;
  destroy();
}


ArcWindow* ArcApp::getWindow()
{
  return mWindow;
}

ArcEngine* ArcApp::getEngine()
{
  return mEngine;
}

ArcApp* ArcApp::getInstance()
{
  if (mInstance == NULL)
  {
    mInstance = new ArcApp();
    return mInstance;
  }
  else
    return mInstance;
}

bool ArcApp::initialize()
{
  if (mWindow->initialize() == false) return false;
  if (mEngine->initialize() == false) return false;
  return true;
}

void ArcApp::start()
{
  bool quit = false;

  while (!quit)
  {
    quit = mController.listen();
    mEngine->update();
    mEngine->render();

    // Cap the frame rate
    if (mTimer.getTicks() < 1000 / mEngine->getFPS())
      SDL_Delay((1000 / mEngine->getFPS()) - mTimer.getTicks());
  }
}

void ArcApp::destroy()
{
}

int main(int argc, char** argv)
{

  ArcApp* Application = ArcApp::getInstance();
  if (Application->initialize() == false) return 1;
  Application->start();
  return 0;
}
