/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

#include <entity_3d.h>
#include <vector>
#include <algorithm>

typedef std::ratio<1l, 1000l> milli;
typedef std::chrono::duration<long long, milli> Milliseconds;

// Init entity
Entity::Entity()
{
  scale_ = {0, 0, 0};
  rotate_ = {0, 0, 0};

  res_ = 0;
  points_ = nullptr;
  centers_ = nullptr;

  draw_sdl_ = nullptr;
  renderLight_ = true;

  faces_ = nullptr;

  order_ = nullptr;

  dim_ = 0;
  vertex_ = 0;
  nFaces_ = 0;
  mov_ = {0, 0, 0};
  orbit_ = {0, 0, 0};
  orbit_center_ = {0, 0, 0};
  fillColor_ = {0, 0, 0, 0};
  linesColor_ = {0, 0, 0, 0};
  fill_ = false;
  lines_ = false;
  orbit_vel_ = 0;
  destroying_ = false;
  destroyed_ = false;

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
  bytesSize += sizeof(bool);
  bytesSize += sizeof(bool);
};

void Entity::operator=(const Entity &other)
{
  dim_ = other.dim_;
  mov_ = other.mov_;
  orbit_ = other.orbit_;
  orbit_center_ = other.orbit_center_;
  renderLight_ = other.renderLight_;
  fillColor_ = other.fillColor_;
  linesColor_ = other.linesColor_;
  fill_ = other.fill_; 
  lines_ = other.lines_;
  orbit_vel_ = other.orbit_vel_;
  bytesSize = bytesSize;
  destroying_ = other.destroying_;
  destroyed_ = other.destroyed_;
  nFaces_ = other.nFaces_;
  scale_ = other.scale_; 
  rotate_ = other.rotate_;

  res_ = other.res_;
  vertex_ = other.vertex_;

  points_ = (Vec3 *)calloc(vertex_, sizeof(Vec3));

  draw_sdl_ = (Render_Vert *)calloc(vertex_, sizeof(Render_Vert));

  centers_ = (Vec3 *)calloc(nFaces_, sizeof(Vec3));

  faces_ = (Faces *)calloc(nFaces_, sizeof(Faces));

  order_ = (int *)calloc(nFaces_, sizeof(int));

  for (int i = 0; i < vertex_; i++)
  {
    points_[i] = other.points_[i];
    draw_sdl_[i] = other.draw_sdl_[i];
  }
  for (int i = 0; i < nFaces_; i++)
  {
    centers_[i] = other.centers_[i];
    faces_[i] = other.faces_[i];
    order_[i] = other.order_[i];
  }
}

void Entity::proportion()
{
  Vec3 extrem = MathUtils::TakeMax(points_, vertex_);

  float max = extrem.x;
  max = std::max(max, extrem.y);
  max = std::max(max, extrem.z);

  scale_.x = scale_.y = scale_.z = dim_ = max;

  if (max != 1.0f)
  {
    scale(1 / max);
  }

  scale(0.5f);
}

void Entity::centered()
{
  Vec3 min = MathUtils::TakeMin(points_, vertex_);
  Vec3 max = MathUtils::TakeMax(points_, vertex_);
  translation(min * -1);
  mov_ -= min * -1;
  Vec3 newTranslation = (min - max) / 2;
  translation(newTranslation);
  mov_ -= newTranslation;
}

void Entity::standarize()
{
  centered();
  proportion();
}

Vec3 Entity::point(int i)
{
  return *(points_ + i);
}

Vec3 Entity::getScale()
{
  return scale_;
}

int Entity::getFaces()
{
  return nFaces_;
}

int Entity::getSize()
{
  return bytesSize;
}

