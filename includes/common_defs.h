/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Common_defs.h
 * Header to define all the defines that are used in the program.
 */

/////////////////////////
#ifndef __COMMON_DEFS_H__
#define __COMMON_DEFS_H__ 1
/////////////////////////

#include <SDL2/SDL.h>

#define RGBA(x) x.r, x.g, x.b, x.a

enum
{
  RED = 0,
  GREEN = 1,
  BLUE = 2,
  CYAN = 3,
  MAGENTA = 4,
  YELLOW = 5,
  WHITE = 6,
  GREY = 7,
  BLACK = 8,
  MAX_COLORS = 9,
};

#ifndef PI
#define PI 3.14159265358979323846f
#endif

#ifndef Between
#define Between(x, y, z) (x >= y && y >= z)
#endif

#ifndef DESTROY
#define DESTROY(x)  \
  if (x != nullptr) \
  {                 \
    free(x);        \
    x = nullptr;    \
  }
#endif

#ifndef CLEAR
#define CLEAR(x) memset(x, 0, sizeof(x));
#endif

#define FONT_PATH "../data/fonts/anonymous_pro.ttf"

#ifdef _WIN32
#ifndef FONT_PATH_R
#define FONT_PATH_R "C:/Windows/Fonts/Arial.ttf"
#define CLEAR_CONSOLE "cls"
#endif
#elif __linux__
#ifndef FONT_PATH_R
#define FONT_PATH_R "/usr/share/fonts/truetype/lao/Phetsarath_OT.ttf"
#define CLEAR_CONSOLE "clear"
#endif
#endif

/////////////////////////
#endif /* __COMMON_DEFS_H__ */
/////////////////////////
