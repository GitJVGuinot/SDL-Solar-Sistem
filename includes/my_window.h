/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file My_window.h
 * Class to control SDL2 window.
 */

////////////////////////////////
#ifndef __MY_WINDOW_H__
#define __MY_WINDOW_H__ 1
////////////////////////////////

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <cstring>

#include <SDL_event_control.h>

#ifdef _WIN32
#define FONT_PATH_R "C:/Windows/Fonts/Arial.ttf"
#elif __linux__
#define FONT_PATH_R "/usr/share/fonts/truetype/lao/Phetsarath_OT.ttf"
#endif

class My_Window
{
private:
  int rows;
  int columns;
  int textHeight;
  int textWidth;

#ifdef IMGUI_API
  bool imguiState;
#endif

  double current_time = 0.0;
  double last_time = 0.0;

  float frame_rate = 0;
  int ticks = 0;

public:
  double fps = 60.0;
  bool fps_control;
  bool show_fps;
  float win_x;
  float win_y;
  bool runing;
  int state;

  SDL_Renderer *render = NULL;
  SDL_Window *window = NULL;

  SDL_Texture *texture = NULL;
  SDL_Surface *textSurface = NULL;

  TTF_Font *font = NULL;

  SDL_Color background_color;

  /** @brief
   * Class constructor
   */
  My_Window(int height_, int width_, int rows_, int columns_, SDL_Color background_color);

  /** @brief
   * This is necesary at start in any displayport loop
   * ¡¡¡¡ BE SURE THAT IS CLOSED !!!!
   */
  void whileInit(Keys *keys);

  /** @brief
   * This is necesary at end in any displayport loop
   * ¡¡¡¡ BE SURE THAT IS STARTED !!!!
   */
  void whileEnd(Keys *keys);

  /** @brief
   * Defines THE PATH to the font.ttf
   * It`s fine if you put a wrong path it will put one preinstale in the sistem
   * @return In case the path was wrong it will print a error in console and return it
   */
  bool setTextFont(char *font_path);

  /** @brief
   * Set the name for the window
   */
  void setGameTitle(char *completeTitle);

  void changeResolution(int rows, int columns);

  int getRows();
  int getColumns();
  int getTextHeight();
  int getTextWidth();

  /** @brief
   * Print text in the window
   */
  void text(char *literal, int row, int column, SDL_Color color);

  /** @brief
   * Draw a poligonal shape with SDL_Vertex
   * Taking the color from it
   */
  static int drawPoligon(SDL_Renderer *render, SDL_Vertex *vertex, const int n_vertex);

  /** @brief
   * Draw a rect in the position you are going to write
   */
  void drawCursor(int row, int column, SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE}, SDL_Color fill = {0, 0, 0, SDL_ALPHA_OPAQUE});

  /** @brief
   * Draw a rectangle
   */
  void drawRect(int row, int column, int height, int width, SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE}, SDL_Color fill = {255, 255, 255, SDL_ALPHA_OPAQUE});

  /** @brief
   * Destroyer of the window. Use it before you close your window
   */
  void Destroy();

  ~My_Window() = default;
};

////////////////////////////////
#endif /* __MY_WINDOW_H__ */
////////////////////////////////
