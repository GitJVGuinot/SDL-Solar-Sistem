#include <entity_3d.h>

// Inicializa la entity
Entity::Entity()
{
  scale_ = {0,0,0};
  rotate_ = {0,0,0};

  res_ = 0;
  points_ = nullptr;
  centers_ = nullptr;

  draw_sdl_ = nullptr;

  faces_ = nullptr;

  order_ = nullptr;

  dim_ = 0;
  vertex_ = 0;
  mov_ = {0,0,0};
  orbit_ = {0,0,0};
  orbit_center_ = {0,0,0};
  color_ = {0,0,0,0};
  fill_ = false;
  orbit_vel_ = 0;
};

void Entity::operator=(const Entity& other){
  scale_ = other.scale_;
  rotate_ = other.rotate_;
  dim_ = other.dim_;
  mov_ = other.mov_;

  res_ = other.res_;

  vertex_ = other.vertex_;
  nFaces_ = other.nFaces_;
  orbit_ = other.orbit_;
  orbit_center_ = other.orbit_center_;
  color_ = other.color_;
  fill_ = other.fill_;
  orbit_vel_ = other.orbit_vel_;

  points_ = (MV::Pnt3*) calloc(vertex_, sizeof(MV::Pnt3));

  draw_sdl_ = (Render_Vert*) calloc(vertex_, sizeof(Render_Vert));

  centers_ = (MV::Pnt3*) calloc(nFaces_, sizeof(MV::Pnt3));

  faces_ = (Faces*) calloc(nFaces_, sizeof(Faces));

  order_ = (int*) calloc(nFaces_, sizeof(int));

  for(int i = 0; i < vertex_; i++){
    points_[i] = other.points_[i];
    draw_sdl_[i] = other.draw_sdl_[i];
  }
  for(int i = 0; i < nFaces_; i++){
    centers_[i] = other.centers_[i];
    faces_[i] = other.faces_[i];
    order_[i] = other.order_[i];
  }

}

MV::Pnt3 Entity::point(int i)
{
  return *(points_ + i);
}

MV::Pnt3 Entity::getScale()
{
  return scale_;
}


void Entity::rotation(MV::Pnt3 p_rot)
{
  rotate_ = MV::Vec_Sum(rotate_, p_rot);
  if (rotate_.x >= 360)
    rotate_.x -= 360;
  if (rotate_.y >= 360)
    rotate_.y -= 360;
  if (rotate_.z >= 360)
    rotate_.z -= 360;

  MV::Mat4 rot_x;
  if (p_rot.x != 0)
    rot_x = MV::Mat4RotateX((p_rot.x * PI) / 180);

  MV::Mat4 rot_y;
  if (p_rot.y != 0)
    rot_y = MV::Mat4RotateY((p_rot.y * PI) / 180);

  MV::Mat4 rot_z;
  if (p_rot.z != 0)
    rot_z = MV::Mat4RotateZ((p_rot.z * PI) / 180);

  MV::Mat4 model = MV::Mat4Identity();
  if (p_rot.x != 0)
    model = MV::Mat4Multiply(model, rot_x);
  if (p_rot.y != 0)
    model = MV::Mat4Multiply(model, rot_y);
  if (p_rot.z != 0)
    model = MV::Mat4Multiply(model, rot_z);

  MV::Pnt3 mov = mov_;
  translation({-mov_.x, -mov_.y, -mov_.z});
  for (int i = 0; i < vertex_; i++)
  {
    *(points_ + i) = MV::Mat4TransformVec3(model, *(points_ + i));
  }
  for(int i=0; i<nFaces_; i++){
    *(centers_ + i) = MV::Mat4TransformVec3(model, *(centers_ + i));
  }
  translation(mov);
}

