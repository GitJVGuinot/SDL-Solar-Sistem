/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

#include <main.h>

int main(int argc, char **argv)
{
  system(CLEAR_CONSOLE);
  srand(time(nullptr));

  // Inputs init
  Keys keys[MAX_INPUTS];
  InitKeyboard(keys);

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
  std::vector<struct Objects> objects(7);
  Vec3 light;
  Render drawRender;
  Vec3 *objects_mov = nullptr;
  Vec3 *objects_scale = nullptr;
  Basic_Objects_Init(objects, light, drawRender, &objects_mov, &objects_scale);

  // Print window data on console
  std::cout << "Window Information" << std::endl;
  std::cout << "Win_x: " << g_max_win.x << ", Win_y: " << g_max_win.y << std::endl;
  std::cout << "Height: " << k_TextHeight << ", Width: " << k_TextWitdh << ", Rows: " << k_Rows << ", Columns: " << k_Columns << std::endl;

  while (win.runing)
  {
    // Start of the graphic window
    win.whileInit(keys);
    Debug_Window::Update();
    drawRender.inputs(keys);

    // Objects orbit
    for (int i = 0; i < (int)objects.size(); i++)
    {
      switch (objects.at(i).type)
      {
      case typeSphere:
        objects.at(i).sphere.orbit();
        break;
      case typeCube:
        objects.at(i).cube.orbit();
        break;
      case typeFigure:
        objects.at(i).figure.orbit();
        break;
      }
    }

    if(objects.size()>6){
      switch (objects.at(6).type){
        case typeSphere:
          objects.at(6).sphere.rotation(Vec3(0,0.1f,0));
          break;
        case typeCube:
          objects.at(6).cube.rotation(Vec3(0,0.1f,0));
          break;
        case typeFigure:
          objects.at(6).figure.rotation(Vec3(0,0.1f,0));
          break;
      }
    }

    // Get the positioning variables on the screen
    for (int i = 0; i < (int)objects.size(); i++)
    {
      switch (objects.at(i).type)
      {
      case typeSphere:
        objects_mov[i] = objects.at(i).sphere.mov_;
        objects_scale[i] = objects.at(i).sphere.getScale();
        break;
      case typeCube:
        objects_mov[i] = objects.at(i).cube.mov_;
        objects_scale[i] = objects.at(i).cube.getScale();
        break;
      case typeFigure:
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
        objects.at(order[i]).sphere.draw(keys, win.render, drawRender, light, order[i]);
        break;
      case typeCube:
        objects.at(order[i]).cube.draw(keys, win.render, drawRender, light, order[i]);
        break;
      case typeFigure:
        objects.at(order[i]).figure.draw(keys, win.render, drawRender, light, order[i]);
        break;
      }
    }

    // ImGui window for objects control
    Camera_Control(drawRender, win, {win.win_x, win.win_y});
    Objects_Control(objects, &objects_mov, &objects_scale, g_max_win);

    // Limits camera draw
    drawRender.cameraDraw(keys, win.render, {win.win_x, win.win_y});

    // End of grafic window
    Debug_Window::Render();
    win.whileEnd(keys);
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
  std::cout << "Sizeof Entity: " << sizeof(struct Entity) << std::endl;

  std::cout << "Generating objects..." << std::endl;

  for (int i = 0; i < 5; i++)
    objects.at(i).type = typeSphere;
  objects.at(0).sphere.init(g_colors[WHITE], false, 15, {12, 12, 12}, {g_middle_win.x, g_middle_win.y, 0.0f});
  objects.at(1).sphere.init({255,0,0,127}, true, 10, {2, 2, 2}, {objects.at(0).sphere.mov_.x - 40, objects.at(0).sphere.mov_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.01f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(2).sphere.init(g_colors[GREEN], false, 10, {2, 2, 2}, {objects.at(0).sphere.mov_.x, objects.at(0).sphere.mov_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.0f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(3).sphere.init(g_colors[BLUE], false, 10, {2, 2, 2}, {objects.at(0).sphere.mov_.x - 60, objects.at(0).sphere.mov_.y, 0.0f}, {0, 0, 0}, {0.0f, 0.01f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(4).sphere.init(g_colors[CYAN], false, 10, {2, 2, 2}, {objects.at(0).sphere.mov_.x + 60, objects.at(0).sphere.mov_.y + 60, 0.0f}, {0, 0, 0}, {0.01f, -0.01f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(4).sphere.lines_ = true;
  objects.at(4).sphere.linesColor_ = g_colors[CYAN];
  for (int i = 1; i < 5; i++)
    objects.at(i).sphere.orbit_vel_ = 10.0f;

  objects.at(5).type = typeCube;
  objects.at(5).cube.init({255, 255, 255, 128}, true, {2.1f, 2.1f, 2.1f}, {objects.at(0).sphere.mov_.x - 40, objects.at(0).sphere.mov_.y + 40, 0.0f}, {0, 0, 0}, {0.01f, 0.01f, 0.0f}, objects.at(0).sphere.mov_);
  objects.at(5).cube.orbit_vel_ = 10.0f;
  objects.at(5).cube.lines_ = true;
  objects.at(5).cube.linesColor_ = {255, 0, 255, 255};

  objects.at(6).type = typeFigure;
  objects.at(6).figure.init("../data/3d_obj/keqing.obj", {175,0,255,255}, true, {15, 15, 15}, {objects.at(0).sphere.mov_.x-50 , objects.at(0).sphere.mov_.y , 0.0f});

  std::cout << "Objects generated" << std::endl;

  light = objects.at(0).sphere.mov_;

  *objects_mov = (Vec3 *)realloc(*objects_mov, objects.size() * sizeof(Vec3));
  *objects_scale = (Vec3 *)realloc(*objects_scale, objects.size() * sizeof(Vec3));

  drawRender.init(g_max_win, {g_middle_win.x, g_middle_win.y, 100});
}
