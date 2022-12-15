/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Matrix_4.h
 *--------------------------------------------------------------
 *  Math Library
 *  Matrix 3 Class Definition.
 *--------------------------------------------------------------
 *
 *   m0  m1  m2  m3
 *   m4  m5  m6  m7
 *   m8  m9  m10 m11
 *   m12 m13 m14 m15
 *
 *--------------------------------------------------------------
 */

////////////////////////
#ifndef __MATRIX_4_H__
#define __MATRIX_4_H__ 1
////////////////////////

#include "vector_3.h"
#include "vector_4.h"
#include "matrix_3.h"
#include <stdio.h>

class Mat4
{
public:
  inline void print(char *name = (char *)"Mat4")
  {
    printf("%s:\n", name);
    printf("%f, %f, %f, %f,\n", this->m[0], this->m[1], this->m[2], this->m[3]);
    printf("%f, %f, %f, %f,\n", this->m[4], this->m[5], this->m[6], this->m[7]);
    printf("%f, %f, %f, %f,\n", this->m[8], this->m[9], this->m[10], this->m[11]);
    printf("%f, %f, %f, %f\n", this->m[12], this->m[13], this->m[14], this->m[15]);
  }

  Mat4(const float &value = 0);
  Mat4(const float a[16]);
  Mat4(const Vec4 &a, const Vec4 &b, const Vec4 &c, const Vec4 &d);
  Mat4(const Mat4 &copy);

  ~Mat4();

  static Mat4 Identity();
  static Mat4 Projection();

  float Determinant() const;
  Mat4 Adjoint() const;
  bool GetInverse(Mat4 &out) const;
  bool Inverse();

  Mat4 Transpose() const;

  static Mat4 Translate(const Vec3 &distance);
  static Mat4 Translate(float x, float y, float z);

  static Mat4 Scale(const Vec3 &scale);
  static Mat4 Scale(float x, float y, float z);

  static Mat4 RotateX(float radians);
  static Mat4 RotateY(float radians);
  static Mat4 RotateZ(float radians);

  static Mat4 GetTransform(const Vec3 &translate, const Vec3 &scale,
                           float rotateX, float rotateY, float rotateZ);

  static Mat4 GetTransform(float trans_x, float trans_y, float trans_z,
                           float scale_x, float scale_y, float scale_Z,
                           float rotateX, float rotateY, float rotateZ);

  Mat4 PerspectiveMatrix(float fov, float aspect,
                         float near, float far) const;

  Mat4 OrthoMatrix(float right, float left, float top, float bottom,
                   float near, float far) const;

  Vec4 GetColum(int colum) const;
  Vec4 GetLine(int line) const;

  inline Mat4 Sum(const Mat4 &other) const
  {
    float ret[16];
    for (int i = 0; i < 16; i++)
      ret[i] = this->m[i] + other.m[i];
    return Mat4(ret);
  }

  inline Mat4 Sum(float value) const
  {
    float ret[16];
    for (int i = 0; i < 16; i++)
      ret[i] = this->m[i] + value;
    return Mat4(ret);
  }

  inline Mat4 Substract(const Mat4 &other) const
  {
    float ret[16];
    for (int i = 0; i < 16; i++)
      ret[i] = this->m[i] - other.m[i];
    return Mat4(ret);
  }

  inline Mat4 Substract(float value) const
  {
    float ret[16];
    for (int i = 0; i < 16; i++)
      ret[i] = this->m[i] - value;
    return Mat4(ret);
  }

