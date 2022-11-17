/// @author F.c.o Javier Guinot Almenar

#include "SDL_event_control.h"

void InitKeyboard(Keys *keys)
{

  for (int i = 0; i < MAX_INPUTS; i++)
  {
    keys[i].down = keys[i].up = false;
  }

  keys[K_0].letter = '0';
  keys[K_0].may_letter = '=';
  keys[K_1].letter = '1';
  keys[K_1].may_letter = '!';
  keys[K_2].letter = '2';
  keys[K_2].may_letter = '"';
  keys[K_3].letter = '3';
  keys[K_3].may_letter = ' ';
  keys[K_4].letter = '4';
  keys[K_4].may_letter = '$';
  keys[K_5].letter = '5';
  keys[K_5].may_letter = '%';
  keys[K_6].letter = '6';
  keys[K_6].may_letter = '&';
  keys[K_7].letter = '7';
  keys[K_7].may_letter = '/';
  keys[K_8].letter = '8';
  keys[K_8].may_letter = '(';
  keys[K_9].letter = '9';
  keys[K_9].may_letter = ')';

  keys[K_a].letter = 'a';
  keys[K_a].may_letter = 'A';
  keys[K_b].letter = 'b';
  keys[K_b].may_letter = 'B';
  keys[K_c].letter = 'c';
  keys[K_c].may_letter = 'C';
  keys[K_d].letter = 'd';
  keys[K_d].may_letter = 'D';
  keys[K_e].letter = 'e';
  keys[K_e].may_letter = 'E';
  keys[K_f].letter = 'f';
  keys[K_f].may_letter = 'F';
  keys[K_g].letter = 'g';
  keys[K_g].may_letter = 'G';
  keys[K_h].letter = 'h';
  keys[K_h].may_letter = 'H';
  keys[K_i].letter = 'i';
  keys[K_i].may_letter = 'I';
  keys[K_j].letter = 'j';
  keys[K_j].may_letter = 'J';
  keys[K_k].letter = 'k';
  keys[K_k].may_letter = 'K';
  keys[K_l].letter = 'l';
  keys[K_l].may_letter = 'L';
  keys[K_m].letter = 'm';
  keys[K_m].may_letter = 'M';
  keys[K_n].letter = 'n';
  keys[K_n].may_letter = 'N';
  keys[K_o].letter = 'o';
  keys[K_o].may_letter = 'O';
  keys[K_p].letter = 'p';
  keys[K_p].may_letter = 'P';
  keys[K_q].letter = 'q';
  keys[K_q].may_letter = 'Q';
  keys[K_r].letter = 'r';
  keys[K_r].may_letter = 'R';
  keys[K_s].letter = 's';
  keys[K_s].may_letter = 'S';
  keys[K_t].letter = 't';
  keys[K_t].may_letter = 'T';
  keys[K_u].letter = 'u';
  keys[K_u].may_letter = 'U';
  keys[K_v].letter = 'v';
  keys[K_v].may_letter = 'V';
  keys[K_w].letter = 'w';
  keys[K_w].may_letter = 'W';
  keys[K_x].letter = 'x';
  keys[K_x].may_letter = 'X';
  keys[K_y].letter = 'y';
  keys[K_y].may_letter = 'Y';
  keys[K_z].letter = 'z';
  keys[K_z].may_letter = 'Z';

  /* This are special inputs that doesn´t have any letter */
  for (int i = 36; i < MAX_INPUTS; i++)
    keys[i].letter = '\0';
  for (int i = 36; i < MAX_INPUTS; i++)
    keys[i].may_letter = '\0';

  /* Exceptions the space bar */
  keys[SPACE].letter = ' ';
  keys[SPACE].may_letter = ' ';
  keys[PLUS].letter = '+';
  keys[PLUS].may_letter = '*';
  keys[MINUS].letter = '-';
  keys[MINUS].may_letter = '_';
  keys[COMMA].letter = ',';
  keys[COMMA].may_letter = ';';
  keys[DOT].letter = '.';
  keys[DOT].may_letter = ':';
}

