/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

/** @file Cube_3d.h
 * Class to define a cube.
 * Makes a cube based in Entity.
 */

////////////////////////
#ifndef __CUBE_3D_H__
#define __CUBE_3D_H__ 1
////////////////////////

#include <entity_3d.h>

class Cube : public Entity
{
private:
  // Gets the entity points
  void obtainCube();

public:
  Cube(){};

  int init(SDL_Color color, bool fill = false, Vec3 scale = {1, 1, 1}, Vec3 mov = {0, 0, 0}, Vec3 rot = {0, 0, 0}, Vec3 orbit = {0, 0, 0}, Vec3 orbit_center = {0, 0, 0});

  ~Cube(){};
};

////////////////////////
#endif /* __CUBE_3D_H__ */
////////////////////////
