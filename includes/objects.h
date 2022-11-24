#ifndef objects_h
#define objects_h

#include <sphere_3d.h>
#include <cube_3d.h>

struct Objects{
  int type;
  class Sphere sphere;
  class Cube cube;
};

#define MAX_OBJECTS_TYPE 3
enum ObjectsType{
  notSet = 0,
  typeSphere,
  typeCube,
  // ...
};

void Not_Set_Controls(Objects &objects);
void Spheres_Controls(Objects &objects);
void Cubes_Controls(Objects &objects);


#endif /* objects_h */
