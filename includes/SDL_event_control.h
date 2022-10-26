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

const int EXIT_WINDOW = 61;

const int MAX_INPUTS = 62;

struct Keys{
  bool down;
  bool up;
}; Keys keys[MAX_INPUTS];

// Use in the while Start
void TakeKeyboard()
{
  // Limpia los inputs del frame anterior
  for(unsigned int i=0; i<MAX_INPUTS-1; i++){
    keys[i].down=false;
    keys[i].up=false;
  }

  // Copia los inputs del frame anterior
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      keys[EXIT_WINDOW].down = true;
      keys[EXIT_WINDOW].up = true;
    }
    if(event.type==SDL_KEYDOWN)
    {
      switch(event.key.keysym.sym)
      {
        // Numbers
        case SDLK_0: keys[K_0].down =true; break;
        case SDLK_1: keys[K_1].down =true; break;
        case SDLK_2: keys[K_2].down =true; break;
        case SDLK_3: keys[K_3].down =true; break;
        case SDLK_4: keys[K_4].down =true; break;
        case SDLK_5: keys[K_5].down =true; break;
        case SDLK_6: keys[K_6].down =true; break;
        case SDLK_7: keys[K_7].down =true; break;
        case SDLK_8: keys[K_8].down =true; break;
        case SDLK_9: keys[K_9].down =true; break;

        // Minusc keys
        case SDLK_a: keys[K_a].down =true; break;
        case SDLK_b: keys[K_b].down =true; break;
        case SDLK_c: keys[K_c].down =true; break;
        case SDLK_d: keys[K_d].down =true; break;
        case SDLK_e: keys[K_e].down =true; break;
        case SDLK_f: keys[K_f].down =true; break;
        case SDLK_g: keys[K_g].down =true; break;
        case SDLK_h: keys[K_h].down =true; break;
        case SDLK_i: keys[K_i].down =true; break;
        case SDLK_j: keys[K_j].down =true; break;
        case SDLK_k: keys[K_k].down =true; break;
        case SDLK_l: keys[K_l].down =true; break;
        case SDLK_m: keys[K_m].down =true; break;
        case SDLK_n: keys[K_n].down =true; break;
        case SDLK_o: keys[K_o].down =true; break;
        case SDLK_p: keys[K_p].down =true; break;
        case SDLK_q: keys[K_q].down =true; break;
        case SDLK_r: keys[K_r].down =true; break;
        case SDLK_s: keys[K_s].down =true; break;
        case SDLK_t: keys[K_t].down =true; break;
        case SDLK_u: keys[K_u].down =true; break;
        case SDLK_v: keys[K_v].down =true; break;
        case SDLK_w: keys[K_w].down =true; break;
        case SDLK_x: keys[K_x].down =true; break;
        case SDLK_y: keys[K_y].down =true; break;
        case SDLK_z: keys[K_z].down =true; break;

        // F Keys
        case SDLK_F1: keys[F1].down =true; break;
        case SDLK_F2: keys[F2].down =true; break;
        case SDLK_F3: keys[F3].down =true; break;
        case SDLK_F4: keys[F4].down =true; break;
        case SDLK_F5: keys[F5].down =true; break;
        case SDLK_F6: keys[F6].down =true; break;
        case SDLK_F7: keys[F7].down =true; break;
        case SDLK_F8: keys[F8].down =true; break;
        case SDLK_F9: keys[F9].down =true; break;
        case SDLK_F10: keys[F10].down =true; break;
        case SDLK_F11: keys[F11].down =true; break;
        case SDLK_F12: keys[F12].down =true; break;

        // Some specials
        case SDLK_LALT: keys[ALT].down =true; break;
        case SDLK_RALT: keys[ALT].down =true; break;
        case SDLK_TAB: keys[TAB].down =true; break;
        case SDLK_KP_ENTER: keys[ENTER].down =true; break;
        case SDLK_LSHIFT: keys[SHIFT].down =true; break;
        case SDLK_RSHIFT: keys[SHIFT].down =true; break;
        case SDLK_SPACE: keys[SPACE].down =true; break;
        case SDLK_BACKSPACE: keys[BACK_SPACE].down =true; break;
        case SDLK_ESCAPE: keys[EXIT_WINDOW].down =true; break;
        case SDLK_DELETE: keys[DELETE].down =true; break;
        case SDLK_RCTRL: keys[CONTROL].down =true; break;
        case SDLK_LCTRL: keys[CONTROL].down =true; break;
        case SDLK_UP: keys[UP].down =true; break;
        case SDLK_DOWN: keys[DOWN].down =true; break;
        case SDLK_LEFT: keys[LEFT].down =true; break;
        case SDLK_RIGHT: keys[RIGHT].down =true; break;
      }
    }
    if(event.type==SDL_KEYUP)
    {
      switch(event.key.keysym.sym)
      {
        // Numbers
        case SDLK_0: keys[K_0].up =true; break;
        case SDLK_1: keys[K_1].up =true; break;
        case SDLK_2: keys[K_2].up =true; break;
        case SDLK_3: keys[K_3].up =true; break;
        case SDLK_4: keys[K_4].up =true; break;
        case SDLK_5: keys[K_5].up =true; break;
        case SDLK_6: keys[K_6].up =true; break;
        case SDLK_7: keys[K_7].up =true; break;
        case SDLK_8: keys[K_8].up =true; break;
        case SDLK_9: keys[K_9].up =true; break;

        // Minusc keys
        case SDLK_a: keys[K_a].up =true; break;
        case SDLK_b: keys[K_b].up =true; break;
        case SDLK_c: keys[K_c].up =true; break;
        case SDLK_d: keys[K_d].up =true; break;
        case SDLK_e: keys[K_e].up =true; break;
        case SDLK_f: keys[K_f].up =true; break;
        case SDLK_g: keys[K_g].up =true; break;
        case SDLK_h: keys[K_h].up =true; break;
        case SDLK_i: keys[K_i].up =true; break;
        case SDLK_j: keys[K_j].up =true; break;
        case SDLK_k: keys[K_k].up =true; break;
        case SDLK_l: keys[K_l].up =true; break;
        case SDLK_m: keys[K_m].up =true; break;
        case SDLK_n: keys[K_n].up =true; break;
        case SDLK_o: keys[K_o].up =true; break;
        case SDLK_p: keys[K_p].up =true; break;
        case SDLK_q: keys[K_q].up =true; break;
        case SDLK_r: keys[K_r].up =true; break;
        case SDLK_s: keys[K_s].up =true; break;
        case SDLK_t: keys[K_t].up =true; break;
        case SDLK_u: keys[K_u].up =true; break;
        case SDLK_v: keys[K_v].up =true; break;
        case SDLK_w: keys[K_w].up =true; break;
        case SDLK_x: keys[K_x].up =true; break;
        case SDLK_y: keys[K_y].up =true; break;
        case SDLK_z: keys[K_z].up =true; break;

        // F Keys
        case SDLK_F1: keys[F1].up =true; break;
        case SDLK_F2: keys[F2].up =true; break;
        case SDLK_F3: keys[F3].up =true; break;
        case SDLK_F4: keys[F4].up =true; break;
        case SDLK_F5: keys[F5].up =true; break;
        case SDLK_F6: keys[F6].up =true; break;
        case SDLK_F7: keys[F7].up =true; break;
        case SDLK_F8: keys[F8].up =true; break;
        case SDLK_F9: keys[F9].up =true; break;
        case SDLK_F10: keys[F10].up =true; break;
        case SDLK_F11: keys[F11].up =true; break;
        case SDLK_F12: keys[F12].up =true; break;

        // Some specials
        case SDLK_LALT: keys[ALT].up =true; break;
        case SDLK_RALT: keys[ALT].up =true; break;
        case SDLK_TAB: keys[TAB].up =true; break;
        case SDLK_KP_ENTER: keys[ENTER].up =true; break;
        case SDLK_LSHIFT: keys[SHIFT].up =true; break;
        case SDLK_RSHIFT: keys[SHIFT].up =true; break;
        case SDLK_SPACE: keys[SPACE].up =true; break;
        case SDLK_BACKSPACE: keys[BACK_SPACE].up =true; break;
        case SDLK_ESCAPE: keys[EXIT_WINDOW].up =true; break;
        case SDLK_DELETE: keys[DELETE].up =true; break;
        case SDLK_RCTRL: keys[CONTROL].up =true; break;
        case SDLK_LCTRL: keys[CONTROL].up =true; break;
        case SDLK_UP: keys[UP].up =true; break;
        case SDLK_DOWN: keys[DOWN].up =true; break;
        case SDLK_LEFT: keys[LEFT].up =true; break;
        case SDLK_RIGHT: keys[RIGHT].up =true; break;
      }
    }
  }
}

// Devuelve el input down y lo establece en false
bool EVENT_DOWN(int input){
  bool ret = keys[input].down;
  return ret;
}

// Devuelve el input up y lo establece en false
bool EVENT_UP(int input){
  bool ret = keys[input].up;
  return ret;
}

////////////////////////////////
// Guardas, NO TOCAR
#endif /* SDL_event_control_h */
////////////////////////////////
