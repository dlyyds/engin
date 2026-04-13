#pragma once

#include "Core.h"
#include "Event/ApplicationEvent.h"
#include "GEWindow.h"
#include "Layer.h"
#include "LayerStack.h"
#include <memory>

namespace GE {

class GE_API Application {
public:
  Application();
  virtual ~Application();
  void Run();
  void OnEvent(Event &e);

  void PushLayer(Layer *layer);
  void PushOverlay(Layer *layer);

private:
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
  bool OnWindowClose(WindowCloseEvent &e);
  LayerStack m_LayerStack;
};

Application *CreateApplication();
} // namespace GE
