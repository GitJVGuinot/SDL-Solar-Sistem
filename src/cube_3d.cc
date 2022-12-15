/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

#include <cube_3d.h>

void Cube::obtainCube()
{
  vertex_ = 8;

  points_ = (Vec3 *)calloc(vertex_, sizeof(Vec3));

  draw_sdl_ = (Render_Vert *)calloc(vertex_, sizeof(Render_Vert));

  nFaces_ = 6;
  faces_ = (Faces *)calloc(nFaces_, sizeof(Faces));

  for (int i = 0; i < nFaces_; ++i)
  {
    faces_[i].n_points = 4;
    faces_[i].points = (int *)calloc(faces_[i].n_points, sizeof(int));
  }

  centers_ = (Vec3 *)calloc(nFaces_, sizeof(Vec3));

  order_ = (int *)calloc(nFaces_, sizeof(int));

  points_[0] = {0.5f, 0.5f, 0.5f};
  points_[1] = {-0.5f, 0.5f, 0.5f};
  points_[2] = {-0.5f, 0.5f, -0.5f};
  points_[3] = {0.5f, 0.5f, -0.5f};
  points_[4] = {0.5f, -0.5f, 0.5f};
  points_[5] = {-0.5f, -0.5f, 0.5f};
  points_[6] = {-0.5f, -0.5f, -0.5f};
  points_[7] = {0.5f, -0.5f, -0.5f};

  faces_[0].points[0] = 0;
  faces_[0].points[1] = 1;
  faces_[0].points[2] = 2;
  faces_[0].points[3] = 3;

  faces_[1].points[0] = 1;
  faces_[1].points[1] = 0;
  faces_[1].points[2] = 4;
  faces_[1].points[3] = 5;

  faces_[2].points[0] = 2;
  faces_[2].points[1] = 6;
  faces_[2].points[2] = 5;
  faces_[2].points[3] = 1;

  faces_[3].points[0] = 3;
  faces_[3].points[1] = 2;
  faces_[3].points[2] = 6;
  faces_[3].points[3] = 7;

  faces_[4].points[0] = 4;
  faces_[4].points[1] = 0;
  faces_[4].points[2] = 3;
  faces_[4].points[3] = 7;

  faces_[5].points[0] = 5;
  faces_[5].points[1] = 4;
  faces_[5].points[2] = 7;
  faces_[5].points[3] = 6;

  centers_[0] = {0.0f, 1.0f, 0.0f};
  centers_[1] = {0.0f, 0.0f, 1.0f};
  centers_[2] = {-1.0f, 0.0f, 0.0f};
  centers_[3] = {0.0f, 0.0f, -1.0f};
  centers_[4] = {1.0f, 0.0f, 0.0f};
  centers_[5] = {0.0f, -1.0f, 0.0f};
}

int Cube::init(SDL_Color color, bool fill, Vec3 p_scale, Vec3 mov, Vec3 rot, Vec3 orbit, Vec3 orbit_center)
{
  res_ = 0;
  fillColor_ = color;
  linesColor_ = color;
  fill_ = fill;
  lines_ = false;
  orbit_ = orbit;
  orbit_center_ = orbit_center;
  orbit_vel_ = 0.0f;
  rotate_ = {0, 0, 0};
  scale_ = {1, 1, 1};
  dim_ = 1;
  mov_ = {0, 0, 0};

  // Basic sphere
  obtainCube();

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

  std::cout << "Bytes size: " << bytesSize << std::endl;
  std::cout << "Real size " << sizeof(this) << std::endl;

  return 0;
}
