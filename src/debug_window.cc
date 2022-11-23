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
  // Imgui loop initialice
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

void Camera_Control(const char *str, Render &render, My_Window &win, MV::Pnt2 max_win)
{
  if (ImGui::Begin(str))
  {

    ImGui::Checkbox("FPS Control?", &win.fps_control);
    ImGui::Checkbox("Show FPS?", &win.show_fps);

    MV::Vec3 desp = {0, 0, 0};
    ImGui::Text("Desp-> X: %0.0f, Y: %0.0f, Z: %0.0f", render.camara_.x, render.camara_.y, render.camara_.z);
    ImGui::SliderFloat("Add X", &desp.x, -1, 1);
    ImGui::SliderFloat("Add Y", &desp.y, -1, 1);
    ImGui::SliderFloat("Add Z", &desp.z, -1, 1);
    desp.x *= -1;
    desp.z *= -1;
    if (desp.x != 0 || desp.y != 0 || desp.z != 0)
      render.translation(desp);

    MV::Vec3 rot = {0, 0, 0};
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
      render.init(max_win, render.camara_, near, far);

    if (ImGui::Button("Reset camera values"))
    {
      render.reset(max_win);
    }

    ImGui::End();
  }
  else
    ImGui::End();
}

void Planets_Control(const char *str, Entity **planets, MV::Pnt3 **object_desp, int &max_planets, MV::Pnt2 max_win)
{
  Entity *localPlanets = *planets;
  MV::Pnt3 *obj = *object_desp;
  if (ImGui::Begin(str))
  {
    if (max_planets < 100)
    {
      if (ImGui::Button("Add a planet (The last one is going to duplicate)"))
      {
        max_planets++;
        Entity *newPlanets = (Entity *)calloc(max_planets, sizeof(Entity));
        MV::Pnt3 *newObj = (MV::Pnt3 *)calloc(max_planets, sizeof(MV::Pnt3));
        if (max_planets > 1)
        {
          for (int i = 0; i < max_planets - 1; i++)
          {
            newPlanets[i] = localPlanets[i];
          }
          newPlanets[max_planets - 1] = newPlanets[max_planets - 2];
        }
        else
          newPlanets[0].init({255, 255, 255, SDL_ALPHA_OPAQUE}, true, 10, {12, 12, 12}, {max_win.x / 2, max_win.y / 2, 0.0f});
        DESTROY(localPlanets);
        *planets = newPlanets;
        DESTROY(obj);
        *object_desp = newObj;
        ImGui::End();
        return;
      }
    }
    else
      ImGui::Button("You can't create more planets");

    if (max_planets > 0)
    {
      if (ImGui::Button("Destroy the last planet"))
      {
        max_planets--;
        Entity *newPlanets = (Entity *)calloc(max_planets, sizeof(Entity));
        for (int i = 0; i < max_planets; i++)
        {
          newPlanets[i] = localPlanets[i];
        }
        DESTROY(localPlanets);
        *planets = newPlanets;
        ImGui::End();
        return;
      }
    }
    else
      ImGui::Button("You can't destroy planets");

    ImGui::Text("Planets in orbit: %d", max_planets);
    ImGui::Text("Sizeof planet: %d, total planets size: %d", (int)sizeof(localPlanets[0]), (int)(max_planets * sizeof(localPlanets[0])));

    static int nPlanet = 0;
    ImGui::DragInt("Select planet", &nPlanet, 0.25f, 0, max_planets-1);

    ImGui::Separator();
    ImGui::Text("Planet: %d", nPlanet);

    char str[50];
    memset(str, 0, sizeof(str));
    snprintf(str, 50, "Translation %f, %f, %f", localPlanets[nPlanet].desp_.x, localPlanets[nPlanet].desp_.y, localPlanets[nPlanet].desp_.z);
    ImGui::Text("%s",str);

    // Dots draw change
    memset(str, 0, sizeof(str));
    snprintf(str, 50, "Fill %d?", nPlanet);
    ImGui::Checkbox(str, &localPlanets[nPlanet].fill_);

    // Color change
    memset(str, 0, sizeof(str));
    snprintf(str, 50, "Color %d", nPlanet);
    float newColor[4];
    newColor[0] = (float)localPlanets[nPlanet].color_.r / 255;
    newColor[1] = (float)localPlanets[nPlanet].color_.g / 255;
    newColor[2] = (float)localPlanets[nPlanet].color_.b / 255;
    newColor[3] = (float)localPlanets[nPlanet].color_.a / 255;
    ImGui::ColorEdit4(str, newColor);
    localPlanets[nPlanet].color_.r = (Uint8)(newColor[0] * 255);
    localPlanets[nPlanet].color_.g = (Uint8)(newColor[1] * 255);
    localPlanets[nPlanet].color_.b = (Uint8)(newColor[2] * 255);
    localPlanets[nPlanet].color_.a = (Uint8)(newColor[3] * 255);

    // Orbit center
    memset(str, 0, sizeof(str));
    snprintf(str, 50, "Orbit center %d", nPlanet);
    ImGui::SliderFloat3(str, &localPlanets[nPlanet].centro_orbita_.x, -10000, 10000);

    // Orbit desp
    memset(str, 0, sizeof(str));
    snprintf(str, 50, "Orbit angle %d", nPlanet);
    ImGui::SliderFloat3(str, &localPlanets[nPlanet].orbita_.x, -0.5, 0.5);

    // Orbit vel if have orbit desp
    memset(str, 0, sizeof(str));
    snprintf(str, 50, "Orbit vel %d", nPlanet);
    ImGui::SliderFloat(str, &localPlanets[nPlanet].orbit_vel_, -100, 100);

    memset(str, 0, sizeof(str));
    snprintf(str, 50, "Stop planet (orbit vel %d = 0)", nPlanet);
    if (ImGui::Button(str)){
      localPlanets[nPlanet].orbit_vel_=0.0f;
    }

    // Translate Planets
    MV::Vec3 desp = {0, 0, 0};
    memset(str, 0, sizeof(str));
    snprintf(str, 50, "Translate %d", nPlanet);
    ImGui::SliderFloat3(str, &desp.x, -1, 1);
    desp.x *= -1;
    desp.z *= -1;
    if (desp.x != 0 || desp.y != 0 || desp.z != 0)
      localPlanets[nPlanet].translation(desp);

    // Rotate Planets
    MV::Vec3 rot = {0, 0, 0};
    memset(str, 0, sizeof(str));
    snprintf(str, 50, "Rotate %d", nPlanet);
    ImGui::SliderFloat3(str, &rot.x, -1, 1);
    rot.x *= -1;
    rot.y *= -1;
    if (rot.x != 0 || rot.y != 0 || rot.z != 0)
      localPlanets[nPlanet].rotation(rot);

    // Escale Planets
    MV::Vec3 scale = {1, 1, 1};
    memset(str, 0, sizeof(str));
    snprintf(str, 50, "Scale %d", nPlanet);
    ImGui::SliderFloat3(str, &scale.x, 0, 2);
    if (scale.x != 1 || scale.y != 1 || scale.z != 1)
      localPlanets[nPlanet].scale(scale);

    // Escale Planets in the 3 axis
    float eScale = 1;
    memset(str, 0, sizeof(str));
    snprintf(str, 50, "Equal scale %d", nPlanet);
    ImGui::SliderFloat(str, &eScale, 0, 2);
    if (eScale!=1)
      localPlanets[nPlanet].scale({eScale, eScale, eScale});

    ImGui::End();
  }
  else
    ImGui::End();
}
