
#ifndef ARCBUFFER_H
#define ARCBUFFER_H
#include <list>
#include "ArcUtils.h"

class ArcBuffer
{

 public:
  ArcBuffer();

 private:
  GLuint mVertexBuffer;
  GLuint mIndiceBuffer;
  Vertex* mVertices;
  GLuint* mIndices;
};

#endif
