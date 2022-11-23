#include <SDL2/SDL.h>
#include <iostream>
#include <mv_math.h>
#include <SDL_event_control.h>
#include <SDL_colors.h>
#include <render.h>

#ifndef RGBA
#define RGBA(x) x.r, x.g, x.b, x.a
#endif

////////////////////////
// GUARDAS NO TOCAR
#ifndef entity_3d_h
#define entity_3d_h
////////////////////////

struct Caras
{
  int n_points;
  int points[4];
};

class Entity
{
private:
  MV::Pnt3 escala_;
  MV::Pnt3 rotado_;

  int res_;
  MV::Pnt3 *points_;
  MV::Pnt3 *centros_;

  Render_Vert *draw_sdl_;

  Caras *caras_;

  int *order_;

  // Obtiene los puntos de la entity
  void obtenerEntity();

public:
  float dim_;
  int vertices_;
  MV::Pnt3 desp_;
  MV::Pnt3 orbita_;
  MV::Pnt3 centro_orbita_;
  SDL_Color color_;
  bool fill_;
  float orbit_vel_;

  // Inicializa la entity
  Entity();
  int init(SDL_Color color, bool fill = false, int p_res_ = 10, MV::Pnt3 p_escala_ = {1, 1, 1}, MV::Pnt3 p_desp_ = {0, 0, 0}, MV::Pnt3 p_rot = {0, 0, 0}, MV::Pnt3 p_orbita_ = {0, 0, 0}, MV::Pnt3 centro_orbita = {0, 0, 0});

  MV::Pnt3 point(int i);

  void rotation(MV::Pnt3 p_rot);

  void orbitar();

  void translation(MV::Pnt3 p_desp_);

  void scale(MV::Pnt3 p_escala_);

  void inputs(Keys *keys);

  SDL_Color renderColorLight(MV::Pnt3 point, MV::Pnt3 light);

  SDL_Vertex renderSDLVertex(MV::Pnt3 light, MV::Pnt2 draw, MV::Pnt3 point);

  void draw(Keys *keys, SDL_Renderer *render, Render drawRender, MV::Pnt3 light, int drawCallback(SDL_Renderer*, SDL_Vertex*, const int));

  void imprime();

  ~Entity();
};

////////////////////////
// GUARDAS NO TOCAR
#endif /* entity_3d_h */
////////////////////////
