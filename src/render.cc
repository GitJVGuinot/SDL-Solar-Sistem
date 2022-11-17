#include <render.h>

Render::Render()
{
  camara_ = {0, 0, 0};
  mira_ = {0, 0, 0};
  draw_order_ = nullptr;
  max_order_ = 0;
};

Render::Render(MV::Pnt2 max_win, MV::Pnt3 camara, float near, float far, int max_objects)
{
  camara_ = camara;
  near_ = near;
  far_ = far;
  draw_order_ = nullptr;
  draw_order_ = (int *)realloc(draw_order_, max_objects * sizeof(int));
  max_order_ = max_objects;

  // Change
  // Max_win se establecera cuando colisione con el centro
  MV::Pnt3 vector_mira = MV::Normalizar_Vec(MV::Vec_Resta(camara_,{camara.x,camara.y,camara.z+100}));
  centro_render_ = MV::Vec_Sum(camara_, MV::Vec_Escalado(vector_mira, ( (far-near) /2 ) + near ));
  mira_ = centro_render_;

  // Near face
  centros_caras_[0] = {max_win.x/2,max_win.y/2,camara_.z-near};
  vector_caras_[0] = MV::Normalizar_Vec(MV::Vec_Resta(centro_render_, centros_caras_[0]));
  // Far face
  centros_caras_[1] = {max_win.x/2,max_win.y/2,camara_.z-far};
  vector_caras_[1] = MV::Normalizar_Vec(MV::Vec_Resta(centro_render_, centros_caras_[1]));

  // Right face
  centros_caras_[2] = centro_render_;
  centros_caras_[2].x += max_win.x/2;
  // Giro 90 en y
  vector_caras_[2] = MV::Vec_Resta(camara_, centros_caras_[2]);
  vector_caras_[2] = MV::Rotate_Point_3D({0,-90,0}, vector_caras_[2]);
  // Left face
  centros_caras_[3] = centro_render_;
  centros_caras_[3].x -= max_win.x/2;
  // Giro -90 en y
  vector_caras_[3] = MV::Vec_Resta(camara_, centros_caras_[3]);
  vector_caras_[3] = MV::Rotate_Point_3D({0,90,0},vector_caras_[3]);

  // Up face
  centros_caras_[4] = centro_render_;
  centros_caras_[4].y += max_win.y/2;
  // Giro 90 en x
  vector_caras_[4] = MV::Vec_Resta(camara_, centros_caras_[4]);
  vector_caras_[4] = MV::Rotate_Point_3D({90,0,0},vector_caras_[4]);
  // down face
  centros_caras_[5] = centro_render_;
  centros_caras_[5].y -= max_win.y/2;
  // Giro -90 en x
  vector_caras_[5] = MV::Vec_Resta(camara_, centros_caras_[5]);
  vector_caras_[5] = MV::Rotate_Point_3D({-90,0,0}, vector_caras_[5]);

  for(int i=0; i<6; i++)
  {
    char str[100];
    sprintf(str, "i: %d, centros: ", i);
    MV::Vec_Print(centros_caras_[i], str);

    char str2[100];
    sprintf(str2, "i: %d, vectores: ", i);
    MV::Vec_Print(vector_caras_[i], str2);
  }

  MV::Vec_Print(camara_, "Camara: ");
  MV::Vec_Print(mira_, "Mira: ");
  MV::Vec_Print(centro_render_, "Centro: ");

};