void Entity::rotation(Vec3 p_rot)
{
  p_rot *= 10;
  rotate_ += p_rot;
  if (rotate_.x >= 360)
    rotate_.x -= 360;
  if (rotate_.y >= 360)
    rotate_.y -= 360;
  if (rotate_.z >= 360)
    rotate_.z -= 360;

  Mat4 rot_x;
  if (p_rot.x != 0)
    rot_x = Mat4::RotateX((p_rot.x * PI) / 180);

  Mat4 rot_y;
  if (p_rot.y != 0)
    rot_y = Mat4::RotateY((p_rot.y * PI) / 180);

  Mat4 rot_z;
  if (p_rot.z != 0)
    rot_z = Mat4::RotateZ((p_rot.z * PI) / 180);

  Mat4 model = Mat4::Identity();
  if (p_rot.x != 0)
    model *= rot_x;
  if (p_rot.y != 0)
    model *= rot_y;
  if (p_rot.z != 0)
    model *= rot_z;

  Vec3 mov = mov_;
  translation({-mov_.x, -mov_.y, -mov_.z});
  for (int i = 0; i < vertex_; i++)
  {
    *(points_ + i) = MathUtils::Mat4TransformVec3(model, *(points_ + i));
  }
  for (int i = 0; i < nFaces_; i++)
  {
    *(centers_ + i) = MathUtils::Mat4TransformVec3(model, *(centers_ + i));
  }
  translation(mov);
}

void Entity::orbit()
{
  if ((orbit_center_.x + orbit_center_.y + orbit_center_.z) != 0)
  {
    Vec3 p_orbit_ = orbit_ * orbit_vel_;

    Mat4 rot_x;
    Mat4 rot_y;
    Mat4 rot_z;

    if (p_orbit_.x != 0)
      rot_x = Mat4::RotateX((p_orbit_.x * PI) / 180);
    if (p_orbit_.y != 0)
      rot_y = Mat4::RotateY((p_orbit_.y * PI) / 180);
    if (p_orbit_.z != 0)
      rot_z = Mat4::RotateZ((p_orbit_.z * PI) / 180);

    Mat4 model = Mat4::Identity();
    if (p_orbit_.x != 0)
      model *= rot_x;
    if (p_orbit_.y != 0)
      model *= rot_y;
    if (p_orbit_.z != 0)
      model *= rot_z;

    translation(Vec3{-orbit_center_.x, -orbit_center_.y, -orbit_center_.z});
    mov_ = MathUtils::Mat4TransformVec3(model, mov_);
    for (int i = 0; i < vertex_; i++)
    {
      *(points_ + i) = MathUtils::Mat4TransformVec3(model, *(points_ + i));
    }
    for (int i = 0; i < nFaces_; i++)
    {
      *(centers_ + i) = MathUtils::Mat4TransformVec3(model, *(centers_ + i));
    }
    translation(orbit_center_);
  }
}

void Entity::translation(Vec3 p_mov_)
{
  mov_ += p_mov_;

  for (int i = 0; i < vertex_; i++)
  {
    points_[i] += p_mov_;
  }

  for (int i = 0; i < nFaces_; i++)
  {
    centers_[i] += p_mov_;
  }
}

