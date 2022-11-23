#include <entity_3d.h>

////////////////////////
// GUARDAS NO TOCAR
#ifndef esfera_3d_h
#define esfera_3d_h
////////////////////////

class Esfera : public Entity {
private:
  // Obtiene los puntos de la entity
  void obtenerEsfera();
public:
  Esfera(){};

  int init(SDL_Color color, bool fill = false, int p_res_ = 10, MV::Pnt3 p_escala_ = {1, 1, 1}, MV::Pnt3 p_desp_ = {0, 0, 0}, MV::Pnt3 p_rot = {0, 0, 0}, MV::Pnt3 p_orbita_ = {0, 0, 0}, MV::Pnt3 centro_orbita = {0, 0, 0});

  ~Esfera();
};

////////////////////////
// GUARDAS NO TOCAR
#endif /* esfera_3d_h */
////////////////////////
