#include <SDL2/SDL.h>
#include <iostream>
#include "mv_math.h"
#include "SDL_event_control.h"

////////////////////////
// GUARDAS NO TOCAR
#ifndef render_h
#define render_h
////////////////////////

struct Render_Vert{
  SDL_Vertex point;
  bool active;
};

class Render{
public:
  MV::Pnt3 camara_;

  Render();

  Render(MV::Pnt2 max_win, MV::Pnt3 camara, float near, float far, int max_objects);

  void inputs(Keys *keys);

  int* getOrder(MV::Pnt3 *object_desp, int max_objects);

  Render_Vert renderPoint(MV::Pnt3 point, MV::Pnt3 desp, MV::Pnt3 light, SDL_Color color, MV::Mat3 model);

  void cameraDraw(Keys *keys, SDL_Renderer *render, MV::Pnt2 max_win);

private:
  int *draw_order_;
  MV::Pnt3 mira_;
  int max_order_;
  int far_;
  int near_;

  MV::Pnt3 vector_caras_[6];
  MV::Pnt3 centros_caras_[6];
  MV::Pnt3 centro_render_;

  bool active(MV::Pnt3 point);

};

#endif /* render_h */