void Entity::scale(Vec3 p_scale_)
{
  scale_ = scale_ * p_scale_;
  dim_ = p_scale_.x * dim_;

  Mat4 m_scale_ = Mat4::Scale(p_scale_);

  Mat4 model = Mat4::Identity();
  model = model * m_scale_;

  Vec3 mov = mov_;
  translation({-mov_.x, -mov_.y, -mov_.z});
  for (int i = 0; i < vertex_; i++)
  {
    *(points_ + i) = MathUtils::Mat4TransformVec3(model, *(points_ + i));
  }
  for (int i = 0; i < nFaces_; i++)
  {
    *(centers_ + i) = MathUtils::Mat4TransformVec3(model, *(centers_ + i));
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

void Entity::startDestroy()
{
  destroying_ = true;
  destroying_time_ = std::chrono::steady_clock::now();
}

bool Entity::isDestroyed()
{
  return destroyed_;
}

void Entity::destroying()
{
  check_time_ = std::chrono::steady_clock::now();

  auto elapsed_milli = std::chrono::duration_cast<Milliseconds>(check_time_ - destroying_time_);

  fill_ = false;
  lines_ = true;
  renderLight_ = false;

  if (elapsed_milli.count() > 200.0f)
  {
    lines_ = false;
  }

  if (elapsed_milli.count() >= 750.0f)
  {
    if (fillColor_.a > (Uint8)5.0f)
      fillColor_.a -= (Uint8)5.0f;
    else
    {
      fillColor_.a = 0;
      destroyed_ = true;
      destroying_ = false;
    }
  }

  Vec3 mov = mov_;
  translation({-mov_.x, -mov_.y, -mov_.z});
  for (int i = 0; i < vertex_; i++)
  {
    if (rand() < FLT_MAX / 1000)
    {
      Mat4 model = Mat4::Scale(MathUtils::fRand(1.075f, 0.99f));
      *(points_ + i) = MathUtils::Mat4TransformVec3(model, *(points_ + i));
    }
  }
  translation(mov);
}

void Entity::draw(Keys *keys, SDL_Renderer *render, Render drawRender, Vec3 light, int id)
{
  if (destroying_)
    destroying();

  // Transform of 2D points
  Mat3 model = Mat3::Identity();
  Mat3 scale = Mat3::Scale(drawRender.getRenderScale());
  Mat3 mov = Mat3::Translate(drawRender.getRenderCenter());

  model = mov * scale;

  // Necesita optimizacion
  Render_Figure figure;
  figure.verts = &draw_sdl_;
  figure.point = points_;
  figure.n_points = vertex_;
  figure.desp = mov_;
  figure.light = light;
  figure.color = fillColor_;
  figure.model = model;
  figure.forceRender = false;

  drawRender.renderThreadedPoints(figure, renderLight_);
  // drawRender.renderPoints(figure, renderLight_);

  if (lines_)
  {
    SDL_SetRenderDrawColor(render, RGBA(linesColor_));
  }

  // This is to draw with texture | light
  if (fill_ || lines_)
  {
    // Points Ordered
    for (int i = 0; i < nFaces_; i++)
    {
      order_[i] = i;
    }

    std::sort(order_, order_ + nFaces_, [this, &drawRender](int a, int b)
              { return Vec3::Substract(centers_[a], drawRender.camera_).Magnitude() > Vec3::Substract(centers_[b], drawRender.camera_).Magnitude(); });

    // Draw Triangles
    for (int i = 0; i < nFaces_; i++)
    {

      bool draw = true;
      for (int j = 0; j < 3; j++)
      {
        draw = (draw && draw_sdl_[faces_[order_[i]].points[j]].active);
        if (!draw)
          break;
      }

      if (draw)
      {
        static SDL_Vertex triangle[3];
        triangle[0] = draw_sdl_[faces_[order_[i]].points[0]].point;
        triangle[1] = draw_sdl_[faces_[order_[i]].points[1]].point;
        triangle[2] = draw_sdl_[faces_[order_[i]].points[2]].point;

        if (fill_)
        {
          SDL_RenderGeometry(render, NULL, triangle, 3, NULL, 0);
        }

        if (lines_)
        {
          SDL_RenderDrawLine(render, triangle[0].position.x, triangle[0].position.y,
                             triangle[1].position.x, triangle[1].position.y);
          SDL_RenderDrawLine(render, triangle[1].position.x, triangle[1].position.y,
                             triangle[2].position.x, triangle[2].position.y);
          SDL_RenderDrawLine(render, triangle[2].position.x, triangle[2].position.y,
                             triangle[0].position.x, triangle[0].position.y);
        }
      }

      draw = true;
      if (faces_[order_[i]].n_points == 4)
      {
        draw = (draw && draw_sdl_[faces_[order_[i]].points[0]].active);
        draw = (draw && draw_sdl_[faces_[order_[i]].points[2]].active);
        draw = (draw && draw_sdl_[faces_[order_[i]].points[3]].active);
      }
      if (faces_[order_[i]].n_points == 4 && draw)
      {
        static SDL_Vertex triangle1[3];
        triangle1[0] = draw_sdl_[faces_[order_[i]].points[3]].point;
        triangle1[1] = draw_sdl_[faces_[order_[i]].points[2]].point;
        triangle1[2] = draw_sdl_[faces_[order_[i]].points[0]].point;

        if (fill_)
        {
          SDL_RenderGeometry(render, NULL, triangle1, 3, NULL, 0);
        }

        if (lines_)
        {
          SDL_RenderDrawLine(render, triangle1[0].position.x, triangle1[0].position.y,
                             triangle1[1].position.x, triangle1[1].position.y);
          SDL_RenderDrawLine(render, triangle1[1].position.x, triangle1[1].position.y,
                             triangle1[2].position.x, triangle1[2].position.y);
          SDL_RenderDrawLine(render, triangle1[2].position.x, triangle1[2].position.y,
                             triangle1[0].position.x, triangle1[0].position.y);
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

void Entity::print() {}

Entity::~Entity()
{
  DESTROY(points_);

  DESTROY(draw_sdl_);

  DESTROY(faces_);

  DESTROY(centers_);

  DESTROY(order_);
}
