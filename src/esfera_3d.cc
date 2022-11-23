#include <esfera_3d.h>

// Obtiene los puntos de la esfera
void Esfera::obtenerEsfera()
{
  vertices_ = (2 * res_) * (res_ + 1);

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
      caras[i].n_points = 4;

      caras[i].points[0] = i;
      caras[i].points[1] = i + 1;
      caras[i].points[2] = ((filas + 1) * res_ * 2) + columnas + 1;
      caras[i].points[3] = ((filas + 1) * res_ * 2) + columnas;

      if (columnas + 1 == res_ * 2)
      {
        caras[i].points[1] = (filas * res_ * 2);
        caras[i].points[2] = ((filas + 1) * res_ * 2);
      }
      if (filas + 1 > res_)
      {
        caras[i].points[2] = ((filas)*res_ * 2) + columnas + 1;
        caras[i].points[3] = ((filas)*res_ * 2) + columnas;
      }
      if (filas + 1 > res_ && columnas + 1 == res_ * 2)
      {
        caras[i].points[2] = ((filas)*res_ * 2) + columnas;
      }

      i++;
    }
  }

  for (int i = 0; i < vertices_; i++)
  {
    centros_[i] = Vec_Resta(points_[caras[i].points[0]], points_[caras[i].points[2]]);
    centros_[i] = Vec_Escalado(centros_[i], 0.5f);
    centros_[i] = Vec_Sum(centros_[i], points_[caras[i].points[2]]);
  }
}

// Inicializa la esfera
Esfera::Esfera()
{
  escala_ = {0, 0, 0};
  rotado_ = {0, 0, 0};
  res_ = 0;
  dim_ = 0;
  vertices_ = 0;
  desp_ = {0, 0, 0};
  orbita_ = {0, 0, 0};
  centro_orbita_ = {0, 0, 0};
  color_ = {0, 0, 0};
};

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

MV::Pnt3 Esfera::point(int i)
{
  return *(points_ + i);
}

void Esfera::rotation(MV::Pnt3 p_rot)
{
  rotado_ = MV::Vec_Sum(rotado_, p_rot);
  if (rotado_.x >= 360)
    rotado_.x -= 360;
  if (rotado_.y >= 360)
    rotado_.y -= 360;
  if (rotado_.z >= 360)
    rotado_.z -= 360;

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

  MV::Pnt3 desp = desp_;
  translation({-desp_.x, -desp_.y, -desp_.z});
  for (int i = 0; i < vertices_; i++)
  {
    *(points_ + i) = MV::Mat4TransformVec3(model, *(points_ + i));
    *(centros_ + i) = MV::Mat4TransformVec3(model, *(centros_ + i));
  }
  translation(desp);
}

void Esfera::orbitar()
{
  if ((centro_orbita_.x + centro_orbita_.y + centro_orbita_.z) != 0)
  {
    MV::Pnt3 p_orbita_ = MV::Vec_Escalado(orbita_, orbit_vel_);

    MV::Mat4 rot_x;
    MV::Mat4 rot_y;
    MV::Mat4 rot_z;

    if (p_orbita_.x != 0)
      rot_x = MV::Mat4RotateX((p_orbita_.x * PI) / 180);
    if (p_orbita_.y != 0)
      rot_y = MV::Mat4RotateY((p_orbita_.y * PI) / 180);
    if (p_orbita_.z != 0)
      rot_z = MV::Mat4RotateZ((p_orbita_.z * PI) / 180);

    MV::Mat4 model = MV::Mat4Identity();
    if (p_orbita_.x != 0)
      model = MV::Mat4Multiply(model, rot_x);
    if (p_orbita_.y != 0)
      model = MV::Mat4Multiply(model, rot_y);
    if (p_orbita_.z != 0)
      model = MV::Mat4Multiply(model, rot_z);

    translation(MV::Vec3{-centro_orbita_.x, -centro_orbita_.y, -centro_orbita_.z});
    desp_ = MV::Mat4TransformVec3(model, desp_);
    for (int i = 0; i < vertices_; i++)
    {
      *(points_ + i) = MV::Mat4TransformVec3(model, *(points_ + i));
      *(centros_ + i) = MV::Mat4TransformVec3(model, *(centros_ + i));
    }
    translation(centro_orbita_);
  }
}

void Esfera::translation(MV::Pnt3 p_desp_)
{
  desp_ = MV::Vec_Sum(desp_, p_desp_);
  for (int i = 0; i < vertices_; i++)
  {
    *(points_ + i) = MV::Vec_Sum(*(points_ + i), p_desp_);
    *(centros_ + i) = MV::Vec_Sum(*(centros_ + i), p_desp_);
  }
}