void Render::inputs(Keys *keys)
{

  if (EVENT_DOWN(DOWN, keys))
  {
    MV::Orbitar_Punto(camara_, MV::Vec3{1, 0, 0}, mira_);
    for(int i=0; i<6; i++){
      MV::Orbitar_Punto(camara_, MV::Vec3{1, 0, 0}, centros_caras_[i]);
      vector_caras_[i] = MV::Rotate_Point_3D(MV::Vec3{1, 0, 0}, vector_caras_[i]);
    }
  }
  if (EVENT_DOWN(UP, keys))
  {
    MV::Orbitar_Punto(camara_, MV::Vec3{-1, 0, 0}, mira_);
    for(int i=0; i<6; i++){
      MV::Orbitar_Punto(camara_, MV::Vec3{-1, 0, 0}, centros_caras_[i]);
      vector_caras_[i] = MV::Rotate_Point_3D(MV::Vec3{-1, 0, 0}, vector_caras_[i]);
    }
  }
  if (EVENT_DOWN(RIGHT, keys))
  {
    MV::Orbitar_Punto(camara_, MV::Vec3{0, 1, 0}, mira_);
    for(int i=0; i<6; i++){
      MV::Orbitar_Punto(camara_, MV::Vec3{0, 1, 0}, centros_caras_[i]);
      vector_caras_[i] = MV::Rotate_Point_3D(MV::Vec3{0, 1, 0}, vector_caras_[i]);
    }
  }
  if (EVENT_DOWN(LEFT, keys))
  {
    MV::Orbitar_Punto(camara_, MV::Vec3{0, -1, 0}, mira_);
    for(int i=0; i<6; i++){
      MV::Orbitar_Punto(camara_, MV::Vec3{0, -1, 0}, centros_caras_[i]);
      vector_caras_[i] = MV::Rotate_Point_3D(MV::Vec3{0, -1, 0}, vector_caras_[i]);
    }
  }
  if (EVENT_DOWN(K_n, keys))
  {
    MV::Orbitar_Punto(camara_, MV::Vec3{0, 0, 1}, mira_);
    for(int i=0; i<6; i++){
      MV::Orbitar_Punto(camara_, MV::Vec3{0, 0, 1}, centros_caras_[i]);
      vector_caras_[i] = MV::Rotate_Point_3D(MV::Vec3{0, 0, 1}, vector_caras_[i]);
    }
  }
  if (EVENT_DOWN(K_m, keys))
  {
    MV::Orbitar_Punto(camara_, MV::Vec3{0, 0, -1}, mira_);
    for(int i=0; i<6; i++){
      MV::Orbitar_Punto(camara_, MV::Vec3{0, 0, -1}, centros_caras_[i]);
      vector_caras_[i] = MV::Rotate_Point_3D(MV::Vec3{0, 0, -1}, vector_caras_[i]);
    }
  }

  if (EVENT_DOWN(K_w, keys))
  {
    MV::Vec3 front = MV::Vec_Resta(mira_, camara_);
    front = MV::Normalizar_Vec(front);

    camara_ = MV::Vec_Sum(camara_, front);
    mira_ = MV::Vec_Sum(mira_, front);

    for(int i=0; i<6; i++) centros_caras_[i] = MV::Vec_Sum(centros_caras_[i], front);
  }

  if (EVENT_DOWN(K_s, keys))
  {
    MV::Vec3 back = MV::Vec_Resta(mira_, camara_);
    back = MV::Normalizar_Vec(back);
    back = MV::Vec_Escalado(back, -1);

    camara_ = MV::Vec_Sum(camara_, back);
    mira_ = MV::Vec_Sum(mira_, back);
    for(int i=0; i<6; i++) centros_caras_[i] = MV::Vec_Sum(centros_caras_[i], back);
  }

  if (EVENT_DOWN(K_a, keys))
  {
    MV::Vec3 left = MV::Vec_Resta(mira_, camara_);
    left = MV::Normalizar_Vec(left);
    left = Rotate_Point_3D({0,-90,0}, left);

    camara_ = MV::Vec_Sum(camara_, left);
    mira_ = MV::Vec_Sum(mira_, left);
    for(int i=0; i<6; i++) centros_caras_[i] = MV::Vec_Sum(centros_caras_[i], left);
  }

  if (EVENT_DOWN(K_d, keys))
  {
    MV::Vec3 right = MV::Vec_Resta(mira_, camara_);
    right = MV::Normalizar_Vec(right);
    right = Rotate_Point_3D({0,90,0}, right);

    camara_ = MV::Vec_Sum(camara_, right);
    mira_ = MV::Vec_Sum(mira_, right);
    for(int i=0; i<6; i++) centros_caras_[i] = MV::Vec_Sum(centros_caras_[i], right);
  }

  if (EVENT_DOWN(K_q, keys))
  {
    MV::Vec3 down = MV::Vec_Resta(mira_, camara_);
    down = MV::Normalizar_Vec(down);
    down = Rotate_Point_3D({-90,0,0}, down);

    camara_ = MV::Vec_Sum(camara_, down);
    mira_ = MV::Vec_Sum(mira_, down);
    for(int i=0; i<6; i++) centros_caras_[i] = MV::Vec_Sum(centros_caras_[i], down);
  }
  if (EVENT_DOWN(K_e, keys))
  {
    MV::Vec3 up = MV::Vec_Resta(mira_, camara_);
    up = MV::Normalizar_Vec(up);
    up = Rotate_Point_3D({90,0,0}, up);

    camara_ = MV::Vec_Sum(camara_, up);
    mira_ = MV::Vec_Sum(mira_, up);
    for(int i=0; i<6; i++) centros_caras_[i] = MV::Vec_Sum(centros_caras_[i], up);
  }
}

