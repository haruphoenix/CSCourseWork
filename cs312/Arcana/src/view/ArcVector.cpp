#ifndef ArcVec
#define ArcVec

class ArcVec
{
 public:
  float x;
  float y;
  float z;
  float w;

  ArcVec();
  ArcVec(float, float, float);
  ArcVec(float, float, float, float);

  void zero();
  void normalize();
  static float dotProduct(const ArcVec &vec1, const ArcVec &vec2);
  static ArcVec crossProduct(const ArcVec &vec1, const ArcVec &vec2);
  static float getDistance(const ArcVec &vec1, const ArcVec &vec2);
  ArcVec operator + (const ArcVec &vector) const;
  ArcVec operator - (const ArcVec &vector) const;
  ArcVec operator * (const ArcVec &vector) const;
  ArcVec operator * (const float  &scalar) const;
  ArcVec operator / (const ArcVec &vector) const;
  ArcVec operator / (const float  &scalar) const;
  void  operator += (const ArcVec &vector);
  void  operator -= (const ArcVec &vector);
  void  operator *= (const ArcVec &vector);
  void  operator *= (const float  &scalar);
  void  operator /= (const ArcVec &vector);
  void  operator /= (const float  &scalar);
};

#endif
