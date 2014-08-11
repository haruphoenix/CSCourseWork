#include <iostream>
using namespace std;

float LinearTransform(float x, float C, float D, float E, float F)
{
  float A = (F - E) / (D - C);
  float B = E - C * ((F - E) / (D - C));
  return A * x + B;
}

void print(float x, float y, float C, float D, float E, float F)
{
  cout << x << " on a scale from " << C << " to " << D
       << " projected onto a scale from " << E << " to " << F
       << " is " << y << endl;
}

int main(int argc, char** argv)
{
  float leftStart = -4;
  float rightStart = -2;
  float leftEnd    = 10;
  float rightEnd   = 20;
  for (int x = leftStart; x <= rightStart; x++)
  {
     float y = LinearTransform(x, leftStart, rightStart, leftEnd, rightEnd);
     print (x, y, leftStart, rightStart, leftEnd, rightEnd);
  }
  return 0;
}