/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

/** @file Objects.h
 * Structure for grouping entities.
 * Enums for grouping entities.
 */

////////////////////////
#ifndef __OBJECTS_H__
#define __OBJECTS_H__ 1
////////////////////////

#include <sphere_3d.h>
#include <cube_3d.h>
#include <figures_3d.h>

struct Objects
{
  int type;
  class Sphere sphere;
  class Cube cube;
  class Figure figure;
  // class ...
};

#define MAX_OBJECTS_TYPE 4
enum ObjectsType
{
  notSet = 0,
  typeSphere,
  typeCube,
  typeFigure,
  // ...
};

void Not_Set_Controls(Objects &objects);
void Spheres_Controls(Sphere &sphere);
void Cubes_Controls(Cube &cube);
void Figures_Controls(Figure &figure);

////////////////////////
#endif /* __OBJECTS_H__ */
////////////////////////