void Esfera::scale(MV::Pnt3 p_escala_)
{
  escala_ = MV::Vec_Escalado(escala_, p_escala_);
  dim_ = p_escala_.x * dim_;

  MV::Mat4 m_escala_ = MV::Mat4Scale(p_escala_);

  MV::Mat4 model = MV::Mat4Identity();
  model = MV::Mat4Multiply(model, m_escala_);

  MV::Pnt3 desp = desp_;
  translation({-desp_.x, -desp_.y, -desp_.z});
  for (int i = 0; i < vertices_; i++)
  {
    *(points_ + i) = MV::Mat4TransformVec3(model, *(points_ + i));
    *(centros_ + i) = MV::Mat4TransformVec3(model, *(centros_ + i));
  }
  translation(desp);
}

void Esfera::inputs(Keys *keys)
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

void Esfera::draw(Keys *keys, SDL_Renderer *render, Render drawRender, MV::Pnt3 light, int drawCallback(SDL_Renderer *, SDL_Vertex *, const int))
{

  // Transformacion de puntos 2D
  MV::Mat3 model = MV::Mat3Identity();
  MV::Mat3 scala = MV::Mat3Scale(drawRender.getRenderScale());
  MV::Mat3 desp;

  if ((centro_orbita_.x + centro_orbita_.y + centro_orbita_.z) == 0)
  {
    desp = MV::Mat3Translate({desp_.x, desp_.y});
  }
  else
  {
    desp = MV::Mat3Translate(MV::Vec3_Tr_Vec2(centro_orbita_));
  }

  model = MV::Mat3Multiply(desp, scala);

  for (int i = 0; i < vertices_; i++)
  {
    draw_sdl_[i] = drawRender.renderPoint(points_[i], desp_, light, color_, model);
  }

  // This is to draw with texture | light
  if (fill_)
  {
    // Ordenado de puntos
    for (int i = 0; i < vertices_; i++)
      order_[i] = i;

    for (int i = 0; i < vertices_; i++)
    {
      for (int j = 1; j < vertices_; j++)
      {
        if (MV::Vec_Magn(MV::Vec_Resta(centros_[order_[i]], drawRender.camara_)) >= MV::Vec_Magn(MV::Vec_Resta(centros_[order_[j]], drawRender.camara_)))
        {
          int aux = order_[i];
          order_[i] = order_[j];
          order_[j] = aux;
        }
      }
    }

    for (int i = 0; i < vertices_ - 1; i++)
    {
      int aux = order_[i];
      order_[i] = order_[i + 1];
      order_[i + 1] = aux;
    }

    // Draw Triangles
    for (int i = 0; i < vertices_; i++)
    {

      static SDL_Vertex square[4];

      for (int j = 0; j < 4; j++)
        square[j] = draw_sdl_[caras[order_[i]].points[j]].point;

      bool draw = true;
      for (int j = 0; j < 4; j++)
      {
        draw = (draw && draw_sdl_[caras[order_[i]].points[j]].active);
        if(!draw) break;
      }

      /*
      int indices[5]={0,1,2,3,0};
      if(draw){
        int ret = SDL_RenderGeometry(render, NULL, square, 4, indices, 5);
      }
      */

      if (draw)
      {
        if (drawCallback != nullptr)
        {
          drawCallback(render, square, 4);
        }
        else
        {
          static SDL_Vertex triangle[3];
          triangle[0] = draw_sdl_[caras[order_[i]].points[0]].point;
          triangle[1] = draw_sdl_[caras[order_[i]].points[1]].point;
          triangle[2] = draw_sdl_[caras[order_[i]].points[2]].point;

          static SDL_Vertex triangle1[3];
          triangle1[0] = draw_sdl_[caras[order_[i]].points[3]].point;
          triangle1[1] = draw_sdl_[caras[order_[i]].points[2]].point;
          triangle1[2] = draw_sdl_[caras[order_[i]].points[0]].point;

          SDL_RenderGeometry(render, NULL, triangle, 3, NULL, 0);
          SDL_RenderGeometry(render, NULL, triangle1, 3, NULL, 0);
        }
      }
    }
  }
  else
  {
    // That is for points_
    for (int i = 0; i < vertices_; i++)
    {
      SDL_SetRenderDrawColor(render, RGBA(draw_sdl_[i].point.color));
      SDL_RenderDrawPoint(render, draw_sdl_[i].point.position.x, draw_sdl_[i].point.position.y);
    }
  }
}

Esfera::~Esfera() {}
