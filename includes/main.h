/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

/** @file Main.h
 * Main global variables and includes.
 */

////////////////////////
#ifndef __MAIN_H__
#define __MAIN_H__ 1
////////////////////////

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <cstring>
#include <cfloat>
#include <common_defs.h>
#include <math_utils.h>
#include <SDL_event_control.h>

#include <render.h>
#include <objects.h>
#include <my_window.h>
#include <debug_window.h>

const int k_TextHeight = 28;
const int k_TextWitdh = ((float)(k_TextHeight * 4 / 7) - 1);
const int k_Rows = 30;
const int k_Columns = 80;

Vec2 g_max_win = {(float)(k_TextWitdh * k_Columns), (float)(k_TextHeight *k_Rows)};
Vec2 g_middle_win = {g_max_win.x / 2, g_max_win.y / 2};
Vec2 g_min_win = {0, 0};

SDL_Color g_colors[MAX_COLORS] = {
    SDL_Color{255, 000, 000, 255}, // RED

    SDL_Color{000, 255, 000, 255}, // GREEN

    SDL_Color{000, 000, 255, 255}, // BLUE

    SDL_Color{000, 255, 255, 255}, // CYAN

    SDL_Color{255, 000, 255, 255}, // MAGENTA

    SDL_Color{255, 255, 000, 255}, // YELLOW

    SDL_Color{255, 255, 255, 255}, // WHITE
    SDL_Color{127, 127, 127, 255}, // GREY
    SDL_Color{000, 000, 000, 255}, // BLACK
};

void Basic_Objects_Init(std::vector<struct Objects> &objects, Vec3 &light, Render &drawRender, Vec3 **objects_mov, Vec3 **objects_scale);

////////////////////////
#endif /* __MAIN_H__ */
////////////////////////
