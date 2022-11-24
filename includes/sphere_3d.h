#include <entity_3d.h>

////////////////////////
// GUARDAS NO TOCAR
#ifndef sphere_3d_h
#define sphere_3d_h
////////////////////////

class Sphere : public Entity {
private:
  // Obtiene los puntos de la entity
  void obtenerSphere();
public:
  Sphere(){};

  int init(SDL_Color color, bool fill = false, int res = 10, MV::Pnt3 scale = {1, 1, 1}, MV::Pnt3 mov = {0, 0, 0}, MV::Pnt3 rot = {0, 0, 0}, MV::Pnt3 orbit = {0, 0, 0}, MV::Pnt3 orbit_center = {0, 0, 0});

  ~Sphere(){};
};

////////////////////////
// GUARDAS NO TOCAR
#endif /* sphere_3d_h */
////////////////////////
