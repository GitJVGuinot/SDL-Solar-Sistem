#include <cube_3d.h>

void Cube::obtenerCube()
{
  vertex_ = 8;

  points_ = (MV::Pnt3*) calloc(vertex_, sizeof(MV::Pnt3));
  centers_ = (MV::Pnt3*) calloc(vertex_, sizeof(MV::Pnt3));

  draw_sdl_ = (Render_Vert*) calloc(vertex_, sizeof(Render_Vert));

  nFaces_ = 6;
  faces_ = (Faces*) calloc(nFaces_, sizeof(Faces));

  order_ = (int*) calloc(nFaces_, sizeof(int));

  points_[0]={0.5f,0.5f,0.5f};
  points_[1]={-0.5f,0.5f,0.5f};
  points_[2]={-0.5f,0.5f,-0.5f};
  points_[3]={0.5f,0.5f,-0.5f};
  points_[4]={0.5f,-0.5f,0.5f};
  points_[5]={-0.5f,-0.5f,0.5f};
  points_[6]={-0.5f,-0.5f,-0.5f};
  points_[7]={0.5f,-0.5f,-0.5f};

  faces_[0].points[0]=0;
  faces_[0].points[1]=1;
  faces_[0].points[2]=2;
  faces_[0].points[3]=3;

  faces_[1].points[0]=1;
  faces_[1].points[1]=0;
  faces_[1].points[2]=4;
  faces_[1].points[3]=5;

  faces_[2].points[0]=2;
  faces_[2].points[1]=6;
  faces_[2].points[2]=5;
  faces_[2].points[3]=1;

  faces_[3].points[0]=3;
  faces_[3].points[1]=2;
  faces_[3].points[2]=6;
  faces_[3].points[3]=7;

  faces_[4].points[0]=4;
  faces_[4].points[1]=0;
  faces_[4].points[2]=3;
  faces_[4].points[3]=7;

  faces_[5].points[0]=5;
  faces_[5].points[1]=4;
  faces_[5].points[2]=7;
  faces_[5].points[3]=6;

}

int Cube::init(SDL_Color color, bool fill, MV::Pnt3 p_scale, MV::Pnt3 mov, MV::Pnt3 rot, MV::Pnt3 orbit, MV::Pnt3 orbit_center)
{
  res_ = 0;
  color_ = color;
  fill_ = fill;
  orbit_ = orbit;
  orbit_center_ = orbit_center;
  orbit_vel_ = 0.0f;
  rotate_ = {0, 0, 0};
  scale_ = {1, 1, 1};
  dim_ = 1;
  mov_ = {0, 0, 0};

  // Sphere basica
  obtenerCube();

  if ((p_scale.x + p_scale.y + p_scale.z) != 3)
    scale(p_scale);

  if ((mov.x + mov.y + mov.z) != 0)
    translation(mov);

  if ((rot.x + rot.y + rot.z) != 0)
    rotation(rot);

  return 0;
}
