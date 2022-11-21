/// @author F.c.o Javier Guinot Almenar

#include "my_window.h"

#ifndef DESTROY
#define DESTROY(x)  \
  if (x != nullptr) \
  {                 \
    free(x);        \
    x = nullptr;    \
  }
#endif

My_Window::My_Window(int height_, int width_, int rows_, int columns_, SDL_Color background_color_)
{
  std::cout << "Creando My_Window..." << std::endl;
  runing = true;
  state = 0;

  fps_control = true;
  show_fps = true;
  rows = rows_;
  columns = columns_;
  textHeight = height_;
  textWidth = width_;

  win_x = columns * textWidth;
  win_y = rows * textHeight;

  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL |
                                                   SDL_WINDOW_RESIZABLE |
                                                   SDL_WINDOW_ALLOW_HIGHDPI);
  window = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_x, win_y, window_flags);

  SDL_RendererFlags render_flags = (SDL_RendererFlags)(SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  render = SDL_CreateRenderer(window, -1, render_flags);

  SDL_ShowCursor(1);
  background_color = background_color_;

  std::cout << "My_Window creada" << std::endl;
}

void My_Window::whileInit(Keys *keys)
{
  ticks = SDL_GetTicks();
  // Limpia la pantalla dejandola en negro
  SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
  SDL_RenderClear(render);
  TakeKeyboard(keys);
}

void My_Window::whileEnd(Keys *keys)
{
  if (fps_control)
  {
    do
    { // control fps por segundo.
      current_time = SDL_GetTicks();
    } while (((current_time - last_time) <= (1000) / fps) && runing);
    last_time = SDL_GetTicks();
  }

  if (show_fps)
  {
    static int cont = 0;
    ticks = SDL_GetTicks() - ticks;
    if (cont >= 100 || cont == 0)
    {
      if (ticks != 0)
        frame_rate = 1000.0f / (float)ticks;
      else
        frame_rate = FLT_MAX;
      cont -= 100;
    }
    cont++;

    char texto[15];
    snprintf(texto, 15, "%d", (int)frame_rate);
    text(texto, 1, columns - 1 - strlen(texto), {255, 255, 255, SDL_ALPHA_OPAQUE});
  }

  SDL_RenderPresent(render);
  if (EVENT_DOWN(EXIT_WINDOW, keys))
  {
    runing = false;
    keys[EXIT_WINDOW].down = false;
  }
  if (EVENT_DOWN(FULL_EXIT_WINDOW, keys))
  {
    runing = false;
  }
}

bool My_Window::setTextFont(char *font_path)
{

  font = TTF_OpenFont(font_path, textHeight);

  if (!font)
  {
    TTF_CloseFont(font);
    std::cout << SDL_GetError() << std::endl;
    std::cout << "Trying default font -> " << FONT_PATH_R << std::endl;
    font = TTF_OpenFont(FONT_PATH_R, textHeight);
  }
  else
  {
    TTF_CloseFont(font);
    font = TTF_OpenFont(font_path, textHeight);
  }

  std::cout << "Font Height: " << TTF_FontHeight(font) << std::endl;

  return font;
}

void My_Window::setGameTitle(char *completeTitle)
{
  // Linux -> /home/whitewholf/.../.../game.elf
  // Windows -> game.exe
  std::cout << "Estableciendo titulo del juego" << std::endl;
  int len = (int)strlen(completeTitle);
  len -= 4;

  char *titleNoExtension = (char *)calloc(len + 1, sizeof(char));
  for (int i = 0; i < len; i++)
  {
    titleNoExtension[i] = completeTitle[i];
  }
  titleNoExtension[len + 1] = '\0';

#ifdef _WIN32

  SDL_SetWindowTitle(window, titleNoExtension);

#elif __linux__

  std::string str = titleNoExtension;

  std::string strReversed(str.rbegin(), str.rend());

  char *preTitle = (char *)calloc(strlen(titleNoExtension), sizeof(char));

  int i;
  for (i = 0; i < (int)strlen(titleNoExtension) && preTitle[i - 1] != '/'; i++)
  {
    preTitle[i] = strReversed[i];
  }
  preTitle[i - 1] = '\0';

  std::string str_2 = preTitle;
  std::string title_(str_2.rbegin(), str_2.rend());

  SDL_SetWindowTitle(window, (char *)title_.c_str());

#endif

  std::cout << "Titulo de juego establecido" << std::endl;
}

