/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

#include "matrix_3.h"
#include "matrix_2.h"
#include <math.h>

// Constructors
Mat3::Mat3(const float &value)
{
  for (int i = 0; i < 9; i++)
    m[i] = value;
}

Mat3::Mat3(const float value[9])
{
  for (int i = 0; i < 9; i++)
    m[i] = value[i];
}

Mat3::Mat3(const Vec3 &a, const Vec3 &b, const Vec3 &c)
{
  m[0] = a.x;
  m[1] = a.y;
  m[2] = a.z;
  m[3] = b.x;
  m[4] = b.y;
  m[5] = b.z;
  m[6] = c.x;
  m[7] = c.y;
  m[8] = c.z;
}

Mat3::Mat3(const Mat3 &copy)
{
  for (int i = 0; i < 9; i++)
  {
    this->m[i] = copy.m[i];
  }
}

// Destructor
Mat3::~Mat3()
{
  for (int i = 0; i < 9; i++)
    m[i] = 0;
}

Mat3 Mat3::Identity()
{
  float ret[9] = {
      1, 0, 0,
      0, 1, 0,
      0, 0, 1};
  return Mat3(ret);
}

float Mat3::Determinant() const
{
  return (
      (
          (m[0] * m[4] * m[8]) +
          (m[3] * m[7] * m[2]) +
          (m[6] * m[1] * m[5])) -
      ((m[2] * m[4] * m[6]) +
       (m[5] * m[7] * m[0]) +
       (m[8] * m[1] * m[3])));
}

float Mat3::Determinant(float value[9])
{
  return (
      (
          (value[0] * value[4] * value[8]) +
          (value[3] * value[7] * value[2]) +
          (value[6] * value[1] * value[5])) -
      ((value[2] * value[4] * value[6]) +
       (value[5] * value[7] * value[0]) +
       (value[8] * value[1] * value[3])));
}

bool Mat3::GetInverse(Mat3 &out) const
{
  Mat3 ret = out.Adjoint().Transpose();
  float det = out.Determinant();
  if (det == 0)
    return false;
  ret /= det;

  for (int i = 0; i < 9; i++)
    out.m[i] = ret.m[i];
  return true;
}

bool Mat3::Inverse()
{
  Mat3 ret = Adjoint().Transpose();
  float det = Determinant();
  if (det == 0)
    return false;
  ret /= det;

  for (int i = 0; i < 9; i++)
    this->m[i] = ret.m[i];
  return true;
}

Mat3 Mat3::Translate(const Vec2 &mov)
{
  float ret[9] = {
      1, 0, 0,
      0, 1, 0,
      mov.x, mov.y, 1};

  return Mat3(ret);
}

Mat3 Mat3::Translate(float a, float b)
{
  float ret[9] = {
      1, 0, 0,
      0, 1, 0,
      a, b, 1};

  return Mat3(ret);
}

Mat3 Mat3::Rotate(float rotation)
{
  float rot[9] = {
      (float)cos(rotation), (float)sin(rotation), 0,
      (float)-sin(rotation), (float)cos(rotation), 0,
      0, 0, 1};

  return Mat3(rot);
}

Mat3 Mat3::Scale(const Vec2 &scale)
{
  float f[9] = {
      scale.x, 0, 0,
      0, scale.y, 0,
      0, 0, 1};

  return Mat3(f);
}

Mat3 Mat3::Adjoint() const
{
  float ret[9];

  float det_0[4] = {this->m[4], this->m[5], this->m[7], this->m[8]};
  ret[0] = Mat2::Determinant(det_0);

  float det_1[4] = {this->m[3], this->m[5], this->m[6], this->m[8]};
  ret[1] = -1 * Mat2::Determinant(det_1);

  float det_2[4] = {this->m[3], this->m[4], this->m[6], this->m[7]};
  ret[2] = Mat2::Determinant(det_2);

  float det_3[4] = {this->m[1], this->m[2], this->m[7], this->m[8]};
  ret[3] = -1 * Mat2::Determinant(det_3);

  float det_4[4] = {this->m[0], this->m[2], this->m[6], this->m[8]};
  ret[4] = Mat2::Determinant(det_4);

  float det_5[4] = {this->m[0], this->m[1], this->m[6], this->m[7]};
  ret[5] = -1 * Mat2::Determinant(det_5);

  float det_6[4] = {this->m[1], this->m[2], this->m[4], this->m[5]};
  ret[6] = Mat2::Determinant(det_6);

  float det_7[4] = {this->m[0], this->m[2], this->m[3], this->m[5]};
  ret[7] = -1 * Mat2::Determinant(det_7);

  float det_8[4] = {this->m[0], this->m[1], this->m[3], this->m[4]};
  ret[8] = Mat2::Determinant(det_8);

  return Mat3(ret);
}

Mat3 Mat3::Transpose() const
{
  float ret[9];
  ret[0] = m[0];
  ret[1] = m[3];
  ret[2] = m[6];
  ret[3] = m[1];
  ret[4] = m[4];
  ret[5] = m[7];
  ret[6] = m[2];
  ret[7] = m[5];
  ret[8] = m[8];
  return Mat3(ret);
}

Vec3 Mat3::GetColum(int column) const
{
  if (column < 3)
  {
    return Vec3(m[0 + column], m[3 + column], m[6 + column]);
  }
  else
    return Vec3(0, 0, 0);
}

Vec3 Mat3::GetLine(int line) const
{
  if (line < 3)
  {
    return Vec3(m[0 + line * 3], m[1 + line * 3], m[2 + line * 3]);
  }
  else
    return Vec3(0, 0, 0);
}
