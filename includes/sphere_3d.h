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

  int init(SDL_Color color, bool fill = false, int p_res_ = 10, MV::Pnt3 p_escala_ = {1, 1, 1}, MV::Pnt3 p_desp_ = {0, 0, 0}, MV::Pnt3 p_rot = {0, 0, 0}, MV::Pnt3 p_orbita_ = {0, 0, 0}, MV::Pnt3 centro_orbita = {0, 0, 0});

  ~Sphere();
};

////////////////////////
// GUARDAS NO TOCAR
#endif /* sphere_3d_h */
////////////////////////
