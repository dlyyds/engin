#include "Application.h"
#include "GEWindow.h"
#include "Log.h"
#include "pch.h"
#include <Event/ApplicationEvent.h>
#include <GLFW/glfw3.h>
#include <gl/gl.h>
#include <memory>
#include <regex>

namespace GE {

Application::Application() {

  m_Window = std::unique_ptr<Window>(Window::Create());
}
Application::~Application() {}
void Application::Run() {

  while (m_Running) {
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    m_Window->OnUpdate();
  }
}

} // namespace GE
