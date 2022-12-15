/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

/** @file Vector_4.h
 *--------------------------------------------------------------
 *  Math Library
 *  Vector 4 Class Definition.
 *--------------------------------------------------------------
 */

/////////////////////////
#ifndef __VECTOR_4_H__
#define __VECTOR_4_H__ 1
/////////////////////////

#include "vector_3.h"
#include "matrix_3.h"
#include <stdio.h>

class Vec4
{
public:
  inline void print(char *name = (char *)"Vec4")
  {
    printf("%s: %f, %f, %f, %f\n", name, this->x, this->y, this->z, this->w);
  }

  Vec4(float value = 0);
  Vec4(float x, float y, float z, float w);
  Vec4(float *values_array);
  Vec4(const Vec4 &other);
  ~Vec4();

  // Static functions
  static inline Vec4 Sum(const Vec4 &first, const Vec4 &second)
  {
    return Vec4(first.x + second.x, first.y + second.y, first.z + second.z, first.w + second.w);
  }

  static inline Vec4 Sum(const Vec4 &first, float value)
  {
    return Vec4(first.x + value, first.y + value, first.z + value, first.w + value);
  }

  static inline Vec4 Substract(const Vec4 &first, const Vec4 &second)
  {
    return Vec4(first.x - second.x, first.y - second.y, first.z - second.z, first.w - second.w);
  }

  static inline Vec4 Substract(const Vec4 &first, float value)
  {
    return Vec4(first.x - value, first.y - value, first.z - value, first.w - value);
  }

  static inline Vec4 Multiply(const Vec4 &first, const Vec4 &second)
  {
    return Vec4(first.x * second.x, first.y * second.y, first.z * second.z, first.w * second.w);
  }

  static inline Vec4 Multiply(const Vec4 &first, float value)
  {
    return Vec4(first.x * value, first.y * value, first.z * value, first.w * value);
  }

  static inline Vec4 Divide(const Vec4 &first, float value)
  {
    return Vec4(first.x / value, first.y / value, first.z / value, first.w / value);
  }

  // Normal functions
  inline Vec4 Sum(const Vec4 &other) const
  {
    return Vec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
  }

  inline Vec4 Sum(float value) const
  {
    return Vec4(this->x + value, this->y + value, this->z + value, this->w + value);
  }

  inline Vec4 Substract(const Vec4 &other) const
  {
    return Vec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
  }

  inline Vec4 Substract(float value) const
  {
    return Vec4(this->x - value, this->y - value, this->z - value, this->w - value);
  }

  inline Vec4 Multiply(const Vec4 &other) const
  {
    return Vec4(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
  }

  inline Vec4 Multiply(float value) const
  {
    return Vec4(this->x * value, this->y * value, this->z * value, this->w * value);
  }

  inline Vec4 Divide(float value) const
  {
    return Vec4(this->x / value, this->y / value, this->z / value, this->w / value);
  }

  // Operators
  inline Vec4 operator+(const Vec4 &other) const
  {
    return Sum(other);
  }

  inline Vec4 operator+(float value) const
  {
    return Sum(value);
  }

  inline void operator+=(const Vec4 &other)
  {
    Vec4 ret = Sum(other);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    this->w = ret.w;
  }

  inline void operator+=(float value)
  {
    Vec4 ret = Sum(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    this->w = ret.w;
  }

  inline Vec4 operator-(const Vec4 &other) const
  {
    return Substract(other);
  }

  inline Vec4 operator-(float value) const
  {
    return Substract(value);
  }

  inline void operator-=(const Vec4 &other)
  {
    Vec4 ret = Substract(other);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    this->w = ret.w;
  }

  inline void operator-=(float value)
  {
    Vec4 ret = Substract(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    this->w = ret.w;
  }

  inline bool operator==(const Vec4 &value) const
  {
    if (this->x != value.x)
    {
      return false;
    }
    if (this->y != value.y)
    {
      return false;
    }
    if (this->z != value.z)
    {
      return false;
    }
    if (this->w != value.w)
    {
      return false;
    }
    return true;
  }

  inline bool operator!=(const Vec4 &value) const
  {
    if (this->x == value.x)
    {
      return false;
    }
    if (this->y == value.y)
    {
      return false;
    }
    if (this->z == value.z)
    {
      return false;
    }
    if (this->w == value.w)
    {
      return false;
    }
    return true;
  }

  inline void operator=(const Vec4 &other)
  {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
  }

  inline Vec4 operator*(float value) const
  {
    return Multiply(value);
  }

  inline void operator*=(float value)
  {
    Vec4 ret = Multiply(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    this->w = ret.w;
  }

  inline Vec4 operator/(float value) const
  {
    return Divide(value);
  }

  inline void operator/=(float value)
  {
    Vec4 ret = Divide(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    this->w = ret.w;
  }

  float Magnitude() const;
  bool IsNormalized() const;
  void Normalize();
  Vec4 Normalized() const;
  void Scale(Vec4 scale);
  float SqrMagnitude() const;

  static float Distance(const Vec4 a, const Vec4 b);
  static float DotProduct(Vec4 a, Vec4 b);
  static Vec4 Lerp(const Vec4 a, const Vec4 b, float value);

  static const Vec4 one;
  static const Vec4 zero;

  float x;
  float y;
  float z;
  float w;
};

/////////////////////////
#endif /* __VECTOR_4_H__ */
/////////////////////////
