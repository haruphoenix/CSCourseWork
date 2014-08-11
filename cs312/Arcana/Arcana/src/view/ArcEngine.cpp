#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ArcTimer.h"
#include "ArcEngine.h"
#include "ArcApp.h"
#include "ArcUtils.h"
#include "ArcShaderProgram.h"
#include "ArcCamera.h"
#include "ArcCanvas.h"
#include <iostream>
#include <list>

ArcEngine::ArcEngine()
{
  mFPS = 60;
  mWidth = 800;
  mHeight = 600;
  mCamera.setScreen(mWidth, mHeight);
}

ArcCamera& ArcEngine::getCamera()
{
  return mCamera;
}

ArcShaderProgram& ArcEngine::getShaderProgram()
{
  return mShaderProgram;
}

ArcCanvas& ArcEngine::getCanvas()
{
  return mCanvas;
}

int ArcEngine::getFPS()
{
  return mFPS;
}

void ArcEngine::resize(int width, int height)
{
  mWidth  = width;
  mHeight = height;
  mCamera.setScreen(mWidth, mHeight);
  glViewport(0, 0, mWidth, mHeight);
  mProjectionMatrix = CreateProjectionMatrix(60,
					     (float)mWidth / mHeight,
					     1.0f, 1000.0f);
  mShaderProgram.setProjectionMatrix(mProjectionMatrix);
}

/*
 * Initialize OpenGL
 */
bool ArcEngine::initialize()
{
  glewExperimental = GL_TRUE;

  // Initialize GLEW
  GLenum GlewInitResult = glewInit();

  if (GLEW_OK != GlewInitResult) {
    fprintf(stderr, "ERROR: %s\n", 
	    glewGetErrorString(GlewInitResult));
    return false;
  }

  fprintf(stdout, "INFO: OpenGL Version: %s\n", 
	  glGetString(GL_VERSION));

  glGetError();

  // Clear Window
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  ExitOnGLError("ERROR: Could not set OpenGL depth testing options");

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  ExitOnGLError("ERROR: Could not set OpenGL culling options");

  mProjectionMatrix = 
    CreateProjectionMatrix(60, (float)mWidth / mHeight,
  			   1.0f, 1000.0f);
  startShaderProgram();
  initializeCanvas();

  return true;
}


/*
 * Clears screen, then re-renders
 */
void ArcEngine::render()
{
  // Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Draw
  glClearColor(0, 0, 0.3f, 1);
  mShaderProgram.run(mCanvas, mCamera.getMatrix());
}

void ArcEngine::startShaderProgram()
{
  mShaderProgram.initialize();
  mShaderProgram.loadShader("src/view/shaders/vertexShader.glsl",
  			   GL_VERTEX_SHADER);
  mShaderProgram.loadShader("src/view/shaders/fragmentShader.glsl",
  			   GL_FRAGMENT_SHADER);
  mShaderProgram.link();
  mShaderProgram.setUniforms();
  mShaderProgram.setProjectionMatrix(mProjectionMatrix);
}

void ArcEngine::initializeCanvas()
{
  std::list<ArcVertexData> dataList = ArcApp::getInstance().
    getModel().getData();
  std::list<ArcVertexData>::iterator vertex;
  for (vertex = dataList.begin(); vertex != dataList.end(); ++vertex)
    mCanvas.addItem(*vertex); 
  mCanvas.generate();
}
