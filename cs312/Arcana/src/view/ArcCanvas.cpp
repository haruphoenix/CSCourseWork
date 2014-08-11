
#include "ArcCanvas.h"
#include "ArcUtils.h"
#include "GL/glew.h"
#include <list>
#include <iostream> // debugging

ArcCanvas::ArcCanvas()
{
}

void ArcCanvas::addItem(ArcVertexData data)
{
  mVertexData.push_back(data);
}

void ArcCanvas::formArrays()
{
  // Delete old arrays - Can cause seg-fault :-/
  //delete mVertexArray;
  //delete mIndexArray;

  // Find size of new arrays
  std::list<ArcVertexData>::iterator data;
  int vertexSize = 0;
  int indexSize  = 0;
  for (data = mVertexData.begin();
       data != mVertexData.end(); ++data)
  {
    mVertexSize += data->getVertexSize();
    mIndexSize  += data->getIndexSize();
  }

  mVertexArray = new ArcVertex[mVertexSize];
  mIndexArray  = new GLuint   [mIndexSize ];
  
  // Start copying over
  std::list<ArcVertex>::iterator vertex;
  std::list<GLuint>::iterator index;
  std::list<ArcVertex> vertexList;
  std::list<GLuint>    indexList;
  int v = 0; // vertex index
  int i = 0; // index  index
  int offset = 0;
  for (data = mVertexData.begin();
       data != mVertexData.end(); ++data)
  {
    vertexList = data->getVertices();
    for (vertex = vertexList.begin(); 
	 vertex != vertexList.end(); ++vertex, v++)
      mVertexArray[v] = *vertex;

    indexList  = data->getIndices();
    for (index = indexList.begin();
       index != indexList.end(); ++index, i++)
    mIndexArray[i] = *index + offset;
    offset += v;
  }

  //std::cout << "VERTICES\n";
  //for (i = 0; i < mVertexSize; i++)
  //{
  //  printVertex(mVertexArray[i]);
  //}

  //std::cout << "\nINDICES\n";
  //for (i = 0; i < mIndexSize; i += 3)
  //{
  //  std::cout << mIndexArray[i] << ", "
  //	      << mIndexArray[i + 1] << ", "
  //	      << mIndexArray[i + 2] << std::endl;
  //}

}

void ArcCanvas::generate()
{
  formArrays();

  glGenBuffers(2, &mBufferIDs[1]);
  ExitOnGLError("ERROR: Could not generate the buffer objects");

  glGenVertexArrays(1, &mBufferIDs[0]);
  ExitOnGLError("ERROR: Could not generate the VAO");

  glBindVertexArray(mBufferIDs[0]);
  ExitOnGLError("ERROR: Could not bind the VAO");

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  ExitOnGLError("ERROR: Could not enable vertex attributes");

  // check sizeof occasions
  glBindBuffer(GL_ARRAY_BUFFER, mBufferIDs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(ArcVertex) * mVertexSize, 
	       mVertexArray, GL_STATIC_DRAW);
  ExitOnGLError("ERROR: Could not bind the BVO to the VAO");

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
			sizeof(mVertexArray[0]), (GLvoid*)0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
			sizeof(mVertexArray[0]), (GLvoid*)
			sizeof(mVertexArray[0].Position));

  ExitOnGLError("ERROR: Could not set VAO attributes");

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferIDs[2]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mIndexSize,
	       mIndexArray, GL_STATIC_DRAW);
  ExitOnGLError("ERROR: Could not bind the IBO to the VAO");

  glBindVertexArray(0);
}

void ArcCanvas::draw()
{
  glBindVertexArray(mBufferIDs[0]);
  ExitOnGLError("ERROR: Could not bind the VAO for drawing purposes");
  glDrawElements(GL_TRIANGLES, mIndexSize, 
		 GL_UNSIGNED_INT, (GLvoid*)0);
  ExitOnGLError("ERROR: Couldn't draw");
  glBindVertexArray(0);
} 

void ArcCanvas::destroy()
{
  glDeleteBuffers(2, &mBufferIDs[1]);
  glDeleteVertexArrays(1, &mBufferIDs[0]);
  ExitOnGLError("ERROR: Could not destroy the buffer objects");
  delete mVertexArray;
  delete mIndexArray;
}

ArcCanvas::~ArcCanvas()
{
  destroy();
}
