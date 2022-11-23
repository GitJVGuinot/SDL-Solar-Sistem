#ifndef debug_window_h
#define debug_winfow_h

#include <SDL2/SDL.h>
#include <iostream>
#include <render.h>
#include <sphere_3d.h>
#include <my_window.h>

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_sdl.h>
#include <IMGUI/imgui_impl_sdlrenderer.h>

class Debug_Window
{
public:
  static void Init(SDL_Window *window, SDL_Renderer *render);
  // Call in while Init
  static void Update();
  // Call in while End
  static void Render();
  // Call after while init
  static void Input(SDL_Event *event);
  // Call when close ImGui
  static void Quit();
};

void Camera_Control(const char *str, Render &drawRender, My_Window &win, MV::Pnt2 max_win);
void Planets_Control(const char *str, Sphere **planets, MV::Pnt3 **object_desp, int &max_planets, MV::Pnt2 max_win);

#endif
