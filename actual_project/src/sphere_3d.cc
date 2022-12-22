/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

#include <sphere_3d.h>

void Sphere::obtainSphere()
{
  vertex_ = (2 * res_) * (res_ + 1);

  points_ = (Vec3 *)calloc(vertex_, sizeof(Vec3));

  draw_sdl_ = (Render_Vert *)calloc(vertex_, sizeof(Render_Vert));

  nFaces_ = vertex_;
  faces_ = (Faces *)calloc(nFaces_, sizeof(Faces));

  for (int i = 0; i < nFaces_; ++i)
  {
    faces_[i].n_points = 4;
    faces_[i].points = (int *)calloc(faces_[i].n_points, sizeof(int));
  }

  centers_ = (Vec3 *)calloc(nFaces_, sizeof(Vec3));

  order_ = (int *)calloc(nFaces_, sizeof(int));

  float increment = (PI / res_);

  int i = 0;
  for (int row = 0; row <= res_; row++)
  {
    for (int column = 0; column < (2 * res_); column++)
    {
      (points_ + i)->z = ((float)sin(row * increment)) * ((float)cos(column * increment));
      (points_ + i)->x = ((float)sin(row * increment)) * ((float)sin(column * increment));
      (points_ + i)->y = ((float)cos(row * increment));
      i++;
    }
  }

  i = 0;
  for (int rows = 0; rows <= res_; rows++)
  {
    for (int columns = 0; columns < (res_ * 2); columns++)
    {
      faces_[i].n_points = 4;

      faces_[i].points[0] = i;
      faces_[i].points[1] = i + 1;
      faces_[i].points[2] = ((rows + 1) * res_ * 2) + columns + 1;
      faces_[i].points[3] = ((rows + 1) * res_ * 2) + columns;

      if (columns + 1 == res_ * 2)
      {
        faces_[i].points[1] = (rows * res_ * 2);
        faces_[i].points[2] = ((rows + 1) * res_ * 2);
      }
      if (rows + 1 > res_)
      {
        faces_[i].points[2] = ((rows)*res_ * 2) + columns + 1;
        faces_[i].points[3] = ((rows)*res_ * 2) + columns;
      }
      if (rows + 1 > res_ && columns + 1 == res_ * 2)
      {
        faces_[i].points[2] = ((rows)*res_ * 2) + columns;
      }

      i++;
    }
  }

  for (int i = 0; i < nFaces_; i++)
  {
    centers_[i] = points_[faces_[i].points[0]] - points_[faces_[i].points[2]];
    centers_[i] *= 0.5f;
    centers_[i] += points_[faces_[i].points[2]];
  }
}

int Sphere::init(SDL_Color color, bool fill, int res, Vec3 p_scale, Vec3 mov, Vec3 rot, Vec3 orbit, Vec3 orbit_center)
{
  if (res > 50)
    return 1;

  fillColor_ = color;
  linesColor_ = color;
  fill_ = fill;
  lines_ = false;
  res_ = res;
  orbit_ = orbit;
  orbit_center_ = orbit_center;
  orbit_vel_ = 0.0f;
  rotate_ = {0, 0, 0};
  scale_ = {1, 1, 1};
  dim_ = 1;
  mov_ = {0, 0, 0};

  // Basic sphere
  obtainSphere();

  standarize();

  if ((p_scale.x + p_scale.y + p_scale.z) != 3)
    scale(p_scale);

  if ((mov.x + mov.y + mov.z) != 0)
    translation(mov);

  if ((rot.x + rot.y + rot.z) != 0)
    rotation(rot);

  bytesSize = 0;
  bytesSize += sizeof(Vec3);
  bytesSize += sizeof(Vec3);
  bytesSize += sizeof(int);
  bytesSize += sizeof(int);
  bytesSize += sizeof(Vec3) * vertex_;
  bytesSize += sizeof(Vec3) * vertex_;
  bytesSize += sizeof(Render_Vert) * vertex_;
  for (int i = 0; i < nFaces_; i++)
  {
    bytesSize += sizeof(int) * faces_[i].n_points;
  }
  bytesSize += sizeof(int);
  bytesSize += sizeof(int) * vertex_;
  bytesSize += sizeof(int);
  bytesSize += sizeof(float);
  bytesSize += sizeof(Vec3);
  bytesSize += sizeof(Vec3);
  bytesSize += sizeof(Vec3);
  bytesSize += sizeof(SDL_Color);
  bytesSize += sizeof(SDL_Color);
  bytesSize += sizeof(bool);
  bytesSize += sizeof(bool);
  bytesSize += sizeof(float);

  return 0;
}

void Sphere::print () {}
