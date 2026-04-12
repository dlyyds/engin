
#include "Application.h"
#include "Log.h"
#include "spdlog/spdlog.h"
#include <iostream>
namespace GE {

Application::Application() {}
Application::~Application() {}
void Application::Run() {
  // std::cout << "hello\n";
  Log::Init();
  GE_CORE_INFO("Initialized log");
  GE_INFO("Hello");
  while (true) {
  }
}

} // namespace GE
