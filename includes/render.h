#include <SDL2/SDL.h>
#include <iostream>
#include "mv_math.h"
#include "SDL_event_control.h"

////////////////////////
// GUARDAS NO TOCAR
#ifndef render_h
#define render_h
////////////////////////

class Render{
public:
  MV::Pnt3 camara_;
  MV::Pnt3 light_;
  MV::Pnt3 mira_;
  int *draw_order_;
  int max_order_;

  Render();

  Render(MV::Pnt3 camara, MV::Pnt3 mira, int max_objects);

  void inputs(Keys *keys);

  void order(MV::Pnt3 *object_desp, int max_objects);

  SDL_Vertex renderPoint(MV::Pnt3 point, MV::Pnt3 desp, MV::Pnt3 light, SDL_Color color, MV::Mat3 model);

private:

};

#endif /* render_h */
