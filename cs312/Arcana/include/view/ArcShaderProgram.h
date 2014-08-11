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
  void setMatrix(ArcMatrix projectionMatrix);
  void setMatrices(ArcMatrix modelMatrix, ArcMatrix viewMatrix);
  void run(ArcCanvas &canvas, ArcMatrix m, ArcMatrix v);
  void destroy();
 private:
  GLuint mProgram;
  GLuint mProjectionMatrixUniformLocation;
  GLuint mViewMatrixUniformLocation;
  GLuint mModelMatrixUniformLocation;
  std::list<ArcShader> mShaders;
};

#endif
