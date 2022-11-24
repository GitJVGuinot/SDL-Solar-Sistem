#include <sphere_3d.h>

// Obtiene los puntos de la entity
void Sphere::obtenerSphere()
{
  vertex_ = (2 * res_) * (res_ + 1);

  points_ = (MV::Pnt3*) calloc(vertex_, sizeof(MV::Pnt3));

  draw_sdl_ = (Render_Vert*) calloc(vertex_, sizeof(Render_Vert));

  nFaces_ = vertex_;
  faces_ = (Faces*) calloc(nFaces_, sizeof(Faces));

  centers_ = (MV::Pnt3*) calloc(nFaces_, sizeof(MV::Pnt3));

  order_ = (int*) calloc(nFaces_, sizeof(int));

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

  for (int i = 0; i < nFaces_; i++)
  {
    centers_[i] = Vec_Resta(points_[faces_[i].points[0]], points_[faces_[i].points[2]]);
    centers_[i] = Vec_Escalado(centers_[i], 0.5f);
    centers_[i] = Vec_Sum(centers_[i], points_[faces_[i].points[2]]);
  }
}

int Sphere::init(SDL_Color color, bool fill, int res, MV::Pnt3 p_scale, MV::Pnt3 mov, MV::Pnt3 rot, MV::Pnt3 orbit, MV::Pnt3 orbit_center)
{
  if (res > 50)
    return 1;

  color_ = color;
  fill_ = fill;
  res_ = res;
  orbit_ = orbit;
  orbit_center_ = orbit_center;
  orbit_vel_ = 0.0f;
  rotate_ = {0, 0, 0};
  scale_ = {1, 1, 1};
  dim_ = 1;
  mov_ = {0, 0, 0};

  // Sphere basica
  obtenerSphere();

  if ((p_scale.x + p_scale.y + p_scale.z) != 3)
    scale(p_scale);

  if ((mov.x + mov.y + mov.z) != 0)
    translation(mov);

  if ((rot.x + rot.y + rot.z) != 0)
    rotation(rot);

  return 0;
}
