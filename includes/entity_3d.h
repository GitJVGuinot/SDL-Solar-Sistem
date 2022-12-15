/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Entity_3d.h
 * Class to define an object.
 */

////////////////////////
#ifndef __ENTITY_3D_H__
#define __ENTITY_3D_H__ 1
////////////////////////

#include <SDL2/SDL.h>
#include <iostream>
#include <math_utils.h>
#include <SDL_event_control.h>
#include <common_defs.h>
#include <render.h>

struct Faces
{
  int n_points;
  int *points;
};

class Entity
{
protected:
  Vec3 scale_;
  Vec3 rotate_;

  int res_;
  int vertex_;
  Vec3 *points_;
  Vec3 *centers_;

  Render_Vert *draw_sdl_;

  Faces *faces_;
  int nFaces_;

  int *order_;

  int bytesSize;

public:
  float dim_;
  Vec3 mov_;
  Vec3 orbit_;
  Vec3 orbit_center_;
  bool renderLight_;
  SDL_Color fillColor_;
  SDL_Color linesColor_;
  bool fill_;
  bool lines_;
  float orbit_vel_;

  // Init entity
  Entity();

  void operator=(const Entity &other);

  void proportion();
  void centered();
  void standarize();

  Vec3 point(int position);

  Vec3 getScale();

  int getFaces();

  int getSize();

  void rotation(Vec3 rot);

  void orbit();

  void translation(Vec3 mov);

  void scale(Vec3 scale);

  void inputs(Keys *keys);

  SDL_Color renderColorLight(Vec3 point, Vec3 light);

  SDL_Vertex renderSDLVertex(Vec3 light, Vec2 draw, Vec3 point);

  void draw(Keys *keys, SDL_Renderer *render, Render drawRender, Vec3 light, int id = 0);

  ~Entity();
};

////////////////////////
#endif /* __ENTITY_3D_H__ */
////////////////////////
