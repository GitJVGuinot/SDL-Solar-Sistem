/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Render.h
 * Class tgo render 3d in a 2d window.
 */

////////////////////////
#ifndef __RENDER_H__
#define __RENDER_H__ 1
////////////////////////

#include <SDL2/SDL.h>
#include <iostream>
#include <common_defs.h>
#include "math_utils.h"
#include "SDL_event_control.h"

struct Render_Vert
{
  SDL_Vertex point;
  bool active;
};

struct Render_Figure
{
  Render_Vert **verts;
  Vec3 *point;
  int n_points;
  Vec3 desp;
  Vec3 light;
  SDL_Color color;
  Mat3 model;
  bool forceRender = false;
};

class Render
{
public:
  Vec3 camera_;

  Render();

  void init(Vec2 max_win, Vec3 camera, float near = 1, float far = 1000);

  void reset(Vec2 max_win);

  void rotation(Vec3 rot);
  void translation(Vec3 desp);

  void inputs(Keys *keys);

  int *getOrder(Vec3 *objects_mov, Vec3 *objects_scale, int max_objects);

  void renderPoints(Render_Figure &figure, bool renderLight);
  void renderThreadedPoints(Render_Figure &figure, bool renderLight);
  void renderPoint(Render_Vert &ret_vert, Vec3 point, Vec3 desp, Vec3 light, SDL_Color color, Mat3 model, bool forceRender = false, bool renderLight = false );

  void cameraDraw(Keys *keys, SDL_Renderer *render, Vec2 max_win);

  Vec2 getRenderScale();
  float getFar();
  float getNear();

  Vec3 getUp();

private:
  int *draw_order_;
  Vec3 target_;
  Vec3 up_;
  Vec3 down_;
  Vec3 right_;
  Vec3 left_;
  Vec3 front_;
  Vec3 back_;
  int max_order_;
  float far_;
  float near_;
  Vec2 render_scale_;

  Vec3 faces_vector_[6];
  Vec3 faces_centers_[6];
  Vec3 paint_square_[4];
  Vec3 render_centers_;

  int current_threads_;

  bool active(Vec3 point);
};

/////////////////////////
#endif /* __RENDER_H__ */
/////////////////////////
