/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

/** @file Matrix_2.h
 *--------------------------------------------------------------
 *  Math Library
 *  Matrix 2 Class Definition.
 *--------------------------------------------------------------
 *
 *   m0 m1
 *   m2 m3
 *
 *--------------------------------------------------------------
 */

////////////////////////
#ifndef __MATRIX_2_H__
#define __MATRIX_2_H__ 1
////////////////////////

#include "vector_2.h"
#include <iostream>

class Mat2
{
public:
  inline void print(char *name = (char *)"Mat2")
  {
    printf("%s:\n", name);
    printf("%f, %f,\n", this->m[0], this->m[1]);
    printf("%f, %f\n", this->m[2], this->m[3]);
  }

  Mat2(const float &value = 0);
  Mat2(const float a[4]);
  Mat2(const Vec2 &a, const Vec2 &b);
  Mat2(const Mat2 &copy);

  ~Mat2();

  static Mat2 Identity();
  float Determinant() const;
  static float Determinant(float val[4]);
  Mat2 Adjoint() const;
  Vec2 GetLine(int line) const;
  Vec2 GetColum(int line) const;

  Mat2 Inverse() const;
  Mat2 Transpose() const;

  inline Mat2 operator+(const Mat2 &other) const;
  inline Mat2 &operator+=(const Mat2 &other);
  inline Mat2 Sum(const Mat2 &other) const;

  inline Mat2 operator+(float value) const;
  inline Mat2 &operator+=(float value);
  inline Mat2 Sum(float value) const;

  inline Mat2 operator-(const Mat2 &other) const;
  inline Mat2 &operator-=(const Mat2 &other);
  inline Mat2 Substract(const Mat2 &other) const;

  inline Mat2 operator-(float value) const;
  inline Mat2 &operator-=(float value);
  inline Mat2 Substract(float value) const;

  inline Mat2 operator*(const Mat2 &other) const;
  inline Mat2 &operator*=(const Mat2 &other);
  inline Mat2 Multiply(const Mat2 &other) const;

  inline Mat2 operator*(float value) const;
  inline Mat2 &operator*=(float value);
  inline Mat2 Multiply(float value) const;

  inline Mat2 operator/(float value) const;
  inline Mat2 &operator/=(float value);
  inline Mat2 Divide(float value) const;

  bool operator==(const Mat2 &other) const;
  bool operator!=(const Mat2 &other) const;
  inline void operator=(const Mat2 &other);

  float m[4];
};

////////////////////////
#endif /* __MATRIX_2_H__ */
////////////////////////