  inline Mat4 Multiply(const Mat4 &other) const
  {
    float a[16];

    a[0] = (this->m[0] * other.m[0]) + (this->m[4] * other.m[1]) + (this->m[8] * other.m[2]) + (this->m[12] * other.m[3]);
    a[1] = (this->m[1] * other.m[0]) + (this->m[5] * other.m[1]) + (this->m[9] * other.m[2]) + (this->m[13] * other.m[3]);
    a[2] = (this->m[2] * other.m[0]) + (this->m[6] * other.m[1]) + (this->m[10] * other.m[2]) + (this->m[14] * other.m[3]);
    a[3] = (this->m[3] * other.m[0]) + (this->m[7] * other.m[1]) + (this->m[11] * other.m[2]) + (this->m[15] * other.m[3]);
    a[4] = (this->m[0] * other.m[4]) + (this->m[4] * other.m[5]) + (this->m[8] * other.m[6]) + (this->m[12] * other.m[7]);
    a[5] = (this->m[1] * other.m[4]) + (this->m[5] * other.m[5]) + (this->m[9] * other.m[6]) + (this->m[13] * other.m[7]);
    a[6] = (this->m[2] * other.m[4]) + (this->m[6] * other.m[5]) + (this->m[10] * other.m[6]) + (this->m[14] * other.m[7]);
    a[7] = (this->m[3] * other.m[4]) + (this->m[7] * other.m[5]) + (this->m[11] * other.m[6]) + (this->m[15] * other.m[7]);
    a[8] = (this->m[0] * other.m[8]) + (this->m[4] * other.m[9]) + (this->m[8] * other.m[10]) + (this->m[12] * other.m[11]);
    a[9] = (this->m[1] * other.m[8]) + (this->m[5] * other.m[9]) + (this->m[9] * other.m[10]) + (this->m[13] * other.m[11]);
    a[10] = (this->m[2] * other.m[8]) + (this->m[6] * other.m[9]) + (this->m[10] * other.m[10]) + (this->m[14] * other.m[11]);
    a[11] = (this->m[3] * other.m[8]) + (this->m[7] * other.m[9]) + (this->m[11] * other.m[10]) + (this->m[15] * other.m[11]);
    a[12] = (this->m[0] * other.m[12]) + (this->m[4] * other.m[13]) + (this->m[8] * other.m[14]) + (this->m[12] * other.m[15]);
    a[13] = (this->m[1] * other.m[12]) + (this->m[5] * other.m[13]) + (this->m[9] * other.m[14]) + (this->m[13] * other.m[15]);
    a[14] = (this->m[2] * other.m[12]) + (this->m[6] * other.m[13]) + (this->m[10] * other.m[14]) + (this->m[14] * other.m[15]);
    a[15] = (this->m[3] * other.m[12]) + (this->m[7] * other.m[13]) + (this->m[11] * other.m[14]) + (this->m[15] * other.m[15]);

    return Mat4(a);
  }

  inline Mat4 Multiply(float value) const
  {
    float ret[16];
    for (int i = 0; i < 16; i++)
      ret[i] = this->m[i] * value;
    return Mat4(ret);
  }

  inline Mat4 Divide(float value) const
  {
    float ret[16];
    for (int i = 0; i < 16; i++)
      ret[i] = this->m[i] / value;
    return Mat4(ret);
  }

  inline Mat4 operator+(const Mat4 &other) const
  {
    return Sum(other);
  }

  inline Mat4 &operator+=(const Mat4 &other)
  {
    Mat4 ret = Sum(other);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline Mat4 operator+(float value) const
  {
    return Sum(value);
  }

  inline Mat4 &operator+=(float value)
  {
    Mat4 ret = Sum(value);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline Mat4 operator-(const Mat4 &other) const
  {
    return Substract(other);
  }

  inline Mat4 &operator-=(const Mat4 &other)
  {
    Mat4 ret = Substract(other);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline Mat4 operator-(float value) const
  {
    return Substract(value);
  }

  inline Mat4 &operator-=(float value)
  {
    Mat4 ret = Substract(value);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline Mat4 operator*(const Mat4 &other) const
  {
    return Multiply(other);
  }

  inline Mat4 &operator*=(const Mat4 &other)
  {
    Mat4 ret = Multiply(other);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline Mat4 operator*(float value) const
  {
    return Multiply(value);
  }

  inline Mat4 &operator*=(float value)
  {
    Mat4 ret = Multiply(value);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline Mat4 operator/(float value) const
  {
    return Divide(value);
  }

  inline Mat4 &operator/=(float value)
  {
    Mat4 ret = Divide(value);
    for (int i = 0; i < 16; i++)
      this->m[i] = ret.m[i];
    return (*this);
  }

  inline bool operator==(const Mat4 &other) const
  {
    for (int i = 0; i < 16; ++i)
    {
      if (this->m[i] != other.m[i])
      {
        return false;
      }
    }
    return true;
  }

  inline bool operator!=(const Mat4 &other) const
  {
    for (int i = 0; i < 16; ++i)
    {
      if (this->m[i] != other.m[i])
      {
        return true;
      }
    }
    return false;
  }

  inline void operator=(const Mat4 &other)
  {
    for (int i = 0; i < 16; i++)
      this->m[i] = other.m[i];
  }

  float m[16];
};

////////////////////////
#endif /* __MATRIX_4_H__ */
////////////////////////
