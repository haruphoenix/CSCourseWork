#include "ArcApp.h"
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
  mVertexSizes = new int[mVertexData.size()];
  mIndexSizes  = new int[mVertexData.size()];

  int sizeIndex = 0;

  for (data = mVertexData.begin();
       data != mVertexData.end(); ++data, sizeIndex++)
  {
    mVertexSizes[sizeIndex] = data->getVertexSize();
    mIndexSizes[sizeIndex]  = data->getIndexSize();
  }

  mVertexArrays = new ArcVertex*[mVertexData.size()];
  mIndexArrays  = new GLuint*   [mVertexData.size()];

  for (sizeIndex = 0; sizeIndex < mVertexData.size(); sizeIndex++)
  {
    mVertexArrays[sizeIndex] = new ArcVertex[mVertexSizes[sizeIndex]];
    mIndexArrays[sizeIndex]  = new GLuint[mIndexSizes[sizeIndex]];
  }
  
  // Start copying over
  std::list<ArcVertex>::iterator vertex;
  std::list<GLuint>::iterator index;
  std::list<ArcVertex> vertexList;
  std::list<GLuint>    indexList;
  int v = 0; // vertex index
  int i = 0; // index  index

  int dataIndex = 0;
  for (data = mVertexData.begin();
       data != mVertexData.end(); ++data, dataIndex++)
  {
    v = 0;
    i = 0;
    vertexList = data->getVertices();
    for (vertex = vertexList.begin(); 
	 vertex != vertexList.end(); ++vertex, v++)
      mVertexArrays[dataIndex][v] = *vertex;
    indexList  = data->getIndices();
    for (index = indexList.begin();
       index != indexList.end(); ++index, i++)
      mIndexArrays[dataIndex][i] = *index;
  }
  /*
  for (int k = 0; k < mVertexData.size(); k++)
  {
    printVertex(mVertexArrays[k][0]);
    std::cout << std::endl;
  }
  */
}

void ArcCanvas::generate()
{
  formArrays();

  mBufferIDs = new GLuint*[mVertexData.size()];
  for (int i = 0; i < mVertexData.size(); i++)
    mBufferIDs[i] = new GLuint[2];

  mVertexArrayIDs = new GLuint[mVertexData.size()];
  glGenVertexArrays(mVertexData.size(), &mVertexArrayIDs[0]);
  ExitOnGLError("ERROR: Could not generate the VAOs");

  for (int i = 0; i < mVertexData.size(); i++)
  {
    glGenBuffers(2, &mBufferIDs[i][0]);
    ExitOnGLError("ERROR: Could not generate the buffer objects");

    glBindVertexArray(mVertexArrayIDs[i]);
    ExitOnGLError("ERROR: Could not bind the VAOs");

    glEnableVertexAttribArray(0); //xyzw
    glEnableVertexAttribArray(1); //rgba
    ExitOnGLError("ERROR: Could not enable vertex attributes");

    // check sizeof occasions
    glBindBuffer(GL_ARRAY_BUFFER, mBufferIDs[i][0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ArcVertex) * mVertexSizes[i], 
		 mVertexArrays[i], GL_STATIC_DRAW);
    ExitOnGLError("ERROR: Could not bind the BVO to the VAO");

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
			  sizeof(mVertexArrays[i][0]), (GLvoid*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
			  sizeof(mVertexArrays[i][0]), (GLvoid*)
			  sizeof(mVertexArrays[i][0].Position));

    ExitOnGLError("ERROR: Could not set VAO attributes");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferIDs[i][1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mIndexSizes[i],
		 mIndexArrays[i], GL_STATIC_DRAW);
    ExitOnGLError("ERROR: Could not bind the IBO to the VAO");

    glBindVertexArray(0);
  }
}

void ArcCanvas::draw()
{
  int n = 0;
  std::list<ArcVertexData>::iterator i;
  
  for (i = mVertexData.begin(); i != mVertexData.end(); ++i)
  {
    //    std::cout << n << std::endl;
    glBindVertexArray(mVertexArrayIDs[n++]);
    ExitOnGLError("ERROR: Could not bind the VAO for drawing purposes");
  
    //ArcMatrix modelMatrix = i->getModelMatrix();
    //printMatrix(modelMatrix);
    ArcApp::getInstance().getEngine().getShaderProgram().
      setModelMatrix(i->getModelMatrix());
    
    glDrawElements(GL_TRIANGLES, i->getNumIndices(), 
		   GL_UNSIGNED_INT, (GLvoid*)0);
    //starts at beginning each time
    //n++;
    //std::cout << n << std::endl;
    ExitOnGLError("ERROR: Couldn't draw");
    glBindVertexArray(0);
  }
} 

void ArcCanvas::destroy()
{
  for (int i = 0; i < mVertexData.size(); i++)
    glDeleteBuffers(2, &mBufferIDs[i][0]);
  for (int i = 0; i < mVertexData.size(); i++)
    glDeleteVertexArrays(mVertexSizes[i], &mVertexArrayIDs[i]);

    ExitOnGLError("ERROR: Could not destroy the buffer objects");

  for (int i = 0; i < mVertexData.size(); i++)
  {
    delete mVertexArrays[i];
    delete mIndexArrays[i];
    delete mBufferIDs[i];
  }

  delete mVertexArrays;
  delete mIndexArrays;
  delete mVertexArrayIDs;
  delete mBufferIDs;
  
  std::list<ArcVertexData>::iterator i;
  for (i = mVertexData.begin(); i != mVertexData.end(); ++i)
    i->destroy();
}

ArcCanvas::~ArcCanvas()
{
  destroy();
}
