#pragma once

#include "Core.h"
#include "GEWindow.h"

#include <memory>

namespace GE {

class GE_API Application {
public:
  Application();
  virtual ~Application();
  void Run();

private:
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
};

Application *CreateApplication();
} // namespace GE
