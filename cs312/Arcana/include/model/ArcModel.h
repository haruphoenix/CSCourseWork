#ifndef MODEL_H
#define MODEL_H

#include "ArcVertexData.h"
#include <list>

class ArcModel
{

public:

  ArcModel();
  void initialize();
  void loadObjects();
  void registerData(ArcVertexData data);
  std::list<ArcVertexData> getData();

  void stopForward();
  void stopBackward();
  void stopLeft();
  void stopRight();

  void moveForward();
  void moveLeft();
  void moveRight();
  void moveBackward();

private:
  std::list<ArcVertexData> mData;
};

#endif