void Entity::orbitar()
{
  if ((orbit_center_.x + orbit_center_.y + orbit_center_.z) != 0)
  {
    MV::Pnt3 p_orbit_ = MV::Vec_Escalado(orbit_, orbit_vel_);

    MV::Mat4 rot_x;
    MV::Mat4 rot_y;
    MV::Mat4 rot_z;

    if (p_orbit_.x != 0)
      rot_x = MV::Mat4RotateX((p_orbit_.x * PI) / 180);
    if (p_orbit_.y != 0)
      rot_y = MV::Mat4RotateY((p_orbit_.y * PI) / 180);
    if (p_orbit_.z != 0)
      rot_z = MV::Mat4RotateZ((p_orbit_.z * PI) / 180);

    MV::Mat4 model = MV::Mat4Identity();
    if (p_orbit_.x != 0)
      model = MV::Mat4Multiply(model, rot_x);
    if (p_orbit_.y != 0)
      model = MV::Mat4Multiply(model, rot_y);
    if (p_orbit_.z != 0)
      model = MV::Mat4Multiply(model, rot_z);

    translation(MV::Vec3{-orbit_center_.x, -orbit_center_.y, -orbit_center_.z});
    mov_ = MV::Mat4TransformVec3(model, mov_);
    for (int i = 0; i < vertex_; i++)
    {
      *(points_ + i) = MV::Mat4TransformVec3(model, *(points_ + i));
    }
    for(int i=0; i<nFaces_;i++){
      *(centers_ + i) = MV::Mat4TransformVec3(model, *(centers_ + i));
    }
    translation(orbit_center_);
  }
}

void Entity::translation(MV::Pnt3 p_mov_)
{
  mov_ = MV::Vec_Sum(mov_, p_mov_);
  for (int i = 0; i < vertex_; i++)
  {
    *(points_ + i) = MV::Vec_Sum(*(points_ + i), p_mov_);
  }
  for(int i=0; i<nFaces_; i++){
    *(centers_ + i) = MV::Vec_Sum(*(centers_ + i), p_mov_);
  }
}

void Entity::scale(MV::Pnt3 p_scale_)
{
  scale_ = MV::Vec_Escalado(scale_, p_scale_);
  dim_ = p_scale_.x * dim_;

  MV::Mat4 m_scale_ = MV::Mat4Scale(p_scale_);

  MV::Mat4 model = MV::Mat4Identity();
  model = MV::Mat4Multiply(model, m_scale_);

  MV::Pnt3 mov = mov_;
  translation({-mov_.x, -mov_.y, -mov_.z});
  for (int i = 0; i < vertex_; i++)
  {
    *(points_ + i) = MV::Mat4TransformVec3(model, *(points_ + i));
  }
  for(int i=0; i<nFaces_; i++){
    *(centers_ + i) = MV::Mat4TransformVec3(model, *(centers_ + i));
  }
  translation(mov);
}

void Entity::inputs(Keys *keys)
{
  if (EVENT_DOWN(DOWN, keys))
    rotation({1.0f, 0.0f, 0.0f});
  if (EVENT_DOWN(UP, keys))
    rotation({-1.0f, 0.0f, 0.0f});
  if (EVENT_DOWN(RIGHT, keys))
    rotation({0.0f, 1.0f, 0.0f});
  if (EVENT_DOWN(LEFT, keys))
    rotation({0.0f, -1.0f, 0.0f});
  if (EVENT_DOWN(K_z, keys))
    rotation({0.0f, 0.0f, -1.0f});
  if (EVENT_DOWN(K_x, keys))
    rotation({0.0f, 0.0f, 1.0f});

  if (EVENT_DOWN(K_a, keys))
    translation({-0.1f, 0.0f, 0.0f});
  if (EVENT_DOWN(K_d, keys))
    translation({0.1f, 0.0f, 0.0f});
  if (EVENT_DOWN(K_w, keys))
    translation({0.0f, -0.1f, 0.0f});
  if (EVENT_DOWN(K_s, keys))
    translation({0.0f, 0.1f, 0.0f});
  if (EVENT_DOWN(K_q, keys))
    translation({0.0f, 0.0f, 0.1f});
  if (EVENT_DOWN(K_e, keys))
    translation({0.0f, 0.0f, -0.1f});

  if (EVENT_DOWN(SHIFT, keys))
    scale({0.9f, 0.9f, 0.9f});
  if (EVENT_DOWN(SPACE, keys))
    scale({1.1f, 1.1f, 1.1f});
}

