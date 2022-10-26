#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstring>
#include <cfloat>
#include <mv_math.h>
#include <SDL_event_control.h>
#include <SDL_colors.h>

#include <esfera_3d.h>
#include <my_window.h>

int k_TextHeight = 28;
int k_TextWitdh = (k_TextHeight*4/7)-1;
int g_Filas = 35;
int g_Columnas = 50;

#ifndef RGBA
#define RGBA(x) x.r,x.g,x.b,x.a
#endif

#define FONT_PATH "../data/fonts/anonymous_pro.ttf"
#define FONT_PATH_1 "/usr/share/fonts/truetype/lao/Phetsarath_OT.ttf"

MV::Pnt2 max_win = {(float)(k_TextWitdh * g_Columnas), (float)(k_TextHeight *g_Filas)};
MV::Pnt2 middle_win = {max_win.x / 2, max_win.y / 2};
MV::Pnt2 min_win = {0, 0};

void Orbitar_Camara(MV::Pnt3 centro_orbita, MV::Pnt3 p_orbita, MV::Pnt3 &punto)
{
  MV::Mat4 rot_x;
  if (p_orbita.x != 0)
    rot_x = MV::Mat4RotateX((p_orbita.x * PI) / 180);
  MV::Mat4 rot_y;
  if (p_orbita.y != 0)
    rot_y = MV::Mat4RotateY((p_orbita.y * PI) / 180);
  MV::Mat4 rot_z;
  if (p_orbita.z != 0)
    rot_z = MV::Mat4RotateZ((p_orbita.z * PI) / 180);

  MV::Mat4 model = MV::Mat4Identity();
  if (p_orbita.x != 0)
    model = MV::Mat4Multiply(model, rot_x);
  if (p_orbita.y != 0)
    model = MV::Mat4Multiply(model, rot_y);
  if (p_orbita.z != 0)
    model = MV::Mat4Multiply(model, rot_z);

  punto = MV::Vec_Resta(punto, centro_orbita);
  punto = MV::Mat4TransformVec3(model, punto);
  punto = MV::Vec_Sum(punto, centro_orbita);
}

int main(int argc, char **argv)
{

  srand(time(nullptr));
  //////////////////////////////////////////////////////////////////////////
  // Comprobante de metodo burbuja para ordenar numeros
  /*
    int array[220];

    for(int i=0; i<220; i++) array[i]=iRand(2000,-1000);

    for(int i=0; i<220; i++){
      for(int j = 0; j<220; j++){
        if(array[i]<array[j]){
          int aux = array[i];
          array[i]=array[j];
          array[j]=aux;
        }
      }
    }
    for(int i=0; i<220; i++){
      std::cout << "I: " << i << ", Array: " << array[i] << std::endl;
    }
    std::cout << std::endl;
  */
  //////////////////////////////////////////////////////////////////////////

  // Inicializacion de los servicios de SDL
  TTF_Init();
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    std::cout << "Failed at SDL_Init(): " << SDL_GetError() << std::endl;
    return -1;
  }

  // Inicializacion ventana de juego
  My_Window win = *new My_Window(k_TextHeight, k_TextWitdh, g_Filas, g_Columnas);
  if (!win.setTextFont((char *)FONT_PATH))
  {
    std::cout << "Failed at TTF_Font_Init(): " << SDL_GetError() << std::endl;
    return -1;
  }
  win.setGameTitle(*argv);

  Esfera sun = *new Esfera(colores[BLANCO], 10, {30,30,30}, {middle_win.x, middle_win.y, 0.0f});
  int max_planets = 4;
  Esfera *planet = (Esfera *)calloc(max_planets, sizeof(Esfera));
  sun.rotar({ fRand(0.075f,0),fRand(0.075f,0), fRand(0.075f,0) });

  *(planet + 0) = *new Esfera(colores[0], 3, {6, 6, 6}, {sun.desp_.x - 50, sun.desp_.y + 50, 0.0f}, {0, 0, 0}, {0.01f, 0.01f, 0.0f}, sun.desp_);
  *(planet + 1) = *new Esfera(colores[1], 3, {5, 5, 5}, {sun.desp_.x, sun.desp_.y + 50, 0.0f}, {0, 0, 0}, {0.01f, 0.0f, 0.0f}, sun.desp_);
  *(planet + 2) = *new Esfera(colores[2], 3, {4, 4, 4}, {sun.desp_.x - 70, sun.desp_.y, 0.0f}, {0, 0, 0}, {0.0f, 0.01f, 0.0f}, sun.desp_);
  *(planet + 3) = *new Esfera(colores[3], 3, {3, 3, 3}, {sun.desp_.x + 70, sun.desp_.y + 70, 0.0f}, {0, 0, 0}, {0.01f, -0.01f, 0.0f}, sun.desp_);

  // Imprimir en pantalla los datos de la ventana
  std::cout << "WIN_X: " << max_win.x << ", WIN_Y: " << max_win.y << std::endl;
  std::cout << "HEIGHT: " << k_TextHeight << ", WIDTH: " << k_TextWitdh << ", g_Filas: " << g_Filas << ", g_Columnas: " << g_Columnas << std::endl;

  MV::Pnt3 camara = {middle_win.x, middle_win.y, -100.0f};
  MV::Pnt3 light = {0,middle_win.y,0};
  MV::Pnt3 mira = sun.desp_;
  while (win.runing)
  {
    win.whileInit();

    sun.draw(win.render, camara, sun.desp_, light, false);
    sun.rotar({fRand(0.0075f,0),fRand(0.0075f,0), fRand(0.0075f,0)});

    if (EVENT_DOWN(K_o))
    {
      sun.imprime();
      MV::Vec_Print(camara, "Camera point");
      MV::Vec_Print(sun.desp_, "Desplazamiento");
      std::cout << "Magnitud: " << MV::Vec_Magn(MV::Vec_Resta(camara, sun.desp_)) << std::endl;
    }

    // for (int i = 0; i < max_planets; i++)
    // {
    //   (planet + i)->orbitar(0.1f);
    //   (planet + i)->draw(win.render, camara, mira, light, false);
    // }

    if (EVENT_DOWN(DOWN))
      Orbitar_Camara(mira, {1, 0, 0}, camara);
    if (EVENT_DOWN(UP))
      Orbitar_Camara(mira, {-1, 0, 0}, camara);
    if (EVENT_DOWN(RIGHT))
      Orbitar_Camara(mira, {0, 1, 0}, camara);
    if (EVENT_DOWN(LEFT))
      Orbitar_Camara(mira, {0, -1, 0}, camara);
    if (EVENT_DOWN(K_n))
      Orbitar_Camara(mira, {0, 0, 1}, camara);
    if (EVENT_DOWN(K_m))
      Orbitar_Camara(mira, {0, 0, -1}, camara);

    if (EVENT_DOWN(K_a))
    {
      camara.x--;
    }
    if (EVENT_DOWN(K_d))
    {
      camara.x++;
    }
    if (EVENT_DOWN(K_w))
    {
      camara.y--;
    }
    if (EVENT_DOWN(K_s))
    {
      camara.y++;
    }
    if (EVENT_DOWN(K_q))
    {
      camara.z--;
    }
    if (EVENT_DOWN(K_e))
    {
      camara.z++;
    }

    win.whileEnd();
  }

  win.Destroy();
  TTF_Quit();
  SDL_Quit();

  return 0;
}
