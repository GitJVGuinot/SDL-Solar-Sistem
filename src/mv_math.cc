#include <mv_math.h>

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

  int iRand(int max, int min)
  {
    return min + rand() % (max + 1);
  }

  float fRand(float max, float min)
  {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(min, max);

    return distr(eng);
  }

  namespace MV
  {

    Vec3 Vec2_Tr_Vec3(Vec2 v2, bool homogeneizado)
    {
      Vec3 v3 = {v2.x, v2.y, (float)homogeneizado};
      return v3;
    }

    Vec4 Vec3_Tr_Vec4(Vec3 v3, bool homogeneizado)
    {
      Vec4 v4 = {v3.x, v3.y, v3.z, (float)homogeneizado};
      return v4;
    }

    Vec2 Vec3_Tr_Vec2(Vec3 v3)
    {
      Vec2 v2 = {v3.x, v3.y};
      return v2;
    }

    Vec3 Vec4_Tr_Vec3(Vec4 v4)
    {
      Vec3 v3 = {v4.x, v4.y, v4.z};
      return v3;
    }

    float Radian_Angulo(float f)
    {
      f = (f * 180) / PI;
      return f;
    }

    float Angulo_Radian(float f)
    {
      f = (f * PI) / 180;
      return f;
    }

    Mat2 Mat2Identity()
    {
      Mat2 id = {
          1, 0,
          0, 1};
      return id;
    }
    Mat3 Mat3Identity()
    {
      Mat3 id = {
          1, 0, 0,
          0, 1, 0,
          0, 0, 1};
      return id;
    }
    Mat4 Mat4Identity()
    {
      Mat4 id = {
          1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1};
      return id;
    }

    Mat4 Mat4Projection()
    {
      Mat4 pro = {
          1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 1,
          0, 0, 0, 0};
      return pro;
    }

    Vec2 Vec_Sum(Vec2 v, Vec2 v1)
    {
      Vec2 v2 = {
          v.x + v1.x, v.y + v1.y};
      // v2=v+v1;
      return v2;
    }
    Vec3 Vec_Sum(Vec3 v, Vec3 v1)
    {
      Vec3 v2 = {
          v.x + v1.x, v.y + v1.y, v.z + v1.z};

      // v2=v+v1;
      return v2;
    }
    Vec4 Vec_Sum(Vec4 v, Vec4 v1)
    {
      Vec4 v2 = {
          v.x + v1.x, v.y + v1.y, v.z + v1.z, v.w + v1.w};

      // v2=v+v1;
      return v2;
    }

    Vec2 Vec_Resta(Vec2 v, Vec2 v1)
    {
      Vec2 v2 = {
          v.x - v1.x, v.y - v1.y};

      // v2=v-v1;
      return v2;
    }
    Vec3 Vec_Resta(Vec3 v, Vec3 v1)
    {
      Vec3 v2 = {
          v.x - v1.x, v.y - v1.y, v.z - v1.z};

      // v2=v-v1;
      return v2;
    }
    Vec4 Vec_Resta(Vec4 v, Vec4 v1)
    {
      Vec4 v2 = {
          v.x - v1.x, v.y - v1.y, v.z - v1.z, v.w - v1.w};

      // v2=v-v1;
      return v2;
    }

    Vec2 Vec_Escalado(Vec2 v, float escalar)
    {
      Vec2 v1 = {
          v.x *= escalar, v.y *= escalar};

      // v1={v}*escalar;
      return v1;
    }
    Vec3 Vec_Escalado(Vec3 v, float escalar)
    {
      Vec3 v1 = {
          v.x *= escalar, v.y *= escalar, v.z *= escalar};

      // v1={v}*escalar;
      return v1;
    }
    Vec4 Vec_Escalado(Vec4 v, float escalar)
    {
      Vec4 v1 = {
          v.x *= escalar, v.y *= escalar, v.z *= escalar, v.w *= escalar};

      // v1={v}*escalar;
      return v1;
    }

    Vec2 Vec_Escalado(Vec2 v, Vec2 v1)
    {
      Vec2 v2 = {
          v.x * v1.x, v.y * v1.y};

      // v2={v.x*v1.x,v.y*v1.y};
      return v2;
    }
    Vec3 Vec_Escalado(Vec3 v, Vec3 v1)
    {
      Vec3 v2 = {
          v.x * v1.x, v.y * v1.y, v.z * v1.z};
      return v2;
    }
    Vec4 Vec_Escalado(Vec4 v, Vec4 v1)
    {
      Vec4 v2 = {
          v.x * v1.x, v.y * v1.y, v.z * v1.z, v.w * v.w};
      return v2;
    }

    Vec2 VecEntreEscalar(Vec2 v, float escalar)
    {
      Vec2 v1 = {
          v.x /= escalar, v.y /= escalar};

      // v1={v}*escalar;
      return v1;
    }
    Vec3 VecEntreEscalar(Vec3 v, float escalar)
    {
      Vec3 v1 = {
          v.x /= escalar, v.y /= escalar, v.z /= escalar};

      // v1={v}*escalar;
      return v1;
    }
    Vec4 VecEntreEscalar(Vec4 v, float escalar)
    {
      Vec4 v1 = {
          v.x /= escalar, v.y /= escalar, v.z /= escalar, v.w /= escalar};

      // v1={v}*escalar;
      return v1;
    }

    float Vec_Magn(Vec2 v)
    {
      float magn = 0;
      magn = sqrt((v.x * v.x) + (v.y * v.y));

      // Pitagoras
      return magn;
    }
    float Vec_Magn(Vec3 v)
    {
      float magn = 0;
      magn = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

      // Pitagoras
      return magn;
    }
    float Vec_Magn(Vec4 v)
    {
      float magn = 0;
      magn = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));

      // Pitagoras
      return magn;
    }

    bool Vec_Normalizado(Vec2 v)
    {
      float magn = 0;
      bool vuelta = false;
      magn = sqrt((v.x * v.x) + (v.y * v.y));

      if (magn < 1.001 && magn > 0.999)
        vuelta = true;
      return vuelta;
    }
    bool Vec_Normalizado(Vec3 v)
    {
      float magn = 0;
      bool vuelta = false;
      magn = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

      if (magn < 1.001 && magn > 0.999)
        vuelta = true;
      return vuelta;
    }
    bool Vec_Normalizado(Vec4 v)
    {
      float magn = 0;
      bool vuelta = false;
      magn = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));

      if (magn < 1.001 && magn > 0.999)
        vuelta = true;
      return vuelta;
    }

    Vec2 Normalizar_Vec(Vec2 v)
    {
      if(!Vec_Normalizado(v)){
        float magn = 0;
        magn = sqrt((v.x * v.x) + (v.y * v.y));

        v.x /= magn;
        v.y /= magn;
      }
      return v;
    }
    Vec3 Normalizar_Vec(Vec3 v)
    {
      if(!Vec_Normalizado(v)){
        float magn = 0;
        magn = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

        v.x /= magn;
        v.y /= magn;
        v.z /= magn;
      }
      return v;
    }
    Vec4 Normalizar_Vec(Vec4 v)
    {
      if(!Vec_Normalizado(v)){
        float magn = 0;
        magn = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));

        v.x /= magn;
        v.y /= magn;
        v.z /= magn;
        v.w /= magn;
      }
      return v;
    }

    // Revisar perpendiculares
    Vec2 Vec_PerpendilacularM1(Vec2 v)
    {
      Vec2 vp = {-v.y, v.x};

      // Perpendicular a la derecha
      //  v1 sera perpendicular a v cuando (v*v1=0) o (v1*v=0)
      return vp;
    }
    Vec2 Vec_PerpendilacularM2(Vec2 v)
    {
      Vec2 vp = {v.y, -v.x};

      // Perpendicular a la izquierda
      //  v1 sera perpendicular a v cuando (v*v1=0) o (v1*v=0)
      return vp;
    }

    Vec3 Vec_PerpendilacularM1(Vec3 v)
    {
      Vec3 vp;
      vp.x = 1;
      vp.y = 1;
      vp.z = (-(v.x * vp.x) - (v.y * vp.y)) / v.z;

      // v1 sera perpendicular a v cuando (v*v1=0) o (v1*v=0)
      return vp;
    }
    Vec3 Vec_PerpendilacularM2(Vec3 v)
    {
      Vec3 vp;
      vp.x = 1;
      vp.z = 1;
      vp.y = (-(v.x * vp.x) - (v.z * vp.z)) / v.y;

      // v1 sera perpendicular a v cuando (v*v1=0) o (v1*v=0)
      return vp;
    }
    Vec3 Vec_PerpendilacularM3(Vec3 v)
    {
      Vec3 vp;
      vp.y = 1;
      vp.z = 1;
      vp.x = (-(v.y * vp.y) - (v.z * vp.z)) / v.x;

      // v1 sera perpendicular a v cuando (v*v1=0) o (v1*v=0)
      return vp;
    }

    Vec4 Vec_PerpendilacularM1(Vec4 v)
    {
      Vec4 vp;
      vp.x = 1;
      vp.y = 1;
      vp.z = 1;
      vp.w = (-(v.x * vp.x) - (v.y * vp.y) - (v.z * vp.z)) / v.w;

      // v1 sera perpendicular a v cuando (v*v1=0) o (v1*v=0)
      return vp;
    }
    Vec4 Vec_PerpendilacularM2(Vec4 v)
    {
      Vec4 vp;
      vp.w = 1;
      vp.y = 1;
      vp.z = 1;
      vp.x = (-(v.w * vp.w) - (v.y * vp.y) - (v.z * vp.z)) / v.x;

      // v1 sera perpendicular a v cuando (v*v1=0) o (v1*v=0)
      return vp;
    }
    Vec4 Vec_PerpendilacularM3(Vec4 v)
    {
      Vec4 vp;
      vp.x = 1;
      vp.w = 1;
      vp.z = 1;
      vp.y = (-(v.x * vp.x) - (v.w * vp.w) - (v.z * vp.z)) / v.y;

      // v1 sera perpendicular a v cuando (v*v1=0) o (v1*v=0)
      return vp;
    }
    Vec4 Vec_PerpendilacularM4(Vec4 v)
    {
      Vec4 vp;
      vp.x = 1;
      vp.y = 1;
      vp.w = 1;
      vp.z = (-(v.x * vp.x) - (v.y * vp.y) - (v.w * vp.w)) / v.z;

      // v1 sera perpendicular a v cuando (v*v1=0) o (v1*v=0)
      return vp;
    }

    bool Vec_Iguales(Pnt2 vec, Pnt2 vec_1, Pnt2 error)
    {
      bool ret = false;

      if ((vec_1.x + error.x) >= vec.x && vec.x >= (vec_1.x - error.x))
        if ((vec_1.y + error.y) >= vec.y && vec.y >= (vec_1.y - error.y))
          ret = true;

      return ret;
    }

    bool Vec_Iguales(Pnt3 vec, Pnt3 vec_1, Pnt3 error)
    {
      bool ret = false;

      if ((vec_1.x + error.x) >= vec.x && vec.x >= (vec_1.x - error.x))
        if ((vec_1.y + error.y) >= vec.y && vec.y >= (vec_1.y - error.y))
          if ((vec_1.z + error.z) >= vec.z && vec.z >= (vec_1.z - error.z))
            ret = true;

      return ret;
    }

    Vec2 Vec_Init(float x, float y)
    {
      Vec2 vi;
      vi.x = x;
      vi.y = y;
      return vi;
    }
    Vec3 Vec_Init(float x, float y, float z)
    {
      Vec3 vi;
      vi.x = x;
      vi.y = y;
      vi.z = z;
      return vi;
    }
    Vec4 Vec_Init(float x, float y, float z, float w)
    {
      Vec4 vi;
      vi.x = x;
      vi.y = y;
      vi.z = z;
      vi.w = w;
      return vi;
    }

    void Vec_Print(Vec2 v, const char *s)
    {
      printf("%s{%2.6f, %2.6f} \n", s, v.x, v.y);
    }
    void Vec_Print(Vec3 v, const char *s)
    {
      printf("%s{%2.6f, %2.6f, %2.6f} \n", s, v.x, v.y, v.z);
    }
    void Vec_Print(Vec4 v, const char *s)
    {
      printf("%s{%2.6f, %2.6f, %2.6f, %2.6f} \n", s, v.x, v.y, v.z, v.w);
    }

    void Mat_Print(Mat2 m, const char *s)
    {
      printf("\n %s \n", s);
      for (unsigned int i = 0; i < 4; i++)
      {
        if (i == 2)
          printf("\n");
        printf(" m[%d]: %f,", i, m.m[i]);
      }
    }
    void Mat_Print(Mat3 m, const char *s)
    {
      printf("\n %s \n", s);
      for (unsigned int i = 0; i < 9; i++)
      {
        if (i == 3 || i == 6)
          printf("\n");
        printf(" m[%d]: %f,", i, m.m[i]);
      }
    }
    void Mat_Print(Mat4 m, const char *s)
    {
      printf("\n %s \n", s);
      for (unsigned int i = 0; i < 16; i++)
      {
        if (i == 4 || i == 8 || i == 12)
          printf("\n");
        printf(" m[%d]: %f,", i, m.m[i]);
      }
    }

    Mat2 Mat_Sum(Mat2 m, Mat2 m1)
    {
      Mat2 m2 = {
          m.m[0] + m1.m[0], m.m[1] + m1.m[1],
          m.m[2] + m1.m[2], m.m[3] + m1.m[3]};

      // m2=m+m1
      return m2;
    }
    Mat3 Mat_Sum(Mat3 m, Mat3 m1)
    {
      Mat3 m2 = {
          m.m[0] + m1.m[0], m.m[1] + m1.m[1], m.m[2] + m1.m[2],
          m.m[3] + m1.m[3], m.m[4] + m1.m[4], m.m[5] + m1.m[5],
          m.m[6] + m1.m[6], m.m[7] + m1.m[7], m.m[8] + m1.m[8]};

      // m2=m+m1
      return m2;
    }
    Mat4 Mat_Sum(Mat4 m, Mat4 m1)
    {
      Mat4 m2 = {
          m.m[0] + m1.m[0], m.m[1] + m1.m[1], m.m[2] + m1.m[2], m.m[3] + m1.m[3],
          m.m[4] + m1.m[4], m.m[5] + m1.m[5], m.m[6] + m1.m[6], m.m[7] + m1.m[7],
          m.m[8] + m1.m[8], m.m[9] + m1.m[9], m.m[10] + m1.m[10], m.m[11] + m1.m[11],
          m.m[12] + m1.m[12], m.m[13] + m1.m[13], m.m[14] + m1.m[14], m.m[15] + m1.m[15]};

      // m2=m+m1
      return m2;
    }

    Mat2 Mat_Resta(Mat2 m, Mat2 m1)
    {
      Mat2 m2 = {
          m.m[0] - m1.m[0], m.m[1] - m1.m[1],
          m.m[2] - m1.m[2], m.m[3] - m1.m[3]};

      // m2=m-m1
      return m2;
    }
    Mat3 Mat_Resta(Mat3 m, Mat3 m1)
    {
      Mat3 m2 = {
          m.m[0] - m1.m[0], m.m[1] - m1.m[1], m.m[2] - m1.m[2],
          m.m[3] - m1.m[3], m.m[4] - m1.m[4], m.m[5] - m1.m[5],
          m.m[6] - m1.m[6], m.m[7] - m1.m[7], m.m[8] - m1.m[8]};

      // m2=m-m1
      return m2;
    }
    Mat4 Mat_Rest(Mat4 m, Mat4 m1)
    {
      Mat4 m2 = {
          m.m[0] - m1.m[0], m.m[1] - m1.m[1], m.m[2] - m1.m[2], m.m[3] - m1.m[3],
          m.m[4] - m1.m[4], m.m[5] - m1.m[5], m.m[6] - m1.m[6], m.m[7] - m1.m[7],
          m.m[8] - m1.m[8], m.m[9] - m1.m[9], m.m[10] - m1.m[10], m.m[11] - m1.m[11],
          m.m[12] - m1.m[12], m.m[13] - m1.m[13], m.m[14] - m1.m[14], m.m[15] - m1.m[15]};

      // m2=m-m1
      return m2;
    }

    Mat2 Mat_Escalada(Mat2 m, float escalar)
    {
      Mat2 m1 = {
          m.m[0] * escalar, m.m[1] * escalar,
          m.m[2] * escalar, m.m[3] * escalar};

      // m1=m*escalar
      return m1;
    }
    Mat3 Mat_Escalada(Mat3 m, float escalar)
    {
      Mat3 m1 = {
          m.m[0] * escalar, m.m[1] * escalar, m.m[2] * escalar,
          m.m[3] * escalar, m.m[4] * escalar, m.m[5] * escalar,
          m.m[6] * escalar, m.m[7] * escalar, m.m[8] * escalar};

      // m1=m*escalar
      return m1;
    }
    Mat4 Mat_Escalada(Mat4 m, float escalar)
    {
      Mat4 m1 = {
          m.m[0] * escalar, m.m[1] * escalar, m.m[2] * escalar, m.m[3] * escalar,
          m.m[3] * escalar, m.m[4] * escalar, m.m[5] * escalar, m.m[7] * escalar,
          m.m[6] * escalar, m.m[7] * escalar, m.m[8] * escalar, m.m[11] * escalar,
          m.m[12] * escalar, m.m[13] * escalar, m.m[14] * escalar, m.m[15] * escalar};

      // m1=m*escalar
      return m1;
    }

    Mat2 MatEntreEscalar(Mat2 m, float escalar)
    {
      Mat2 m1 = {
          m.m[0] / escalar, m.m[1] / escalar,
          m.m[2] / escalar, m.m[3] / escalar};

      // m1=m/escalar
      return m1;
    }
    Mat3 MatEntreEscalar(Mat3 m, float escalar)
    {
      Mat3 m1 = {
          m.m[0] / escalar, m.m[1] / escalar, m.m[2] / escalar,
          m.m[3] / escalar, m.m[4] / escalar, m.m[5] / escalar,
          m.m[6] / escalar, m.m[7] / escalar, m.m[8] / escalar};

      // m1=m/escalar
      return m1;
    }
    Mat4 MatEntreEscalar(Mat4 m, float escalar)
    {
      Mat4 m1 = {
          m.m[0] / escalar, m.m[1] / escalar, m.m[2] / escalar, m.m[3] / escalar,
          m.m[3] / escalar, m.m[4] / escalar, m.m[5] / escalar, m.m[7] / escalar,
          m.m[6] / escalar, m.m[7] / escalar, m.m[8] / escalar, m.m[11] / escalar,
          m.m[12] / escalar, m.m[13] / escalar, m.m[14] / escalar, m.m[15] / escalar};

      // m1=m/escalar
      return m1;
    }

    Mat3 Mat3Translate(Pnt2 desp)
    {
      Mat3 tras = {
          1, 0, 0,
          0, 1, 0,
          desp.x, desp.y, 1};

      return tras;
    }
    Mat4 Mat4Translate(Pnt3 desp)
    {
      Mat4 tras = {
          1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          desp.x, desp.y, desp.z, 1};

      return tras;
    }
    Mat3 Mat3Rotate(float angulo)
    {
      Mat3 rot = {
          (float)cos(angulo), (float)sin(angulo), 0,
          (float)-sin(angulo), (float)cos(angulo), 0,
          0, 0, 1};

      return rot;
    }
    Mat4 Mat4RotateX(float rotacion)
    {
      Mat4 rot = {
          1, 0, 0, 0,
          0, (float)cos(rotacion), (float)sin(rotacion), 0,
          0, (float)-sin(rotacion), (float)cos(rotacion), 0,
          0, 0, 0, 1};
      return rot;
    }
    Mat4 Mat4RotateY(float rotacion)
    {
      Mat4 rot = {
          (float)cos(rotacion), 0, (float)-sin(rotacion), 0,
          0, 1, 0, 0,
          (float)sin(rotacion), 0, (float)cos(rotacion), 0,
          0, 0, 0, 1};
      return rot;
    }
    Mat4 Mat4RotateZ(float rotacion)
    {
      Mat4 rot = {
          (float)cos(rotacion), (float)sin(rotacion), 0, 0,
          (float)-sin(rotacion), (float)cos(rotacion), 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1};
      return rot;
    }
    Mat3 Mat3Scale(Vec2 escala)
    {
      Mat3 scala = {
          escala.x, 0, 0,
          0, escala.y, 0,
          0, 0, 1};

      return scala;
    }
    Mat4 Mat4Scale(Pnt3 escala)
    {
      Mat4 scala = {
          escala.x, 0, 0, 0,
          0, escala.y, 0, 0,
          0, 0, escala.z, 0,
          0, 0, 0, 1};
      return scala;
    }
    Mat3 Mat3Multiply(Mat3 m, Mat3 m1)
    {
      float a[9];

      a[0] = (m.m[0] * m1.m[0]) + (m.m[3] * m1.m[1]) + (m.m[6] * m1.m[2]);
      a[1] = (m.m[1] * m1.m[0]) + (m.m[4] * m1.m[1]) + (m.m[7] * m1.m[2]);
      a[2] = (m.m[2] * m1.m[0]) + (m.m[5] * m1.m[1]) + (m.m[8] * m1.m[2]);
      a[3] = (m.m[0] * m1.m[3]) + (m.m[3] * m1.m[4]) + (m.m[6] * m1.m[5]);
      a[4] = (m.m[1] * m1.m[3]) + (m.m[4] * m1.m[4]) + (m.m[7] * m1.m[5]);
      a[5] = (m.m[2] * m1.m[3]) + (m.m[5] * m1.m[4]) + (m.m[8] * m1.m[5]);
      a[6] = (m.m[0] * m1.m[6]) + (m.m[3] * m1.m[7]) + (m.m[6] * m1.m[8]);
      a[7] = (m.m[1] * m1.m[6]) + (m.m[4] * m1.m[7]) + (m.m[7] * m1.m[8]);
      a[8] = (m.m[2] * m1.m[6]) + (m.m[5] * m1.m[7]) + (m.m[8] * m1.m[8]);

      Mat3 m2 = {
          a[0], a[1], a[2],
          a[3], a[4], a[5],
          a[6], a[7], a[8]};
      return m2;
    }
    Mat4 Mat4Multiply(Mat4 m, Mat4 m1)
    {
      float a[16];

      a[0] = (m.m[0] * m1.m[0]) + (m.m[4] * m1.m[1]) + (m.m[8] * m1.m[2]) + (m.m[12] * m1.m[3]);
      a[1] = (m.m[1] * m1.m[0]) + (m.m[5] * m1.m[1]) + (m.m[9] * m1.m[2]) + (m.m[13] * m1.m[3]);
      a[2] = (m.m[2] * m1.m[0]) + (m.m[6] * m1.m[1]) + (m.m[10] * m1.m[2]) + (m.m[14] * m1.m[3]);
      a[3] = (m.m[3] * m1.m[0]) + (m.m[7] * m1.m[1]) + (m.m[11] * m1.m[2]) + (m.m[15] * m1.m[3]);
      a[4] = (m.m[0] * m1.m[4]) + (m.m[4] * m1.m[5]) + (m.m[8] * m1.m[6]) + (m.m[12] * m1.m[7]);
      a[5] = (m.m[1] * m1.m[4]) + (m.m[5] * m1.m[5]) + (m.m[9] * m1.m[6]) + (m.m[13] * m1.m[7]);
      a[6] = (m.m[2] * m1.m[4]) + (m.m[6] * m1.m[5]) + (m.m[10] * m1.m[6]) + (m.m[14] * m1.m[7]);
      a[7] = (m.m[3] * m1.m[4]) + (m.m[7] * m1.m[5]) + (m.m[11] * m1.m[6]) + (m.m[15] * m1.m[7]);
      a[8] = (m.m[0] * m1.m[8]) + (m.m[4] * m1.m[9]) + (m.m[8] * m1.m[10]) + (m.m[12] * m1.m[11]);
      a[9] = (m.m[1] * m1.m[8]) + (m.m[5] * m1.m[9]) + (m.m[9] * m1.m[10]) + (m.m[13] * m1.m[11]);
      a[10] = (m.m[2] * m1.m[8]) + (m.m[6] * m1.m[9]) + (m.m[10] * m1.m[10]) + (m.m[14] * m1.m[11]);
      a[11] = (m.m[3] * m1.m[8]) + (m.m[7] * m1.m[9]) + (m.m[11] * m1.m[10]) + (m.m[15] * m1.m[11]);
      a[12] = (m.m[0] * m1.m[12]) + (m.m[4] * m1.m[13]) + (m.m[8] * m1.m[14]) + (m.m[12] * m1.m[15]);
      a[13] = (m.m[1] * m1.m[12]) + (m.m[5] * m1.m[13]) + (m.m[9] * m1.m[14]) + (m.m[13] * m1.m[15]);
      a[14] = (m.m[2] * m1.m[12]) + (m.m[6] * m1.m[13]) + (m.m[10] * m1.m[14]) + (m.m[14] * m1.m[15]);
      a[15] = (m.m[3] * m1.m[12]) + (m.m[7] * m1.m[13]) + (m.m[11] * m1.m[14]) + (m.m[15] * m1.m[15]);

      Mat4 m2 = {
          a[0], a[1], a[2], a[3],
          a[4], a[5], a[6], a[7],
          a[8], a[9], a[10], a[11],
          a[12], a[13], a[14], a[15]};
      return m2;
    }

    Vec3 Mat3TransformVec3(Mat3 m, Vec3 v)
    {
      Vec3 v1 = {
          (m.m[0] * v.x) + (m.m[3] * v.y) + (m.m[6] * v.z),
          (m.m[1] * v.x) + (m.m[4] * v.y) + (m.m[7] * v.z),
          (m.m[2] * v.x) + (m.m[5] * v.y) + (m.m[8] * v.z)};

      return v1;
    }
    Vec4 Mat4TransformVec4(Mat4 m, Vec4 v)
    {
      Vec4 v1 = {
          (m.m[0] * v.x) + (m.m[4] * v.y) + (m.m[8] * v.z) + (m.m[12] * v.w),
          (m.m[1] * v.x) + (m.m[5] * v.y) + (m.m[9] * v.z) + (m.m[13] * v.w),
          (m.m[2] * v.x) + (m.m[6] * v.y) + (m.m[10] * v.z) + (m.m[14] * v.w),
          (m.m[3] * v.x) + (m.m[7] * v.y) + (m.m[11] * v.z) + (m.m[15] * v.w)};

      return v1;
    }
    Vec4 HomogeinizaVec(Vec4 v)
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
    Vec3 Mat4TransformVec3(Mat4 m, Vec3 v)
    {

      Vec4 v1 = {
          (m.m[0] * v.x) + (m.m[4] * v.y) + (m.m[8] * v.z) + (m.m[12] * 1.0f),
          (m.m[1] * v.x) + (m.m[5] * v.y) + (m.m[9] * v.z) + (m.m[13] * 1.0f),
          (m.m[2] * v.x) + (m.m[6] * v.y) + (m.m[10] * v.z) + (m.m[14] * 1.0f),
          (m.m[3] * v.x) + (m.m[7] * v.y) + (m.m[11] * v.z) + (m.m[15] * 1.0f)};

      Vec4 v2 = HomogeinizaVec(v1);
      Vec3 homo = {v2.x, v2.y, v2.z};
      return homo;
    }
    float Determinante(Mat2 m)
    {
      float det;

      det = {(m.m[0] * m.m[3]) - (m.m[2] * m.m[1])};

      return det;
    }
    float Obten_Angulo(Pnt2 vec, Pnt2 vec1)
    {

      float dividendo = (vec.x * vec1.x) + (vec.y * vec1.y);
      float divisor = ( sqrt((vec.x * vec.x) + (vec.y * vec.y)) );
      float divisor1 = ( sqrt((vec1.x * vec1.x) + (vec1.y * vec1.y)) );
      float radian = acos(dividendo / (divisor * divisor1));
      float angulo = (radian * 180 / PI) * (-1);

      return angulo;
    }
    float Obten_Angulo(Pnt3 vec, Pnt3 vec1){

      float dividendo = (vec.x * vec1.x) + (vec.y * vec1.y) + (vec.z * vec1.z);
      float divisor = ( sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)) );
      float divisor1 = ( sqrt((vec1.x * vec1.x) + (vec1.y * vec1.y) + (vec1.z * vec1.z)) );
      float radian = acos(dividendo / (divisor * divisor1));
      float angulo = (radian * 180 / PI) * (-1);

      if (!Between(180, angulo, -180))
        return 180;
      
      return angulo;
    }

    float Dot_Product(Vec2 v, Vec2 v1)
    {
      float ret;
      ret = (v.x * v1.x) + (v.y * v1.y);
      return ret;
    }

    float Dot_Product(Vec3 v, Vec3 v1)
    {
      float ret;
      ret = (v.x * v1.x) + (v.y * v1.y) + (v.z * v1.z);
      return ret;
    }

    Pnt3 Cross_Product(Pnt3 v, Pnt3 v1)
    {

      Pnt3 ret = {
          v.y * v1.z - v1.y * v.z,
          v.z * v1.x - v1.z * v.x,
          v.x * v1.y - v1.x * v.y};

      return ret;
    }

    float Calcula_Angulo(Vec2 v, Vec2 v1)
    {
      float angulo = Dot_Product(v, v1);
      angulo = acosf(angulo / (Vec_Magn(v) * Vec_Magn(v1)));
      return angulo;
    } // Devuelve el valor en radianes

    Vec2 *Inicia_Circulo_Basico(int vertices, float dim, float rotacion, Vec2 desp)
    {
      Vec2 *circle = (Vec2 *)calloc(vertices + 2, sizeof(Vec2));

      float radianes = 0;
      int vertex = 0;

      while (radianes <= ((2 * PI)))
      {

        *(circle + vertex) = {
            dim * (float)cos(radianes - rotacion) + desp.x, // vertice en x
            dim * (float)sin(radianes - rotacion) + desp.y  // vertice en y
        };

        vertex++;
        radianes += (2 * PI) / vertices;
      }

      *(circle + vertex) = {FLT_MAX, FLT_MAX};

      return circle;
    }

    bool Colision_Circular(Vec2 centro, int dim, Vec2 centro1, int dim1)
    {
      bool colision = false;
      Vec2 v = {
          centro.x - centro1.x, centro.y - centro1.y}; // Vec2 Resta para hallar la distancia entre los centros

      if (v.x < 0)
        v.x *= (-1);
      if (v.y < 0)
        v.y *= (-1);
      // Convierte la distancia de 'X' e 'Y' en absolutas

      float magn;
      magn = sqrt((v.x * v.x) + (v.y * v.y));
      magn -= dim;
      magn -= dim1;
      // Obtiene la distancia entre los dos puntos externos de la circunferencia
      if (magn <= 0)
        colision = true;
      // Si la distancia entre ellos es igual o inferior a 0 hay colision

      return colision;
    }

    bool Colision_Esferas(Pnt3 centro_1, float dim_1, Pnt3 centro_2, float dim_2)
    {
      bool colision = false;
      Vec3 v = {centro_1.x - centro_2.x, centro_1.y - centro_2.y, centro_1.z - centro_2.z}; // Vec3 Resta para hallar la distancia entre los centros

      if (v.x < 0)
        v.x *= (-1);
      if (v.y < 0)
        v.y *= (-1);
      if (v.z < 0)
        v.z *= (-1);
      // Convierte la distancia de 'X' , 'Y' y "Z" en absolutas

      float magn;
      magn = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
      magn -= dim_1;
      magn -= dim_2;
      // Obtiene la distancia entre los dos puntos externos de la circunferencia
      if (magn <= 0)
        colision = true;
      // Si la distancia entre ellos es igual o inferior a 0 hay colision

      return colision;
    }

    bool Colision(float x1, float y1, float x2, float y2, float ox1, float oy1, float ox2, float oy2)
    {
      bool colision = true;

      if (x2 <= ox1 || x1 >= ox2 || y2 <= oy1 || y1 >= oy2)
        colision = false;

      // Si algun valor es NaN
      if (x1 != x1)
        colision = false;
      if (x2 != x2)
        colision = false;
      if (y1 != y1)
        colision = false;
      if (y2 != y2)
        colision = false;

      if (ox1 != ox1)
        colision = false;
      if (ox2 != ox2)
        colision = false;
      if (oy1 != oy1)
        colision = false;
      if (oy2 != oy2)
        colision = false;

      return colision;
    }

    bool Colision(Pnt2 init, float w, float h, Pnt2 c, float r)
    {
      // Círculo con centro en (cx,cy) y radio r
      // Rectángulo con esquina superior izquierda en (x,y) ancho w y algo h
      // Punto (en verde) del perímetro del rectángulo más cercano a la circunferencia en (px,py)
      float px, py;
      px = c.x; // En principio son iguales
      if (px < init.x)
        px = init.x;
      if (px > init.x + w)
        px = init.x + w;
      py = c.y;
      if (py < init.y)
        py = init.y;
      if (py > init.y + h)
        py = init.y + h;
      float distancia = sqrt((c.x - px) * (c.x - px) + (c.y - py) * (c.y - py));
      if (distancia < r)
      {
        return true;
      }
      return false;
    }

    bool Colision(Pnt2 init, Pnt2 fin, Pnt2 init_o, Pnt2 fin_o)
    {
      bool colision = true;

      if (fin.x <= init_o.x || init.x >= fin_o.x || fin.y <= init_o.y || init.y >= fin_o.y)
        colision = false;

      if (init.x != init.x)
        colision = false;
      if (init.y != init.y)
        colision = false;
      if (fin.x != fin.x)
        colision = false;
      if (fin.y != fin.y)
        colision = false;

      if (init_o.x != init_o.x)
        colision = false;
      if (init_o.y != init_o.y)
        colision = false;
      if (fin_o.x != fin_o.x)
        colision = false;
      if (fin_o.y != fin_o.y)
        colision = false;

      return colision;
    }

    Pnt3 HallaRecta(Pnt2 a, Pnt2 b)
    { // a==1 b==2
      Pnt3 ret;

      double m = (b.y - a.y) / (b.x - a.x);

      ret = {(float)m, 1.0f, (float)-m * a.x + a.y};
      return ret;
    }

    Pnt2 Interseccion_Rectas(Pnt3 recta_a, Pnt3 recta_b)
    {
      Pnt2 interseccion;

      float det = Determinante({recta_a.x, recta_a.y, recta_b.x, recta_b.y});

      interseccion.x = -Determinante({recta_a.z, recta_a.y, recta_b.z, recta_b.y}) / det;
      interseccion.y = Determinante({recta_a.x, recta_a.z, recta_b.x, recta_b.z}) / det;

      return interseccion;
    }

    bool Colision_3_Cuadrados(Vec2 a_init, Vec2 a_fin, Vec2 b_init, Vec2 b_fin, Vec2 c_init, Vec2 c_fin)
    {
      bool colision = false;

      if (Colision(a_init, a_fin, b_init, b_fin))
        if (Colision(a_init, a_fin, c_init, c_fin))
          if (Colision(b_init, b_fin, c_init, c_fin))
            colision = true;

      return colision;
    }

    // Dados tres puntos colineales: A, B, C.
    // la función verifica si el punto B se encuentra en el segmento de línea 'AC'
    bool Segmento(Pnt2 A, Pnt2 B, Pnt2 C)
    {

      if (B.x <= std::max(A.x, C.x) && B.x >= std::min(A.x, C.x) &&
          B.y <= std::max(A.y, C.y) && B.y >= std::min(A.y, C.y))
        return true;

      return false;
    }

    // Para hallar la orientacion de A, B, C
    int Orientacion(Pnt2 A, Pnt2 B, Pnt2 C)
    {

      int val = (B.y - A.y) * (C.x - B.x) - (B.x - A.x) * (C.y - B.y);

      if (!val)
        return 0; // Los puntos pertenecen a la misma recta

      // Consulta en sentido horario o antihorario
      if (val > 0)
        return 1;
      else
        return 2;
    }

    // Devuelve true si 'AB' y 'CD' Intersecan
    bool Interseccion(Pnt2 A, Pnt2 B, Pnt2 C, Pnt2 D)
    {

      // Encuentra las 4 orientaciones necesarias para los distintos casos
      int o1 = Orientacion(A, B, C);
      int o2 = Orientacion(A, B, D);
      int o3 = Orientacion(C, D, A);
      int o4 = Orientacion(C, D, B);

      // Casos generales
      if (o1 != o2 && o3 != o4)
        return true;

      // Casos Speciales
      // A, B, C pertenecen a la misma recta y C recae sobre AB
      if (!o1 && Segmento(A, C, B))
        return true;

      // A, B, D pertenecen a la misma recta y D recae sobre AB
      if (!o2 && Segmento(A, D, B))
        return true;

      // C, D, A pertenecen a la misma recta y A recae sobre CD
      if (!o3 && Segmento(C, A, D))
        return true;

      // C, D, B pertenecen a la misma recta y B recae sobre CD
      if (!o4 && Segmento(C, B, D))
        return true;

      return false; // No es ningun caso anterior por ende no hay interseccion
    }

    Vec2 Vec_Unitario(Vec2 v)
    {
      Vec2 v1 = {
          v.x /= (float)sqrt((v.x * v.x) + (v.y * v.y)),
          v.y /= (float)sqrt((v.x * v.x) + (v.y * v.y))};

      return v1;
    }

    Mat4 Mat4View(Vec3 camara, Vec3 mira, Vec3 up)
    {

      Vec3 zAxis = Vec_Resta(camara, mira); // Vector Z
      if (!Vec_Normalizado(zAxis))
        zAxis = Normalizar_Vec(zAxis);

      Vec3 xAxis = Cross_Product(up, zAxis); // Vector X
      if (!Vec_Normalizado(xAxis))
        xAxis = Normalizar_Vec(xAxis);

      Vec3 yAxis = Cross_Product(zAxis, xAxis); // Vector Y
      if (!Vec_Normalizado(yAxis))
        yAxis = Normalizar_Vec(yAxis);

      // Crea una matriz de vista a partir de los vectores de la camara
      Mat4 vMat = {
          xAxis.x, yAxis.x, zAxis.x, 0,
          xAxis.y, yAxis.y, zAxis.y, 0,
          xAxis.z, yAxis.z, zAxis.z, 0,
          -Dot_Product(xAxis, camara), -Dot_Product(yAxis, camara), -Dot_Product(zAxis, camara), 1};

      return vMat;
    }

    void Orbitar_Punto(Pnt3 centro_orbita, Pnt3 p_orbita, Pnt3 &punto)
    {
      Mat4 rot_x;
      if (p_orbita.x != 0)
        rot_x = Mat4RotateX((p_orbita.x * PI) / 180);
      Mat4 rot_y;
      if (p_orbita.y != 0)
        rot_y = Mat4RotateY((p_orbita.y * PI) / 180);
      Mat4 rot_z;
      if (p_orbita.z != 0)
        rot_z = Mat4RotateZ((p_orbita.z * PI) / 180);

      Mat4 model = Mat4Identity();
      if (p_orbita.x != 0)
        model = Mat4Multiply(model, rot_x);
      if (p_orbita.y != 0)
        model = Mat4Multiply(model, rot_y);
      if (p_orbita.z != 0)
        model = Mat4Multiply(model, rot_z);

      punto = Vec_Resta(punto, centro_orbita);
      punto = Mat4TransformVec3(model, punto);
      punto = Vec_Sum(punto, centro_orbita);
    }

    MV::Pnt3 Centro_Triangulo(MV::Pnt3 *triangulos) {
      MV::Pnt3 ret={0,0,0};

      ret.x = ((triangulos + 0)->x + (triangulos + 1)->x + (triangulos + 2)->x)/3;
      ret.y = ((triangulos + 0)->y + (triangulos + 1)->y + (triangulos + 2)->y)/3;
      ret.z = ((triangulos + 0)->z + (triangulos + 1)->z + (triangulos + 2)->z)/3;

      return ret;
    }


  }
