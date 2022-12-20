/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

#include "math_utils.h"
#include "vector_2.h"
#include <math.h>

const Vec2 Vec2::down = Vec2(0.0f, -1.0f);
const Vec2 Vec2::left = Vec2(-1.0f, 0.0f);
const Vec2 Vec2::one = Vec2(1.0f, 1.0f);
const Vec2 Vec2::right = Vec2(1.0f, 0.0f);
const Vec2 Vec2::up = Vec2(0.0f, 1.0f);
const Vec2 Vec2::zero = Vec2(0.0f, 0.0f);

// Constructors
Vec2::Vec2(float value) : x(value), y(value) {}
Vec2::Vec2(float a, float b) : x(a), y(b) {}
Vec2::Vec2(float *values_array) : x(values_array[0]), y(values_array[1]) {}
Vec2::Vec2(const Vec2 &other) : x(other.x), y(other.y) {}

// Destructor
Vec2::~Vec2() { x = y = 0; }

// Methods
float Vec2::Magnitude() const
{
  return sqrt((this->x * this->x) + (this->y * this->y));
}

bool Vec2::IsNormalized() const
{
  if ((this->x + this->y) == 0)
    return true;

  float magn = 0;
  bool vuelta = false;
  magn = Magnitude();

  if (magn < 1.001 && magn > 0.999)
    vuelta = true;
  return vuelta;
}

void Vec2::Normalize()
{
  if (!IsNormalized())
  {
    float magn = 0;
    magn = Magnitude();
    this->x /= magn;
    this->y /= magn;
  }
}

Vec2 Vec2::Normalized() const
{
  if (IsNormalized())
  {
    return Vec2(this->x, this->y);
  }
  else
  {
    float magn = 0;
    magn = Magnitude();
    return Vec2(this->x / magn, this->y / magn);
  }
}

void Vec2::Scale(const Vec2 scale)
{
  this->x *= scale.x;
  this->y *= scale.y;
}

float Vec2::SqrMagnitude() const
{
  return Magnitude() * Magnitude();
}

float Vec2::Distance(const Vec2 a, const Vec2 b)
{
  Vec2 newVec = a;
  newVec -= b;
  return sqrt((newVec.x * newVec.x) + (newVec.y * newVec.y));
}

Vec2 Vec2::Lerp(const Vec2 a, const Vec2 b, float value)
{
  value = MathUtils::Clamp(value, 0, 1);
  return Vec2(((b - a) * value) + a);
}

Vec2 Vec2::LerpUnclamped(const Vec2 a, const Vec2 b, float value)
{
  return Vec2(((b - a) * value) + a);
}

float Vec2::DotProduct(Vec2 a, Vec2 b)
{
  float ret;
  ret = (a.x * b.x) + (a.y * b.y);
  return ret;
}
