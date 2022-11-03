#include <SDL2/SDL.h>
#include <iostream>
#include <mv_math.h>
#include <SDL_event_control.h>
#include <SDL_colors.h>

#ifndef RGBA
#define RGBA(x) x.r, x.g, x.b, x.a
#endif

////////////////////////
// GUARDAS NO TOCAR
#ifndef esfera_3d_h
#define esfera_3d_h
////////////////////////

class Esfera
{
private:
    MV::Pnt3 escala_;
    MV::Pnt3 rotado_;

    int res_;
    MV::Pnt3 *points_;
    MV::Pnt3 *centros_;
    SDL_Vertex *draw_sdl_;

    struct Caras
    {
        int n_points;
        int *points;
    };
    Caras *caras;

    // Obtiene los puntos de la esfera
    void obtenerEsfera();

public:
    float dim_;
    int vertices_;
    MV::Pnt3 desp_;
    MV::Pnt3 orbita_;
    MV::Pnt3 centro_orbita_;
    SDL_Color color_;

    // Inicializa la esfera
    Esfera(SDL_Color color, int p_res_ = 50, MV::Pnt3 p_escala_ = {1, 1, 1}, MV::Pnt3 p_desp_ = {0, 0, 0}, MV::Pnt3 p_rot = {0, 0, 0}, MV::Pnt3 p_orbita_ = {0, 0, 0}, MV::Pnt3 centro_orbita = {0, 0, 0});

    MV::Pnt3 point(int i);

    void rotar(MV::Pnt3 p_rot);

    void orbitar(float vel);

    void desplazar(MV::Pnt3 p_desp_);

    void escalar(MV::Pnt3 p_escala_);

    void inputs(Keys *keys);

    SDL_Color obtenerColorLight(MV::Pnt3 point, MV::Pnt3 light);

    SDL_Vertex obtenerSDLVertex(MV::Pnt3 light, MV::Pnt2 draw, MV::Pnt3 point);

    void draw(SDL_Renderer *render, MV::Pnt3 camara /* Ubicacion de la camara */, MV::Pnt3 mira, MV::Pnt3 light = {0, 0, 0}, bool puntos = true);

    void imprime();
};

////////////////////////
// GUARDAS NO TOCAR
#endif /* esfera_3d_h */
////////////////////////
