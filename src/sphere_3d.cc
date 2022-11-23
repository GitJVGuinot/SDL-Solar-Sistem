#include <sphere_3d.h>

// Obtiene los puntos de la entity
void Sphere::obtenerSphere()
{
  vertex_ = (2 * res_) * (res_ + 1);

  points_ = (MV::Pnt3*) calloc(vertex_, sizeof(MV::Pnt3));
  centers_ = (MV::Pnt3*) calloc(vertex_, sizeof(MV::Pnt3));

  draw_sdl_ = (Render_Vert*) calloc(vertex_, sizeof(Render_Vert));

  faces_ = (Faces*) calloc(vertex_, sizeof(Faces));

  order_ = (int*) calloc(vertex_, sizeof(int));

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
      faces_[i].n_points = 4;

      faces_[i].points[0] = i;
      faces_[i].points[1] = i + 1;
      faces_[i].points[2] = ((filas + 1) * res_ * 2) + columnas + 1;
      faces_[i].points[3] = ((filas + 1) * res_ * 2) + columnas;

      if (columnas + 1 == res_ * 2)
      {
        faces_[i].points[1] = (filas * res_ * 2);
        faces_[i].points[2] = ((filas + 1) * res_ * 2);
      }
      if (filas + 1 > res_)
      {
        faces_[i].points[2] = ((filas)*res_ * 2) + columnas + 1;
        faces_[i].points[3] = ((filas)*res_ * 2) + columnas;
      }
      if (filas + 1 > res_ && columnas + 1 == res_ * 2)
      {
        faces_[i].points[2] = ((filas)*res_ * 2) + columnas;
      }

      i++;
    }
  }

  for (int i = 0; i < vertex_; i++)
  {
    centers_[i] = Vec_Resta(points_[faces_[i].points[0]], points_[faces_[i].points[2]]);
    centers_[i] = Vec_Escalado(centers_[i], 0.5f);
    centers_[i] = Vec_Sum(centers_[i], points_[faces_[i].points[2]]);
  }
}

int Sphere::init(SDL_Color color, bool fill, int res, MV::Pnt3 escala, MV::Pnt3 mov, MV::Pnt3 rot, MV::Pnt3 orbita, MV::Pnt3 centro_orbita)
{
  if (res > 50)
    return 1;

  color_ = color;
  fill_ = fill;
  res_ = res;
  orbit_ = orbita;
  orbit_center_ = centro_orbita;
  orbit_vel_ = 0.0f;
  rotate_ = {0, 0, 0};
  scale_ = {1, 1, 1};
  dim_ = 1;
  mov_ = {0, 0, 0};

  // Sphere basica
  obtenerSphere();

  if ((escala.x + escala.y + escala.z) != 3)
    scale(escala);

  if ((mov.x + mov.y + mov.z) != 0)
    translation(mov);

  if ((rot.x + rot.y + rot.z) != 0)
    rotation(rot);

  return 0;
}
