#include "pch.h"

#include "Application.h"
#include "GEWindow.h"
#include "Log.h"

#include <Event/ApplicationEvent.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <gl/gl.h>
#include <memory>
#include <regex>

namespace GE {

Application *Application::s_Instance = nullptr;
Application::Application() {

  GE_CORE_ASSERT(!s_Instance, "Application already exists!");
  s_Instance = this;
  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallback(
      std::bind(&Application::OnEvent, this, std::placeholders::_1));
}
Application::~Application() {}
void Application::Run() {

  while (m_Running) {
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Layer *layer : m_LayerStack)
      layer->OnUpdate();

    m_Window->OnUpdate();
  }
}

void Application::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(
      std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
  GE_CORE_TRACE("Application::OnEvent {0}", e);
  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    (*--it)->OnEvent(e);
    if (e.Handled)
      break;
  }
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}

void Application::PushLayer(Layer *layer) {
  m_LayerStack.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
  m_LayerStack.PushOverlay(layer);
  layer->OnAttach();
}

} // namespace GE
