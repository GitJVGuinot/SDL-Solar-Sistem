/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Debug_window.h
 * Class to use ImGui.
 */

////////////////////////
#ifndef __DEBUG_WINDOW_H__
#define __DEBUG_WINDOW_H__ 1
////////////////////////

#include <SDL2/SDL.h>

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_sdl.h>
#include <IMGUI/imgui_impl_sdlrenderer.h>

#include <iostream>
#include <vector>
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

void Camera_Control(Render &drawRender, My_Window &win, Vec2 max_win);
void Objects_Control(std::vector<Objects> &objects, Vec3 **objects_mov, Vec3 **objects_scale, Vec2 max_win);

////////////////////////
#endif /* __DEBUG_WINDOW_H__ */
////////////////////////
