#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstring>
#include <cfloat>
#include <mv_math.h>
#include <SDL_event_control.h>
#include <SDL_colors.h>

#include <render.h>
#include <esfera_3d.h>
#include <my_window.h>

int k_TextHeight = 28;
int k_TextWitdh = ((float)(k_TextHeight*4/7)-1);
int g_Filas = 30;
int g_Columnas = 85;

#ifndef RGBA
#define RGBA(x) x.r,x.g,x.b,x.a
#endif

#define FONT_PATH "../data/fonts/anonymous_pro.ttf"
#define FONT_PATH_1 "/usr/share/fonts/truetype/lao/Phetsarath_OT.ttf"

MV::Pnt2 max_win = {(float)(k_TextWitdh * g_Columnas), (float)(k_TextHeight *g_Filas)};
MV::Pnt2 middle_win = {max_win.x / 2, max_win.y / 2};
MV::Pnt2 min_win = {0, 0};

SDL_Color colores[MAX_COLORS] = {
  SDL_Color{255, 000, 000, SDL_ALPHA_OPAQUE},    // ROJO

  SDL_Color{000, 255, 000, SDL_ALPHA_OPAQUE},    // VERDE

  SDL_Color{000, 000, 255, SDL_ALPHA_OPAQUE},    // AZUL

  SDL_Color{000, 255, 255, SDL_ALPHA_TRANSPARENT},    // CYAN

  SDL_Color{255, 000, 255, SDL_ALPHA_OPAQUE},    // MAGENTA

  SDL_Color{255, 255, 000, SDL_ALPHA_OPAQUE},    // AMARILLO

  SDL_Color{255, 255, 255, SDL_ALPHA_OPAQUE},    // BLANCO
  SDL_Color{127, 127, 127, SDL_ALPHA_OPAQUE},    // GRIS
  SDL_Color{000, 000, 000, SDL_ALPHA_OPAQUE},    // NEGRO
};


int main(int argc, char **argv)
{

  srand(time(nullptr));

  Keys keys[MAX_INPUTS];

  InitKeyboard(keys);

  // Inicializacion de los servicios de SDL
  TTF_Init();
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    std::cout << "Failed at SDL_Init(): " << SDL_GetError() << std::endl;
    return -1;
  }

  // Inicializacion ventana de juego
  My_Window win = *new My_Window(k_TextHeight, k_TextWitdh, g_Filas, g_Columnas);
  if (!win.setTextFont((char *)FONT_PATH))
  {
    std::cout << "Failed at TTF_Font_Init(): " << SDL_GetError() << std::endl;
    return -1;
  }
  win.setGameTitle(*argv);

  const int max_planets = 5;
  Esfera *planet=(Esfera*)calloc(max_planets, sizeof(Esfera));

  // 0 -> planet[0], 1 - 4 -> Planets
  std::cout << "Generando planetas..." << std::endl;
  planet[0].init(colores[BLANCO], 10, {30,30,30}, {middle_win.x, middle_win.y, 0.0f});
  planet[1].init(colores[0], 10, {5, 5, 5}, {(planet + 0)->desp_.x - 40, (planet + 0)->desp_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.01f, 0.0f}, (planet + 0)->desp_);
  planet[2].init(colores[1], 10, {5, 5, 5}, {(planet + 0)->desp_.x, (planet + 0)->desp_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.0f, 0.0f}, (planet + 0)->desp_);
  planet[3].init(colores[2], 10, {5, 5, 5}, {(planet + 0)->desp_.x - 60, (planet + 0)->desp_.y, 0.0f}, {0, 0, 0}, {0.0f, 0.01f, 0.0f}, (planet + 0)->desp_);
  planet[4].init(colores[3], 10, {5, 5, 5}, {(planet + 0)->desp_.x + 60, (planet + 0)->desp_.y + 60, 0.0f}, {0, 0, 0}, {0.01f, -0.01f, 0.0f}, (planet + 0)->desp_);
  std::cout << "Planetas generados" << std::endl;

  // Imprimir en pantalla los datos de la ventana
  std::cout << "WIN_X: " << max_win.x << ", WIN_Y: " << max_win.y << std::endl;
  std::cout << "HEIGHT: " << k_TextHeight << ", WIDTH: " << k_TextWitdh << ", g_Filas: " << g_Filas << ", g_Columnas: " << g_Columnas << std::endl;

  MV::Pnt3 light = (planet + 0)->desp_;

  float far = 1000, near = 5;
  Render drawRender(max_win, {middle_win.x,middle_win.y,100}, near, far, max_planets);
  MV::Pnt3 *object_desp=(MV::Pnt3*)calloc(max_planets,sizeof(MV::Pnt3));

  while (win.runing)
  {
    win.whileInit(keys);

    (planet + 0)->rotar({fRand(0.0075f,0),fRand(0.0075f,0), fRand(0.0075f,0)});
    for (int i = 1; i < max_planets; i++)
    {
      (planet + i)->orbitar(10.0f);
    }

    drawRender.inputs(keys);

    for(int i = 0; i<max_planets; i++){
      object_desp[i]=planet[i].desp_;
    }

    int *order = drawRender.getOrder(object_desp, max_planets);

    for(int i=0; i<max_planets; i++){
      if(EVENT_DOWN(K_p, keys)){
        std::cout << std::endl << "Drawing planet " << order[i] << std::endl;
      }
      (planet + order[i])->draw(keys, win.render, drawRender, light, false);
    }

    win.whileEnd(keys);
  }

  win.Destroy();
  TTF_Quit();
  SDL_Quit();

  return 0;
}
