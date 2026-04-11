
#include "Application.h"
#include "spdlog/spdlog.h"
namespace GE {

Application::Application() {}
Application::~Application() {}
void Application::Run() {
  spdlog::info("Welcome to spdlog!");
  while (true) {
  }
}

} // namespace GE
