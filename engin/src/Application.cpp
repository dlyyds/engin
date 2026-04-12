#include "Application.h"
#include "Log.h"
#include "pch.h"
#include <Event/ApplicationEvent.h>

namespace GE {

Application::Application() {}
Application::~Application() {}
void Application::Run() {
  // std::cout << "hello\n";
  Log::Init();
  GE_CORE_INFO("Initialized log");
  GE_INFO("Hello");
  WindowResizeEvent e(1000, 1000);
  GE_TRACE(e);
  while (true) {
  }
}

} // namespace GE
