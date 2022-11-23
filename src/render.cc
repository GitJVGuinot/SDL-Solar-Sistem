#include <render.h>

MV::Pnt2 Render::getRenderScale()
{
  return render_scale_;
};

float Render::getFar()
{
  return far_;
}
float Render::getNear()
{
  return near_;
}

Render::Render()
{
  camara_ = {0, 0, 0};
  mira_ = {0, 0, 0};
  draw_order_ = nullptr;
  max_order_ = 0;
};

void Render::init(MV::Pnt2 max_win, MV::Pnt3 camara, float near, float far)
{
  std::cout << "Creando camara..." << std::endl;
  up_ = {0, 1, 0};
  down_ = {0, -1, 0};
  right_ = {1, 0, 0};
  left_ = {-1, 0, 0};
  front_ = {0, 0, 1};
  back_ = {0, 0, -1};
  camara_ = camara;
  near_ = near;
  far_ = far;
  max_order_ = 0;
  draw_order_ = nullptr;

  float newScale = (500 * far_) / 1000;
  render_scale_ = {newScale, newScale};

  // Max_win se establecera cuando colisione con el centro
  MV::Pnt3 vector_mira = MV::Normalizar_Vec(MV::Vec_Resta(camara_, {camara.x, camara.y, camara.z + 100}));
  centro_render_ = MV::Vec_Sum(camara_, MV::Vec_Escalado(vector_mira, ((far - near) / 2) + near));
  mira_ = centro_render_;

  // Near face
  centros_caras_[0] = {max_win.x / 2, max_win.y / 2, camara_.z - near};
  vector_caras_[0] = MV::Normalizar_Vec(MV::Vec_Resta(centro_render_, centros_caras_[0]));
  // Far face
  centros_caras_[1] = {max_win.x / 2, max_win.y / 2, camara_.z - far};
  vector_caras_[1] = MV::Normalizar_Vec(MV::Vec_Resta(centro_render_, centros_caras_[1]));

  // Right face
  centros_caras_[2] = centro_render_;
  centros_caras_[2].x += max_win.x / 2;
  // Giro 90 en y
  vector_caras_[2] = MV::Vec_Resta(camara_, centros_caras_[2]);
  vector_caras_[2] = MV::Rotate_Point_3D({0, -90, 0}, vector_caras_[2]);
  // Left face
  centros_caras_[3] = centro_render_;
  centros_caras_[3].x -= max_win.x / 2;
  // Giro -90 en y
  vector_caras_[3] = MV::Vec_Resta(camara_, centros_caras_[3]);
  vector_caras_[3] = MV::Rotate_Point_3D({0, 90, 0}, vector_caras_[3]);

  // Up face
  centros_caras_[4] = centro_render_;
  centros_caras_[4].y += max_win.y / 2;
  // Giro 90 en x
  vector_caras_[4] = MV::Vec_Resta(camara_, centros_caras_[4]);
  vector_caras_[4] = MV::Rotate_Point_3D({90, 0, 0}, vector_caras_[4]);
  // down face
  centros_caras_[5] = centro_render_;
  centros_caras_[5].y -= max_win.y / 2;
  // Giro -90 en x
  vector_caras_[5] = MV::Vec_Resta(camara_, centros_caras_[5]);
  vector_caras_[5] = MV::Rotate_Point_3D({-90, 0, 0}, vector_caras_[5]);

  // Need to change
  paint_square_[0] = {centros_caras_[3].x, centros_caras_[4].y, centros_caras_[2].z};
  paint_square_[1] = {centros_caras_[2].x, centros_caras_[4].y, centros_caras_[2].z};
  paint_square_[2] = {centros_caras_[2].x, centros_caras_[5].y, centros_caras_[2].z};
  paint_square_[3] = {centros_caras_[3].x, centros_caras_[5].y, centros_caras_[2].z};

  MV::Vec_Print(camara_, "Camara: ");
  MV::Vec_Print(mira_, "Mira: ");
  MV::Vec_Print(up_, "Up: ");

  std::cout << "Camara creada" << std::endl;
};

