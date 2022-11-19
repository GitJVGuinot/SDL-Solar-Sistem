#ifndef DEBUG_WINDOW_H
#define DEBUG_WINDOW_H 1

#include <SDL2/SDL.h>
#include <iostream>

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

#endif
