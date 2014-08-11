#ifndef TERRA_H
#define TERRA_H

#include "ArcVertexData.h"

class ArcTerrain
{
 public:
  ArcTerrain(int size, float height);
  ~ArcTerrain();
  void generate();
  void display();
  ArcVertexData getVertexData();
 private:
  float randomHeight(int level);
  void diamond(int tL[], int tR[], int bL[], int bR[], int level);
  void square(int T[], int B[], int L[], int R[], int level);
  void diamondSquare(int tL[], int tR[], int bL[], int bR[], 
		     int level);
  float** mMap;
  int mSize;
  int mLevel;
  float mMaxHeight;
  float getRed(float value);
  float getGreen(float value);
  float getBlue(float value);
  float mMax;
  float mMin;
};

#endif