int* Render::getOrder(MV::Pnt3 *object, int max_order)
{
  // Draw Planets ir order
  if (max_order != max_order_)
  {
    max_order_ = max_order;
    draw_order_ = (int *)realloc(draw_order_, max_order_);
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

  point_vector = MV::Normalizar_Vec(point_vector);
  light_vector = MV::Normalizar_Vec(light_vector);

  float angulo = MV::Obten_Angulo(point_vector, light_vector);

  if (light.x == desp.x && light.y == desp.y && light.z == desp.z)
    angulo = 0;

  if (angulo < 0)
    angulo *= -1;

  Uint8 angleRest = (Uint8)((float)255 / 180 * angulo);

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
  bool ret=true;

  // Crear la normal desde el centro de las 6 caras al centro del cubo
  for(int i=0; i<6; i++)
  {
    MV::Pnt3 pointvec = MV::Normalizar_Vec(MV::Vec_Resta(point, centros_caras_[i]));
    float angulo=MV::Obten_Angulo(pointvec, vector_caras_[i]);
    if(!Between(90, angulo, -90)){
      return false;
    }
  }

  return ret;
}

Render_Vert Render::renderPoint(MV::Pnt3 point, MV::Pnt3 desp, MV::Pnt3 light, SDL_Color color, MV::Mat3 model)
{
  // Proyeccion de puntos 3D a 2D teniendo en cuenta la camara
  MV::Mat4 vMatrix = MV::Mat4View(camara_, mira_);
  MV::Mat4 pro = MV::Mat4Projection();
  vMatrix = MV::Mat4Multiply(pro, vMatrix);

  MV::Vec3 new_point = MV::Mat4TransformVec3(vMatrix, point);

  new_point = MV::Vec2_Tr_Vec3(MV::Vec3_Tr_Vec2(new_point), 1);

  new_point = MV::Mat3TransformVec3(model, new_point);

  SDL_Vertex ret = renderSDLVertex(light, MV::Vec3_Tr_Vec2(new_point), point, desp, color);

  return Render_Vert{ret, active(point)};
}

void Render::cameraDraw(Keys *keys, SDL_Renderer *render)
{
  // Transformacion de puntos 2D
  MV::Mat3 model = MV::Mat3Identity();
  MV::Mat3 scala = MV::Mat3Scale({200, 200});
  MV::Mat3 desp;
  desp = MV::Mat3Translate(MV::Vec3_Tr_Vec2(centro_render_));
  model = MV::Mat3Multiply(desp, scala);
  Render_Vert draw[6];

  for(int i=0; i<6; i++){
    draw[i] = renderPoint(centros_caras_[i], {0}, {0}, {0}, model);
  }

  SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);

  SDL_RenderDrawLine(render, draw[2].point.position.x,draw[2].point.position.y, draw[4].point.position.x,draw[4].point.position.y);
  SDL_RenderDrawLine(render, draw[2].point.position.x,draw[2].point.position.y, draw[5].point.position.x,draw[5].point.position.y);
  SDL_RenderDrawLine(render, draw[3].point.position.x,draw[3].point.position.y, draw[4].point.position.x,draw[4].point.position.y);
  SDL_RenderDrawLine(render, draw[3].point.position.x,draw[3].point.position.y, draw[5].point.position.x,draw[5].point.position.y);

}
