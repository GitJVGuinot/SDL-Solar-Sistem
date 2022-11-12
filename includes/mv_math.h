#include <iostream>
#include <cmath>
#include <random>
#include <float.h>

//////////////////////
// Guardas, NO TOCAR
#ifndef mv_math_h
#define mv_math_h
// Guardas, NO TOCAR
//////////////////////

#define PI 3.14159265358979323846
#define Between(x, y, z) (x > y && y >= z)
#define DESTROY(x)  \
  if (x != nullptr) \
  {                 \
    free(x);        \
    x = nullptr;    \
  }

int InF();
int NaN();

int iRand(int max = RAND_MAX, int min = 0);

float fRand(float max, float min = 0);

namespace MV
{

#define Pnt2 Vec2
#define Pnt3 Vec3
#define Pnt4 Vec4

  struct Vec2
  {
    float x, y;
  };
  struct Mat2
  {
    float m[4];
  };

  struct Vec3
  {
    float x, y, z;
  };
  struct Mat3
  {
    float m[9];
  };

  struct Vec4
  {
    float x, y, z, w;
  };
  struct Mat4
  {
    float m[16];
  };

  Vec3 Vec2_Tr_Vec3(Vec2 v2, bool homogeneizado = true);

  Vec4 Vec3_Tr_Vec4(Vec3 v3, bool homogeneizado = true);

  Vec2 Vec3_Tr_Vec2(Vec3 v3);

  Vec3 Vec4_Tr_Vec3(Vec4 v4);

  float Radian_Angulo(float f);

  float Angulo_Radian(float f);

  Mat2 Mat2Identity();
  Mat3 Mat3Identity();
  Mat4 Mat4Identity();

  Mat4 Mat4Projection();

  Vec2 Vec_Sum(Vec2 v, Vec2 v1);
  Vec3 Vec_Sum(Vec3 v, Vec3 v1);
  Vec4 Vec_Sum(Vec4 v, Vec4 v1);

  Vec2 Vec_Resta(Vec2 v, Vec2 v1);
  Vec3 Vec_Resta(Vec3 v, Vec3 v1);
  Vec4 Vec_Resta(Vec4 v, Vec4 v1);

  Vec2 Vec_Escalado(Vec2 v, float escalar);
  Vec3 Vec_Escalado(Vec3 v, float escalar);
  Vec4 Vec_Escalado(Vec4 v, float escalar);

  Vec2 Vec_Escalado(Vec2 v, Vec2 v1);
  Vec3 Vec_Escalado(Vec3 v, Vec3 v1);
  Vec4 Vec_Escalado(Vec4 v, Vec4 v1);

  Vec2 VecEntreEscalar(Vec2 v, float escalar);
  Vec3 VecEntreEscalar(Vec3 v, float escalar);
  Vec4 VecEntreEscalar(Vec4 v, float escalar);

  float Vec_Magn(Vec2 v);
  float Vec_Magn(Vec3 v);
  float Vec_Magn(Vec4 v);

  bool Vec_Normalizado(Vec2 v);
  bool Vec_Normalizado(Vec3 v);
  bool Vec_Normalizado(Vec4 v);

  Vec2 Normalizar_Vec(Vec2 v);
  Vec3 Normalizar_Vec(Vec3 v);
  Vec4 Normalizar_Vec(Vec4 v);

  // Revisar perpendiculares
  Vec2 Vec_PerpendilacularM1(Vec2 v);
  Vec2 Vec_PerpendilacularM2(Vec2 v);

  Vec3 Vec_PerpendilacularM1(Vec3 v);
  Vec3 Vec_PerpendilacularM2(Vec3 v);
  Vec3 Vec_PerpendilacularM3(Vec3 v);

  Vec4 Vec_PerpendilacularM1(Vec4 v);
  Vec4 Vec_PerpendilacularM2(Vec4 v);
  Vec4 Vec_PerpendilacularM3(Vec4 v);

  bool Vec_Iguales(Pnt2 vec, Pnt2 vec_1, Pnt2 error);
  bool Vec_Iguales(Pnt3 vec, Pnt3 vec_1, Pnt3 error);

  Vec2 Vec_Init(float x, float y);
  Vec3 Vec_Init(float x, float y, float z);
  Vec4 Vec_Init(float x, float y, float z, float w);

  void Vec_Print(Vec2 v, const char *s = "El vector es: ");
  void Vec_Print(Vec3 v, const char *s = "El vector es: ");
  void Vec_Print(Vec4 v, const char *s = "El vector es: ");

