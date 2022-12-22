/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>
/// @file My_window.h

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

/**
 * @brief This class represents a window that
 * can be used to draw text and shapes using the SDL library.
 * Is responsible for creating, updating, and rendering a window.
 * Provides various methods for
 * manipulating and drawing on an SDL window, including setting the font,
 * changing the resolution, and drawing shapes and text.
 */
class My_Window
{
private:
  int rows; ///< The number of rows in the window.
  int columns; ///< The number of columns in the window.
  int textHeight; ///< The height of the text in the window.
  int textWidth; ///< The width of the text in the window.

#ifdef IMGUI_API
  bool imguiState; ///< The state of the ImGui API (if it is enabled).
#endif

  double current_time; ///< The current time (in seconds).
  double last_time; ///< The last time (in seconds).

  float frame_rate; ///< The current frame rate (in frames per second).
  int ticks; ///< The number of ticks (used to calculate the frame rate).

public:
  double fps; ///< The target frame rate (in frames per second).
  bool fps_control; ///< Whether to control the frame rate or not.
  bool show_fps; ///< Whether to show the frame rate or not.
  float win_x; ///< The x-coordinate of the window.
  float win_y; ///< The y-coordinate of the window.
  bool runing; ///< Whether the window is running or not.
  int state; ///< The current state of the window.

  SDL_Renderer *render; ///< The SDL renderer for the window.
  SDL_Window *window; ///< The SDL window.

  SDL_Texture *texture; ///< The SDL texture for the window.
  SDL_Surface *textSurface; ///< The SDL surface for text rendering.

  TTF_Font *font; ///< The SDL TTF font for text rendering.

  SDL_Color background_color; ///< The background color of the window.

  /**
   * @brief Constructs a new My_Window object.
   *
   * @param height_ The height of the window, in pixels.
   * @param width_ The width of the window, in pixels.
   * @param rows_ The number of rows in the window's grid.
   * @param columns_ The number of columns in the window's grid.
   * @param background_color The background color of the window.
   */
  My_Window(int height_, int width_, int rows_, int columns_, SDL_Color background_color);

  /**
   * @brief Initializes the window. for each game loop
   *
   * @param keys A pointer to a Keys object that will be used to handle input.
   */
  void whileInit(Keys *keys);

  /**
   * @brief Closes the window. for each game loop
   *
   * @param keys A pointer to a Keys object that will be used to handle input.
   */
  void whileEnd(Keys *keys);

  /**
   * @brief Sets the font that will be used for drawing text on the window.
   *
   * @param font_path The path to the font file.
   * @return true if the font was successfully set, false otherwise.
   */
  bool setTextFont(char *font_path);

  /**
   * @brief Sets the title of the window.
   *
   * @param completeTitle The new title for the window.
   */
  void setGameTitle(char *completeTitle);

  /**
   * @brief Changes the resolution of the window.
   *
   * @param rows The new number of rows in the window's grid.
   * @param columns The new number of columns in the window's grid.
   */
  void changeResolution(int rows, int columns); ///< Doesn't work well

  /**
   * @brief Returns the number of rows in the window's grid.
   *
   * @return The number of rows.
   */
  int getRows();

  /**
   * @brief Returns the number of columns in the window's grid.
   *
   * @return The number of columns.
   */
  int getColumns();

  /**
   * @brief Returns the height of the text that is drawn on the window.
   *
   * @return The height of the text, in pixels.
   */
  int getTextHeight();

  /**
   * @brief Returns the width of the text.
   *
   * This function calculates the width of the given text in pixels.
   *
   * @return The width of the text in pixels.
   */
  int getTextWidth();

  /**
   * @brief Renders the given text on the window.
   *
   * This function renders the given text on the window at the specified row and column. The text color can also be specified.
   *
   * @param[in] literal The text to be rendered.
   * @param[in] row The row index where the text should be rendered.
   * @param[in] column The column index where the text should be rendered.
   * @param[in] color The color of the text.
   */
  void text(char *literal, int row, int column, SDL_Color color);

  /**
   * @brief Renders a polygon on the window.
   *
   * This function renders a polygon on the window using the given vertices.
   *
   * @param[in] render The SDL renderer to use for rendering.
   * @param[in] vertex An array of vertices defining the polygon.
   * @param[in] n_vertex The number of vertices in the array.
   *
   * @return 0 on success, a negative error code on failure.
   */
  static int drawPoligon(SDL_Renderer *render, SDL_Vertex *vertex, const int n_vertex);

  /**
   * @brief Renders a cursor on the window.
   *
   * This function renders a cursor on the window at the specified row and column. The cursor's color and fill color can also be specified.
   *
   * @param[in] row The row index where the cursor should be rendered.
   * @param[in] column The column index where the cursor should be rendered.
   * @param[in] color The color of the cursor's outline.
   * @param[in] fill The fill color of the cursor.
   */
  void drawCursor(int row, int column, SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE}, SDL_Color fill = {0, 0, 0, SDL_ALPHA_OPAQUE});

  /**
   * @brief Renders a rectangle on the window.
   *
   * This function renders a rectangle on the window at the specified row and column with the given height and width. The rectangle's color and fill color can also be specified.
   *
   * @param[in] row The row index where the rectangle should be rendered.
   * @param[in] column The column index where the rectangle should be rendered.
   * @param[in] height The height of the rectangle in pixels.
   * @param[in] width The width of the rectangle in pixels.
   * @param[in] color The color of the rectangle's outline.
   * @param[in] fill The fill color of the rectangle.
   */
  void drawRect(int row, int column, int height, int width, SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE}, SDL_Color fill = {255, 255, 255, SDL_ALPHA_OPAQUE});

  /**
   * @brief Destroys the window.
   *
   * This function destroys the window and frees any associated resources.
   */
  void Destroy();

  /**
   * @brief Destructor for the My_Window class.
   *
   * The destructor is defaulted to ensure that the window is properly destroyed when the object goes out of scope.
   */
  ~My_Window() = default;
};

////////////////////////////////
#endif /* __MY_WINDOW_H__ */
////////////////////////////////
