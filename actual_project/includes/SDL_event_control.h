/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>
/// @file SDL_event_control.h

////////////////////////////////
#ifndef __SDL_EVENT_CONTROL_H__
#define __SDL_EVENT_CONTROL_H__ 1
////////////////////////////////

#include <SDL2/SDL.h>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_sdl.h>
#include <IMGUI/imgui_impl_sdlrenderer.h>

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

/**
 * @struct Keys
 * @brief Struct representing a keyboard key
 *
 * The Keys struct stores information about a keyboard key.
 */
struct Keys
{
  bool down; ///< Boolean indicating whether the key is currently being pressed down
  bool up; ///< Boolean indicating whether the key is currently not being pressed
  char letter; ///< Character representing the lowercase version of the key
  char may_letter; ///< Character representing the uppercase version of the key
};

/**
 * @brief Initializes a Keys struct
 * @param keys Pointer to the Keys struct to be initialized
 */
void InitKeyboard(Keys *keys);

/**
 * @brief Updates a Keys struct to reflect the current state of the keyboard
 * @param keys Pointer to the Keys struct to be updated
 */
void TakeKeyboard(Keys *keys);

/**
 * @brief Returns a boolean indicating whether the key represented by input is currently being pressed down
 * @param input Integer representing the key
 * @param keys Pointer to the Keys struct
 * @return Boolean indicating whether the key is currently being pressed down
 */
bool EVENT_DOWN(int input, Keys *keys);

/**
 * @brief Returns a boolean indicating whether the key represented by input is currently not being pressed
 * @param input Integer representing the key
 * @param keys Pointer to the Keys struct
 * @return Boolean indicating whether the key is currently not being pressed
 */
bool EVENT_UP(int input, Keys *keys);

////////////////////////////////
#endif /* __SDL_EVENT_CONTROL_H__ */
////////////////////////////////