void Render::reset(MV::Pnt2 max_win)
{
  DESTROY(draw_order_);
  init(max_win, {max_win.x / 2, max_win.y / 2, 100});
}

void Render::rotation(MV::Pnt3 rot)
{

  MV::Orbitar_Punto(camara_, rot, mira_);

  up_ = MV::Rotate_Point_3D(rot, up_);
  down_ = MV::Rotate_Point_3D(rot, down_);
  right_ = MV::Rotate_Point_3D(rot, right_);
  left_ = MV::Rotate_Point_3D(rot, left_);
  front_ = MV::Rotate_Point_3D(rot, front_);
  back_ = MV::Rotate_Point_3D(rot, back_);

  for (int i = 0; i < 6; i++)
  {
    if (i < 4)
      MV::Orbitar_Punto(camara_, rot, paint_square_[i]);
    MV::Orbitar_Punto(camara_, rot, centros_caras_[i]);
    vector_caras_[i] = MV::Rotate_Point_3D(rot, vector_caras_[i]);
  }
}

void Render::translation(MV::Pnt3 desp)
{
  camara_ = MV::Vec_Sum(camara_, desp);
  mira_ = MV::Vec_Sum(mira_, desp);
  for (int i = 0; i < 6; i++)
  {
    if (i < 4)
      paint_square_[i] = MV::Vec_Sum(paint_square_[i], desp);
    centros_caras_[i] = MV::Vec_Sum(centros_caras_[i], desp);
  }
}

void Render::inputs(Keys *keys)
{

  if (EVENT_DOWN(UP, keys))
    rotation(right_);
  if (EVENT_DOWN(DOWN, keys))
    rotation(left_);

  if (EVENT_DOWN(RIGHT, keys))
    rotation(up_);
  if (EVENT_DOWN(LEFT, keys))
    rotation(down_);

  if (EVENT_DOWN(K_n, keys))
    rotation(front_);
  if (EVENT_DOWN(K_m, keys))
    rotation(back_);

  if (EVENT_DOWN(K_w, keys))
    translation(back_);
  if (EVENT_DOWN(K_s, keys))
    translation(front_);

  if (EVENT_DOWN(K_a, keys))
    translation(right_);
  if (EVENT_DOWN(K_d, keys))
    translation(left_);

  if (EVENT_DOWN(K_q, keys))
    translation(down_);
  if (EVENT_DOWN(K_e, keys))
    translation(up_);
}

int *Render::getOrder(MV::Pnt3 *object, int max_order)
{
  // Draw Planets ir order
  if (max_order != max_order_)
  {
    max_order_ = max_order;
    draw_order_ = (int *)realloc(draw_order_, max_order_ * sizeof(int));
  }
  for (int i = 0; i < max_order_; i++)
  {
    draw_order_[i] = i;
  }

  for (int i = 0; i < max_order_; i++)
  {
    for (int j = 1; j < max_order_; j++)
    {
      if (MV::Vec_Magn(MV::Vec_Resta(object[draw_order_[i]], camara_)) >= MV::Vec_Magn(MV::Vec_Resta(object[draw_order_[j]], camara_)))
      {
        int aux = draw_order_[i];
        draw_order_[i] = draw_order_[j];
        draw_order_[j] = aux;
      }
    }
  }

  for (int i = 0; i < max_order_ - 1; i++)
  {
    int aux = draw_order_[i];
    draw_order_[i] = draw_order_[i + 1];
    draw_order_[i + 1] = aux;
  }

  return draw_order_;
}

