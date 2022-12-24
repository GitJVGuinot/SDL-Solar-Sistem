/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>
/// @file Debug_window.h

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

/**
 * @class Debug_Window
 *
 * @brief Class to use ImGui.
 *
 * The Debug_Window class provides static methods to initialize, update, render, and process input for ImGui, as well as a method to clean up ImGui resources.
 */
class Debug_Window
{
public:
  /**
   * @brief Initializes ImGui for use with the given SDL_Window and SDL_Renderer.
   *
   * @param window Pointer to the SDL_Window.
   * @param render Pointer to the SDL_Renderer.
   */
  static void Init(SDL_Window *window, SDL_Renderer *render);

  /**
   * @brief Updates ImGui state.
   */
  static void Update();

  /**
   * @brief Renders ImGui windows and widgets.
   */
  static void Render();

  /**
   * @brief Processes ImGui input events.
   *
   * @param event Pointer to the SDL_Event.
   */
  static void Input(SDL_Event *event);

  /**
   * @brief Cleans up ImGui resources.
   */
  static void Quit();
};

/**
 * @brief Modifies the given Render object, My_Window object, and Vec2 object to implement camera control using ImGui.
 *
 * @param drawRender Reference to the Render object.
 * @param win Reference to the My_Window object.
 * @param max_win Reference to the Vec2 object.
 */
void Camera_Control(Render &drawRender, My_Window &win, Vec2 max_win, Vec3 &light);

/**
 * @brief Modifies the given vector of Objects objects, two pointers to Vec3 objects, and Vec2 object to implement object control using ImGui.
 *
 * @param objects Reference to the vector of Objects objects.
 * @param objects_mov Pointer to the Vec3 object for object movement.
 * @param objects_scale Pointer to the Vec3 object for object scaling.
 * @param max_win Reference to the Vec2 object.
 */
void Objects_Control(std::vector<Objects> &objects, Vec3 **objects_mov, Vec3 **objects_scale, Vec2 max_win);

////////////////////////
#endif /* __DEBUG_WINDOW_H__ */
////////////////////////
