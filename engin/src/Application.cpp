#include "Application.h"
#include "GEWindow.h"
#include "Log.h"
#include "pch.h"
#include <Event/ApplicationEvent.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <gl/gl.h>
#include <memory>
#include <regex>

namespace GE {

Application::Application() {

  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallback(
      std::bind(&Application::OnEvent, this, std::placeholders::_1));
}
Application::~Application() {}
void Application::Run() {

  while (m_Running) {
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    m_Window->OnUpdate();
  }
}

void Application::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(
      std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
  GE_CORE_INFO(e);
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}

} // namespace GE