SDL_Color renderColorLight(MV::Pnt3 point, MV::Pnt3 desp, MV::Pnt3 light, SDL_Color color)
{

  SDL_Color ret = color;

  MV::Vec3 point_vector = MV::Vec_Resta(desp, point); // Vector director  al centro desde el punto
  MV::Vec3 light_vector = MV::Vec_Resta(desp, light); // Vector director apuntando al centro desde la luz

  if(point_vector.x+point_vector.y+point_vector.z!=0) point_vector = MV::Normalizar_Vec(point_vector);
  if(light_vector.x+light_vector.y+light_vector.z!=0) light_vector = MV::Normalizar_Vec(light_vector);

  float angulo = MV::Obten_Angulo(point_vector, light_vector);

  if (light.x == desp.x && light.y == desp.y && light.z == desp.z)
    angulo = 0;

  if (angulo < 0)
    angulo *= -1;

  Uint8 angleRest = (Uint8)((float)(255 / 180) * angulo);

  if (ret.r > 0)
    ret.r -= (Uint8)angleRest;
  if (ret.g > 0)
    ret.g -= (Uint8)angleRest;
  if (ret.b > 0)
    ret.b -= (Uint8)angleRest;

  if (ret.r < 0)
    ret.r = 0;
  if (ret.g < 0)
    ret.g = 0;
  if (ret.b < 0)
    ret.b = 0;

  return ret;
}

SDL_Vertex renderSDLVertex(MV::Pnt3 light, MV::Pnt2 draw, MV::Pnt3 point, MV::Pnt3 desp, SDL_Color color)
{
  return SDL_Vertex{{draw.x, draw.y}, renderColorLight(point, desp, light, color), {0, 0}};
}

bool Render::active(MV::Pnt3 point)
{
  bool ret = true;

  // Crear la normal desde el centro de las 6 caras al centro del cubo
  for (int i = 0; i < 6; i++)
  {
    MV::Pnt3 pointvec = MV::Normalizar_Vec(MV::Vec_Resta(point, centros_caras_[i]));
    float angulo = MV::Obten_Angulo(pointvec, vector_caras_[i]);
    if (!Between(90, angulo, -90))
    {
      return false;
    }
  }

  return ret;
}

Render_Vert Render::renderPoint(MV::Pnt3 point, MV::Pnt3 desp, MV::Pnt3 light, SDL_Color color, MV::Mat3 model, bool forceRender)
{
  if (active(point) || forceRender)
  {
    // Proyeccion de puntos 3D a 2D teniendo en cuenta la camara
    MV::Mat4 vMatrix = MV::Mat4View(camara_, mira_, up_);
    MV::Mat4 pro = MV::Mat4Projection();
    vMatrix = MV::Mat4Multiply(pro, vMatrix);

    MV::Vec3 new_point = MV::Mat4TransformVec3(vMatrix, point);

    new_point = MV::Vec2_Tr_Vec3(MV::Vec3_Tr_Vec2(new_point), 1);

    new_point = MV::Mat3TransformVec3(model, new_point);

    SDL_Vertex ret = renderSDLVertex(light, MV::Vec3_Tr_Vec2(new_point), point, desp, color);

    return Render_Vert{ret, true};
  }
  else
    return Render_Vert{{0, 0, 0}, false};
}

void Render::cameraDraw(Keys *keys, SDL_Renderer *render, MV::Pnt2 max_win)
{
  // Transformacion de puntos 2D
  MV::Mat3 model = MV::Mat3Identity();
  MV::Mat3 scala = MV::Mat3Scale(render_scale_);
  MV::Mat3 desp = MV::Mat3Translate(MV::Vec3_Tr_Vec2(centro_render_));
  model = MV::Mat3Multiply(desp, scala);

  Render_Vert draw[6];
  Render_Vert square[4];

  for (int i = 0; i < 6; i++)
  {
    if (i < 4)
      square[i] = renderPoint(paint_square_[i], {0}, {0}, {0}, model, true);
    draw[i] = renderPoint(centros_caras_[i], {0}, {0}, {0}, model, true);
  }

  SDL_SetRenderDrawColor(render, 255, 0, 255, 128);
  SDL_RenderDrawLine(render, square[0].point.position.x, square[0].point.position.y, square[1].point.position.x, square[1].point.position.y);
  SDL_RenderDrawLine(render, square[1].point.position.x, square[1].point.position.y, square[2].point.position.x, square[2].point.position.y);
  SDL_RenderDrawLine(render, square[2].point.position.x, square[2].point.position.y, square[3].point.position.x, square[3].point.position.y);
  SDL_RenderDrawLine(render, square[3].point.position.x, square[3].point.position.y, square[0].point.position.x, square[0].point.position.y);
}

MV::Pnt3 Render::getUp()
{
  return up_;
}
