/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Vector_2.h
 *--------------------------------------------------------------
 *  Math Library
 *  Vector 2 Class Definition.
 *--------------------------------------------------------------
 */

/////////////////////////
#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__ 1
/////////////////////////

#include <stdio.h>

class Vec2
{
public:
  inline void print(char *name = (char *)"Vec2")
  {
    printf("%s: %f, %f\n", name, this->x, this->y);
  }

  Vec2(float value = 0);
  Vec2(float x, float y);
  Vec2(float *values_array);
  Vec2(const Vec2 &copy);
  ~Vec2();

  // Static funtions
  static inline Vec2 Sum(const Vec2 &first, const Vec2 &second)
  {
    return Vec2(first.x + second.x, first.y + second.y);
  }
  static inline Vec2 Sum(const Vec2 &first, float value)
  {
    return Vec2(first.x + value, first.y + value);
  }
  static inline Vec2 Substract(const Vec2 &first, const Vec2 &second)
  {
    return Vec2(first.x - second.x, first.y - second.y);
  }
  static inline Vec2 Substract(const Vec2 & first, float value)
  {
    return Vec2(first.x - value, first.y - value);
  }
  static inline Vec2 Multiply(const Vec2 &first, const Vec2 &second)
  {
    return Vec2(first.x * second.x, first.y * second.y);
  }
  static inline Vec2 Multiply(const Vec2 & first, float value)
  {
    return Vec2(first.x * value, first.y * value);
  }
  static inline Vec2 Divide(const Vec2 & first, float value)
  {
    return Vec2(first.x / value, first.y / value);
  };

  // Normal functions
  inline Vec2 Sum(const Vec2 &other) const
  {
    return Vec2(this->x + other.x, this->y + other.y);
  }
  inline Vec2 Sum(float value) const
  {
    return Vec2(this->x + value, this->y + value);
  }
  inline Vec2 Substract(const Vec2 &other) const
  {
    return Vec2(this->x - other.x, this->y - other.y);
  }
  inline Vec2 Substract(float value) const
  {
    return Vec2(this->x - value, this->y - value);
  }
  inline Vec2 Multiply(const Vec2 &other) const
  {
    return Vec2(this->x * other.x, this->y * other.y);
  }
  inline Vec2 Multiply(float value) const
  {
    return Vec2(this->x * value, this->y * value);
  }
  inline Vec2 Divide(float value) const
  {
    return Vec2(this->x / value, this->y / value);
  };

  inline Vec2 operator+(const Vec2 &other) const
  {
    return Sum(other);
  }
  inline Vec2 &operator+=(const Vec2 &other)
  {
    Vec2 ret = Sum(other);
    this->x = ret.x;
    this->y = ret.y;
    return *this;
  }

  inline Vec2 operator+(float value) const
  {
    return Sum(value);
  }
  inline Vec2 &operator+=(float value)
  {
    Vec2 ret = Sum(value);
    this->x = ret.x;
    this->y = ret.y;
    return *this;
  }

  inline Vec2 operator-() const
  {
    return Vec2(-this->x, -this->y);
  }

  inline Vec2 operator-(const Vec2 &other) const
  {
    return Substract(other);
  }

  inline Vec2 operator-(float value) const
  {
    return Substract(value);
  }

  inline Vec2 &operator-=(const Vec2 &other)
  {
    Vec2 ret = Substract(other);
    this->x = ret.x;
    this->y = ret.y;
    return *this;
  }

  inline Vec2 &operator-=(float value)
  {
    Vec2 ret = Substract(value);
    this->x = ret.x;
    this->y = ret.y;
    return *this;
  }

  inline bool operator==(const Vec2 &value) const
  {
    if (this->x != value.x)
    {
      return false;
    }
    if (this->y != value.y)
    {
      return false;
    }
    return true;
  }

  inline bool operator!=(const Vec2 &value) const
  {
    if (this->x == value.x)
    {
      return false;
    }
    if (this->y == value.y)
    {
      return false;
    }
    return true;
  }

  inline void operator=(const Vec2 &other)
  {
    this->x = other.x;
    this->y = other.y;
  }

  inline void operator=(float value)
  {
    this->x = value;
    this->y = value;
  }

  inline Vec2 operator*(float value) const
  {
    return Multiply(value);
  }

  inline Vec2 &operator*=(float value)
  {
    Vec2 ret = Multiply(value);
    this->x = ret.x;
    this->y = ret.y;
    return *this;
  }

  inline Vec2 operator/(float value) const
  {
    return Divide(value);
  }

  inline Vec2 &operator/=(float value)
  {
    Vec2 ret = Divide(value);
    this->x = ret.x;
    this->y = ret.y;
    return *this;
  }

  float Magnitude() const;
  bool IsNormalized() const;
  void Normalize();
  Vec2 Normalized() const;

  void Scale(const Vec2 scale);

  float SqrMagnitude() const;
  static float Distance(const Vec2 a, const Vec2 b);

  static float DotProduct(Vec2 a, Vec2 b);

  static Vec2 Lerp(const Vec2 a, const Vec2 b, float t);
  static Vec2 LerpUnclamped(const Vec2 a, const Vec2 b, float t);

  static const Vec2 up;
  static const Vec2 down;
  static const Vec2 right;
  static const Vec2 left;
  static const Vec2 zero;
  static const Vec2 one;

  float x;
  float y;
};

/////////////////////////
#endif /* __VECTOR_2_H__ */
/////////////////////////