void Entity::draw(Keys *keys, SDL_Renderer *render, Render drawRender, MV::Pnt3 light, int drawCallback(SDL_Renderer *, SDL_Vertex *, const int))
{

  // Transformacion de puntos 2D
  MV::Mat3 model = MV::Mat3Identity();
  MV::Mat3 scala = MV::Mat3Scale(drawRender.getRenderScale());
  MV::Mat3 mov;

  if ((orbit_center_.x + orbit_center_.y + orbit_center_.z) == 0)
  {
    mov = MV::Mat3Translate({mov_.x, mov_.y});
  }
  else
  {
    mov = MV::Mat3Translate(MV::Vec3_Tr_Vec2(orbit_center_));
  }

  model = MV::Mat3Multiply(mov, scala);

  for (int i = 0; i < vertex_; i++)
  {
    draw_sdl_[i] = drawRender.renderPoint(points_[i], mov_, light, color_, model);
  }

  // This is to draw with texture | light
  if (fill_)
  {
    // Ordenado de puntos
    for (int i = 0; i < nFaces_; i++)
      order_[i] = i;

    for (int i = 0; i < nFaces_; i++)
    {
      for (int j = 1; j < nFaces_; j++)
      {
        if (MV::Vec_Magn(MV::Vec_Resta(centers_[order_[i]], drawRender.camera_)) >= MV::Vec_Magn(MV::Vec_Resta(centers_[order_[j]], drawRender.camera_)))
        {
          int aux = order_[i];
          order_[i] = order_[j];
          order_[j] = aux;
        }
      }
    }

    for (int i = 0; i < nFaces_ - 1; i++)
    {
      int aux = order_[i];
      order_[i] = order_[i + 1];
      order_[i + 1] = aux;
    }

    // Draw Triangles
    for (int i = 0; i < nFaces_; i++)
    {

      static SDL_Vertex square[4];

      for (int j = 0; j < 4; j++)
        square[j] = draw_sdl_[faces_[order_[i]].points[j]].point;

      bool draw = true;
      for (int j = 0; j < 4; j++)
      {
        draw = (draw && draw_sdl_[faces_[order_[i]].points[j]].active);
        if(!draw) break;
      }

      if (draw)
      {
        if (drawCallback != nullptr)
        {
          drawCallback(render, square, 4);
        }
        else
        {
          static SDL_Vertex triangle[3];
          triangle[0] = draw_sdl_[faces_[order_[i]].points[0]].point;
          triangle[1] = draw_sdl_[faces_[order_[i]].points[1]].point;
          triangle[2] = draw_sdl_[faces_[order_[i]].points[2]].point;

          static SDL_Vertex triangle1[3];
          triangle1[0] = draw_sdl_[faces_[order_[i]].points[3]].point;
          triangle1[1] = draw_sdl_[faces_[order_[i]].points[2]].point;
          triangle1[2] = draw_sdl_[faces_[order_[i]].points[0]].point;

          SDL_RenderGeometry(render, NULL, triangle, 3, NULL, 0);
          SDL_RenderGeometry(render, NULL, triangle1, 3, NULL, 0);
        }
      }
    }
  }
  else
  {
    // That is for points_
    for (int i = 0; i < vertex_; i++)
    {
      SDL_SetRenderDrawColor(render, RGBA(draw_sdl_[i].point.color));
      SDL_RenderDrawPoint(render, draw_sdl_[i].point.position.x, draw_sdl_[i].point.position.y);
    }
  }
}

Entity::~Entity() {
  DESTROY(points_);

  DESTROY(draw_sdl_);

  DESTROY(faces_);

  DESTROY(centers_);

  DESTROY(order_);
}
