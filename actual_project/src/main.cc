/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

#include <main.h>

int total_planets = 20; // Cambia a la cantidad que necesites

int main(int argc, char **argv)
{
  system(CLEAR_CONSOLE);
  system("title Solar System");
  srand(time(nullptr));

  // Inputs init
  InitKeyboard();

  // SDL services init
  TTF_Init();
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    std::cout << "Failed at SDL_Init(): " << SDL_GetError() << std::endl;
    return -1;
  }

  // Game window init
  My_Window win = *new My_Window(k_TextHeight, k_TextWitdh, k_Rows, k_Columns, g_colors[BLACK]);
  if (!win.setTextFont((char *)FONT_PATH))
  {
    std::cout << "Failed at TTF_Font_Init(): " << SDL_GetError() << std::endl;
    return -1;
  }
  win.setGameTitle(*argv);

  // ImGui init
  Debug_Window::Init(win.window, win.render);

  // Variables init
  std::vector<struct Objects> objects(total_planets);
  Vec3 light;
  Render drawRender;
  Vec3 *objects_mov = nullptr;
  Vec3 *objects_scale = nullptr;
  Basic_Objects_Init(objects, light, drawRender, &objects_mov, &objects_scale);

  // Print window data on console
  std::cout << "Window Information" << std::endl;
  std::cout << "Win_x: " << g_max_win.x << ", Win_y: " << g_max_win.y << std::endl;
  std::cout << "Height: " << k_TextHeight << ", Width: " << k_TextWitdh << ", Rows: " << k_Rows << ", Columns: " << k_Columns << std::endl;

  bool showImgui = true;
  float dt = 0.016f;
  while (win.runing)
  {
    // Start of the graphic window
    win.whileInit();
    Debug_Window::Update();
    drawRender.inputs();

    // Limits camera draw & light
    drawRender.cameraDraw(win.render, {win.win_x, win.win_y}, light);

    // Objects orbit
    // Get the positioning variables on the screen
    for (int i = 0; i < (int)objects.size(); i++)
    {
      switch (objects.at(i).type)
      {
      case typeSphere:
        objects.at(i).sphere.orbit(dt);
        objects_mov[i] = objects.at(i).sphere.mov_;
        objects_scale[i] = objects.at(i).sphere.getScale();
        break;
      case typeCube:
        objects.at(i).cube.orbit(dt);
        objects_mov[i] = objects.at(i).cube.mov_;
        objects_scale[i] = objects.at(i).cube.getScale();
        break;
      case typeFigure:
        objects.at(i).figure.orbit(dt);
        objects_mov[i] = objects.at(i).figure.mov_;
        objects_scale[i] = objects.at(i).figure.getScale();
        break;
      }
    }

    // Drawing order on screen
    int *order = drawRender.getOrder(objects_mov, objects_scale, objects.size());

    // Objects draw
    for (int i = 0; i < (int)objects.size(); i++)
    {
      switch (objects.at(order[i]).type)
      {
      case typeSphere:
        objects.at(order[i]).sphere.draw(win.render, drawRender, light, order[i]);
        break;
      case typeCube:
        objects.at(order[i]).cube.draw(win.render, drawRender, light, order[i]);
        break;
      case typeFigure:
        objects.at(order[i]).figure.draw(win.render, drawRender, light, order[i]);
        break;
      }
    }

    // ImGui window for objects control
    if (EVENT_DOWN(F11))
      objects.at(1).sphere.startDestroy();
    if (EVENT_DOWN(F12))
      showImgui = !showImgui;
    if (showImgui)
    {
      Camera_Control(drawRender, win, {win.win_x, win.win_y}, light, dt);
      Objects_Control(objects, &objects_mov, &objects_scale, g_max_win);
    }

    // End of grafic window
    Debug_Window::Render();
    win.whileEnd();
    dt = 1.0f / win.frame_rate;
  }

  // Memory allocs liberation
  win.Destroy();
  TTF_Quit();
  SDL_Quit();
  Debug_Window::Quit();

  return 0;
}

void Basic_Objects_Init(std::vector<struct Objects> &objects, Vec3 &light, Render &drawRender, Vec3 **objects_mov, Vec3 **objects_scale)
{
  std::cout << "Sizeof Entity: " << sizeof(class Entity) << std::endl;

  std::cout << "Generating objects..." << std::endl;

  // Inicializar el primer objeto (la esfera central)
  objects.at(0).type = typeSphere;
  objects.at(0).sphere.init(
      SDL_Color{255, 255, 255, 100},         // Color blanco
      true,                                  // Relleno
      20,                                    // Resolución
      {30, 30, 30},                          // Escala
      {g_middle_win.x, g_middle_win.y, 0.0f} // Posición central
  );

  // Bucle para inicializar los demás planetas orbitando
  for (int i = 1; i < total_planets; i++)
  {
    objects.at(i).type = typeSphere;

    // Posicionamos cada planeta en un círculo alrededor del punto (0,0,0)
    float angle = i * (360.0f / total_planets); // Ángulo de separación entre planetas
    float distance = 40.0f + (i * 10);          // Distancia creciente desde el centro de la órbita (0,0,0)

    // Convertimos el ángulo a radianes para calcular la posición inicial de los planetas
    float radians = angle * M_PI / 180.0f;
    float x_pos = objects.at(0).sphere.mov_.x + distance * cos(radians); // Posición X inicial del planeta en órbita
    float y_pos = objects.at(0).sphere.mov_.y + distance * sin(radians); // Posición Y inicial del planeta en órbita

    // Calcular la velocidad tangencial
    float vel_x = -0.01f * sin(radians); // Velocidad tangente en X (90 grados de la posición)
    float vel_y = 0.01f * cos(radians);  // Velocidad tangente en Y

    // Iniciar la esfera en una posición orbital alrededor de (0,0,0)
    objects.at(i).sphere.init(
        g_colors[i % 6],          // Color del planeta
        true,                     // Relleno
        10,                       // Resolución
        {5, 5, 5},                // Escala
        {x_pos, y_pos, 0.0f},     // Posición calculada en la órbita
        {0, 0, 0},                // Rotación inicial
        {vel_x, vel_y, 0.0f},     // Velocidad tangencial para orbitar
        objects.at(0).sphere.mov_ // Centro de la órbita
    );

    // Establecer la velocidad de órbita de los planetas
    objects.at(i).sphere.orbit_vel_ = 100.0f + i * 5.0f; // Variar ligeramente la velocidad orbital por planeta
  }

  // Establecer la velocidad de órbita
  for (int i = 1; i < total_planets; i++)
    objects.at(i).sphere.orbit_vel_ = 1000.0f;

  std::cout << "Objects generated" << std::endl;

  light = objects.at(0).sphere.mov_;

  *objects_mov = (Vec3 *)realloc(*objects_mov, objects.size() * sizeof(Vec3));
  *objects_scale = (Vec3 *)realloc(*objects_scale, objects.size() * sizeof(Vec3));

  drawRender.init(g_max_win, {g_middle_win.x, g_middle_win.y, 100});
}
