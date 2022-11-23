#include <entity_3d.h>

////////////////////////
// GUARDAS NO TOCAR
#ifndef cube_3d_h
#define cube_3d_h
////////////////////////

class Cube : public Entity {
private:
  // Obtiene los puntos de la entity
  void obtenerCube();
public:
  Cube(){};

  int init(SDL_Color color, bool fill = false, MV::Pnt3 scale = {1, 1, 1}, MV::Pnt3 mov = {0, 0, 0}, MV::Pnt3 rot = {0, 0, 0}, MV::Pnt3 orbit = {0, 0, 0}, MV::Pnt3 orbit_center = {0, 0, 0});

  ~Cube(){};
};

////////////////////////
// GUARDAS NO TOCAR
#endif /* cube_3d_h */
