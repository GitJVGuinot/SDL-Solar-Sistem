#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <cstring>
#include <cfloat>
#include <common_defs.h>
#include <SDL_event_control.h>

#include <render.h>
#include <objects.h>
#include <my_window.h>
#include <debug_window.h>

const int k_TextHeight = 28;
const int k_TextWitdh = ((float)(k_TextHeight * 4 / 7) - 1);
const int k_Filas = 30;
const int k_Columnas = 80;

MV::Pnt2 max_win = {(float)(k_TextWitdh * k_Columnas), (float)(k_TextHeight * k_Filas)};
MV::Pnt2 middle_win = {max_win.x / 2, max_win.y / 2};
MV::Pnt2 min_win = {0, 0};

SDL_Color colores[MAX_COLORS] = {
    SDL_Color{255, 000, 000, 255}, // RED

    SDL_Color{000, 255, 000, 255}, // GREEN

    SDL_Color{000, 000, 255, 255}, // BLUE

    SDL_Color{000, 255, 255, 255}, // CYAN

    SDL_Color{255, 000, 255, 255}, // MAGENTA

    SDL_Color{255, 255, 000, 255}, // YELLOW

    SDL_Color{255, 255, 255, 255}, // WHITE
    SDL_Color{127, 127, 127, 255}, // GREY
    SDL_Color{000, 000, 000, 255}, // BLACK
};

void Basic_Objects_Init(std::vector <struct Objects>&objects, MV::Pnt3& light, Render& drawRender, MV::Pnt3** objects_mov, MV::Pnt3** objects_scale){
  std::cout << "Sizeof Entity: " << sizeof(struct Entity) << std::endl;

  std::cout << "Generando planetas..." << std::endl;
  for(int i=0; i<5; i++) objects.at(i).type=typeSphere;
  objects.at(0).sphere.init(colores[WHITE], false, 50, {12, 12, 12}, {middle_win.x, middle_win.y, 0.0f});
  objects.at(1).sphere.init(colores[0], true, 10, {2, 2, 2}, {objects.at(0).sphere.mov_.x - 40, objects.at(0).sphere.mov_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.01f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(2).sphere.init(colores[1], true, 10, {2, 2, 2}, {objects.at(0).sphere.mov_.x, objects.at(0).sphere.mov_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.0f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(3).sphere.init(colores[3], true, 10, {2, 2, 2}, {objects.at(0).sphere.mov_.x + 60, objects.at(0).sphere.mov_.y + 60, 0.0f}, {0, 0, 0}, {0.01f, -0.01f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(4).sphere.init(colores[2], true, 10, {2, 2, 2}, {objects.at(0).sphere.mov_.x - 60, objects.at(0).sphere.mov_.y, 0.0f}, {0, 0, 0}, {0.0f, 0.01f, 0.0f}, objects.at(0).sphere.mov_);
  for(int i=1; i<5; i++) objects.at(i).sphere.orbit_vel_=10.0f;

  objects.at(5).type=typeCube;
  objects.at(5).cube.init({255,255,255,128}, true, {4,4,4}, {objects.at(0).sphere.mov_.x - 40, objects.at(0).sphere.mov_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.01f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(5).cube.orbit_vel_=10.0f;
  std::cout << "Planetas generados" << std::endl;

  light = objects.at(0).sphere.mov_;
  *objects_mov = (MV::Pnt3 *)realloc(*objects_mov, objects.size() * sizeof(MV::Pnt3));
  *objects_scale = (MV::Pnt3 *)realloc(*objects_scale, objects.size() * sizeof(MV::Pnt3));
  drawRender.init(max_win, {middle_win.x, middle_win.y, 100});
}
