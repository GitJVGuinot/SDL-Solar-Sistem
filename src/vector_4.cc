/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

#include "math_utils.h"
#include "vector_4.h"
#include <math.h>

const Vec4 Vec4::one = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
const Vec4 Vec4::zero = Vec4(0.0f, 0.0f, 0.0f, 0.0f);

// Constructors
Vec4::Vec4(float value) : x(value), y(value), z(value), w(value) {}
Vec4::Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
Vec4::Vec4(float *values_array) : x(values_array[0]), y(values_array[1]), z(values_array[2]), w(values_array[3]) {}
Vec4::Vec4(const Vec4 &other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

// Destructor
Vec4::~Vec4() { x = y = z = w = 0; }

// Methods
float Vec4::Magnitude() const
{
  return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w));
}

bool Vec4::IsNormalized() const
{
  float magn = 0;
  bool turn = false;
  magn = Magnitude();

  if (magn < 1.001 && magn > 0.999)
  {
    turn = true;
  }
  return turn;
}

void Vec4::Normalize()
{
  if (!IsNormalized())
  {
    float magn = 0;
    magn = Magnitude();
    this->x /= magn;
    this->y /= magn;
    this->z /= magn;
    this->w /= magn;
  }
}

Vec4 Vec4::Normalized() const
{
  if (IsNormalized())
  {
    return Vec4(this->x, this->y, this->z, this->w);
  }
  else
  {
    float magn = 0;
    magn = Magnitude();
    return Vec4(this->x / magn, this->y / magn, this->z / magn, this->w / magn);
  }
}

void Vec4::Scale(Vec4 scale)
{
  this->x *= scale.x;
  this->y *= scale.y;
  this->z *= scale.z;
  this->w *= scale.w;
}

float Vec4::SqrMagnitude() const
{
  return Magnitude() * Magnitude();
}

float Vec4::Distance(const Vec4 a, const Vec4 b)
{
  Vec4 newVec = a;
  newVec -= b;
  return sqrt((newVec.x * newVec.x) + (newVec.y * newVec.y) + (newVec.z * newVec.z) + (newVec.w * newVec.w));
}

Vec4 Vec4::Lerp(const Vec4 a, const Vec4 b, float value)
{
  value = MathUtils::Clamp(value, 0, 1);
  return Vec4(((b - a) * value) + a);
}

float Vec4::DotProduct(Vec4 a, Vec4 b)
{
  float ret;
  ret = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
  return ret;
}
