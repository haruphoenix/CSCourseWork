#include "ArcTerrain.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include "ArcVertexData.h"
#include "ArcMath.h"


float lerp(float n, float min, float max)
{
  float range = max - min;
  float newN  = n - min;
  return newN / range;
}

ArcTerrain::ArcTerrain(int size, float height)
{
  mMin = 0;
  mMax = 0;
  srand(time(NULL));
  mLevel = size * 2 + 1;
  mSize = 1;
  for (int i = 0; i < size; i++) mSize *= 2;
  mSize++;
  mMaxHeight = height;
  // Create map
  mMap = new float*[mSize];
  for (int i = 0; i < mSize; i++)
    mMap[i] = new float[mSize];
  // Clear map
  for (int i = 0; i < mSize; i++)
    for (int j = 0; j < mSize; j++)
      mMap[i][j] = 20;//rand() % (int)mMaxHeight;
}

ArcTerrain::~ArcTerrain()
{
  // Delete Map
  for (int i = 0; i < mSize; i++)
    delete mMap[i];
  delete mMap;
}

void ArcTerrain::generate()
{
  mMap[0        ][0        ] = -2;//(rand() % (int)mMaxHeight * 10) / 20;
  mMap[0        ][mSize - 1] = -2;//(rand() % (int)mMaxHeight * 10) / 20;
  mMap[mSize - 1][0        ] = -2;//(rand() % (int)mMaxHeight * 10) / 20;
  mMap[mSize - 1][mSize - 1] = -2;//(rand() % (int)mMaxHeight * 10) / 20;
  int tL[] = {0, 0};
  int tR[] = {mSize - 1, 0};
  int bL[] = {0, mSize - 1};
  int bR[] = {mSize - 1, mSize - 1};
  diamond(tL, tR, bL, bR, mLevel - 1);
  //diamondSquare(tL, tR, bL, bR, mLevel - 1);
}

void ArcTerrain::diamondSquare(int tL[], int tR[], int bL[], int bR[], int level)
{
  // PROBLEM: ACCESSING UNASSIGNED VALUES FOR AVERAGE
  //std::cout << "bR = " << bR[0] << ", " << bR[1] << std::endl;
  //std::cout << "bL = " << bL[0] << ", " << bL[1] << std::endl;
  // find average
  float average = (mMap[tL[0]][tL[1]] +
		   mMap[tR[0]][tR[1]] +
		   mMap[bL[0]][bL[1]] +
		   mMap[bR[0]][bR[1]]) / 4;
  // find midPoint
  int cX = (tL[0] + bR[0]) / 2;
  int cY = (tL[1] + bR[1]) / 2;
  int C[] = {cX, cY};


  mMap[cX][cY] = average + randomHeight(level--);
  if (mMap[cX][cY] > mMax) mMax = mMap[cX][cY];
  if (mMap[cX][cY] < mMin) mMin = mMap[cX][cY];
  int T[] = {cX, tL[1]};
  double tA = (mMap[tL[0]][tL[1]] + 
	       mMap[tR[0]][tR[1]] + 
	       mMap[cX][cY]) / 3;

  //std::cout << cX << ", " << bL[1] << std::endl;
  int B[] = {cX, bL[1]};
  double bA = (mMap[bL[0]][bL[1]] + 
	       mMap[bR[0]][bR[1]] + 
	       mMap[cX][cY]) / 3;

  int L[] = {tL[0], cY};
  double lA = (mMap[tL[0]][tL[1]] + 
	       mMap[bL[0]][bL[1]] + 
	       mMap[cX][cY]) / 3;

  int R[] = {tR[0], cY};
  double rA = (mMap[tR[0]][tR[1]] + 
	       mMap[bR[0]][bR[1]] + 
	       mMap[cX][cY]) / 3;
 
  // Set midpoint to average + random height
  mMap[T[0]][T[1]] = tA;
  mMap[B[0]][B[1]] = bA;
  mMap[L[0]][L[1]] = lA;
  mMap[R[0]][R[1]] = rA;
  //level--;

  if (level > 0)
  {
    diamondSquare(tL, T, L, C, level); // TL
    diamondSquare(T, tR, C, R, level); // TR
    diamondSquare(L, C, bL, B, level); // BL
    diamondSquare(C, R, B, bR, level); // BR
  }
}

void ArcTerrain::diamond(int tL[], int tR[], int bL[], int bR[], int level)
{
  //std::cout << "Diamond level " << level << ":\n";
  // find average
  float average = (mMap[tL[0]][tL[1]] +
		   mMap[tR[0]][tR[1]] +
		   mMap[bL[0]][bL[1]] +
		   mMap[bR[0]][bR[1]]) / 4;
  //std::cout << average << " ";
  // find midPoint
  int midX = (tL[0] + bR[0]) / 2;
  int midY = (tL[1] + bR[1]) / 2;
  
  // Set midpoint to average + random height
  mMap[midX][midY] = average + randomHeight(level--);
  if (mMap[midX][midY] > mMax) mMax = mMap[midX][midY];
  if (mMap[midX][midY] < mMin) mMin = mMap[midX][midY];
  //level--;
  if (level > 0)
  {
    // Find Diamonds
    int leftX   = 2 * tL[0] - midX;
    int rightX  = 2 * tR[0] - midX;
    int topY    = 2 * tL[1] - midY;
    int bottomY = 2 * bL[1] - midY;

    int left   [2] = {leftX ,  midY};
    int right  [2] = {rightX,  midY};
    int top    [2] = {midX,    topY};
    int bottom [2] = {midX, bottomY};
    int mid    [2] = {midX,    midY};

    // Square diamonds
    square(top, mid, tL, tR,    level); // top diamond
    square(mid, bottom, bL, bR, level); // bottom diamond
    square(tL, bL, left, mid,   level); // left diamond
    square(tR, bR, mid,  right, level); // right diamond
  }
}

