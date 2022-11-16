/// @author F.c.o Javier Guinot Almenar

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <cstring>

#include "SDL_event_control.h"
#include "SDL_colors.h"

#ifdef _WIN32
#define FONT_PATH_R "C:/Windows/Fonts/Arial.ttf"
#elif __linux__
#define FONT_PATH_R "/usr/share/fonts/truetype/lao/Phetsarath_OT.ttf"
#endif

////////////////////////////////
// Guardas, NO TOCAR
#ifndef my_window_h
#define my_window_h
////////////////////////////////

/** \class
 * Defines the display viewport
 */
class My_Window
{
private:
  int rows;
  int columns;
  int textHeight;
  int textWidth;

  const double fps = 60.0;
  double current_time = 0.0;
  double last_time = 0.0;

  float frame_rate = 0;
  int ticks;

public:
  float win_x;
  float win_y;
  bool runing;
  int state;

  SDL_Renderer *render = NULL;
  SDL_Window *window = NULL;

  TTF_Font *font = NULL;

  SDL_Texture *texture = NULL;
  SDL_Surface *textSurface = NULL;

  SDL_Color background_color;

  /**
   * Class constructor
   */
  My_Window(int height_, int width_, int rows_, int columns_, SDL_Color p_background_color = {0, 0, 0, SDL_ALPHA_OPAQUE});

  /**
   * This is necesary at start in any displayport loop
   * ¡¡¡¡ BE SURE THAT IS CLOSED !!!!
   */
  void whileInit(Keys *keys);

  /**
   * This is necesary at end in any displayport loop
   * ¡¡¡¡ BE SURE THAT IS STARTED !!!!
   */
  void whileEnd(Keys *keys, bool frame_rat = true);

  /**
   * Defines THE PATH to the font.ttf
   * It`s fine if you put a wrong path it will put one preinstale in the sistem
   * @return In case the path was wrong it will print a error in console and return it
   */
  bool setTextFont(char *font_path);

  /**
   * Set the name for the window
   */
  void setGameTitle(char *completeTitle);

  void changeResolution(int rows, int columns);

  int getRows();
  int getColumns();
  int getTextHeight();
  int getTextWidth();

  /**
   * Print thext in the window
   */
  void text(char *literal, int row, int column, SDL_Color color);

  /**
   * Draw a rect in the position you are going to write
   */
  void drawCursor(int row, int column, SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE}, SDL_Color fill = {0, 0, 0, SDL_ALPHA_OPAQUE});

  /**
   * Draw a rectangle
   */
  void drawRect(int row, int column, int height, int width, SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE}, SDL_Color fill = {255, 255, 255, SDL_ALPHA_OPAQUE});

  void drawLine(int x1, int y1, int x2, int y2, SDL_Color color = {255,255,255,SDL_ALPHA_OPAQUE});

  /**
   * Destroyer of the window. Use it before you close your window
   */
  void Destroy();

  ~My_Window() = default;
};

////////////////////////////////
// Guardas, NO TOCAR
#endif /* my_window_h */
////////////////////////////////
