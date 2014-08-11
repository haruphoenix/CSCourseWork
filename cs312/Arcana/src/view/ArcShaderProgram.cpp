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

void ArcShaderProgram::setMatrix(ArcMatrix projectionMatrix)
{
  glUseProgram(mProgram);
  ExitOnGLError("ERROR: Could not use the shader program");
  glUniformMatrix4fv(mProjectionMatrixUniformLocation, 1,
		     GL_FALSE, projectionMatrix.m);
  glUseProgram(0);
}

void ArcShaderProgram::setMatrices(ArcMatrix modelMatrix, ArcMatrix viewMatrix)
{

  glUniformMatrix4fv(mModelMatrixUniformLocation, 1,
		     GL_FALSE, modelMatrix.m);
  
  glUniformMatrix4fv(mViewMatrixUniformLocation, 1,
		     GL_FALSE, viewMatrix.m);

  ExitOnGLError("ERROR: Could not set the shader uniforms");
}

void ArcShaderProgram::run(ArcCanvas &canvas, 
			   ArcMatrix model, 
			   ArcMatrix view)
{
  glUseProgram(mProgram);
  ExitOnGLError("ERROR: Could not use the shader program");

  setMatrices(model, view);
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