void My_Window::changeResolution(int filas_, int columnas_)
{
  rows = filas_;
  columns = columnas_;

  win_x = columns * textWidth;
  win_y = rows * textHeight;
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);

  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL |
                                                   SDL_WINDOW_RESIZABLE |
                                                   SDL_WINDOW_ALLOW_HIGHDPI);
  window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_x, win_y, window_flags);

  render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

int My_Window::getRows()
{
  return rows;
}
int My_Window::getColumns()
{
  return columns;
}
int My_Window::getTextHeight()
{
  return textHeight;
}
int My_Window::getTextWidth()
{
  return textWidth;
}

// Mostrar texto en pantalla
void My_Window::text(char *frase, int fila, int columna, SDL_Color color)
{
  SDL_Rect textRect;
  SDL_Color textColor = color;

  if (strcmp(frase, "") == 0)
    return;

  char *str = (char *)calloc(columns * rows, sizeof(char));

  SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
  sprintf(str, "%s", frase);
  textSurface = TTF_RenderUTF8_Blended(font, str, textColor);
  // Si no se consigue la surface:
  if (!textSurface)
  {
    printf("Surface: Error SDL2_ttf: %s\n", TTF_GetError());
    DESTROY(str);
    return;
  }
  else
  {
    // Crear la texture desde los pixels de la surface:
    texture = SDL_CreateTextureFromSurface(render, textSurface);
    // Si no se consigue la texture:
    if (!texture)
    {
      printf("Texture: SDL2 Error: %s\n", SDL_GetError());
      DESTROY(str);
      exit(EXIT_FAILURE);
    }
    // Ver las dimensiones del texto a mostrar:
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;
  }
  textRect.x = columna * (win_x / columns);
  textRect.y = fila * (win_y / rows);

  // Mostrar el texto:
  // -----------------
  SDL_RenderCopy(render, texture, NULL, &textRect);
  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(texture);
  DESTROY(str);
}

void My_Window::drawCursor(int fila, int columna, SDL_Color color, SDL_Color fill)
{
  int px = columna * (win_x / columns);
  int py = fila * (win_y / rows);
  SDL_Rect rect = {px, py, (int)textWidth, (int)textHeight};
  SDL_SetRenderDrawColor(render, fill.r, fill.g, fill.b, fill.a);
  SDL_RenderFillRect(render, &rect);
  SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
  SDL_RenderDrawRect(render, &rect);
}

void My_Window::drawRect(int fila, int columna, int height, int width, SDL_Color color, SDL_Color fill)
{
  int px = columna * (win_x / columns);
  int py = fila * (win_y / rows);
  px -= 3;
  py -= 3;
  SDL_Rect rect = {px, py, width + 6, height + 6};
  SDL_SetRenderDrawColor(render, fill.r, fill.g, fill.b, fill.a);
  SDL_RenderFillRect(render, &rect);
  SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
  SDL_RenderDrawRect(render, &rect);
}

void My_Window::Destroy()
{
  std::cout << "Destruyendo My_Window, SDL & SDL_ttf..." << std::endl;

  if (render != nullptr && render != NULL)
    SDL_DestroyRenderer(render);
  if (window != nullptr && window != NULL)
    SDL_DestroyWindow(window);
  if (font != nullptr && font != NULL)
    TTF_CloseFont(font);

  std::cout << "My_Window, SDL & SDL_ttf destruidos" << std::endl
            << std::endl;
}
