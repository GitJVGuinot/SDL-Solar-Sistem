/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

/// @file Cube_3d.h

////////////////////////
#ifndef __CUBE_3D_H__
#define __CUBE_3D_H__ 1
////////////////////////

#include <entity_3d.h>

/**
 * @class To define a Cube.
 *
 * @brief Makes a Cube based on Entity.
 */
class Cube : public Entity
{
private:
  /**
   * @brief Function to create a cube based on Entity.
   */
  void obtainCube();

public:
  /**
   * @brief Does nothing.
   */
  Cube(){};

  /**
   * @brief Initializes a Cube with all its parameters.
   *
   * @param color Sets the fill colour of the Cube.
   * @param fill Sets the fill colour of the Cube.
   * @param scale Sets the initial scale of the Cube.
   * @param mov Sets the initial offset of the Cube.
   * @param rot Sets the initial rotation of the Cube.
   * @param orbit Sets the initial orbit of the Cube.
   * @param orbit_center Sets the starting point of the Cube's orbit.
   *
   * @return Always returns 0.
   */
  int init(SDL_Color color, bool fill = false, Vec3 scale = {1, 1, 1}, Vec3 mov = {0, 0, 0}, Vec3 rot = {0, 0, 0}, Vec3 orbit = {0, 0, 0}, Vec3 orbit_center = {0, 0, 0});

  /**
   * @brief Function created to demostrate virtual inheritance.
   */
  void print ();

  /**
   * @brief Destructor of the Cube.
   */
  ~Cube(){};
};

////////////////////////
#endif /* __CUBE_3D_H__ */
////////////////////////
