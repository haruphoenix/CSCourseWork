
#ifndef ARCCANVAS_H
#define ARCCANVAS_H

#include <GL/glew.h>
#include <list>
#include "ArcUtils.h"
#include "ArcVertexData.h"

class ArcCanvas
{
 public:
  ArcCanvas();
  ~ArcCanvas();
  void draw();
  void addItem(ArcVertexData data);
  void generate();
  void destroy();
 private:
  void formArrays();
  GLuint** mBufferIDs; // x, y, z, w & r, g, b, a
  GLuint* mVertexArrayIDs;
  std::list<ArcVertexData> mVertexData;
  ArcVertex** mVertexArrays;
  int*        mVertexSizes;
  GLuint**    mIndexArrays;
  int*        mIndexSizes;
};

#endif