void TakeKeyboard(Keys *keys)
{
  // Limpia los inputs del frame anterior
  for (unsigned int i = 0; i < MAX_INPUTS - 1; i++)
  {
    keys[i].down = false;
    keys[i].up = false;
  }

  // Copia los inputs del frame anterior
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    #ifdef IMGUI_API
    ImGui_ImplSDL2_ProcessEvent(&event);
    #endif
    
    if (event.type == SDL_QUIT)
    {
      keys[FULL_EXIT_WINDOW].down = true;
      keys[FULL_EXIT_WINDOW].up = true;
    }
    if (event.type == SDL_KEYDOWN)
    {
      switch (event.key.keysym.sym)
      {
      // Numbers
      case SDLK_0:
        keys[K_0].down = true;
        break;
      case SDLK_1:
        keys[K_1].down = true;
        break;
      case SDLK_2:
        keys[K_2].down = true;
        break;
      case SDLK_3:
        keys[K_3].down = true;
        break;
      case SDLK_4:
        keys[K_4].down = true;
        break;
      case SDLK_5:
        keys[K_5].down = true;
        break;
      case SDLK_6:
        keys[K_6].down = true;
        break;
      case SDLK_7:
        keys[K_7].down = true;
        break;
      case SDLK_8:
        keys[K_8].down = true;
        break;
      case SDLK_9:
        keys[K_9].down = true;
        break;

      // Minusc keys
      case SDLK_a:
        keys[K_a].down = true;
        break;
      case SDLK_b:
        keys[K_b].down = true;
        break;
      case SDLK_c:
        keys[K_c].down = true;
        break;
      case SDLK_d:
        keys[K_d].down = true;
        break;
      case SDLK_e:
        keys[K_e].down = true;
        break;
      case SDLK_f:
        keys[K_f].down = true;
        break;
      case SDLK_g:
        keys[K_g].down = true;
        break;
      case SDLK_h:
        keys[K_h].down = true;
        break;
      case SDLK_i:
        keys[K_i].down = true;
        break;
      case SDLK_j:
        keys[K_j].down = true;
        break;
      case SDLK_k:
        keys[K_k].down = true;
        break;
      case SDLK_l:
        keys[K_l].down = true;
        break;
      case SDLK_m:
        keys[K_m].down = true;
        break;
      case SDLK_n:
        keys[K_n].down = true;
        break;
      case SDLK_o:
        keys[K_o].down = true;
        break;
      case SDLK_p:
        keys[K_p].down = true;
        break;
      case SDLK_q:
        keys[K_q].down = true;
        break;
      case SDLK_r:
        keys[K_r].down = true;
        break;
      case SDLK_s:
        keys[K_s].down = true;
        break;
      case SDLK_t:
        keys[K_t].down = true;
        break;
      case SDLK_u:
        keys[K_u].down = true;
        break;
      case SDLK_v:
        keys[K_v].down = true;
        break;
      case SDLK_w:
        keys[K_w].down = true;
        break;
      case SDLK_x:
        keys[K_x].down = true;
        break;
      case SDLK_y:
        keys[K_y].down = true;
        break;
      case SDLK_z:
        keys[K_z].down = true;
        break;

      // F Keys
      case SDLK_F1:
        keys[F1].down = true;
        break;
      case SDLK_F2:
        keys[F2].down = true;
        break;
      case SDLK_F3:
        keys[F3].down = true;
        break;
      case SDLK_F4:
        keys[F4].down = true;
        break;
      case SDLK_F5:
        keys[F5].down = true;
        break;
      case SDLK_F6:
        keys[F6].down = true;
        break;
      case SDLK_F7:
        keys[F7].down = true;
        break;
      case SDLK_F8:
        keys[F8].down = true;
        break;
      case SDLK_F9:
        keys[F9].down = true;
        break;
      case SDLK_F10:
        keys[F10].down = true;
        break;
      case SDLK_F11:
        keys[F11].down = true;
        break;
      case SDLK_F12:
        keys[F12].down = true;
        break;

      // Some specials
      case SDLK_LALT:
        keys[ALT].down = true;
        break;
      case SDLK_RALT:
        keys[ALT].down = true;
        break;
      case SDLK_TAB:
        keys[TAB].down = true;
        break;
      case SDLK_KP_ENTER:
        keys[ENTER].down = true;
        break;
      case SDLK_RETURN:
        keys[ENTER].down = true;
        break;
      case SDLK_LSHIFT:
        keys[SHIFT].down = true;
        break;
      case SDLK_RSHIFT:
        keys[SHIFT].down = true;
        break;
      case SDLK_SPACE:
        keys[SPACE].down = true;
        break;
      case SDLK_BACKSPACE:
        keys[BACK_SPACE].down = true;
        break;
      case SDLK_ESCAPE:
        keys[EXIT_WINDOW].down = true;
        keys[ESCAPE].down = true;
        break;
      case SDLK_DELETE:
        keys[DELETE].down = true;
        break;
      case SDLK_RCTRL:
        keys[CONTROL].down = true;
        break;
      case SDLK_LCTRL:
        keys[CONTROL].down = true;
        break;
      case SDLK_UP:
        keys[UP].down = true;
        break;
      case SDLK_DOWN:
        keys[DOWN].down = true;
        break;
      case SDLK_LEFT:
        keys[LEFT].down = true;
        break;
      case SDLK_RIGHT:
        keys[RIGHT].down = true;
        break;
      case SDLK_PLUS:
        keys[PLUS].down = true;
        break;
      case SDLK_MINUS:
        keys[MINUS].down = true;
        break;
      case SDLK_COMMA:
        keys[COMMA].down = true;
        break;
      case SDLK_PERIOD:
        keys[DOT].down = true;
        break;
      }
    }
    if (event.type == SDL_KEYUP)
    {
      switch (event.key.keysym.sym)
      {
      // Numbers
      case SDLK_0:
        keys[K_0].up = true;
        break;
      case SDLK_1:
        keys[K_1].up = true;
        break;
      case SDLK_2:
        keys[K_2].up = true;
        break;
      case SDLK_3:
        keys[K_3].up = true;
        break;
      case SDLK_4:
        keys[K_4].up = true;
        break;
      case SDLK_5:
        keys[K_5].up = true;
        break;
      case SDLK_6:
        keys[K_6].up = true;
        break;
      case SDLK_7:
        keys[K_7].up = true;
        break;
      case SDLK_8:
        keys[K_8].up = true;
        break;
      case SDLK_9:
        keys[K_9].up = true;
        break;

      // Minusc keys
      case SDLK_a:
        keys[K_a].up = true;
        break;
      case SDLK_b:
        keys[K_b].up = true;
        break;
      case SDLK_c:
        keys[K_c].up = true;
        break;
      case SDLK_d:
        keys[K_d].up = true;
        break;
      case SDLK_e:
        keys[K_e].up = true;
        break;
      case SDLK_f:
        keys[K_f].up = true;
        break;
      case SDLK_g:
        keys[K_g].up = true;
        break;
      case SDLK_h:
        keys[K_h].up = true;
        break;
      case SDLK_i:
        keys[K_i].up = true;
        break;
      case SDLK_j:
        keys[K_j].up = true;
        break;
      case SDLK_k:
        keys[K_k].up = true;
        break;
      case SDLK_l:
        keys[K_l].up = true;
        break;
      case SDLK_m:
        keys[K_m].up = true;
        break;
      case SDLK_n:
        keys[K_n].up = true;
        break;
      case SDLK_o:
        keys[K_o].up = true;
        break;
      case SDLK_p:
        keys[K_p].up = true;
        break;
      case SDLK_q:
        keys[K_q].up = true;
        break;
      case SDLK_r:
        keys[K_r].up = true;
        break;
      case SDLK_s:
        keys[K_s].up = true;
        break;
      case SDLK_t:
        keys[K_t].up = true;
        break;
      case SDLK_u:
        keys[K_u].up = true;
        break;
      case SDLK_v:
        keys[K_v].up = true;
        break;
      case SDLK_w:
        keys[K_w].up = true;
        break;
      case SDLK_x:
        keys[K_x].up = true;
        break;
      case SDLK_y:
        keys[K_y].up = true;
        break;
      case SDLK_z:
        keys[K_z].up = true;
        break;

      // F Keys
      case SDLK_F1:
        keys[F1].up = true;
        break;
      case SDLK_F2:
        keys[F2].up = true;
        break;
      case SDLK_F3:
        keys[F3].up = true;
        break;
      case SDLK_F4:
        keys[F4].up = true;
        break;
      case SDLK_F5:
        keys[F5].up = true;
        break;
      case SDLK_F6:
        keys[F6].up = true;
        break;
      case SDLK_F7:
        keys[F7].up = true;
        break;
      case SDLK_F8:
        keys[F8].up = true;
        break;
      case SDLK_F9:
        keys[F9].up = true;
        break;
      case SDLK_F10:
        keys[F10].up = true;
        break;
      case SDLK_F11:
        keys[F11].up = true;
        break;
      case SDLK_F12:
        keys[F12].up = true;
        break;

      // Some specials
      case SDLK_LALT:
        keys[ALT].up = true;
        break;
      case SDLK_RALT:
        keys[ALT].up = true;
        break;
      case SDLK_TAB:
        keys[TAB].up = true;
        break;
      case SDLK_KP_ENTER:
        keys[ENTER].up = true;
        break;
      case SDLK_LSHIFT:
        keys[SHIFT].up = true;
        break;
      case SDLK_RSHIFT:
        keys[SHIFT].up = true;
        break;
      case SDLK_SPACE:
        keys[SPACE].up = true;
        break;
      case SDLK_BACKSPACE:
        keys[BACK_SPACE].up = true;
        break;
      case SDLK_ESCAPE:
        keys[EXIT_WINDOW].up = true;
        keys[ESCAPE].up = true;
        break;
      case SDLK_DELETE:
        keys[DELETE].up = true;
        break;
      case SDLK_RCTRL:
        keys[CONTROL].up = true;
        break;
      case SDLK_LCTRL:
        keys[CONTROL].up = true;
        break;
      case SDLK_UP:
        keys[UP].up = true;
        break;
      case SDLK_DOWN:
        keys[DOWN].up = true;
        break;
      case SDLK_LEFT:
        keys[LEFT].up = true;
        break;
      case SDLK_RIGHT:
        keys[RIGHT].up = true;
        break;
      case SDLK_PLUS:
        keys[PLUS].up = true;
        break;
      case SDLK_MINUS:
        keys[MINUS].up = true;
        break;
      case SDLK_COMMA:
        keys[COMMA].up = true;
        break;
      case SDLK_PERIOD:
        keys[DOT].up = true;
        break;
      }
    }
  }
}

bool EVENT_DOWN(int input, Keys *keys)
{
  bool ret = keys[input].down;
  return ret;
}

bool EVENT_UP(int input, Keys *keys)
{
  bool ret = keys[input].up;
  return ret;
}
