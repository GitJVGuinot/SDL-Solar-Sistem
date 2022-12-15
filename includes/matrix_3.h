/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Matrix_3.h
 *--------------------------------------------------------------
 *  Math Library
 *  Matrix 3 Class Definition.
 *--------------------------------------------------------------
 *
 *   m0 m1 m2
 *   m3 m4 m5
 *   m6 m7 m8
 *
 *--------------------------------------------------------------
 */

////////////////////////
#ifndef __MATRIX_3_H__
#define __MATRIX_3_H__ 1
////////////////////////

#include "vector_2.h"
#include "vector_3.h"
#include <stdio.h>

class Mat3
{
public:
  inline void print(char *name = (char *)"Mat3")
  {
    printf("%s:\n", name);
    printf("%f, %f, %f,\n", this->m[0], this->m[1], this->m[2]);
    printf("%f, %f, %f,\n", this->m[3], this->m[4], this->m[5]);
    printf("%f, %f, %f\n", this->m[6], this->m[7], this->m[8]);
  }

  Mat3(const float &value = 0);
  Mat3(const float value[9]);
  Mat3(const Vec3 &a, const Vec3 &b, const Vec3 &c);
  Mat3(const Mat3 &copy);
  ~Mat3();

  inline Mat3 Sum(const Mat3 &other) const
  {
    float ret[9];
    for (int i = 0; i < 9; i++)
      ret[i] = this->m[i] + other.m[i];
    return Mat3(ret);
  }

  inline Mat3 Sum(float value) const
  {
    float ret[9];
    for (int i = 0; i < 9; i++)
      ret[i] = this->m[i] + value;
    return Mat3(ret);
  }

  inline Mat3 Substract(const Mat3 &other) const
  {
    float ret[9];
    for (int i = 0; i < 9; i++)
      ret[i] = this->m[i] - other.m[i];
    return Mat3(ret);
  }

  inline Mat3 Substract(float value) const
  {
    float ret[9];
    for (int i = 0; i < 9; i++)
      ret[i] = this->m[i] - value;
    return Mat3(ret);
  }

  inline Mat3 Multiply(const Mat3 &other) const
  {
    float a[9];

    a[0] = (this->m[0] * other.m[0]) + (this->m[3] * other.m[1]) + (this->m[6] * other.m[2]);
    a[1] = (this->m[1] * other.m[0]) + (this->m[4] * other.m[1]) + (this->m[7] * other.m[2]);
    a[2] = (this->m[2] * other.m[0]) + (this->m[5] * other.m[1]) + (this->m[8] * other.m[2]);
    a[3] = (this->m[0] * other.m[3]) + (this->m[3] * other.m[4]) + (this->m[6] * other.m[5]);
    a[4] = (this->m[1] * other.m[3]) + (this->m[4] * other.m[4]) + (this->m[7] * other.m[5]);
    a[5] = (this->m[2] * other.m[3]) + (this->m[5] * other.m[4]) + (this->m[8] * other.m[5]);
    a[6] = (this->m[0] * other.m[6]) + (this->m[3] * other.m[7]) + (this->m[6] * other.m[8]);
    a[7] = (this->m[1] * other.m[6]) + (this->m[4] * other.m[7]) + (this->m[7] * other.m[8]);
    a[8] = (this->m[2] * other.m[6]) + (this->m[5] * other.m[7]) + (this->m[8] * other.m[8]);

    return Mat3(a);
  }

  inline Mat3 Multiply(float value) const
  {
    float ret[9];
    for (int i = 0; i < 9; i++)
      ret[i] = this->m[i] * value;
    return Mat3(ret);
  }

  inline Mat3 Divide(float value) const
  {
    float ret[9];
    for (int i = 0; i < 9; i++)
      ret[i] = this->m[i] / value;
    return Mat3(ret);
  }

  // Operators
  inline Mat3 operator+(const Mat3 &other) const
  {
    return Sum(other);
  }

  inline Mat3 &operator+=(const Mat3 &other)
  {
    Mat3 ret = Sum(other);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline Mat3 operator+(float value) const
  {
    return Sum(value);
  }

  inline Mat3 &operator+=(float value)
  {
    Mat3 ret = Sum(value);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline Mat3 operator-(const Mat3 &other) const
  {
    return Substract(other);
  }

  inline Mat3 &operator-=(const Mat3 &other)
  {
    Mat3 ret = Substract(other);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline Mat3 operator-(float value) const
  {
    return Substract(value);
  }

  inline Mat3 &operator-=(float value)
  {
    Mat3 ret = Substract(value);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline Mat3 operator*(const Mat3 &other) const
  {
    return Multiply(other);
  }

  inline Mat3 &operator*=(const Mat3 &other)
  {
    Mat3 ret = Multiply(other);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline Mat3 operator*(float value) const
  {
    return Multiply(value);
  }

  inline Mat3 &operator*=(float value)
  {
    Mat3 ret = Multiply(value);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline Mat3 operator/(float value) const
  {
    return Divide(value);
  }

  inline Mat3 &operator/=(float value)
  {
    Mat3 ret = Divide(value);
    for (int i = 0; i < 9; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline bool operator==(const Mat3 &other) const
  {
    for (int i = 0; i < 9; ++i)
    {
      if (this->m[i] != other.m[i])
      {
        return false;
      }
    }
    return true;
  }

  inline bool operator!=(const Mat3 &other) const
  {
    for (int i = 0; i < 9; ++i)
    {
      if (this->m[i] != other.m[i])
      {
        return true;
      }
    }
    return false;
  }

  inline void operator=(const Mat3 &other)
  {
    for (int i = 0; i < 9; i++)
      this->m[i] = other.m[i];
  }

  static Mat3 Identity();

  float Determinant() const;
  static float Determinant(float value[9]);

  Mat3 Adjoint() const;
  bool GetInverse(Mat3 &out) const;
  bool Inverse();

  Mat3 Transpose() const;

  static Mat3 Translate(const Vec2 &position);
  static Mat3 Translate(float x, float y);

  static Mat3 Scale(const Vec2 &scale);

  static Mat3 Rotate(float rotation);

  Vec3 GetColum(int colum) const;
  Vec3 GetLine(int line) const;

  float m[9];
};

////////////////////////
#endif /* __MATRIX_3_H__ */
////////////////////////
