/// @author F.c.o Javier Guinot Almenar

#include <SDL2/SDL.h>

////////////////////////////////
// Guardas, NO TOCAR
#ifndef SDL_event_control_h
#define SDL_event_control_h
////////////////////////////////

// Numbers
const int K_0 = 0;
const int K_1 = 1;
const int K_2 = 2;
const int K_3 = 3;
const int K_4 = 4;
const int K_5 = 5;
const int K_6 = 6;
const int K_7 = 7;
const int K_8 = 8;
const int K_9 = 9;

// Minusc Keys
const int K_a = 10;
const int K_b = 11;
const int K_c = 12;
const int K_d = 13;
const int K_e = 14;
const int K_f = 15;
const int K_g = 16;
const int K_h = 17;
const int K_i = 18;
const int K_j = 19;
const int K_k = 20;
const int K_l = 21;
const int K_m = 22;
const int K_n = 23;
const int K_o = 24;
const int K_p = 25;
const int K_q = 26;
const int K_r = 27;
const int K_s = 28;
const int K_t = 29;
const int K_u = 30;
const int K_v = 31;
const int K_w = 32;
const int K_x = 33;
const int K_y = 34;
const int K_z = 35;

// F Keys
const int F1 = 36;
const int F2 = 37;
const int F3 = 38;
const int F4 = 39;
const int F5 = 40;
const int F6 = 41;
const int F7 = 42;
const int F8 = 43;
const int F9 = 44;
const int F10 = 45;
const int F11 = 46;
const int F12 = 47;

// Some Specials
const int ALT = 48;
const int TAB = 49;
const int ENTER = 50;
const int SHIFT = 51;
const int SPACE = 52;
const int BACK_SPACE = 53;
const int ESCAPE = 54;
const int DELETE = 55;
const int CONTROL = 56;
const int UP = 57;
const int DOWN = 58;
const int LEFT = 59;
const int RIGHT = 60;
const int PLUS = 61;
const int MINUS = 62;
const int COMMA = 63;
const int DOT = 64;

const int EXIT_WINDOW = 65;

const int FULL_EXIT_WINDOW = 66;

const int MAX_INPUTS = 67;

struct Keys
{
  bool down;
  bool up;
  char letter;
  char may_letter;
};

/**
  * Init a Keys array use after SDL_Inits
*/
void InitKeyboard(Keys *keys);

/**
  * Use in the while Start
  * You can found it in My_Window::whileInit
*/
void TakeKeyboard(Keys *keys);

/**
  * @return the input down of the Keys array
*/
bool EVENT_DOWN(int input, Keys *keys);

/**
  * @return the input up of the Keys array
*/
bool EVENT_UP(int input, Keys *keys);

////////////////////////////////
// Guardas, NO TOCAR
#endif /* SDL_event_control_h */
////////////////////////////////
