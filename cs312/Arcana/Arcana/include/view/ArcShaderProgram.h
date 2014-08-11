#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <list>
#include "ArcUtils.h"
#include "ArcCanvas.h"

class ArcShaderProgram
{
 public:
  ArcShaderProgram();
  ~ArcShaderProgram();
  void initialize();
  void loadShader(const char* filename, GLenum shader_type);
  void link();
  void setUniforms();
  void setProjectionMatrix(ArcMatrix projectionMatrix);
  void setModelMatrix(ArcMatrix modelMatrix);
  void setViewMatrix(ArcMatrix viewMatrix);
  void run(ArcCanvas &canvas, ArcMatrix v);
  void destroy();
 private:
  GLuint mProgram;
  GLuint mProjectionMatrixUniformLocation;
  GLuint mViewMatrixUniformLocation;
  GLuint mModelMatrixUniformLocation;
  std::list<ArcShader> mShaders;
};

#endif
