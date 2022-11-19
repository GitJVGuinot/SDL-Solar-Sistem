#include <debug_window.h>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

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
