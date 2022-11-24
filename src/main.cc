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
#include <objects.h>
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

  std::vector <struct Objects>objects(6);

  for(int i=0; i<5; i++) objects.at(i).type=typeSphere;

  // 0 -> planet[0], 1 - 4 -> Planets
  std::cout << "Sizeof Entity: " << sizeof(Sphere) << std::endl;

  std::cout << "Generando planetas..." << std::endl;
  objects.at(0).sphere.init(colores[WHITE], false, 50, {12, 12, 12}, {middle_win.x, middle_win.y, 0.0f});
  objects.at(1).sphere.init(colores[0], true, 10, {2, 2, 2}, {objects.at(0).sphere.mov_.x - 40, objects.at(0).sphere.mov_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.01f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(2).sphere.init(colores[1], true, 10, {2, 2, 2}, {objects.at(0).sphere.mov_.x, objects.at(0).sphere.mov_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.0f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(3).sphere.init(colores[3], true, 10, {2, 2, 2}, {objects.at(0).sphere.mov_.x + 60, objects.at(0).sphere.mov_.y + 60, 0.0f}, {0, 0, 0}, {0.01f, -0.01f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(4).sphere.init(colores[2], true, 10, {2, 2, 2}, {objects.at(0).sphere.mov_.x - 60, objects.at(0).sphere.mov_.y, 0.0f}, {0, 0, 0}, {0.0f, 0.01f, 0.0f}, objects.at(0).sphere.mov_);
  for(int i=1; i<5; i++) objects.at(i).sphere.orbit_vel_=10.0f;
  objects.at(5).type=typeCube;
  objects.at(5).cube.init(colores[WHITE], true, {5,5,5}, {objects.at(0).sphere.mov_.x - 40, objects.at(0).sphere.mov_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.01f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(5).cube.orbit_vel_=10.0f;
  std::cout << "Planetas generados" << std::endl;

  // Imprimir en pantalla los datos de la ventana
  std::cout << "WIN_X: " << max_win.x << ", WIN_Y: " << max_win.y << std::endl;
  std::cout << "HEIGHT: " << k_TextHeight << ", WIDTH: " << k_TextWitdh << ", g_Filas: " << g_Filas << ", g_Columnas: " << g_Columnas << std::endl;

  MV::Pnt3 light = objects.at(0).sphere.mov_;

  // Inicializacion del render 3D
  Render drawRender;
  drawRender.init(max_win, {middle_win.x, middle_win.y, 100});

  MV::Pnt3 *object_mov = nullptr;
  object_mov = (MV::Pnt3 *)realloc(object_mov, objects.size() * sizeof(MV::Pnt3));


  while (win.runing)
  {
    win.whileInit(keys);
    Debug_Window::Update();

    drawRender.inputs(keys);

    for (int i = 0; i < objects.size(); i++){
      switch (objects.at(i).type) {
        case typeSphere:
          objects.at(i).sphere.orbitar();
          break;
        case typeCube:
          objects.at(i).cube.orbitar();
          break;
      }
    }

    for (int i = 0; i < objects.size(); i++){
      switch (objects.at(i).type) {
        case typeSphere:
          object_mov[i] = objects.at(i).sphere.mov_;
          break;
        case typeCube:
          object_mov[i] = objects.at(i).cube.mov_;
          break;
      }
    }

    int *order = drawRender.getOrder(object_mov, objects.size());

    for (int i = 0; i < objects.size(); i++)
    {
      switch (objects.at(order[i]).type) {
        case typeSphere:
          objects.at(order[i]).sphere.draw(keys, win.render, drawRender, light, nullptr);
          break;
        case typeCube:
          objects.at(order[i]).cube.draw(keys, win.render, drawRender, light, nullptr);
          break;
      }
    }

    drawRender.cameraDraw(keys, win.render, {win.win_x, win.win_y});

    Camera_Control(drawRender, win, {win.win_x, win.win_y});
    Objects_Control(objects, &object_mov, max_win);

    Debug_Window::Render();
    win.whileEnd(keys);
  }

  win.Destroy();
  TTF_Quit();
  SDL_Quit();
  Debug_Window::Quit();

  return 0;
}
