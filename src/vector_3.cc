/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

#include "math_utils.h"
#include "vector_3.h"
#include <math.h>

const Vec3 Vec3::up = Vec3(0.0f, 1.0f, 0.0f);
const Vec3 Vec3::down = Vec3(0.0f, -1.0f, 0.0f);
const Vec3 Vec3::right = Vec3(1.0f, 0.0f, 0.0f);
const Vec3 Vec3::left = Vec3(-1.0f, 0.0f, 0.0f);
const Vec3 Vec3::forward = Vec3(0.0f, 0.0f, 1.0f);
const Vec3 Vec3::back = Vec3(0.0f, 0.0f, -1.0f);
const Vec3 Vec3::zero = Vec3(0.0f, 0.0f, 0.0f);
const Vec3 Vec3::unit = Vec3(1.0f, 1.0f, 1.0f);

// Constructors
Vec3::Vec3(float value) : x(value), y(value), z(value) {}
Vec3::Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
Vec3::Vec3(float *values_array) : x(values_array[0]), y(values_array[1]), z(values_array[2]) {}
Vec3::Vec3(const Vec3 &other) : x(other.x), y(other.y), z(other.z) {}

// Destructor
Vec3::~Vec3() { x = y = z = 0; }

// Methods
float Vec3::Magnitude() const
{
  return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

bool Vec3::IsNormalized() const
{
  if ((this->x + this->y + this->z) == 0)
    return true;

  float magn = 0;
  bool turn = false;

  magn = Magnitude();

  if (magn < 1.001 && magn > 0.999)
  {
    turn = true;
  }
  return turn;
}

void Vec3::Normalize()
{
  if (!IsNormalized())
  {
    float magn = 0;
    magn = Magnitude();
    this->x /= magn;
    this->y /= magn;
    this->z /= magn;
  }
}

Vec3 Vec3::Normalized() const
{
  if (IsNormalized())
  {
    return Vec3(this->x, this->y, this->z);
  }
  else
  {
    float magn = 0;
    magn = Magnitude();
    return Vec3(this->x / magn, this->y / magn, this->z / magn);
  }
}

void Vec3::Scale(const Vec3 &scale)
{
  this->x *= scale.x;
  this->y *= scale.y;
  this->z *= scale.z;
}

float Vec3::SqrMagnitude() const
{
  return Magnitude() * Magnitude();
}

float Vec3::Distance(const Vec3 a, const Vec3 b)
{
  Vec3 newVec = a;
  newVec -= b;
  return sqrt((newVec.x * newVec.x) + (newVec.y * newVec.y) + (newVec.z * newVec.z));
}

Vec3 Vec3::Lerp(const Vec3 a, const Vec3 b, float value)
{
  value = MathUtils::Clamp(value, 0, 1);
  return Vec3(((b - a) * value) + a);
}

Vec3 Vec3::LerpUnclamped(const Vec3 a, const Vec3 b, float value)
{
  return Vec3(((b - a) * value) + a);
}

float Vec3::DotProduct(const Vec3 a, const Vec3 b)
{
  float ret;
  ret = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
  return ret;
}

float Vec3::Angle(const Vec3 a, const Vec3 b)
{
  if (a == Vec3{0, 0, 0} || b == Vec3{0, 0, 0})
    return 0;

  float ret = 0;
  float dot = DotProduct(a, b);
  float magn_a = a.Magnitude();
  float magn_b = b.Magnitude();

  ret = dot / (magn_a * magn_b);

  if (ret >= 1.0f)
  {
    return 0;
  }

  if (ret == 0.0f)
  {
    return PI / 2;
  }

  if (ret <= -1.0f)
  {
    return PI;
  }

  ret = acos(ret);

  return ret;
}

Vec3 Vec3::CrossProduct(const Vec3 a, const Vec3 b)
{
  Vec3 ret;
  ret.x = a.y * b.z - a.z * b.y;
  ret.y = a.z * b.x - a.x * b.z;
  ret.z = a.x * b.y - a.y * b.x;
  return ret;
}

Vec3 Vec3::Reflect(const Vec3 direction, const Vec3 normal)
{
  float ret;
  ret = 2 * DotProduct(direction, normal);
  return direction - normal * ret;
}
