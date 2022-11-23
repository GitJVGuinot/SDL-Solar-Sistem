#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <cstring>
#include <cfloat>
#include <common_defs.h>
#include <mv_math.h>
#include <SDL_event_control.h>

#include <render.h>
#include <entity_3d.h>
#include <sphere_3d.h>
#include <cube_3d.h>
#include <my_window.h>
#include <debug_window.h>

int k_TextHeight = 28;
int k_TextWitdh = ((float)(k_TextHeight * 4 / 7) - 1);
int g_Filas = 30;
int g_Columnas = 80;

MV::Pnt2 max_win = {(float)(k_TextWitdh * g_Columnas), (float)(k_TextHeight *g_Filas)};
MV::Pnt2 middle_win = {max_win.x / 2, max_win.y / 2};
MV::Pnt2 min_win = {0, 0};

SDL_Color colores[MAX_COLORS] = {
    SDL_Color{255, 000, 000, SDL_ALPHA_OPAQUE}, // RED

    SDL_Color{000, 255, 000, SDL_ALPHA_OPAQUE}, // GREEN

    SDL_Color{000, 000, 255, SDL_ALPHA_OPAQUE}, // BLUE

    SDL_Color{000, 255, 255, SDL_ALPHA_TRANSPARENT}, // CYAN

    SDL_Color{255, 000, 255, SDL_ALPHA_OPAQUE}, // MAGENTA

    SDL_Color{255, 255, 000, SDL_ALPHA_OPAQUE}, // YELLOW

    SDL_Color{255, 255, 255, SDL_ALPHA_OPAQUE}, // WHITE
    SDL_Color{127, 127, 127, SDL_ALPHA_OPAQUE}, // GREY
    SDL_Color{000, 000, 000, SDL_ALPHA_OPAQUE}, // BLACK
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
  My_Window win = *new My_Window(k_TextHeight, k_TextWitdh, g_Filas, g_Columnas, colores[BLACK]);
  if (!win.setTextFont((char *)FONT_PATH))
  {
    std::cout << "Failed at TTF_Font_Init(): " << SDL_GetError() << std::endl;
    return -1;
  }
  win.setGameTitle(*argv);

  // Inicializacion de ImGui
  Debug_Window::Init(win.window, win.render);

  int max_planets = 5;
  Sphere *planet = (Sphere *)calloc(max_planets, sizeof(Entity));

  // 0 -> planet[0], 1 - 4 -> Planets
  std::cout << "Sizeof Entity: " << sizeof(Sphere) << std::endl;

  std::cout << "Generando planetas..." << std::endl;
  planet[0].init(colores[WHITE], false, 50, {12, 12, 12}, {middle_win.x, middle_win.y, 0.0f});
  planet[1].init(colores[0], true, 10, {2, 2, 2}, {(planet + 0)->mov_.x - 40, (planet + 0)->mov_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.01f, 0.0f}, (planet + 0)->mov_);
  planet[2].init(colores[1], true, 10, {2, 2, 2}, {(planet + 0)->mov_.x, (planet + 0)->mov_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.0f, 0.0f}, (planet + 0)->mov_);
  planet[3].init(colores[3], true, 10, {2, 2, 2}, {(planet + 0)->mov_.x + 60, (planet + 0)->mov_.y + 60, 0.0f}, {0, 0, 0}, {0.01f, -0.01f, 0.0f}, (planet + 0)->mov_);
  planet[4].init(colores[2], true, 10, {2, 2, 2}, {(planet + 0)->mov_.x - 60, (planet + 0)->mov_.y, 0.0f}, {0, 0, 0}, {0.0f, 0.01f, 0.0f}, (planet + 0)->mov_);
  std::cout << "Planetas generados" << std::endl;

  // Imprimir en pantalla los datos de la ventana
  std::cout << "WIN_X: " << max_win.x << ", WIN_Y: " << max_win.y << std::endl;
  std::cout << "HEIGHT: " << k_TextHeight << ", WIDTH: " << k_TextWitdh << ", g_Filas: " << g_Filas << ", g_Columnas: " << g_Columnas << std::endl;

  MV::Pnt3 light = (planet + 0)->mov_;

  // Inicializacion del render 3D
  Render drawRender;
  drawRender.init(max_win, {middle_win.x, middle_win.y, 100});

  MV::Pnt3 *object_mov = nullptr;
  object_mov = (MV::Pnt3 *)realloc(object_mov, max_planets * sizeof(MV::Pnt3));

  // Cube cube;
  // cube.init(colores[WHITE], true, {5,5,5}, {(planet + 0)->mov_.x - 40, (planet + 0)->mov_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.01f, 0.0f}, (planet + 0)->mov_);
  // cube.orbit_vel_=10.0f;

  while (win.runing)
  {
    win.whileInit(keys);
    Debug_Window::Update();

    for (int i = 0; i < max_planets; i++)
      (planet + i)->orbitar();

    // cube.orbitar();

    drawRender.inputs(keys);

    for (int i = 0; i < max_planets; i++)
      object_mov[i] = planet[i].mov_;

    int *order = drawRender.getOrder(object_mov, max_planets);

    for (int i = 0; i < max_planets; i++)
    {
      if (EVENT_DOWN(K_p, keys))
      {
        std::cout << std::endl
                  << "Drawing planet " << order[i] << std::endl;
      }
      (planet + order[i])->draw(keys, win.render, drawRender, light, nullptr);
    }

    // cube.draw(keys, win.render, drawRender, light, nullptr);
    drawRender.cameraDraw(keys, win.render, {win.win_x, win.win_y});

    Camera_Control("Camera controls", drawRender, win, {win.win_x, win.win_y});
    Planets_Control("Planets controls", &planet, &object_mov, max_planets, {win.win_x, win.win_y});

    Debug_Window::Render();
    win.whileEnd(keys);
  }

  win.Destroy();
  TTF_Quit();
  SDL_Quit();
  Debug_Window::Quit();

  return 0;
}
