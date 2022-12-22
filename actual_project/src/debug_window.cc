/// @author F.c.o Javier Guinot Almenar <guinotal@esat-alumni.com>

#include <debug_window.h>

void Debug_Window::Init(SDL_Window *window, SDL_Renderer *render)
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(window, render);
  ImGui_ImplSDLRenderer_Init(render);

  ImVec4 *colors = ImGui::GetStyle().Colors;
  ImGui::GetStyle().WindowRounding = 1.0f;
  colors[ImGuiCol_WindowBg] = ImVec4(1.00f, 0.0f, 1.00f, 0.25f);
}

void Debug_Window::Update()
{
  // Imgui loop initialise
  ImGui_ImplSDLRenderer_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
}

void Debug_Window::Render()
{
  ImGui::Render();
  // Send ImGui commands to GPU
  ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void Debug_Window::Input(SDL_Event *ev)
{
  ImGui_ImplSDL2_ProcessEvent(ev);
}

void Debug_Window::Quit()
{
  // Imgui clean-Up
  ImGui_ImplSDLRenderer_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

void Camera_Control(Render &render, My_Window &win, Vec2 max_win)
{
  if (ImGui::Begin("Camera controls"))
  {

    ImGui::Checkbox("FPS Control?", &win.fps_control);
    ImGui::Checkbox("Show FPS?", &win.show_fps);

    Vec3 mov = {0, 0, 0};
    ImGui::Text("Desp-> X: %0.0f, Y: %0.0f, Z: %0.0f", render.camera_.x, render.camera_.y, render.camera_.z);
    ImGui::SliderFloat("Add X", &mov.x, -1, 1);
    ImGui::SliderFloat("Add Y", &mov.y, -1, 1);
    ImGui::SliderFloat("Add Z", &mov.z, -1, 1);
    mov.x *= -1;
    mov.z *= -1;
    if (mov.x != 0 || mov.y != 0 || mov.z != 0)
      render.translation(mov);

    Vec3 rot = {0, 0, 0};
    ImGui::Text("Up-> X: %f, Y: %f, Z: %f", render.getUp().x, render.getUp().y, render.getUp().z);
    ImGui::SliderFloat("Rot X", &rot.x, -1, 1);
    ImGui::SliderFloat("Rot Y", &rot.y, -1, 1);
    ImGui::SliderFloat("Rot Z", &rot.z, -1, 1);
    rot.z *= -1;
    if (rot.x != 0 || rot.y != 0 || rot.z != 0)
      render.rotation(rot);

    float far = render.getFar();
    float near = render.getNear();
    ImGui::Text("Best far=1000 & near=1");
    ImGui::SliderFloat("Far", &far, 2, 10000);
    ImGui::SliderFloat("Near", &near, 0, 100);
    if (far != render.getFar() || near != render.getNear())
      render.init(max_win, render.camera_, near, far);

    if (ImGui::Button("Reset camera values"))
    {
      render.reset(max_win);
    }

    ImGui::End();
  }
  else
    ImGui::End();
}

void Objects_Control(std::vector<Objects> &objects, Vec3 **objects_mov, Vec3 **objects_scale, Vec2 max_win)
{

  if (ImGui::Begin("Objects controls"))
  {
    if (objects.size() < 100)
    {
      if (ImGui::Button("Create Object"))
      {
        *objects_mov = (Vec3 *)realloc(*objects_mov, (objects.size() + 1) * sizeof(Vec3));
        *objects_scale = (Vec3 *)realloc(*objects_scale, (objects.size() + 1) * sizeof(Vec3));
        std::vector<Objects> copyObjects(objects.size());
        for (int i = 0; i < (int)objects.size(); i++)
        {
          copyObjects.at(i) = objects.at(i);
        }
        objects.resize(objects.size() + 1);
        objects.at(objects.size() - 1).type = notSet;
        for (int i = 0; i < (int)objects.size() - 1; i++)
        {
          objects.at(i) = copyObjects.at(i);
        }
      }
    }
    else
      ImGui::Button("You can't create more objects, Max = 100");

    if (objects.size() > 0)
    {
      if (ImGui::Button("Destroy Object"))
      {
        *objects_mov = (Vec3 *)realloc(*objects_mov, (objects.size() - 1) * sizeof(Vec3));
        *objects_scale = (Vec3 *)realloc(*objects_scale, (objects.size() - 1) * sizeof(Vec3));
        std::vector<Objects> copyObjects(objects.size());
        for (int i = 0; i < (int)objects.size() - 1; i++)
        {
          copyObjects.at(i) = objects.at(i);
        }
        objects.resize(objects.size() - 1);
        for (int i = 0; i < (int)objects.size(); i++)
        {
          objects.at(i) = copyObjects.at(i);
        }
      }
    }
    else
      ImGui::Button("You can't destroy objects");

    ImGui::Text("Total objects: %d", (int)objects.size());

    static int nObject = 0;
    ImGui::DragInt("Select object", &nObject, 0.25f, 0, objects.size() - 1);
    if (nObject >= (int)objects.size())
      nObject = 0;
    ImGui::Separator();
    ImGui::Text("Object: %d", nObject);

    if (objects.size() > 0)
    {
      switch (objects.at(nObject).type)
      {
      case notSet:
        Not_Set_Controls(objects.at(nObject));
        break;
      case typeSphere:
        Spheres_Controls(objects.at(nObject).sphere);
        break;
      case typeCube:
        Cubes_Controls(objects.at(nObject).cube);
        break;
      case typeFigure:
        Figures_Controls(objects.at(nObject).figure);
      }
    }
    ImGui::End();
  }
  else
    ImGui::End();
}
