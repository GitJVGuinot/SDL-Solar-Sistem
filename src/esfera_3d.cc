#include <esfera_3d.h>

// Obtiene los puntos de la entity
void Esfera::obtenerEsfera()
{
  vertices_ = (2 * res_) * (res_ + 1);

  points_ = (MV::Pnt3*) calloc(vertices_, sizeof(MV::Pnt3));
  centros_ = (MV::Pnt3*) calloc(vertices_, sizeof(MV::Pnt3));

  draw_sdl_ = (Render_Vert*) calloc(vertices_, sizeof(Render_Vert));

  caras_ = (Caras*) calloc(vertices_, sizeof(Caras));

  order_ = (int*) calloc(vertices_, sizeof(int));

  float incremento = (PI / res_);

  int i = 0;
  for (int fila = 0; fila <= res_; fila++)
  {
    for (int columna = 0; columna < (2 * res_); columna++)
    {
      (points_ + i)->z = ((float)sin(fila * incremento)) * ((float)cos(columna * incremento));
      (points_ + i)->x = ((float)sin(fila * incremento)) * ((float)sin(columna * incremento));
      (points_ + i)->y = ((float)cos(fila * incremento));
      i++;
    }
  }

  i = 0;
  for (int filas = 0; filas <= res_; filas++)
  {
    for (int columnas = 0; columnas < (res_ * 2); columnas++)
    {
      caras_[i].n_points = 4;

      caras_[i].points[0] = i;
      caras_[i].points[1] = i + 1;
      caras_[i].points[2] = ((filas + 1) * res_ * 2) + columnas + 1;
      caras_[i].points[3] = ((filas + 1) * res_ * 2) + columnas;

      if (columnas + 1 == res_ * 2)
      {
        caras_[i].points[1] = (filas * res_ * 2);
        caras_[i].points[2] = ((filas + 1) * res_ * 2);
      }
      if (filas + 1 > res_)
      {
        caras_[i].points[2] = ((filas)*res_ * 2) + columnas + 1;
        caras_[i].points[3] = ((filas)*res_ * 2) + columnas;
      }
      if (filas + 1 > res_ && columnas + 1 == res_ * 2)
      {
        caras_[i].points[2] = ((filas)*res_ * 2) + columnas;
      }

      i++;
    }
  }

  for (int i = 0; i < vertices_; i++)
  {
    centros_[i] = Vec_Resta(points_[caras_[i].points[0]], points_[caras_[i].points[2]]);
    centros_[i] = Vec_Escalado(centros_[i], 0.5f);
    centros_[i] = Vec_Sum(centros_[i], points_[caras_[i].points[2]]);
  }
}

int Esfera::init(SDL_Color color, bool fill, int res, MV::Pnt3 escala, MV::Pnt3 desp, MV::Pnt3 rot, MV::Pnt3 orbita, MV::Pnt3 centro_orbita)
{
  if (res > 50)
    return 1;

  color_ = color;
  fill_ = fill;
  res_ = res;
  orbita_ = orbita;
  centro_orbita_ = centro_orbita;
  orbit_vel_ = 0.0f;
  rotado_ = {0, 0, 0};
  escala_ = {1, 1, 1};
  dim_ = 1;
  desp_ = {0, 0, 0};

  // Esfera basica
  obtenerEsfera();

  if ((escala.x + escala.y + escala.z) != 3)
    scale(escala);

  if ((desp.x + desp.y + desp.z) != 0)
    translation(desp);

  if ((rot.x + rot.y + rot.z) != 0)
    rotation(rot);

  return 0;
}
