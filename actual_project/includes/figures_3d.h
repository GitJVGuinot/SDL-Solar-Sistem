/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

/// @file Figures_3d.h

////////////////////////
#ifndef __FIGURES_3D_H__
#define __FIGURES_3D_H__ 1
////////////////////////

#include "entity_3d.h"
#include <Obj_Loader/tiny_obj_loader.h>

/**
 * @class To define a Figure.
 *
 * @brief Makes a Figure based on Entity.
 */
class Figure : public Entity
{
private:
  /**
   * @brief Count the faces of the Figure.
   *
   * @param shape Pass the shape of each face of the figure to count it.
   */
  void count_faces(const tinyobj::shape_t &shape);

  /**
   * @brief Load the triangles in Figure.
   *
   * @param shape Used to set the Figure face.
   * @param cont To set each side.
   */
  void load_triangles(const struct tinyobj::shape_t &shape, int &cont);

  /**
   * @brief Load the Figure.
   *
   * @param path Get the location of the file in the Figure.
   *
   * @return 1 File not found.
   * @return 0 Everything went OK.
   */
  int charger(const char *path);

public:
  /**
   * @brief Does nothing.
   */
  Figure(){};

  /**
   * @brief Initializes a Figure with all its parameters.
   *
   * @param path Sets the Figure path.
   * @param color Sets the fill colour of the Figure.
   * @param fill Sets the fill colour of the Figure.
   * @param scale Sets the initial scale of the Figure.
   * @param mov Sets the initial offset of the Figure.
   * @param rot Sets the initial rotation of the Figure.
   * @param orbit Sets the initial orbit of the Figure.
   * @param orbit_center Sets the starting point of the Figure's orbit.
   *
   * @return 1 Error: Creating Figure.
   * @return 0 Figure created.
   */
  int init(const char *path, SDL_Color color, bool fill = false, Vec3 scale = {1, 1, 1}, Vec3 mov = {0, 0, 0}, Vec3 rot = {0, 0, 0}, Vec3 orbit = {0, 0, 0}, Vec3 orbit_center = {0, 0, 0});

  /**
   * @brief Function created to demostrate virtual inheritance.
   */
  void print ();

  /**
   * @brief Destructor of the Figure.
   */
  ~Figure(){};
};

////////////////////////
#endif /* __FIGURES_3D_H__ */
////////////////////////
