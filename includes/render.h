#include <SDL2/SDL.h>
#include <iostream>
#include "mv_math.h"
#include "SDL_event_control.h"

////////////////////////
// GUARDAS NO TOCAR
#ifndef render_h
#define render_h
////////////////////////

struct Render_Vert
{
  SDL_Vertex point;
  bool active;
};

class Render
{
public:
  MV::Pnt3 camera_;

  Render();

  void init(MV::Pnt2 max_win, MV::Pnt3 camera, float near = 1, float far = 1000);

  void reset(MV::Pnt2 max_win);

  void rotation(MV::Pnt3 rot);
  void translation(MV::Pnt3 desp);

  void inputs(Keys *keys);

  int *getOrder(MV::Pnt3 *object_desp, int max_objects);

  Render_Vert renderPoint(MV::Pnt3 point, MV::Pnt3 desp, MV::Pnt3 light, SDL_Color color, MV::Mat3 model, bool forceRender = false);

  void cameraDraw(Keys *keys, SDL_Renderer *render, MV::Pnt2 max_win);

  MV::Pnt2 getRenderScale();
  float getFar();
  float getNear();

  MV::Pnt3 getUp();

private:
  int *draw_order_;
  MV::Pnt3 mira_;
  MV::Vec3 up_;
  MV::Vec3 down_;
  MV::Vec3 right_;
  MV::Vec3 left_;
  MV::Vec3 front_;
  MV::Vec3 back_;
  int max_order_;
  float far_;
  float near_;
  MV::Pnt2 render_scale_;

  MV::Pnt3 vector_caras_[6];
  MV::Pnt3 centros_caras_[6];
  MV::Pnt3 paint_square_[4];
  MV::Pnt3 centro_render_;

  bool active(MV::Pnt3 point);
};

#endif /* render_h */
