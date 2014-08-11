
#include "ArcBuffer.h"
#include "GL/glew.h"

ArcBuffer::ArcBuffer(const Vertex vertices[], 
		      const GLuint indices[])
{
  mVertices = vertices;
  mIndices  = indices;
}

ArcBuffer::~ArcBuffer()
{
  delete mVertices;
  delete mIndices;
}
