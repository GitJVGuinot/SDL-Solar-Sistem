#include <SDL2/SDL.h>
#include <iostream>
#include <mv_math.h>
#include <SDL_event_control.h>
#include <common_defs.h>
#include <render.h>

////////////////////////
// GUARDAS NO TOCAR
#ifndef entity_3d_h
#define entity_3d_h
////////////////////////

struct Faces
{
  int n_points;
  int points[4];
};

class Entity
{
protected:
  MV::Pnt3 scale_;
  MV::Pnt3 rotate_;

  int res_;
  MV::Pnt3 *points_;
  MV::Pnt3 *centers_;

  Render_Vert *draw_sdl_;

  Faces *faces_;
  int nFaces_;

  int *order_;

public:
  float dim_;
  int vertex_;
  MV::Pnt3 mov_;
  MV::Pnt3 orbit_;
  MV::Pnt3 orbit_center_;
  SDL_Color color_;
  bool fill_;
  float orbit_vel_;

  // Inicializa la entity
  Entity();

  MV::Pnt3 point(int position);

  MV::Pnt3 getScale();

  void rotation(MV::Pnt3 rot);

  void orbitar();

  void translation(MV::Pnt3 mov);

  void scale(MV::Pnt3 scale);

  void inputs(Keys *keys);

  SDL_Color renderColorLight(MV::Pnt3 point, MV::Pnt3 light);

  SDL_Vertex renderSDLVertex(MV::Pnt3 light, MV::Pnt2 draw, MV::Pnt3 point);

  void draw(Keys *keys, SDL_Renderer *render, Render drawRender, MV::Pnt3 light, int drawCallback(SDL_Renderer*, SDL_Vertex*, const int));

  void imprime();

  void operator=(const Entity& other);

  ~Entity();
};

////////////////////////
// GUARDAS NO TOCAR
#endif /* entity_3d_h */
////////////////////////
