#include <SDL2/SDL.h>

/////////////////////////
// Guardas, NO TOCAR
#ifndef SDL_colors_h
#define SDL_colors_h
/////////////////////////

#define RGBA(x) x.r, x.g, x.b, x.a

const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;
const int CYAN = 3;
const int MAGENTA = 4;
const int YELLOW = 5;
const int WHITE = 6;
const int GREY = 7;
const int BLACK = 8;

const int MAX_COLORS = 9;

#ifndef PI
#define PI 3.14159265358979323846
#endif

#ifndef Between
#define Between(x, y, z) (x > y && y >= z)
#endif

#ifndef DESTROY
#define DESTROY(x)  \
  if (x != nullptr) \
  {                 \
    free(x);        \
    x = nullptr;    \
  }
#endif

#define FONT_PATH "../data/fonts/anonymous_pro.ttf"

#ifdef _WIN32
#ifndef FONT_PATH_R
#define FONT_PATH_R "C:/Windows/Fonts/Arial.ttf"
#endif
#elif __linux__
#ifndef FONT_PATH_R
#define FONT_PATH_R "/usr/share/fonts/truetype/lao/Phetsarath_OT.ttf"
#endif
#endif

/////////////////////////
// Guardas, NO TOCAR
#endif /* SDL_colors_h */
// Guardas, NO TOCAR
/////////////////////////
