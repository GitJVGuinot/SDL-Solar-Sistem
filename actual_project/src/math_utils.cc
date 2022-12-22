/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

#include "math_utils.h"

int InF()
{
  int inf = 0x7F800000;
  return *&inf;
}

int NaN()
{
  int nan = 0x7F800001;
  return *&nan;
}

Vec4 MathUtils::HomogenisedVec(Vec4 v)
{
  Vec4 v1;
  if (v.w != 1)
  {
    v1.x = v.x / v.w;
    v1.y = v.y / v.w;
    v1.z = v.z / v.w;
    v1.w = v.w / v.w;
  }
  else
    v1 = v;
  return v1;
}

Vec3 MathUtils::Mat4TransformVec3(Mat4 m, Vec3 v)
{

  Vec4 v1 = {
      (m.m[0] * v.x) + (m.m[4] * v.y) + (m.m[8] * v.z) + (m.m[12] * 1.0f),
      (m.m[1] * v.x) + (m.m[5] * v.y) + (m.m[9] * v.z) + (m.m[13] * 1.0f),
      (m.m[2] * v.x) + (m.m[6] * v.y) + (m.m[10] * v.z) + (m.m[14] * 1.0f),
      (m.m[3] * v.x) + (m.m[7] * v.y) + (m.m[11] * v.z) + (m.m[15] * 1.0f)};

  Vec4 v2 = HomogenisedVec(v1);
  Vec3 homo = {v2.x, v2.y, v2.z};
  return homo;
}

Vec2 MathUtils::Vec3_Tr_Vec2(Vec3 v3)
{
  Vec2 v2 = {v3.x, v3.y};
  return v2;
}

Vec3 MathUtils::Rotate_Point_3D(Vec3 rot, Vec3 point)
{
  Mat4 rot_x;
  if (rot.x != 0)
    rot_x = Mat4::RotateX((rot.x * PI) / 180);

  Mat4 rot_y;
  if (rot.y != 0)
    rot_y = Mat4::RotateY((rot.y * PI) / 180);

  Mat4 rot_z;
  if (rot.z != 0)
    rot_z = Mat4::RotateZ((rot.z * PI) / 180);

  Mat4 model = Mat4::Identity();
  if (rot.x != 0)
    model = model.Multiply(rot_x);
  if (rot.y != 0)
    model = model.Multiply(rot_y);
  if (rot.z != 0)
    model = model.Multiply(rot_z);

  return Mat4TransformVec3(model, point);
}

void MathUtils::Orbit_Point(Vec3 orbit_center, Vec3 p_orbit, Vec3 &point)
{
  Mat4 rot_x;
  if (p_orbit.x != 0)
    rot_x = Mat4::RotateX((p_orbit.x * PI) / 180);
  Mat4 rot_y;
  if (p_orbit.y != 0)
    rot_y = Mat4::RotateY((p_orbit.y * PI) / 180);
  Mat4 rot_z;
  if (p_orbit.z != 0)
    rot_z = Mat4::RotateZ((p_orbit.z * PI) / 180);

  Mat4 model = Mat4::Identity();
  if (p_orbit.x != 0)
    model = model.Multiply(rot_x);
  if (p_orbit.y != 0)
    model = model.Multiply(rot_y);
  if (p_orbit.z != 0)
    model = model.Multiply(rot_z);

  point -= orbit_center;
  point = Mat4TransformVec3(model, point);
  point += orbit_center;
}

Mat4 MathUtils::Mat4View(Vec3 camera, Vec3 front, Vec3 up)
{

  Vec3 zAxis = front; // Vector Z
  if (!zAxis.IsNormalized())
    zAxis.Normalize();

  Vec3 xAxis = Vec3::CrossProduct(up, zAxis); // Vector X
  if (!xAxis.IsNormalized())
    xAxis.Normalize();

  Vec3 yAxis = Vec3::CrossProduct(zAxis, xAxis); // Vector Y
  if (!yAxis.IsNormalized())
    yAxis.Normalize();

  // Creates a view matrix from the vectors of the camera
  float vMat[16] = {
      xAxis.x, yAxis.x, zAxis.x, 0,
      xAxis.y, yAxis.y, zAxis.y, 0,
      xAxis.z, yAxis.z, zAxis.z, 0,
      -Vec3::DotProduct(xAxis, camera), -Vec3::DotProduct(yAxis, camera), -Vec3::DotProduct(zAxis, camera), 1};

  return Mat4(vMat);
}

Vec3 MathUtils::Vec2_Tr_Vec3(Vec2 v2, bool homogenised)
{
  Vec3 v3 = {v2.x, v2.y, (float)homogenised};
  return v3;
}

Vec3 MathUtils::Mat3TransformVec3(Mat3 m, Vec3 v)
{
  Vec3 v1 = {
      (m.m[0] * v.x) + (m.m[3] * v.y) + (m.m[6] * v.z),
      (m.m[1] * v.x) + (m.m[4] * v.y) + (m.m[7] * v.z),
      (m.m[2] * v.x) + (m.m[5] * v.y) + (m.m[8] * v.z)};

  return v1;
}

float MathUtils::Radian_To_Euler(float radian)
{
  return (radian * 180 / PI);
}
float MathUtils::Euler_To_Radian(float euler)
{
  return (euler * PI / 180);
}
