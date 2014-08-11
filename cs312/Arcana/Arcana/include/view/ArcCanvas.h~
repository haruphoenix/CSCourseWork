
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
  GLuint mBufferIDs[3]; // Front & Back Buffers
  std::list<ArcVertexData> mVertexData;
  ArcVertex* mVertexArray;
  int        mVertexSize;
  GLuint*    mIndexArray;
  int        mIndexSize;
};

#endif
