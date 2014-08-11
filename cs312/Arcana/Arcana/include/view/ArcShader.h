#ifndef ARCSHADER_H
#define ARCSHADER_H

#include <GL/glew.h>

class ArcShader
{
 public:
  ArcShader(const char* filename, GLenum shaderType);
  GLuint getHandle() {return mHandle;};
 private:
  GLuint mHandle;
  GLuint loadShader(const char* filename, GLenum shaderType);
};

#endif
