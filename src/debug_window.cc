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

void Camera_Control(const char* str, Render &render, MV::Pnt2 max_win){
  ImGui::Begin(str);

  MV::Vec3 desp={0,0,0};
  ImGui::Text("Desp-> X: %0.0f, Y: %0.0f, Z: %0.0f", render.camara_.x, render.camara_.y, render.camara_.z);
  ImGui::SliderFloat("Add X",&desp.x, -1, 1);
  ImGui::SliderFloat("Add Y",&desp.y, -1, 1);
  ImGui::SliderFloat("Add Z",&desp.z, -1, 1);
  desp.z*=-1;
  if(desp.x!=0 || desp.y!=0 || desp.z!=0) render.translation(desp);

  MV::Vec3 rot={0,0,0};
  ImGui::Text("Up-> X: %f, Y: %f, Z: %f", render.getUp().x, render.getUp().y, render.getUp().z);
  ImGui::SliderFloat("Rot X",&rot.x, -1, 1);
  ImGui::SliderFloat("Rot Y",&rot.y, -1, 1);
  ImGui::SliderFloat("Rot Z",&rot.z, -1, 1);
  rot.z*=-1;
  if(rot.x!=0 || rot.y!=0 || rot.z!=0) render.rotation(rot);

  if(ImGui::Button("Reset camera values")){
    render.reset(max_win);
  }

  ImGui::End();
}
void Planets_Control(const char* str, Esfera **planets){
  Esfera *localPlanets = *planets;
  ImGui::Begin(str);

  ImGui::End();
}
