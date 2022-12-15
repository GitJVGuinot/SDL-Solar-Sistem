/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

/** @file Vector_3.h
 *--------------------------------------------------------------
 *  Math Library
 *  Vector 3 Class Definition.
 *--------------------------------------------------------------
 */

/////////////////////////
#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__ 1
/////////////////////////

#include <stdio.h>

class Vec3
{
public:
  inline void print(char *name = (char *)"Vec3")
  {
    printf("%s: %f, %f, %f\n", name, this->x, this->y, this->z);
  }

  Vec3(float value = 0);
  Vec3(float x, float y, float z);
  Vec3(float *values_array);
  Vec3(const Vec3 &other);
  ~Vec3();

  // Static funtions
  static inline Vec3 Sum(const Vec3 &first, const Vec3 &second)
  {
    return Vec3(first.x + second.x, first.y + second.y, first.z + second.z);
  }

  static inline Vec3 Sum(const Vec3 &first, float value)
  {
    return Vec3(first.x + value, first.y + value, first.z + value);
  }

  static inline Vec3 Substract(const Vec3 &first, const Vec3 &second)
  {
    return Vec3(first.x - second.x, first.y - second.y, first.z - second.z);
  }

  static inline Vec3 Substract(const Vec3 &first, float value)
  {
    return Vec3(first.x - value, first.y - value, first.z - value);
  }

  static inline Vec3 Multiply(const Vec3 &first, const Vec3 &second)
  {
    return Vec3(first.x * second.x, first.y * second.y, first.z * second.z);
  }

  static inline Vec3 Multiply(const Vec3 &first, float value)
  {
    return Vec3(first.x * value, first.y * value, first.z * value);
  }

  static inline Vec3 Divide(const Vec3 &first, float value)
  {
    return Vec3(first.x / value, first.y / value, first.z / value);
  }

  // Normal funtions
  inline Vec3 Sum(const Vec3 &other) const
  {
    return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
  }

  inline Vec3 Sum(float value) const
  {
    return Vec3(this->x + value, this->y + value, this->z + value);
  }

  inline Vec3 Substract(const Vec3 &other) const
  {
    return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
  }

  inline Vec3 Substract(float value) const
  {
    return Vec3(this->x - value, this->y - value, this->z - value);
  }

  inline Vec3 Multiply(const Vec3 &other) const
  {
    return Vec3(this->x * other.x, this->y * other.y, this->z * other.z);
  }

  inline Vec3 Multiply(float value) const
  {
    return Vec3(this->x * value, this->y * value, this->z * value);
  }

  inline Vec3 Divide(float value) const
  {
    return Vec3(this->x / value, this->y / value, this->z / value);
  }

  // Operators
  inline Vec3 operator+(const Vec3 &other) const
  {
    return Sum(other);
  }

  inline Vec3 operator+(float value) const
  {
    return Sum(value);
  }

  inline Vec3 &operator+=(const Vec3 &other)
  {
    Vec3 ret = Sum(other);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  inline Vec3 &operator+=(float value)
  {
    Vec3 ret = Sum(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  inline Vec3 operator-(const Vec3 &other) const
  {
    return Substract(other);
  }

  inline Vec3 operator-(float value) const
  {
    return Substract(value);
  }

  inline Vec3 &operator-=(const Vec3 &other)
  {
    Vec3 ret = Substract(other);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  inline Vec3 &operator-=(float value)
  {
    Vec3 ret = Substract(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  inline bool operator==(const Vec3 &value) const
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
    return true;
  }

  inline bool operator!=(const Vec3 &value) const
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
    return true;
  }

  inline void operator=(const Vec3 &other)
  {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
  }

  inline void operator=(float value)
  {
    this->x = value;
    this->y = value;
    this->z = value;
  }

  inline Vec3 operator*(float value) const
  {
    return Multiply(value);
  }

  inline Vec3 &operator*=(float value)
  {
    Vec3 ret = Multiply(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  inline Vec3 operator*(Vec3 other) const
  {
    return Multiply(other);
  }

  inline Vec3 &operator*=(Vec3 other)
  {
    Vec3 ret = Multiply(other);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  inline Vec3 operator/(float value) const
  {
    return Divide(value);
  }

  inline Vec3 &operator/=(float value)
  {
    Vec3 ret = Divide(value);
    this->x = ret.x;
    this->y = ret.y;
    this->z = ret.z;
    return *this;
  }

  float Magnitude() const;
  bool IsNormalized() const;
  void Normalize();
  Vec3 Normalized() const;
  float SqrMagnitude() const;
  void Scale(const Vec3 &scale);

  static Vec3 Lerp(const Vec3 a, const Vec3 b, float value);
  static Vec3 LerpUnclamped(const Vec3 a, const Vec3 b, float t);
  static float DotProduct(const Vec3 a, const Vec3 b);
  static float Angle(const Vec3 a, const Vec3 b);
  static Vec3 CrossProduct(const Vec3 a, const Vec3 b);
  static float Distance(const Vec3 a, const Vec3 b);
  static Vec3 Reflect(const Vec3 direction, const Vec3 normal);

  static const Vec3 up;
  static const Vec3 down;
  static const Vec3 right;
  static const Vec3 left;
  static const Vec3 forward;
  static const Vec3 back;
  static const Vec3 zero;
  static const Vec3 unit;

  float x;
  float y;
  float z;
};

/////////////////////////
#endif /* __VECTOR_3_H__ */
/////////////////////////
