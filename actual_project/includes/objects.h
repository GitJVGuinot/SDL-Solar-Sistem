/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

/// @file Objects.h

////////////////////////
#ifndef __OBJECTS_H__
#define __OBJECTS_H__ 1
////////////////////////

#include <sphere_3d.h>
#include <cube_3d.h>
#include <figures_3d.h>

/**
* @struct Objects.
*
* @brief For grouping entities childs.
*/
struct Objects
{
  int type; ///< Used to select the object type, it is define in enum ObjectsType.
  class Sphere sphere; ///< Object Sphere.
  class Cube cube; ///< Object Cube.
  class Figure figure; ///< Object Figure.
  // class ...
};

#define MAX_OBJECTS_TYPE 4

/**
* @enum The objectstype for.
*
* @brief Enums the types that an object can be.
*/
enum ObjectsType
{
  notSet = 0,
  typeSphere,
  typeCube,
  typeFigure,
  // ...
};

/**
 * @brief Adds an empty object to the list.
 *
 * @param objects Passes an object in the last position.
 */
void Not_Set_Controls(Objects &objects);

/**
 * @brief Modifies the Sphere created.
 *
 * @param sphere Sphere to be modified.
 */
void Spheres_Controls(Sphere &sphere);

/**
 * @brief Modifies the Cube created.
 *
 * @param cube Cube to be modified.
 */
void Cubes_Controls(Cube &cube);

/**
 * @brief Modifies the Figure created.
 *
 * @param figure Figure to be modified.
 */
void Figures_Controls(Figure &figure);

////////////////////////
#endif /* __OBJECTS_H__ */
////////////////////////
