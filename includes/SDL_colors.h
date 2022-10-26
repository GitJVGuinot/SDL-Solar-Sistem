#include <SDL2/SDL.h>

/////////////////////////
// Guardas, NO TOCAR
#ifndef SDL_colors_h
#define SDL_colors_h
/////////////////////////

#define RGBA(x) x.r,x.g,x.b,x.a

const int ROJO = 0;
const int VERDE = 1;
const int AZUL = 2;
const int CYAN = 3;
const int MAGENTA = 4;
const int AMARILLO = 5;
const int BLANCO = 6;
const int GRIS = 7;
const int NEGRO = 8;

const int MAX_COLORS = 9;
SDL_Color colores[MAX_COLORS] = {
  {255, 000, 000, SDL_ALPHA_OPAQUE},    // ROJO

  {000, 255, 000, SDL_ALPHA_OPAQUE},    // VERDE

  {000, 000, 255, SDL_ALPHA_OPAQUE},    // AZUL

  {000, 255, 255, SDL_ALPHA_OPAQUE},    // CYAN

  {255, 000, 255, SDL_ALPHA_OPAQUE},    // MAGENTA

  {255, 255, 000, SDL_ALPHA_OPAQUE},    // AMARILLO

  {255, 255, 255, SDL_ALPHA_OPAQUE},    // BLANCO
  {127, 127, 127, SDL_ALPHA_OPAQUE},    // GRIS
  {000, 000, 000, SDL_ALPHA_OPAQUE},    // NEGRO
};

/////////////////////////
// Guardas, NO TOCAR
#endif /* SDL_colors_h */
// Guardas, NO TOCAR
/////////////////////////
