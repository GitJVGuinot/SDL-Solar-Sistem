#include <main.h>

int main(int argc, char **argv)
{
  srand(time(nullptr));

  // Inicializacion de los inputs
  Keys keys[MAX_INPUTS];
  InitKeyboard(keys);

  // Inicializacion de los servicios de SDL
  TTF_Init();
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    std::cout << "Failed at SDL_Init(): " << SDL_GetError() << std::endl;
    return -1;
  }

  // Inicializacion ventana de juego
  My_Window win = *new My_Window(k_TextHeight, k_TextWitdh, k_Filas, k_Columnas, colores[BLACK]);
  if (!win.setTextFont((char *)FONT_PATH))
  {
    std::cout << "Failed at TTF_Font_Init(): " << SDL_GetError() << std::endl;
    return -1;
  }
  win.setGameTitle(*argv);

  // Inicializacion de ImGui
  Debug_Window::Init(win.window, win.render);

  // Inicializacion de variables
  std::vector <struct Objects>objects(6);
  MV::Pnt3 light;
  Render drawRender;
  MV::Pnt3 *objects_mov = nullptr;
  MV::Pnt3 *objects_scale = nullptr;
  Basic_Objects_Init(objects, light, drawRender, &objects_mov, &objects_scale);

  // Imprimir en pantalla los datos de la ventana
  std::cout << "Window Information" << std::endl;
  std::cout << "Win_x: " << max_win.x << ", Win_y: " << max_win.y << std::endl;
  std::cout << "Height: " << k_TextHeight << ", Width: " << k_TextWitdh << ", Rows: " << k_Filas << ", Columns: " << k_Columnas << std::endl;

  while (win.runing)
  {
    // Inicio de la ventana grafica
    win.whileInit(keys);
    Debug_Window::Update();
    drawRender.inputs(keys);

    // Orbita de los objetos
    for (int i = 0; i < objects.size(); i++){
      switch (objects.at(i).type) {
        case typeSphere:
          objects.at(i).sphere.orbitar();
          break;
        case typeCube:
          objects.at(i).cube.orbitar();
          break;
      }
    }

    // Obtener las variables de posicionamiento en pantalla
    for (int i = 0; i < objects.size(); i++){
      switch (objects.at(i).type) {
        case typeSphere:
          objects_mov[i] = objects.at(i).sphere.mov_;
          objects_scale[i] = objects.at(i).sphere.getScale();
          break;
        case typeCube:
          objects_mov[i] = objects.at(i).cube.mov_;
          objects_scale[i] = objects.at(i).cube.getScale();
          break;
      }
    }

    // Orden de dibujado en pantalla
    int *order = drawRender.getOrder(objects_mov, objects_scale, objects.size());

    // Dibujado de objetos
    for (int i = 0; i < objects.size(); i++)
    {
      switch (objects.at(order[i]).type) {
        case typeSphere:
          objects.at(order[i]).sphere.draw(keys, win.render, drawRender, light, nullptr);
          break;
        case typeCube:
          objects.at(order[i]).cube.draw(keys, win.render, drawRender, light, nullptr);
          break;
      }
    }

    // ImGui windows para el control de la camara y/o los bojetos
    Camera_Control(drawRender, win, {win.win_x, win.win_y});
    Objects_Control(objects, &objects_mov, &objects_scale, max_win);

    // Dibujado de limites de la camara
    drawRender.cameraDraw(keys, win.render, {win.win_x, win.win_y});

    // Fin de la ventana grafica
    Debug_Window::Render();
    win.whileEnd(keys);
  }

  // Liberacion de memory allocs
  win.Destroy();
  TTF_Quit();
  SDL_Quit();
  Debug_Window::Quit();

  return 0;
}
