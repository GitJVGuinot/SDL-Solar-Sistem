/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>
/// @file Math_utils.h

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

#include <random>

#define PI 3.14159265358979323846f
#define Between(x, y, z) (x >= y && y >= z)

/**
 * @brief Returns an integer representation of positive infinity.
 * @return Integer representation of positive infinity.
 */
int InF();

/**
 * @brief Returns an integer representation of not-a-number (NaN).
 * @return Integer representation of NaN.
 */
int NaN();

/**
 *  @class MathUtils
 *  @brief A class containing several mathematical utility functions.
 */
class MathUtils
{
public:
  /**
   * @brief Clamps a value between a minimum and maximum value.
   * @param value Value to be clamped.
   * @param minVal Minimum value.
   * @param maxVal Maximum value.
   * @return Clamped value.
   */
  static float Clamp(float value, float minVal, float maxVal);

  /**
   * @brief Generates a random integer between a given minimum and maximum value.
   *
   * @param max The maximum value (inclusive).
   * @param min The minimum value (inclusive).
   *
   * @return A random integer between `min` and `max`.
   */
  static int iRand(int max, int min);

  /**
   * @brief Generates a random float between a given minimum and maximum value.
   *
   * @param max The maximum value (inclusive).
   * @param min The minimum value (inclusive).
   *
   * @return A random float between `min` and `max`.
   */
  static float fRand(float max, float min);

  /**
   * @brief Returns the minimum value in an array of Vec3 values.
   * @param values Array of Vec3 values.
   * @param n_values Number of values in the array.
   * @return Minimum value.
   */
  static Vec3 TakeMin(Vec3 *values, int n_values);

  /**
   * @brief Returns the maximum value in an array of Vec3 values.
   * @param values Array of Vec3 values.
   * @param n_values Number of values in the array.
   * @return Maximum value.
   */
  static Vec3 TakeMax(Vec3 *values, int n_values);

  /**
   * @brief Homogenizes a Vec4 value.
   * @param v Vec4 value to be homogenized.
   * @return Homogenized Vec4 value.
   */
  static Vec4 HomogenisedVec(Vec4 v);

  /**
   * @brief Transforms a Vec3 value by a Mat4 matrix.
   * @param m Mat4 matrix.
   * @param v Vec3 value to be transformed.
   * @return Transformed Vec3 value.
   */
  static Vec3 Mat4TransformVec3(Mat4 m, Vec3 v);

  /**
   * @brief Converts a Vec3 value to a Vec2 value.
   * @param v3 Vec3 value to be converted.
   * @return Converted Vec2 value.
   */
  static Vec2 Vec3_Tr_Vec2(Vec3 v3);

  /**
   * @brief Rotates a 3D point by a specified rotation.
   * @param rot Rotation to be applied.
   * @param point Point to be rotated.
   * @return Rotated point.
   */
  static Vec3 Rotate_Point_3D(Vec3 rot, Vec3 point);

  /**
   * @brief Orbits a point around a specified center of orbit.
   * @param orbit_center Center of orbit.
   * @param p_orbit Orbit to be applied.
   * @param point Point to be orbited (passed by reference and updated).
   */
  static void Orbit_Point(Vec3 orbit_center, Vec3 p_orbit, Vec3 &point);

  /**
   *  @brief Generates a view matrix for a camera based on its position, target, and up direction.
   *  @param camera The position of the camera.
   *  @param front The front direction of the camera.
   *  @param up The up direction of the camera.
   *  @return The resulting view matrix.
   */
  static Mat4 Mat4View(Vec3 camera, Vec3 front, Vec3 up);

  /**
   *  @brief Transforms a two-dimensional vector into a three-dimensional vector.
   *  @param v2 The two-dimensional vector to transform.
   *  @param homogenised Whether the resulting vector should be homogenized.
   *  @return The resulting three-dimensional vector.
   */
  static Vec3 Vec2_Tr_Vec3(Vec2 v2, bool homogenised);

  /**
   *  @brief Applies a 3x3 matrix transformation to a 3D vector.
   *  @param m The 3x3 matrix to use for the transformation.
   *  @param v The 3D vector to transform.
   *  @return The resulting transformed vector.
   */
  static Vec3 Mat3TransformVec3(Mat3 m, Vec3 v);

  /**
   *  @brief Converts an angle from radians to degrees.
   *  @param radian The angle in radians.
   *  @return The angle in degrees.
   */
  static float Radian_To_Euler(float radian);

  /**
   *  @brief Converts an angle from degrees to radians.
   *  @param euler The angle in degrees.
   *  @return The angle in radians.
   */
  static float Euler_To_Radian(float euler);

private:
  /**
   *  @brief Private default constructor to prevent instantiation.
   */
  MathUtils();

  /**
   *  @brief Private copy constructor to prevent copy construction.
   */
  MathUtils(const MathUtils &copy);

  /**
   *  @brief Private destructor to prevent deletion.
   */
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

inline Vec3 MathUtils::TakeMin(Vec3 *values, int n_values)
{
  Vec3 min = values[0];
  for (int i = 1; i < n_values; i++)
  {
    min.x = std::min(min.x, values[i].x);
    min.y = std::min(min.y, values[i].y);
    min.z = std::min(min.z, values[i].z);
  }
  return min;
}

inline Vec3 MathUtils::TakeMax(Vec3 *values, int n_values)
{
  Vec3 max = values[0];
  for (int i = 1; i < n_values; i++)
  {
    max.x = std::max(max.x, values[i].x);
    max.y = std::max(max.y, values[i].y);
    max.z = std::max(max.z, values[i].z);
  }
  return max;
}

inline int MathUtils::iRand(int max, int min)
{
  return min + rand() % (max + 1);
}

inline float MathUtils::fRand(float max, float min)
{
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<float> distr(min, max);

  return distr(eng);
}

/////////////////////////
#endif /* __MATHUTILS_H__ */
/////////////////////////
