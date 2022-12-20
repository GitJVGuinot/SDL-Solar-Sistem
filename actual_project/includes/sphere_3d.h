/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>
/// @file Sphere_3d.h

////////////////////////
#ifndef __SPHERE_3D_H__
#define __SPHERE_3D_H__ 1
////////////////////////

#include <entity_3d.h>

class Sphere : public Entity
{
private:

  /**
   *  @brief Obtains the sphere points.
   */
  void obtainSphere();

public:

  /**
   *  @brief Constructor for the Sphere class.
   */
  Sphere(){};

  /**
   *  @brief Initializes the sphere.
   *
   *  @param color An SDL_Color object representing the color of the sphere.
   *  @param fill A boolean value indicating whether the sphere should be filled or not.
   *  @param res An integer representing the resolution of the sphere.
   *  @param scale A Vec3 object representing the scale of the sphere.
   *  @param mov A Vec3 object representing the movement of the sphere.
   *  @param rot A Vec3 object representing the rotation of the sphere.
   *  @param orbit A Vec3 object representing the orbit of the sphere.
   *  @param orbit_center A Vec3 object representing the center of the sphere's orbit.
   *
   *  @return An integer indicating the success or failure of the initialization.
   */
  int init(SDL_Color color, bool fill = false, int res = 10, Vec3 scale = {1, 1, 1}, Vec3 mov = {0, 0, 0}, Vec3 rot = {0, 0, 0}, Vec3 orbit = {0, 0, 0}, Vec3 orbit_center = {0, 0, 0});

  void print();

  /**
   *  @brief Destructor for the Sphere class.
   */
  ~Sphere(){};
};

////////////////////////
#endif /* __SPHERE_3D_H__ */
////////////////////////
