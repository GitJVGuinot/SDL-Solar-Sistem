#ifndef debug_window_h
#define debug_winfow_h

#include <SDL2/SDL.h>
#include <iostream>
#include <render.h>
#include <esfera_3d.h>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

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

void Camera_Control(const char* str, Render &drawRender, MV::Pnt2 max_win);
void Planets_Control(const char* str, Esfera **planets);

#endif