void ArcTerrain::square(int T[], int B[], int L[], int R[], int level)
{
  //std::cout << "Square " << level << ":\n";
  int num2Average = 4;
  float sum = 0;
  float average = 0;
  bool top = true, bottom = true, left = true, right = true;
  // Error Check / find average
  if (((T[0] >= 0) && (T[1] >= 0)) && 
      (((T[0] < mSize) && (T[1] < mSize)))) sum += mMap[T[0]][T[1]];
  else {num2Average--; top = false;}
  if (((B[0] >= 0) && (B[1] >= 0)) && 
      (((B[0] < mSize) && (B[1] < mSize)))) sum += mMap[B[0]][B[1]];
  else {num2Average--; bottom = false;}
  if (((R[0] >= 0) && (R[1] >= 0)) && 
      (((R[0] < mSize) && (R[1] < mSize)))) sum += mMap[R[0]][R[1]];
  else {num2Average--; right = false;}
  if (((L[0] >= 0) && (L[1] >= 0)) && 
      (((L[0] < mSize) && (L[1] < mSize)))) sum += mMap[L[0]][L[1]];
  else {num2Average--; left = false;}
  if (num2Average != 0) average = sum / num2Average;
  //std::cout << average << " ";
  // Find midpoint
  int midX = T[0];
  int midY = L[1];
  // Set midpoint to average + random height
  mMap[midX][midY] = average+ randomHeight(level--);
  if (mMap[midX][midY] > mMax) mMax = mMap[midX][midY];
  if (mMap[midX][midY] < mMin) mMin = mMap[midX][midY];
  //level--;
  if (level > 0)
  {
    // find corners
    int mid[2] = {midX, midY};
    int tL[2] = {L[0], T[1]};
    int tR[2] = {R[0], T[1]};
    int bL[2] = {L[0], B[1]};
    int bR[2] = {R[0], B[1]};

    // diamond each quadrant if they exist
    if (top && left)     {diamond(tL, T, L, mid, level);}
    if (top && right)    {diamond(T, tR, mid, R, level);}
    if (bottom && left)  {diamond(L, mid, bL, B, level);}
    if (bottom && right) {diamond(mid, R, B, bR, level);}
  }
}

float ArcTerrain::randomHeight(int level)
{
  //std::cout << "LEVEL" << level << std::endl;
  //float den = 1.0;
  float den = mLevel - level;
  //for (int i = 0; i < (mLevel - level); i++) den *= 1.5;
  //std::cout << "DEN" << den << std::endl;
  float max = (float)mMaxHeight / ((float)(den) * 2);
  //std::cout << "MAX" << max << std::endl;
  max *= 10000;
  float random = (float)(rand() % (int)max);
  random /= 10000;
  //std::cout << "RANDOM" << random << std::endl;
  return random;
  /*
  int bigNumber = (int)mMaxHeight * level * level * 100;
  float random = (float)(rand() % bigNumber);
  random -= ((float)bigNumber / 2.0);
  random /= ((float)1000 * (mLevel - level) * (mLevel - level));
  return random;
  */
  /*  int bigNumber = (int)mMaxHeight * level * 100;
  float random = (float)(rand() % bigNumber);
  random -= ((float)bigNumber / 2.0);
  random /= ((float)1000 * (mLevel - level));
  return random;*/
}

void ArcTerrain::display()
{
  std::cout << std::setprecision(2) << std::endl;
  for (int i = 0; i < mSize; i++)
  {
    for (int j = 0; j < mSize; j++)
    {
      std::cout << mMap[i][j] << " ";
    }
    std::cout << std::endl << std::endl;
  }
}

ArcVertexData ArcTerrain::getVertexData()
{
  ArcVertexData data;
  int halfSize = mSize / 2;

  for (int i = 0; i < mSize; i++)
  {
    for (int j = 0; j < mSize; j++)
    {
      float value = mMap[i][j];
      float red   = getRed(value);
      float green = getGreen(value);//value / mMaxHeight;//getGreen(value);
      float blue  = getBlue(value);
      ArcVertex vertex = {{(i - halfSize), mMap[i][j], (j - halfSize), 1}, 
			  {red, green, blue, 1}};
      data.addVertex(vertex);
    }
  }
  
  for (int i = 0; i < mSize - 1; i++)
  {
    for (int j = 0; j < mSize - 1; j++)
    {
      data.addIndex(i * mSize + j);
      data.addIndex(i * mSize + j + 1);
      data.addIndex((i + 1) * mSize + j + 1);
      
      data.addIndex(i * mSize + j);
      data.addIndex((i + 1) * mSize + j + 1);
      data.addIndex((i + 1) * mSize + j);
    }
  }
  return data;
}

float ArcTerrain::getRed(float value)
{
  float relativeValue = value - mMin;
  float relativeMax = mMax - mMin;
  if ((relativeValue > ((float)relativeMax * (2.0/3.0))))
    return lerp(value, mMin, mMax);
  else return 0;
}

float ArcTerrain::getGreen(float value)
{
  float relativeValue = value - mMin;
  float relativeMax = mMax - mMin;
  if ((relativeValue < ((float)relativeMax * (2.0/3.0))) || 
      (relativeValue > ((float)relativeMax * (7.0/8.0))))
    return lerp(value, mMin, mMax);
  else return .5;
}

float ArcTerrain::getBlue(float value)
{
  float relativeValue = value - mMin;
  float relativeMax = mMax - mMin;
  if (relativeValue > ((float)relativeMax * (7.0/8.0)))
    return lerp(value, mMin, mMax);
  else return 0;
}

float lerp()
{
}
