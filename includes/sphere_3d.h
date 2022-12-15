/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Sphere_3d.h
 * Class to define a sphere.
 * Makes a sphere based in Entity.
 */

////////////////////////
#ifndef __SPHERE_3D_H__
#define __SPHERE_3D_H__ 1
////////////////////////

#include <entity_3d.h>

class Sphere : public Entity
{
private:
  // Gets the points for Entity.
  void obtenerSphere();

public:
  Sphere(){};

  int init(SDL_Color color, bool fill = false, int res = 10, Vec3 scale = {1, 1, 1}, Vec3 mov = {0, 0, 0}, Vec3 rot = {0, 0, 0}, Vec3 orbit = {0, 0, 0}, Vec3 orbit_center = {0, 0, 0});

  ~Sphere(){};
};

////////////////////////
#endif /* __SPHERE_3D_H__ */
////////////////////////
