#ifndef debug_window_h
#define debug_winfow_h

#include <SDL2/SDL.h>

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_sdl.h>
#include <IMGUI/imgui_impl_sdlrenderer.h>

#include <iostream>
#include <render.h>
#include <objects.h>
#include <my_window.h>

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

void Camera_Control(Render &drawRender, My_Window &win, MV::Pnt2 max_win);
void Objects_Control(std::vector <Objects>&objects, MV::Pnt3 **objects_mov, MV::Pnt3 **objects_scale, MV::Pnt2 max_win);

#endif /* debug_window_h */
