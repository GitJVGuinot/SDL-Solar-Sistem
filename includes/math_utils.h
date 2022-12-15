/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Math_utils.h
 * Header to define all the defines that are used in the program.
 */

/////////////////////////
#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__ 1
/////////////////////////

#include <math.h>

#include "matrix_2.h"
#include "matrix_3.h"
#include "matrix_4.h"

#include "vector_2.h"
#include "vector_3.h"
#include "vector_4.h"

#include <algorithm>

#define PI 3.14159265358979323846f
#define Between(x, y, z) (x >= y && y >= z)

int InF();

int NaN();

class MathUtils
{
public:
  static float Clamp(float value, float minVal, float maxVal);

  static Vec3 TakeMin(Vec3* values, int n_values);
  static Vec3 TakeMax(Vec3* values, int n_values);

  static Vec4 HomogenisedVec(Vec4 v);

  static Vec3 Mat4TransformVec3(Mat4 m, Vec3 v);

  static Vec2 Vec3_Tr_Vec2(Vec3 v3);

  static Vec3 Rotate_Point_3D(Vec3 rot, Vec3 point);

  static void Orbit_Point(Vec3 orbit_center, Vec3 p_orbit, Vec3 &point);

  static Mat4 Mat4View(Vec3 camera, Vec3 target, Vec3 up);

  static Vec3 Vec2_Tr_Vec3(Vec2 v2, bool homogenised);

  static Vec3 Mat3TransformVec3(Mat3 m, Vec3 v);

  static float Radian_To_Euler(float radian);
  static float Euler_To_Radian(float euler);

private:
  MathUtils();
  MathUtils(const MathUtils &copy);
  ~MathUtils();
};

inline MathUtils::MathUtils() {}
inline MathUtils::MathUtils(const MathUtils &copy) {}
inline MathUtils::~MathUtils() {}
inline float MathUtils::Clamp(float value, float minVal, float maxVal)
{
  if (value < minVal)
    return minVal;
  if (value > maxVal)
    return maxVal;
  return value;
}

inline Vec3 MathUtils::TakeMin(Vec3* values, int n_values){
  Vec3 min = values[0];
  for(int i=1; i<n_values; i++){
    min.x = std::min(min.x, values[i].x);
    min.y = std::min(min.y, values[i].y);
    min.z = std::min(min.z, values[i].z);
  }
  return min;
}
inline Vec3 MathUtils::TakeMax(Vec3* values, int n_values){
  Vec3 max = values[0];
  for(int i=1; i<n_values; i++){
    max.x = std::max(max.x, values[i].x);
    max.y = std::max(max.y, values[i].y);
    max.z = std::max(max.z, values[i].z);
  }
  return max;
}

/////////////////////////
#endif /* __MATHUTILS_H__ */
/////////////////////////
