#pragma once

#include "Core.h"
#include "Event/ApplicationEvent.h"
#include "GEWindow.h"

#include <memory>

namespace GE {

class GE_API Application {
public:
  Application();
  virtual ~Application();
  void Run();
  void OnEvent(Event &e);

private:
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
  bool OnWindowClose(WindowCloseEvent &e);
};

Application *CreateApplication();
} // namespace GE
