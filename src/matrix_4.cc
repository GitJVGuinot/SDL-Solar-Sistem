/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

#include <matrix_4.h>
#include <math.h>

// Constructors
Mat4::Mat4(const float &value)
{
  for (int i = 0; i < 16; ++i)
  {
    this->m[i] = value;
  }
}

Mat4::Mat4(const float array[16])
{
  for (int i = 0; i < 16; ++i)
  {
    this->m[i] = array[i];
  }
}

Mat4::Mat4(const Vec4 &a, const Vec4 &b, const Vec4 &c, const Vec4 &d)
{
  m[0] = a.x;
  m[1] = a.y;
  m[2] = a.z;
  m[3] = a.w;

  m[4] = b.x;
  m[5] = b.y;
  m[6] = b.z;
  m[7] = b.w;

  m[8] = c.x;
  m[9] = c.y;
  m[10] = c.z;
  m[11] = c.w;

  m[12] = d.x;
  m[13] = d.y;
  m[14] = d.z;
  m[15] = d.w;
}

Mat4::Mat4(const Mat4 &copy)
{
  for (int i = 0; i < 16; ++i)
  {
    this->m[i] = copy.m[i];
  }
}

Mat4::~Mat4()
{
  for (int i = 0; i < 16; i++)
    m[i] = 0;
}

// Metodos
Mat4 Mat4::Identity()
{
  float ret[16] = {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1};
  return Mat4(ret);
}

Mat4 Mat4::Projection()
{
  float pro[16] = {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 1,
      0, 0, 0, 0};
  return Mat4(pro);
}

float Mat4::Determinant() const
{
  return (
      (m[0] * m[5] * m[10] * m[15]) +
      (m[0] * m[6] * m[11] * m[13]) +
      (m[0] * m[7] * m[9] * m[14]) -
      (m[0] * m[7] * m[10] * m[13]) -
      (m[0] * m[6] * m[9] * m[15]) -
      (m[0] * m[5] * m[11] * m[14]) -
      (m[1] * m[4] * m[10] * m[15]) -
      (m[2] * m[4] * m[11] * m[13]) -
      (m[3] * m[4] * m[9] * m[14]) +
      (m[3] * m[4] * m[10] * m[13]) +
      (m[2] * m[4] * m[9] * m[15]) +
      (m[1] * m[4] * m[11] * m[14]) +
      (m[1] * m[6] * m[8] * m[15]) +
      (m[2] * m[7] * m[8] * m[13]) +
      (m[3] * m[5] * m[8] * m[14]) -
      (m[3] * m[6] * m[8] * m[13]) -
      (m[2] * m[5] * m[8] * m[15]) -
      (m[1] * m[7] * m[8] * m[14]) -
      (m[1] * m[6] * m[11] * m[12]) -
      (m[2] * m[7] * m[9] * m[12]) -
      (m[3] * m[5] * m[10] * m[12]) +
      (m[3] * m[6] * m[9] * m[12]) +
      (m[2] * m[5] * m[11] * m[12]) +
      (m[1] * m[7] * m[10] * m[12]));
}

Mat4 Mat4::Adjoint() const
{
  float ret[16];

  float det_0[9] = {m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15]};
  ret[0] = Mat3::Determinant(det_0);

  float det_1[9] = {m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15]};
  ret[1] = -1 * Mat3::Determinant(det_1);

  float det_2[9] = {m[4], m[5], m[7], m[8], m[9], m[11], m[12], m[13], m[15]};
  ret[2] = Mat3::Determinant(det_2);

  float det_3[9] = {m[4], m[5], m[6], m[8], m[9], m[10], m[12], m[13], m[14]};
  ret[3] = -1 * Mat3::Determinant(det_3);

  float det_4[9] = {m[1], m[2], m[3], m[9], m[10], m[11], m[13], m[14], m[15]};
  ret[4] = -1 * Mat3::Determinant(det_4);

  float det_5[9] = {m[0], m[2], m[3], m[8], m[10], m[11], m[12], m[14], m[15]};
  ret[5] = Mat3::Determinant(det_5);

  float det_6[9] = {m[0], m[1], m[3], m[8], m[9], m[11], m[12], m[13], m[15]};
  ret[6] = -1 * Mat3::Determinant(det_6);

  float det_7[9] = {m[0], m[1], m[2], m[8], m[9], m[10], m[12], m[13], m[14]};
  ret[7] = Mat3::Determinant(det_7);

  float det_8[9] = {m[1], m[2], m[3], m[5], m[6], m[7], m[13], m[14], m[15]};
  ret[8] = Mat3::Determinant(det_8);

  float det_9[9] = {m[0], m[2], m[3], m[4], m[6], m[7], m[12], m[14], m[15]};
  ret[9] = -1 * Mat3::Determinant(det_9);

  float det_10[9] = {m[0], m[1], m[3], m[4], m[5], m[7], m[12], m[13], m[15]};
  ret[10] = Mat3::Determinant(det_10);

  float det_11[9] = {m[0], m[1], m[2], m[4], m[5], m[6], m[12], m[13], m[14]};
  ret[11] = -1 * Mat3::Determinant(det_11);

  float det_12[9] = {m[1], m[2], m[3], m[5], m[6], m[7], m[9], m[10], m[11]};

  ret[12] = -1 * Mat3::Determinant(det_12);
  float det_13[9] = {m[0], m[2], m[3], m[4], m[6], m[7], m[8], m[10], m[11]};
  ret[13] = Mat3::Determinant(det_13);

  float det_14[9] = {m[0], m[1], m[3], m[4], m[5], m[7], m[8], m[9], m[11]};
  ret[14] = -1 * Mat3::Determinant(det_14);

  float det_15[9] = {m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]};
  ret[15] = Mat3::Determinant(det_15);

  return Mat4(ret);
}

