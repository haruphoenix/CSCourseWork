#include <GL/glew.h>
#include <list>
#include "ArcShader.h"
#include "ArcUtils.h"
#include "ArcShaderProgram.h"
#include <iostream>

ArcShaderProgram::ArcShaderProgram()
{
}

ArcShaderProgram::~ArcShaderProgram()
{
  destroy();
}

void ArcShaderProgram::initialize()
{
  mProgram = glCreateProgram();
  ExitOnGLError("ERROR: Could not create the shader program");
}

void ArcShaderProgram::loadShader(const char* filename, GLenum shader_type)
{
  ArcShader shader(filename, shader_type);
  glAttachShader(mProgram, shader.getHandle());
  mShaders.push_back(shader);
}

void ArcShaderProgram::link()
{
  glLinkProgram(mProgram);
  ExitOnGLError("ERROR: Could not link the shader program");
}

void ArcShaderProgram::setUniforms()
{
  mModelMatrixUniformLocation = 
    glGetUniformLocation(mProgram, "ModelMatrix");
  mViewMatrixUniformLocation =
    glGetUniformLocation(mProgram, "ViewMatrix");
  mProjectionMatrixUniformLocation =
    glGetUniformLocation(mProgram, "ProjectionMatrix");
  
  ExitOnGLError("ERROR: Could not get the shader uniform locations");
}

void ArcShaderProgram::setProjectionMatrix(ArcMatrix projectionMatrix)
{
  glUseProgram(mProgram);
  ExitOnGLError("ERROR: Could not use the shader program");
  //std::cout << "Projection Matrix";
  //printMatrix(projectionMatrix);
  glUniformMatrix4fv(mProjectionMatrixUniformLocation, 1,
		     GL_FALSE, projectionMatrix.m);
  glUseProgram(0);
}

void ArcShaderProgram::setModelMatrix(ArcMatrix modelMatrix)
{
  //glUseProgram(mProgram);
  ExitOnGLError("ERROR: Could not use the shader program");
  //std::cout << "Model Matrix";
  //printMatrix(modelMatrix);
  glUniformMatrix4fv(mModelMatrixUniformLocation, 1,
		     GL_FALSE, modelMatrix.m);
  //glUseProgram(0);
}

void ArcShaderProgram::setViewMatrix(ArcMatrix viewMatrix)
{
  //glUseProgram(mProgram);
  ExitOnGLError("ERROR: Could not use the shader program");
  //std::cout << "View Matrix";
  //printMatrix(viewMatrix);
  glUniformMatrix4fv(mViewMatrixUniformLocation, 1,
		     GL_FALSE, viewMatrix.m);
  //glUseProgram(0);
}

void ArcShaderProgram::run(ArcCanvas &canvas,
			   ArcMatrix view)
{
  glUseProgram(mProgram);
  ExitOnGLError("ERROR: Could not use the shader program");
  setViewMatrix(view);
  canvas.draw();
  glUseProgram(0);
}

void ArcShaderProgram::destroy()
{
  std::list<ArcShader>::iterator i;

  for (i = mShaders.begin(); i != mShaders.end(); ++i)
  {
    glDetachShader(mProgram, i->getHandle());
    glDeleteShader(i->getHandle());
  }

  mShaders.clear();

  glDeleteProgram(mProgram);
  ExitOnGLError("ERROR: Could not destroy the shaders");
}