  void Mat_Print(Mat2 m, const char *s = "La matriz es: ");
  void Mat_Print(Mat3 m, const char *s = "La matriz es: ");
  void Mat_Print(Mat4 m, const char *s = "La matriz es: ");

  Mat2 Mat_Sum(Mat2 m, Mat2 m1);
  Mat3 Mat_Sum(Mat3 m, Mat3 m1);
  Mat4 Mat_Sum(Mat4 m, Mat4 m1);

  Mat2 Mat_Resta(Mat2 m, Mat2 m1);
  Mat3 Mat_Resta(Mat3 m, Mat3 m1);
  Mat4 Mat_Rest(Mat4 m, Mat4 m1);

  Mat2 Mat_Escalada(Mat2 m, float escalar);
  Mat3 Mat_Escalada(Mat3 m, float escalar);
  Mat4 Mat_Escalada(Mat4 m, float escalar);

  Mat2 MatEntreEscalar(Mat2 m, float escalar);
  Mat3 MatEntreEscalar(Mat3 m, float escalar);
  Mat4 MatEntreEscalar(Mat4 m, float escalar);

  Mat3 Mat3Translate(Pnt2 desp);
  Mat4 Mat4Translate(Pnt3 desp);
  Mat3 Mat3Rotate(float angulo);
  Mat4 Mat4RotateX(float rotacion);
  Mat4 Mat4RotateY(float rotacion);
  Mat4 Mat4RotateZ(float rotacion);
  Mat3 Mat3Scale(Vec2 escala);
  Mat4 Mat4Scale(Pnt3 escala);
  Mat3 Mat3Multiply(Mat3 m, Mat3 m1);
  Mat4 Mat4Multiply(Mat4 m, Mat4 m1);

  Vec3 Mat3TransformVec3(Mat3 m, Vec3 v);
  Vec4 Mat4TransformVec4(Mat4 m, Vec4 v);
  Vec4 HomogeinizaVec(Vec4 v);
  Vec3 Mat4TransformVec3(Mat4 m, Vec3 v);
  float Determinante(Mat2 m);
  float Obten_Angulo(Pnt2 vec, Pnt2 vec1);
  float Obten_Angulo(Pnt3 vec, Pnt3 vec1);

  float Dot_Product(Vec2 v, Vec2 v1);

  float Dot_Product(Vec3 v, Vec3 v1);

  Pnt3 Cross_Product(Pnt3 v, Pnt3 v1);

  float Calcula_Angulo(Vec2 v, Vec2 v1);

  Vec2 *Inicia_Circulo_Basico(int vertices, float dim, float rotacion, Vec2 desp);

  bool Colision_Circular(Vec2 centro, int dim, Vec2 centro1, int dim1);

  bool Colision_Esferas(Pnt3 centro_1, float dim_1, Pnt3 centro_2, float dim_2);

  bool Colision(float x1, float y1, float x2, float y2, float ox1, float oy1, float ox2, float oy2);
  bool Colision(Pnt2 init, float w, float h, Pnt2 c, float r);

  bool Colision(Pnt2 init, Pnt2 fin, Pnt2 init_o, Pnt2 fin_o);

  Pnt3 HallaRecta(Pnt2 a, Pnt2 b);

  Pnt2 Interseccion_Rectas(Pnt3 recta_a, Pnt3 recta_b);

  bool Colision_3_Cuadrados(Vec2 a_init, Vec2 a_fin, Vec2 b_init, Vec2 b_fin, Vec2 c_init, Vec2 c_fin);

  // Dados tres puntos colineales: A, B, C.
  // la función verifica si el punto B se encuentra en el segmento de línea 'AC'
  bool Segmento(Pnt2 A, Pnt2 B, Pnt2 C);

  // Para hallar la orientacion de A, B, C
  int Orientacion(Pnt2 A, Pnt2 B, Pnt2 C);

  // Devuelve true si 'AB' y 'CD' Intersecan
  bool Interseccion(Pnt2 A, Pnt2 B, Pnt2 C, Pnt2 D);

  Vec2 Vec_Unitario(Vec2 v);

  Mat4 Mat4View(Vec3 camara, Vec3 mira, Vec3 up = {0, 1, 0});

  void Orbitar_Punto(Pnt3 centro_orbita, Pnt3 p_orbita, Pnt3 &punto);

  MV::Pnt3 Centro_Triangulo(MV::Pnt3 *triangulos);

  Pnt3 Rotate_Point_3D(Pnt3 rot, Pnt3 point);

}

//////////////////////
// Guardas, NO TOCAR
#endif /* mv_math_h */
// Guardas, NO TOCAR
//////////////////////
