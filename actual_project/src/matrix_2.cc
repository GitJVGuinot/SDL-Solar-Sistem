/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

#include "matrix_2.h"

// Constructors
Mat2::Mat2(const float &value)
{
  for (int i = 0; i < 4; ++i)
  {
    m[i] = value;
  }
}

Mat2::Mat2(const float a[4])
{
  for (int i = 0; i < 4; ++i)
  {
    this->m[i] = a[i];
  }
}

Mat2::Mat2(const Vec2 &a, const Vec2 &b)
{
  m[0] = a.x;
  m[1] = a.y;
  m[2] = b.x;
  m[3] = b.y;
}

Mat2::Mat2(const Mat2 &copy)
{
  for (int i = 0; i < 4; ++i)
  {
    this->m[i] = copy.m[i];
  }
}

// Destructor
Mat2::~Mat2()
{
  for (int i = 0; i < 4; ++i)
  {
    m[i] = 0;
  }
}

Mat2 Mat2::Sum(const Mat2 &other) const
{
  float ret[4];
  for (int i = 0; i < 4; ++i)
  {
    ret[i] = this->m[i] + other.m[i];
  }
  return Mat2(ret);
}

Mat2 Mat2::Sum(float value) const
{
  float ret[4];
  for (int i = 0; i < 4; ++i)
  {
    ret[i] = this->m[i] + value;
  }
  return Mat2(ret);
}

Mat2 Mat2::Substract(const Mat2 &other) const
{
  float ret[4];
  for (int i = 0; i < 4; ++i)
  {
    ret[i] = this->m[i] - other.m[i];
  }
  return Mat2(ret);
}

Mat2 Mat2::Substract(float value) const
{
  float ret[4];
  for (int i = 0; i < 4; ++i)
  {
    ret[i] = this->m[i] - value;
  }
  return Mat2(ret);
}

Mat2 Mat2::Multiply(const Mat2 &other) const
{
  float ret[4];
  ret[0] = (this->m[0] * other.m[0] + this->m[1] * other.m[2]);
  ret[1] = (this->m[0] * other.m[1] + this->m[1] * other.m[3]);
  ret[2] = (this->m[2] * other.m[0] + this->m[3] * other.m[2]);
  ret[3] = (this->m[2] * other.m[1] + this->m[3] * other.m[3]);

  return Mat2(ret);
}

Mat2 Mat2::Multiply(float value) const
{
  float ret[4];
  for (int i = 0; i < 4; ++i)
  {
    ret[i] = this->m[i] * value;
  }
  return Mat2(ret);
}

Mat2 Mat2::Divide(float value) const
{
  float ret[4];
  for (int i = 0; i < 4; ++i)
  {
    ret[i] = this->m[i] / value;
  }
  return Mat2(ret);
}

// Operators
Mat2 Mat2::operator+(const Mat2 &other) const
{
  return Sum(other);
}

Mat2 &Mat2::operator+=(const Mat2 &other)
{
  Mat2 ret = Sum(other);
  for (int i = 0; i < 4; ++i)
  {
    this->m[i] = ret.m[i];
  }
  return (*this);
}

Mat2 Mat2::operator+(float value) const
{
  return Sum(value);
}

Mat2 &Mat2::operator+=(float value)
{
  Mat2 ret = Sum(value);
  for (int i = 0; i < 4; ++i)
  {
    this->m[i] = ret.m[i];
  }
  return (*this);
}

Mat2 Mat2::operator-(const Mat2 &other) const
{
  return Substract(other);
}

Mat2 &Mat2::operator-=(const Mat2 &other)
{
  Mat2 ret = Substract(other);
  for (int i = 0; i < 4; ++i)
  {
    this->m[i] = ret.m[i];
  }
  return (*this);
}

Mat2 Mat2::operator-(float value) const
{
  return Substract(value);
}

Mat2 &Mat2::operator-=(float value)
{
  Mat2 ret = Substract(value);
  for (int i = 0; i < 4; ++i)
  {
    this->m[i] = ret.m[i];
  }
  return (*this);
}

Mat2 Mat2::operator*(const Mat2 &other) const
{
  return Multiply(other);
}

Mat2 &Mat2::operator*=(const Mat2 &other)
{
  Mat2 ret = Multiply(other);
  for (int i = 0; i < 4; ++i)
  {
    this->m[i] = ret.m[i];
  }
  return (*this);
}

Mat2 Mat2::operator*(float value) const
{
  return Multiply(value);
}

Mat2 &Mat2::operator*=(float value)
{
  Mat2 ret = Substract(value);
  for (int i = 0; i < 4; ++i)
  {
    this->m[i] = ret.m[i];
  }
  return (*this);
}

Mat2 Mat2::operator/(float value) const
{
  return Divide(value);
}

Mat2 &Mat2::operator/=(float value)
{
  Mat2 ret = Divide(value);
  for (int i = 0; i < 4; ++i)
  {
    this->m[i] = ret.m[i];
  }
  return (*this);
}

bool Mat2::operator==(const Mat2 &other) const
{
  for (int i = 0; i < 4; ++i)
  {
    if (this->m[i] != other.m[i])
    {
      return false;
    }
  }
  return true;
}

bool Mat2::operator!=(const Mat2 &other) const
{
  for (int i = 0; i < 4; ++i)
  {
    if (this->m[i] == other.m[i])
    {
      return false;
    }
  }
  return true;
}

void Mat2::operator=(const Mat2 &other)
{
  for (int i = 0; i < 4; ++i)
  {
    this->m[i] = other.m[i];
  }
}

Mat2 Mat2::Identity()
{
  float ret[4] = {
      1, 0,
      0, 1};
  return Mat2(ret);
}

float Mat2::Determinant() const
{
  return ((m[0] * m[3]) - (m[2] * m[1]));
}

float Mat2::Determinant(float val[4])
{
  return ((val[0] * val[3]) - (val[2] * val[1]));
}

Mat2 Mat2::Inverse() const
{
  float det = ((m[0] * m[3]) - (m[2] * m[1]));
  if (det != 0)
  {
    float ret[4];
    ret[0] = m[3] * (1 / det);
    ret[3] = m[0] * (1 / det);
    ret[1] = (m[1] * -1) * (1 / det);
    ret[2] = (m[2] * -1) * (1 / det);
    return Mat2(ret);
  }
  else
    return Mat2();
}

Mat2 Mat2::Adjoint() const
{
  float ret[4];

  ret[0] = m[3];

  ret[1] = -m[2];

  ret[2] = -m[1];

  ret[3] = m[0];

  return Mat2(ret);
}

Mat2 Mat2::Transpose() const
{
  float ret[4];
  ret[0] = m[0];
  ret[1] = m[2];
  ret[2] = m[1];
  ret[2] = m[2];
  return Mat2(ret);
}

Vec2 Mat2::GetLine(int line) const
{
  if (line < 2)
  {
    return Vec2(m[0 + line * 2], m[1 + line * 2]);
  }
  else
    return Vec2(0, 0);
}

Vec2 Mat2::GetColum(int column) const
{
  if (column < 2)
  {
    return Vec2(m[0 + column], m[2 + column]);
  }
  else
    return Vec2(0, 0);
}
