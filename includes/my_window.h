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

////////////////////////////////
// Guardas, NO TOCAR
#ifndef my_window_h
#define my_window_h
////////////////////////////////

#ifndef RGBA
#define RGBA(x) x.r,x.g,x.b,x.a
#endif

#ifndef DESTROY
#define DESTROY(x) if(x!=nullptr){free(x);x=nullptr;}
#endif

class My_Window
{
private:
  int filas;
  int columnas;
  float textHeight;
  int textWidth;
  float win_x;
  float win_y;

  const double fps = 120.0;
  double current_time = 0.0;
  double last_time = 0.0;

  float frame_rate;
  int ticks;

public:
  bool runing;

  SDL_Renderer *render = NULL;
  SDL_Window *window = NULL;

  TTF_Font *font = NULL;

  SDL_Texture *textura = NULL;
  SDL_Surface *textSurface = NULL;

  SDL_Color fondo;

  My_Window(int height_, int width_, int filas_, int columnas_, SDL_Color p_fondo = {0, 0, 0, SDL_ALPHA_OPAQUE})
  {
    std::cout << "Creando My_Window..." << std::endl;
    runing = 1;

    filas = filas_;
    columnas = columnas_;
    textHeight = height_;
    textWidth = width_;

    win_x = columnas * textWidth;
    win_y = filas * textHeight;

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL |
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_ALLOW_HIGHDPI );
    window = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_x, win_y, window_flags);

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_ShowCursor(1);
    fondo = p_fondo;

    std::cout << "My_Window creada" << std::endl;
  }

  void changeResolution(MV::Pnt2 row_col){
    filas=row_col.x;
    columnas=row_col.y;

    win_x = columnas * textWidth;
    win_y = filas * textHeight;
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL |
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_ALLOW_HIGHDPI );
    window = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_x, win_y, window_flags);

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  }

  void whileInit()
  {
    ticks=SDL_GetTicks();
    // Limpia la pantalla dejandola en negro
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);
    TakeKeyboard();
  }

  void whileEnd(bool b_frame_rate)
  {

    // do
    // { // control fps por segundo.
    //   current_time = SDL_GetTicks();
    // } while (((current_time - last_time) <= (1000) / fps) && runing);
    // last_time=SDL_GetTicks();

    if(b_frame_rate){
      static int cont=0;
      ticks=SDL_GetTicks()-ticks;
      if(cont >= 30){ frame_rate=1000/ticks; cont-=30; }
      cont++;

      char texto[5];
      snprintf(texto, 5, "%d", (int)frame_rate);
      text(texto, 1, columnas-1-strlen(texto), colores[BLANCO]);
    }

    SDL_RenderPresent(render);

    if(EVENT_DOWN(EXIT_WINDOW)) runing=false;
  }

  bool setTextFont(char* font_path)
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
  void setGameTitle(char *completeTitle)
  {

    // Linux -> /home/whitewholf/.../.../game.elf
    // Windows -> game.exe
    int len = (int)strlen(completeTitle);
      len-=4;

    char* titleNoExtension=(char*)calloc(len+1, sizeof(char));
    for(int i=0; i < len; i++){
        titleNoExtension[i]=completeTitle[i];
    }
    titleNoExtension[len+1]='\0';

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

  }

  int rFilas()
  {
    return filas;
  }
  int rColumnas()
  {
    return columnas;
  }

  // Mostrar texto en pantalla
  void text(char *frase, int fila, int columna, SDL_Color color)
  {
    SDL_Rect textRect;
    SDL_Color textColor = color;
    char *str = (char *)calloc(columnas * 2, sizeof(char));

    if (strcmp(frase, "") == 0)
      return;
    SDL_SetRenderDrawColor(render, RGBA(color));
    sprintf(str, "%s", frase);
    textSurface = TTF_RenderUTF8_Blended(font, str, textColor);
    // Si no se consigue la surface:
    if (!textSurface)
    {
      printf("Surface: Error SDL2_ttf: %s\n", TTF_GetError());
      return;
    }
    else
    {
      // Crear la textura desde los pixels de la surface:
      textura = SDL_CreateTextureFromSurface(render, textSurface);
      // Si no se consigue la textura:
      if (!textura)
      {
        printf("Texture: SDL2 Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
      }
      // Ver las dimensiones del texto a mostrar:
      textRect.w = textSurface->w;
      textRect.h = textSurface->h;
    }
    textRect.x = columna * (win_x / columnas);
    textRect.y = fila * (win_y / filas);

    // Mostrar el texto:
    // -----------------
    SDL_RenderCopy(render, textura, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textura);
    DESTROY(str);
  }

  void drawLine(float init_x, float init_y, float fin_x, float fin_y, SDL_Color color={255,255,255,SDL_ALPHA_OPAQUE})
  {
    SDL_SetRenderDrawColor(render, RGBA(color));
    SDL_RenderDrawLine(render, init_x, init_y, fin_x, fin_y);
  }

  void drawPoint(float x, float y, SDL_Color color={255,255,255,SDL_ALPHA_OPAQUE})
  {
    SDL_SetRenderDrawColor(render, RGBA(color));
    SDL_RenderDrawPoint(render, (int)x, (int)y);
  }

  void drawRect(int fila, int columna, int width, int height, SDL_Color color={255,255,255,SDL_ALPHA_OPAQUE}, SDL_Color fill={255,255,255,SDL_ALPHA_OPAQUE})
  {
    int px = columna * (win_x / columnas);
    int py = fila * (win_y / filas);
    SDL_Rect rect = {px, py, width, height};
    SDL_SetRenderDrawColor(render, RGBA(fill));
    SDL_RenderFillRect(render, &rect);
    SDL_SetRenderDrawColor(render, RGBA(color));
    SDL_RenderDrawRect(render, &rect);
  }

  void Destroy()
  {
    std::cout << "Destruyendo My_Window..." << std::endl;

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);

    std::cout << "My_Window destruida" << std::endl;
  }

  ~My_Window(){

  }
};

////////////////////////////////
// Guardas, NO TOCAR
#endif /* my_window_h */
////////////////////////////////
