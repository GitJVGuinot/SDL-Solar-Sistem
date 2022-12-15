/// @author Marcos Jiménez Saz <jimenezsa@esat-alumni.com>

////////////////////////
#ifndef __FIGURES_3D_H__
#define __FIGURES_3D_H__ 1
////////////////////////

#include "entity_3d.h"
#include <Obj_Loader/tiny_obj_loader.h>

class Figure : public Entity
{
private:
  void count_faces(const tinyobj::shape_t &shape);

  void load_triangles(const struct tinyobj::shape_t &shape, int &cont);

  int charger(const char *path);

public:
  Figure(){};

  int init(const char *path, SDL_Color color, bool fill = false, Vec3 scale = {1, 1, 1}, Vec3 mov = {0, 0, 0}, Vec3 rot = {0, 0, 0}, Vec3 orbit = {0, 0, 0}, Vec3 orbit_center = {0, 0, 0});

  ~Figure(){};
};

////////////////////////
#endif /* __FIGURES_3D_H__ */
////////////////////////