bool Mat4::Inverse()
{
  Mat4 ret = Adjoint().Transpose();
  float det = Determinant();
  if (det == 0)
    return false;
  ret /= det;

  for (int i = 0; i < 16; i++)
    this->m[i] = ret.m[i];
  return true;
}

bool Mat4::GetInverse(Mat4 &out) const
{
  Mat4 ret = out.Adjoint().Transpose();
  float det = out.Determinant();
  if (det == 0)
    return false;
  ret /= det;

  for (int i = 0; i < 16; i++)
    out.m[i] = ret.m[i];
  return true;
}

Mat4 Mat4::Transpose() const
{
  float f[16];
  f[0] = this->m[0];
  f[1] = this->m[4];
  f[2] = this->m[8];
  f[3] = this->m[12];
  f[4] = this->m[1];
  f[5] = this->m[5];
  f[6] = this->m[9];
  f[7] = this->m[13];
  f[8] = this->m[2];
  f[9] = this->m[6];
  f[10] = this->m[10];
  f[11] = this->m[14];
  f[12] = this->m[3];
  f[13] = this->m[7];
  f[14] = this->m[11];
  f[15] = this->m[15];
  return Mat4(f);
}

Mat4 Mat4::Translate(const Vec3 &mov)
{
  float tras[16] = {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      mov.x, mov.y, mov.z, 1};

  return Mat4(tras);
}

Mat4 Mat4::Translate(float x, float y, float z)
{
  float tras[16] = {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      x, y, z, 1};

  return Mat4(tras);
}

Mat4 Mat4::Scale(const Vec3 &scale)
{
  float f[16] = {
      scale.x, 0, 0, 0,
      0, scale.y, 0, 0,
      0, 0, scale.z, 0,
      0, 0, 0, 1};
  return Mat4(f);
}

Mat4 Mat4::Scale(float x, float y, float z)
{
  float f[16] = {
      x, 0, 0, 0,
      0, y, 0, 0,
      0, 0, z, 0,
      0, 0, 0, 1};
  return Mat4(f);
}

Mat4 Mat4::RotateX(float radians)
{
  float rot[16] = {
      1, 0, 0, 0,
      0, (float)cos(radians), (float)sin(radians), 0,
      0, (float)-sin(radians), (float)cos(radians), 0,
      0, 0, 0, 1};
  return Mat4(rot);
}

Mat4 Mat4::RotateY(float radians)
{
  float rot[16] = {
      (float)cos(radians), 0, (float)-sin(radians), 0,
      0, 1, 0, 0,
      (float)sin(radians), 0, (float)cos(radians), 0,
      0, 0, 0, 1};
  return Mat4(rot);
}

Mat4 Mat4::RotateZ(float radians)
{
  float rot[16] = {
      (float)cos(radians), (float)sin(radians), 0, 0,
      (float)-sin(radians), (float)cos(radians), 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1};
  return Mat4(rot);
}

Mat4 Mat4::GetTransform(const Vec3 &translate,
                        const Vec3 &scale,
                        float rotateX, float rotateY,
                        float rotateZ)
{

  Mat4 m_scale = Scale(scale);
  Mat4 m_rot_x = RotateX(rotateX);
  Mat4 m_rot_y = RotateY(rotateY);
  Mat4 m_rot_z = RotateZ(rotateZ);
  Mat4 m_trans = Translate(translate);

  Mat4 ret = Identity();
  ret = ret.Multiply(m_scale);
  ret = ret.Multiply(m_trans);
  ret = ret.Multiply(m_rot_x);
  ret = ret.Multiply(m_rot_y);
  ret = ret.Multiply(m_rot_z);

  return ret;
}

Mat4 Mat4::GetTransform(float trans_x, float trans_y, float trans_z,
                        float scale_X, float scale_Y, float scale_Z,
                        float rotateX, float rotateY, float rotateZ)
{

  Mat4 m_scale = Scale(scale_X, scale_Y, scale_Z);
  Mat4 m_rot_x = RotateX(rotateX);
  Mat4 m_rot_y = RotateY(rotateY);
  Mat4 m_rot_z = RotateZ(rotateZ);
  Mat4 m_trans = Translate(trans_x, trans_y, trans_z);

  Mat4 ret = Identity();
  ret = ret.Multiply(m_scale);
  ret = ret.Multiply(m_trans);
  ret = ret.Multiply(m_rot_x);
  ret = ret.Multiply(m_rot_y);
  ret = ret.Multiply(m_rot_z);

  return ret;
}

Vec4 Mat4::GetColum(int column) const
{
  if (column < 4)
  {
    return Vec4(m[0 + column], m[4 + column], m[8 + column], m[12 + column]);
  }
  else
    return Vec4(0, 0, 0, 0);
}

Vec4 Mat4::GetLine(int line) const
{
  if (line < 4)
  {
    return Vec4(m[0 + line * 4], m[1 + line * 4], m[2 + line * 4], m[3 + line * 4]);
  }
  else
    return Vec4(0, 0, 0, 0);
}

// Need to do
Mat4 Mat4::PerspectiveMatrix(float fov, float aspect,
                             float near, float far) const
{

  return Mat4();
}

// Need to do
Mat4 Mat4::OrthoMatrix(float right, float left, float top, float valueottom,
                       float near, float far) const
{

  return Mat4();
}
