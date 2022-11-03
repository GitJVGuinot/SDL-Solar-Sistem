#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstring>
#include <cfloat>
#include <mv_math.h>
#include <SDL_event_control.h>
#include <SDL_colors.h>

#include <esfera_3d.h>
#include <my_window.h>

int k_TextHeight = 28;
int k_TextWitdh = (k_TextHeight*4/7)-1;
int g_Filas = 30;
int g_Columnas = 85;

#ifndef RGBA
#define RGBA(x) x.r,x.g,x.b,x.a
#endif

#define FONT_PATH "../data/fonts/anonymous_pro.ttf"
#define FONT_PATH_1 "/usr/share/fonts/truetype/lao/Phetsarath_OT.ttf"

#define VEC3_PRINT(v) v.x<<", "<<v.y<<", "<<v.z

MV::Pnt2 max_win = {(float)(k_TextWitdh * g_Columnas), (float)(k_TextHeight *g_Filas)};
MV::Pnt2 middle_win = {max_win.x / 2, max_win.y / 2};
MV::Pnt2 min_win = {0, 0};

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

  int max_planets = 5;
  Esfera *planet = (Esfera *)calloc(max_planets, sizeof(Esfera));

  // 0 -> *(planet + 0), 1 - 4 -> Planets
  *(planet + 0) = *new Esfera(colores[BLANCO], 10, {30,30,30}, {middle_win.x, middle_win.y, 0.0f});
  *(planet + 1) = *new Esfera(colores[1], 10, {5, 5, 5}, {(planet + 0)->desp_.x - 40, (planet + 0)->desp_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.01f, 0.0f}, (planet + 0)->desp_);
  *(planet + 2) = *new Esfera(colores[2], 10, {5, 5, 5}, {(planet + 0)->desp_.x, (planet + 0)->desp_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.0f, 0.0f}, (planet + 0)->desp_);
  *(planet + 3) = *new Esfera(colores[3], 10, {5, 5, 5}, {(planet + 0)->desp_.x - 60, (planet + 0)->desp_.y, 0.0f}, {0, 0, 0}, {0.0f, 0.01f, 0.0f}, (planet + 0)->desp_);
  *(planet + 4) = *new Esfera(colores[4], 10, {5, 5, 5}, {(planet + 0)->desp_.x + 60, (planet + 0)->desp_.y + 60, 0.0f}, {0, 0, 0}, {0.01f, -0.01f, 0.0f}, (planet + 0)->desp_);

  // Imprimir en pantalla los datos de la ventana
  std::cout << "WIN_X: " << max_win.x << ", WIN_Y: " << max_win.y << std::endl;
  std::cout << "HEIGHT: " << k_TextHeight << ", WIDTH: " << k_TextWitdh << ", g_Filas: " << g_Filas << ", g_Columnas: " << g_Columnas << std::endl;

  MV::Pnt3 camara = {middle_win.x, middle_win.y, 100.0f};
  MV::Pnt3 light = (planet + 0)->desp_;
  MV::Pnt3 mira = (planet + 0)->desp_;
  int *draw_order=(int*)calloc(max_planets, sizeof(int));
  while (win.runing)
  {
    win.whileInit(keys);

    (planet + 0)->rotar({fRand(0.0075f,0),fRand(0.0075f,0), fRand(0.0075f,0)});
    for (int i = 1; i < max_planets; i++)
    {
      (planet + i)->orbitar(10.0f);
    }

    if (EVENT_DOWN(DOWN, keys)){ Orbitar_Punto(mira, MV::Vec3{1, 0, 0}, camara); }
    if (EVENT_DOWN(UP, keys)){ Orbitar_Punto(mira, MV::Vec3{-1, 0, 0}, camara); }
    if (EVENT_DOWN(RIGHT, keys)){ Orbitar_Punto(mira, MV::Vec3{0, 1, 0}, camara); }
    if (EVENT_DOWN(LEFT, keys)){ Orbitar_Punto(mira, MV::Vec3{0, -1, 0}, camara); }
    if (EVENT_DOWN(K_n, keys)){ Orbitar_Punto(mira, MV::Vec3{0, 0, 1}, camara); }
    if (EVENT_DOWN(K_m, keys)){ Orbitar_Punto(mira, MV::Vec3{0, 0, -1}, camara); }


    if (EVENT_DOWN(K_a, keys)){
      camara.x--;
    }
    if (EVENT_DOWN(K_d, keys)){
      camara.x++;
    }
    if (EVENT_DOWN(K_w, keys)){
      camara.y--;
    }
    if (EVENT_DOWN(K_s, keys)){
      camara.y++;
    }
    if (EVENT_DOWN(K_q, keys)){
      camara.z--;
    }
    if (EVENT_DOWN(K_e, keys)){
      camara.z++;
    }

    // Draw Planets ir order
    for(int i=0; i<max_planets; i++){
      draw_order[i]=i;
    }

    for (int i = 0; i < max_planets; i++)
    {
      for (int j = 1; j < max_planets; j++)
      {
        if (MV::Vec_Magn(MV::Vec_Resta(planet[draw_order[i]].desp_,camara)) >= MV::Vec_Magn(MV::Vec_Resta(planet[draw_order[j]].desp_,camara)))
        {
          int aux = draw_order[i];
          draw_order[i] = draw_order[j];
          draw_order[j] = aux;
        }
      }
    }

    for(int i=0; i<max_planets-1; i++){
      int aux=draw_order[i];
      draw_order[i]=draw_order[i+1];
      draw_order[i+1]=aux;
    }

    if(EVENT_DOWN(K_p, keys)){
      std::cout << std::endl;
      std::cout << "Camera: " << VEC3_PRINT(camara) << std::endl;
      for(int i = 0; i<max_planets; i++){
        std::cout << "Order[" << i << "] = " << draw_order[i] << std::endl;
        std::cout << "Distancia a camara: " << MV::Vec_Magn(MV::Vec_Resta(planet[draw_order[i]].desp_,camara)) << std::endl;
      }
      std::cout << std::endl;
    }

    for(int i=0; i<max_planets; i++){
      (planet + draw_order[i])->draw(win.render, camara, mira, light, false);
    }

    win.whileEnd(keys);
  }

  win.Destroy();
  TTF_Quit();
  SDL_Quit();

  return 0;
}
