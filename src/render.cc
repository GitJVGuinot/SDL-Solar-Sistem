#include <render.h>

Render::Render(){
  camara_={0,0,0};
  mira_={0,0,0};
  draw_order_=nullptr;
  max_order_=0;
};

Render::Render(MV::Pnt3 camara, MV::Pnt3 mira, int max_objects){
  camara_=camara;
  mira_=mira;
  draw_order_=nullptr;
  draw_order_=(int*)realloc(draw_order_, max_objects*sizeof(int));
  max_order_=max_objects;
};

void Render::inputs(Keys *keys){

  if (EVENT_DOWN(DOWN, keys)){ Orbitar_Punto(camara_, MV::Vec3{1, 0, 0}, mira_); }
  if (EVENT_DOWN(UP, keys)){ Orbitar_Punto(camara_, MV::Vec3{-1, 0, 0},mira_); }
  if (EVENT_DOWN(RIGHT, keys)){ Orbitar_Punto(camara_, MV::Vec3{0, 1, 0}, mira_); }
  if (EVENT_DOWN(LEFT, keys)){ Orbitar_Punto(camara_, MV::Vec3{0, -1, 0},mira_); }
  if (EVENT_DOWN(K_n, keys)){ Orbitar_Punto(camara_, MV::Vec3{0, 0, 1}, mira_); }
  if (EVENT_DOWN(K_m, keys)){ Orbitar_Punto(camara_, MV::Vec3{0, 0, -1},mira_); }


  if (EVENT_DOWN(K_a, keys)){
    camara_.x++;
    mira_.x++;
  }
  if (EVENT_DOWN(K_d, keys)){
    camara_.x--;
    mira_.x--;
  }
  if (EVENT_DOWN(K_w, keys)){
    camara_.z--;
    mira_.z--;
  }
  if (EVENT_DOWN(K_s, keys)){
    camara_.z++;
    mira_.z++;
  }
  if (EVENT_DOWN(K_q, keys)){
    camara_.y++;
    mira_.y++;
  }
  if (EVENT_DOWN(K_e, keys)){
    camara_.y--;
    mira_.y--;
  }
}

void Render::order(MV::Pnt3 *object, int max_order){
  // Draw Planets ir order
  if(max_order!=max_order_){
    max_order_=max_order;
    draw_order_=(int*)realloc(draw_order_,max_order_);
  }
  for(int i=0; i<max_order_; i++){
    draw_order_[i]=i;
  }

  for (int i = 0; i < max_order_; i++)
  {
    for (int j = 1; j < max_order_; j++)
    {
      if (MV::Vec_Magn(MV::Vec_Resta(object[draw_order_[i]],camara_)) >= MV::Vec_Magn(MV::Vec_Resta(object[draw_order_[j]],camara_)))
      {
        int aux = draw_order_[i];
        draw_order_[i] = draw_order_[j];
        draw_order_[j] = aux;
      }
    }
  }

  for(int i=0; i<max_order_-1; i++){
    int aux=draw_order_[i];
    draw_order_[i]=draw_order_[i+1];
    draw_order_[i+1]=aux;
  }
}

SDL_Color renderColorLight(MV::Pnt3 point, MV::Pnt3 desp, MV::Pnt3 light, SDL_Color color)
{

    SDL_Color ret = color;

    MV::Vec3 point_vector = MV::Vec_Resta(desp, point);  // Vector director  al centro desde el punto
    MV::Vec3 light_vector = MV::Vec_Resta(desp, light);  // Vector director apuntando al centro desde la luz

    point_vector = MV::Normalizar_Vec(point_vector);
    light_vector = MV::Normalizar_Vec(light_vector);

    float angulo = MV::Obten_Angulo(point_vector, light_vector);

    if (light.x == desp.x && light.y == desp.y && light.z == desp.z)
      angulo = 0;

    if (angulo < 0) angulo *= -1;

    Uint8 angleRest = (Uint8)((float)255 / 180 * angulo);

    if(ret.r>0) ret.r -= (Uint8)angleRest;
    if(ret.g>0) ret.g -= (Uint8)angleRest;
    if(ret.b>0) ret.b -= (Uint8)angleRest;

    if(ret.r<0) ret.r=0;
    if(ret.g<0) ret.g=0;
    if(ret.b<0) ret.b=0;

    return ret;
}

SDL_Vertex renderSDLVertex(MV::Pnt3 light, MV::Pnt2 draw, MV::Pnt3 point, MV::Pnt3 desp, SDL_Color color)
{
  return SDL_Vertex{{draw.x,draw.y}, renderColorLight(point, desp, light, color), {0, 0}};
}

SDL_Vertex Render::renderPoint(MV::Pnt3 point, MV::Pnt3 desp, MV::Pnt3 light, SDL_Color color, MV::Mat3 model){

  // Proyeccion de puntos 3D a 2D teniendo en cuenta la camara
  MV::Mat4 vMatrix = MV::Mat4View(camara_, mira_);
  MV::Mat4 pro = MV::Mat4Projection();
  vMatrix = MV::Mat4Multiply(pro, vMatrix);

  MV::Vec3 new_point = MV::Mat4TransformVec3(vMatrix, point);

  new_point = MV::Vec2_Tr_Vec3(MV::Vec3_Tr_Vec2(new_point), 1);

  new_point = MV::Mat3TransformVec3(model, new_point);

  return renderSDLVertex(light, MV::Vec3_Tr_Vec2(new_point), point, desp, color);
}
